#include "kernel.hh"

Kernel::Kernel(VideoCapture* inputv)
	: tbb::filter(tbb::filter::serial_in_order)
{
	input = inputv;
}

Kernel::~Kernel()
{
}

void*
Kernel::operator()(void* data)
{
	struct kernel_info *infos = (struct kernel_info*)data;
	Mat* res = new Mat();
	Point anchor = Point( -1, -1 );
	double delta = 0;
	int ddepth = -1;

	int kernel_size = 1 +
		2 * int(2 * infos->rms);

	Mat kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);
	filter2D(*(infos->src), *res, ddepth , kernel, anchor, delta, BORDER_DEFAULT );

	delete infos->src;
	infos->src = res;

	return infos;
}
