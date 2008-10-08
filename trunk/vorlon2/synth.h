#pragma once

#include <windows.h>

public class Synth
{
public:
	static const int frameSize = 256;
	static const int sampleRate = 44100;

	Synth(HWND hwnd);

	~Synth();

	int playFrame();

	void midiInput(unsigned int input);

private:
	static const int NUM_CHANNELS = 16;
	class Machine *channels[NUM_CHANNELS];				
	class SoundDevice *device;
	float *channelLeft, *channelRight;
	float *masterLeft, *masterRight;	
	int frameCounter;
};