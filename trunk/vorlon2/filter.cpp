#include "filter.h"

#include <math.h>

void Filter::process(float *buffer, int length, float f, float q, bool highpass)
{
	//set feedback amount given f and q between 0 and 1
	float fb = q + q/(1.0f - f);

	//for each sample...
	for(int i = 0; i < length; i++)
	{
		buf0 = buf0 + f * (buffer[i] - buf0 + fb * (buf0 - buf1));
		buf1 = buf1 + f * (buf0 - buf1);

		if (highpass)
		{
			buffer[i] = buffer[i] - buf1;
		}
		else
		{
			buffer[i] = buf1;
		}
	}
}

bool Filter::isActive()
{
	float ep = (1.0f / 65536.0f);
	return abs(buf0) > ep || abs(buf1) > ep;
}

void Filter::reset()
{
	buf0 = buf1 = 0.0f;
}