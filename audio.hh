#ifndef AUDIO_HH
# define AUDIO_HH

# include <tbb/pipeline.h>
# include <sndfile.h>
# include <cstdlib>

# include "kernel.hh"

using namespace cv;

class Audio : public tbb::filter
{
	public:
		Audio(VideoCapture *inputv, char* filename);
		~Audio();

	public:
		void* operator()(void* data) override;

	private:
		VideoCapture* input;
		SF_INFO infos;
		SNDFILE* f;
};

#endif /* AUDIO_HH */
