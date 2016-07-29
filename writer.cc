#include "writer.hh"

Writer::Writer(VideoWriter* outputv)
	: tbb::filter(tbb::filter::serial_in_order)
{
	output = outputv;
}

Writer::~Writer()
{
}

void*
Writer::operator()(void* data)
{
	struct kernel_info *info = (struct kernel_info*)data;
	*output << *(info->src);

	delete info->src;
	free(info);

	return NULL;
}
