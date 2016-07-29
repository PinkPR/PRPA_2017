#include "light.hh"

Light::Light(VideoCapture* inputv)
	: tbb::filter(tbb::filter::serial_in_order)
{
	input = inputv;
}

Light::~Light()
{
}

	void*
Light::operator()(void* data)
{
	struct kernel_info *infos = (struct kernel_info*)data;
	Mat* src = infos->src;

	Mat res = Mat::zeros(src->size(), src->type());
	for( int y = 0; y < src->rows; y++ )
	{
		for( int x = 0; x < src->cols; x++ )
		{
			for( int c = 0; c < 3; c++ )
			{
				res.at<Vec3b>(y,x)[c] =
					saturate_cast<uchar>( (2.0f * 0.2f * infos->rms )*( src->at<Vec3b>(y,x)[c] ));
			}
		}
	}

	delete infos->src;
	infos->src = new Mat(res);

	return infos;
}
