#ifndef WRITER_HH
# define WRITER_HH

# include <tbb/pipeline.h>
# include <sndfile.h>
# include <cstdlib>
# include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
# include <opencv2/highgui/highgui.hpp>  // Video write
# include <opencv2/imgproc/imgproc.hpp>

# include <cstdlib>

# include "kernel.hh"

using namespace cv;

class Writer : public tbb::filter
{
	public:
		Writer(VideoWriter *outputv);
		~Writer();

	public:
		void* operator()(void* data) override;

	private:
		VideoWriter* output;
};

#endif /* WRITER_HH */
