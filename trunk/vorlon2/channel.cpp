#include "channel.h"

#include <math.h>
#include <stdlib.h>

Channel::Channel(int sampleRate) :
	currentNote(0),
	currentPitch(0.0f),
	lastPitchWheelPos(0.0f),
	currentPitchWheelPos(0.0f)
{
	this->sampleRate = sampleRate;

	for (int i = 0; i < MAX_CONTROLLER; i++) {
		controllers[i] = 0.0f;
	}

	controllers[PITCHWHEEL] = 0.0f;
	controllers[MODWHEEL] = 0.0f;	

	controllers[VOLUME] = 0.5f;

	controllers[ATTACK] = 0.1f;
	controllers[DECAY] = 0.3f;
	controllers[SUSTAIN] = 0.7f;
	controllers[RELEASE] = 0.3f;

	controllers[PAN] = 0.5f;
	controllers[WAVEFORM] = 0.0f;
	controllers[CUTOFF] = 0.9f;
	controllers[RESONANCE] = 0.1f;
			
	controllers[DISTORTION] = 0.0f;
	controllers[CHORUS_AMT] = 0.0f;

	controllers[DELAY_TIME] = 0.5f;
	controllers[DELAY_AMT] = 0.0f;

	controllers[MOD_DECAY] = 0.5f;
	controllers[MOD_AMT] = 0.5f;

	controllers[GLIDE] = 0.0f;
}

Channel::~Channel()
{
}

void Channel::noteOn(int note, float velocity)
{
	currentNote = note;
	ampEnvelope.gateOn();
	modValue = 1.0f;

	if (controllers[GLIDE] == 0.0f) {
		currentPitch = (float)currentNote;
	}
}

void Channel::noteOff(int note, float velocity)
{
	if (note == currentNote) {
		ampEnvelope.gateOff();
	}
}

void Channel::controllerChange(int controller, float value)
{
	controllers[controller] = value;
}

void Channel::pitchWheelChange(float value)
{
	controllers[PITCHWHEEL] = value;
}

void Channel::render(float *left, float *right, int length)
{
	float dt = length / (float)sampleRate;

	float lastPitch = currentPitch;
	{
		float notesPerSec = 20.0f / (controllers[GLIDE] + 0.001f);
		if (currentPitch < (float)currentNote)
		{
			currentPitch = __min((float)currentNote, currentPitch + notesPerSec * dt);
		}
		else if (currentPitch > (float)currentNote)
		{
			currentPitch = __max((float)currentNote, currentPitch - notesPerSec * dt);
		}
	}
	

	float startModValue = modValue;
	modValue *= 1.0f - (float)pow(2, -controllers[MOD_DECAY] * dt * 1500.0);
	float modToPitch = 0.0f;
	float modToFilter = 0.0f;
	
	if (controllers[MOD_AMT] < 0.495f)
	{
		modToPitch = (0.5f - controllers[MOD_AMT]) * 2.0f;
		modToPitch = modToPitch * modToPitch * 48.0f;
	} 
	else if (controllers[MOD_AMT] > 0.505f) 
	{
		modToFilter = (controllers[MOD_AMT] - 0.5f) * 2.0f;
	}

	lastPitchWheelPos = currentPitchWheelPos;
	currentPitchWheelPos += (float)((controllers[PITCHWHEEL] - currentPitchWheelPos) * pow(2, -dt * 400.0));
	
	// Oscillator & amp envelope
	float startAmp = ampEnvelope.currentValue;
	float endAmp = ampEnvelope.process(controllers[ATTACK] * controllers[ATTACK], controllers[DECAY], controllers[SUSTAIN], controllers[RELEASE], dt);
	
	if (startAmp > (1.0f / 65536.0f) || endAmp > (1.0f / 65536.0f))
	{
		float lastLFO = lfo.get();
		float currentLFO = lfo.increment(controllers[MODWHEEL] * 7.0f + 4.0f, controllers[MODWHEEL] * 0.5f, dt);

		float startFreq = pitchToFreq(lastPitch + lastPitchWheelPos * 7.0f + modToPitch * startModValue + lastLFO);
		float endFreq = pitchToFreq(currentPitch + currentPitchWheelPos * 7.0f + modToPitch * modValue + currentLFO);
		float startPhasePerSample = startFreq / sampleRate;
		float endPhasePerSample = endFreq / sampleRate;			

		float phaseOffset = controllers[WAVEFORM];
		float pulseFade = __min(controllers[WAVEFORM] * 2.0f, 1.0f);
		
		if (controllers[WAVEFORM] >= 1.0f)
		{
			// Noise
			for (int i = 0; i < length; i++) {
				float amp = (i * endAmp + (length - i) * startAmp) / length;				
				left[i] = ((rand() / (float)RAND_MAX) - 0.5f) * amp * 2.0f;
			}
		}
		else
		{
			// Waveform
			for (int i = 0; i < length; i++) {
				float amp = (i * endAmp + (length - i) * startAmp) / length;
				float pps = (startPhasePerSample * (length - i) + endPhasePerSample * i) / length;
				left[i] = oscillator.get(pps, phaseOffset, pulseFade) * amp;
			}
		}
	}

	// Filter
	filter.process(left, length, pow(16.0f, __min(controllers[CUTOFF] + modToFilter * modValue, 1.2f)) * 2000.0f / sampleRate, (float)sqrt(controllers[RESONANCE]) * 0.98f);

	// Distortion
	if (controllers[DISTORTION] > 0.0f)
	{
		float fade = __min(controllers[DISTORTION] * 2.0f, 1.0f);
		for (int i = 0; i < length; i++) {
			float distorted = tanh(left[i] * 8.0f * controllers[DISTORTION]);
			left[i] = fade * distorted + (1.0f - fade) * left[i];
		}
	}

	float volume = (controllers[VOLUME] * 1.5f) * (controllers[VOLUME] * 1.5f);
	float leftGain = volume * sqrt(1.0f - controllers[PAN]);
	float rightGain = volume * sqrt(controllers[PAN]);
	
	if (controllers[CHORUS_AMT] > 0.0f)
	{
		// Chorus
		float wet = __min(controllers[CHORUS_AMT] * 2.0f, 1.0f);
		float depth = controllers[CHORUS_AMT] * controllers[CHORUS_AMT];
		float rate = (controllers[CHORUS_AMT] * controllers[CHORUS_AMT] + 0.5f) / sampleRate;
		chorus.process(left, right, length, depth, rate, wet, leftGain, rightGain);
	}
	else
	{
		// Volume, pan. Done by chorus effect if enabled.
		for (int i = 0; i < length; i++) {
			float in = left[i];
			left[i] = in * leftGain;
			right[i] = in * rightGain;
		}
	}

	// Delay
	{
		float feedback = controllers[DELAY_AMT] * controllers[DELAY_AMT] * 0.85f;
		float wet = controllers[DELAY_AMT] * 0.75f;
		delay.process(left, right, length, controllers[DELAY_TIME], feedback, wet);
	}
}