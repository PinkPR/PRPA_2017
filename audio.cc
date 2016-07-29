#include "audio.hh"

Audio::Audio(VideoCapture* inputv, char* filename)
	: tbb::filter(tbb::filter::serial_in_order)
{
	input = inputv;
	f = sf_open(filename, SFM_READ, &infos);
}

Audio::~Audio()
{
}

void*
Audio::operator()(void* data)
{
	Mat* src = (Mat*)data;
	struct kernel_info *info = (struct kernel_info*)malloc(sizeof(struct kernel_info));
	info->src = src;

	int len = infos.samplerate / input->get(CV_CAP_PROP_FPS);

	float buff[len * 2];
	int l = sf_readf_float(f, buff, len);

	float rms1 = 0.0f;
	float rms2 = 0.0f;

	for (int i = 0; i < l; i++)
	{
		if (i % 2)
			rms1 += buff[i] * buff[i] + (i > 1 ? buff[i - 1] * buff[i - 1] : 0.0f);
		else
			rms2 += buff[i] * buff[i] + (i > 0 ? buff[i - 1] * buff[i - 1] : 0.0f);
	}

	rms1 = sqrtf(rms1);
	rms2 = sqrtf(rms2);

	info->rms = (rms1 + rms2) / 2.0f;

	return info;
}
