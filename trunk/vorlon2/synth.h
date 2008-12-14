#pragma once

#define WIN32_LEAN_AND_MEAN
#define _INC_STDLIB // To get rid of stdlib.h included by windows.h
#define NOMINMAX
#include <windows.h>

class Synth
{
public:
	static const int frameSize = 128;
	static const int sampleRate = 44100;

	Synth(HWND hwnd);

	~Synth();

	int playFrame();

	void midiInput(unsigned int input);

private:
	static const int NUM_CHANNELS = 16;
	class Machine *channels[NUM_CHANNELS];				
	class Compressor *compressor;
	class SoundDevice *device;
	float *channelLeft, *channelRight;
	float *masterLeft, *masterRight;	
	int frameCounter;
};