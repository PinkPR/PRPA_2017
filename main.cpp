#include <iostream> // for standard I/O
#include <string>   // for strings
#include <cmath>

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include <opencv2/imgproc/imgproc.hpp>

#include <tbb/pipeline.h>

#include <sndfile.h>

#include "reader.hh"
#include "audio.hh"
#include "kernel.hh"
#include "writer.hh"
#include "light.hh"

using namespace std;
using namespace cv;

static void help()
{
    cout
        << "------------------------------------------------------------------------------" << endl
        << "This program apply effect on a video based on an audio file."                   << endl
        << "Usage:"                                                                         << endl
        << "./vefa inputvideoName inputaudioName"                                           << endl
        << "------------------------------------------------------------------------------" << endl
        << endl;
}

static float next_rms(SNDFILE* f, int len)
{
	float buff[len * 2];
	int l = sf_readf_float(f, buff, len);

	float rms1 = 0.0f;
	float rms2 = 0.0f;

	for (int i = 0; i < l; i++)
	{
		if (i % 2)
			rms1 += buff[i] * buff[i];
		else
			rms2 += buff[i] * buff[i];
	}

	rms1 = sqrtf(rms1);
	rms2 = sqrtf(rms2);

	return (rms1 + rms2) / 2.0f;
}

int main(int argc, char *argv[])
{
	tbb::pipeline ppl;

    help();

    if (argc < 3)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    const string source      = argv[1];           // the source file name

    VideoCapture inputVideo(source);              // Open input
    if (!inputVideo.isOpened())
    {
        cout  << "Could not open the input video: " << source << endl;
        return -1;
    }

    string::size_type pAt = source.find_last_of('.');                  // Find extension point
    const string NAME = source.substr(0, pAt) + "_out.avi";   // Form the new name with container
    int ex = static_cast<int>(inputVideo.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form
    std::cout << "Codec : " << ex << std::endl;

    // Transform from int to char via Bitwise operators
    char EXT[] = {(char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0};

    Size S = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));

    VideoWriter outputVideo;                                        // Open the output
    outputVideo.open(NAME, CV_FOURCC('8','B','P','S'),inputVideo.get(CV_CAP_PROP_FPS), S, true);

    if (!outputVideo.isOpened())
    {
        cout  << "Could not open the output video for write: " << source << endl;
        return -1;
    }

    cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
         << " of nr#: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
    cout << "Input codec type: " << EXT << endl;

	Reader reader(&inputVideo);
	Audio audio(&inputVideo, argv[2]);
	Kernel kernel(&inputVideo);
	Light light(&inputVideo);
	Writer writer(&outputVideo);

	ppl.add_filter(reader);
	ppl.add_filter(audio);
	ppl.add_filter(light);
	ppl.add_filter(writer);

	ppl.run(1);

    cout << "Finished writing" << endl;
    return 0;
}
