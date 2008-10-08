#include <windows.h>
#include <dsound.h>

#include "synth.h"
#include "sounddevice.h"
#include "channel.h"
#include "drumbox.h"

Synth::Synth(HWND hwnd) :
	frameCounter(0)
{
	device = new SoundDevice(hwnd, 44100, 1024 * 8);

	for (int i = 0; i < NUM_CHANNELS - 1; i++) {
		channels[i] = new Channel(44100);
	}
	channels[NUM_CHANNELS - 1] = new DrumBox();

	channelLeft = new float[frameSize];
	channelRight = new float[frameSize];

	masterLeft = new float[frameSize];
	masterRight = new float[frameSize];
}

Synth::~Synth()
{
	delete[] channelLeft;
	delete[] channelRight;

	delete[] masterLeft;
	delete[] masterRight;

	for (int i = 0; i < NUM_CHANNELS; i++) {
		delete channels[i];
	}

	delete device;
}

int Synth::playFrame()
{
	ZeroMemory(masterLeft, sizeof(float) * frameSize);
	ZeroMemory(masterRight, sizeof(float) * frameSize);

	for (int i = 0; i < NUM_CHANNELS; i++)
	{
		ZeroMemory(channelLeft, sizeof(float) * frameSize);   // TODO: really clear?
		ZeroMemory(channelRight, sizeof(float) * frameSize);
		
		channels[i]->render(channelLeft, channelRight, frameSize);

		for (int p = 0; p < frameSize; p++)
		{
			masterLeft[p] += channelLeft[p];
			masterRight[p] += channelRight[p];
		}
	}
	
	// TODO: compressor.process(masterLeft, masterRight, frameSize);
	// TODO: limiter.process(masterLeft, masterRight, frameSize);

	device->play(masterLeft, masterRight, frameSize);

	return frameCounter++;
}

void Synth::midiInput(unsigned int input)
{
	int channelNumber = input & 0xf;
    int command = (input >> 4) & 0xf;
    int v1 = (input >> 8) & 0xff;
    int v2 = (input >> 16) & 0xff;

	Machine *c = channels[channelNumber];

	switch(command) {
	case 9: // Note on
		c->noteOn(v1, v2 / 127.0f);
		break;
	case 8: // Note off
		c->noteOff(v1, v2 / 127.0f);
		break;
	case 11: // Controller change
		c->controllerChange(v1, v2 / 127.0f);
		break;
	case 14: // Pitch wheel
		c->pitchWheelChange(((v2 << 7 | v1) - 8192) / 8192.0f);
		break;
	}
}