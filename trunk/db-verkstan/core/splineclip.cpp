#include "core/splineclip.hpp"
#include "core/core.hpp"

SplineClip::SplineClip()
:numberOfControlPoints(0)
{
  
}

float SplineClip::getValue(int tick)
{
    if (numberOfControlPoints == 0)
        return 0.0f;

    if (numberOfControlPoints == 1)
        return controlPoints[0].value;
    
    if (controlPoints[0].tick >= tick)
        return controlPoints[0].value;
    if (controlPoints[numberOfControlPoints - 1].tick <= tick)  
        return controlPoints[numberOfControlPoints - 1].value;
  
    int index = 0;
    for (int i = 0; i < numberOfControlPoints; i++)
    {
        if (controlPoints[i].tick >= tick)
        {
            index = i - 1;
            break;
        }
    }

    ControlPoint p1 = getControlPoint(index - 1);
    ControlPoint p2 = getControlPoint(index);
    ControlPoint p3 = getControlPoint(index + 1);
    ControlPoint p4 = getControlPoint(index + 2);
    float t = (tick - p2.tick) / (float)(p3.tick - p2.tick); 

    // Linear
    {
       // return  (1.0f - t) * p2.value + p3.value * t;
    }
    // Catmull-Rom
    {
        float t2 = 0.5f * (p3.value - p1.value);
        float t3 = 0.5f * (p4.value - p2.value);
            
        float h1 = 2.0f*t*t*t - 3.0f*t*t + 1.0f;
        float h2 = -2.0f*t*t*t + 3.0f*t*t;
        float h3 = t*t*t - 2.0f*t*t + t;
        float h4 = t*t*t - t*t; 

        return h1*p2.value + h2*p3.value + h3*t2 + h4*t3;
    }

}

SplineClip::ControlPoint SplineClip::getControlPoint(int index)
{
    if (index < 0)
    {
        ControlPoint p = controlPoints[0];
        p.tick = - 256*(-1*index);
        return p;
    }

    if (index >= numberOfControlPoints)
    {
        ControlPoint p = controlPoints[numberOfControlPoints - 1];
        p.tick += 256*index;
        return p;
    }

    return controlPoints[index];
}
