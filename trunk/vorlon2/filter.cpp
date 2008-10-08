#include "filter.h"

void Filter::process(float *buffer, int length, float f, float q)
{
	//set feedback amount given f and q between 0 and 1
	float fb = q + q/(1.0f - f);

	//for each sample...
	for(int i = 0; i < length; i++)
	{
		buf0 = buf0 + f * (buffer[i] - buf0 + fb * (buf0 - buf1));
		buf1 = buf1 + f * (buf0 - buf1);
		buffer[i] = buf1;
	}
}