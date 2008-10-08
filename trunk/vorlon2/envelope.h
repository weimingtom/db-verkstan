#pragma once

#include <math.h>

class Envelope {
public:
	Envelope() :
		currentValue(0),
		state(RELEASE)
	{}
	

	float process(float a, float d, float s, float r, float dt) {
		switch(state) {
		case ATTACK:
			{
				currentValue += dt / (a + 0.00001f);
				if (currentValue >= 1.0f) {
					currentValue = 1.0f;
					state = DECAY;				
				}
			}
			break;

		case DECAY:
			{
				float toSustain = currentValue - s;
				currentValue -= (float)(toSustain * pow(2, -d * dt * 1000.0));
			}
			break;

		case RELEASE:
			{
				currentValue *= 1.0f - (float)pow(2, -r * dt * 1000.0);
			}
			break;
		}

		return currentValue;
	}

	void gateOn() {
		state = ATTACK;
	}

	void gateOff() {
		state = RELEASE;
	}
	
	float currentValue;	

private:
	enum State {
		ATTACK,
		DECAY,
		RELEASE
	};

	State state;
};