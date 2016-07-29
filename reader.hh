#ifndef READER_HH
# define READER_HH

# include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
# include <opencv2/highgui/highgui.hpp>  // Video write
# include <opencv2/imgproc/imgproc.hpp>
# include <tbb/pipeline.h>

# include <unistd.h>
# include <iostream>

using namespace cv;

class Reader : public tbb::filter
{
	public:
		Reader(VideoCapture *inputv);
		~Reader();

	public:
		void* operator()(void* data) override;

	private:
		VideoCapture *input;
};

#endif /* READER_HH */
