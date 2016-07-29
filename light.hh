#ifndef LIGHT_HH
# define LIGHT_HH

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include <opencv2/imgproc/imgproc.hpp>
# include <tbb/pipeline.h>

#include "kernel.hh"

using namespace cv;

class Light : public tbb::filter
{
	public:
		Light(VideoCapture *inputv);
		~Light();

	public:
		void* operator()(void* data) override;

	private:
		VideoCapture *input;
};

#endif /* LIGHT_HH */
