#include "reader.hh"

Reader::Reader(VideoCapture* inputv)
	: tbb::filter(tbb::filter::serial_in_order)
{
	input = inputv;
}

Reader::~Reader()
{
}

void*
Reader::operator()(void* data)
{
	Mat* src = new Mat();
	*input >> *src;

	if (src->empty())
	{
		std::cout << "FINISHED" << std::endl;
		_exit(0);
	}

	return src;
}
