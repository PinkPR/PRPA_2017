#ifndef KERNEL_HH
# define KERNEL_HH

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include <opencv2/imgproc/imgproc.hpp>
# include <tbb/pipeline.h>

using namespace cv;

struct kernel_info
{
	Mat* src;
	float rms;
};

class Kernel : public tbb::filter
{
	public:
		Kernel(VideoCapture *inputv);
		~Kernel();

	public:
		void* operator()(void* data) override;

	private:
		VideoCapture *input;
};

#endif /* KERNEL_HH */
