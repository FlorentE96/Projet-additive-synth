#include "echo.hpp"
#include "global.hpp"

Echo::Echo() : delayTime((int)(SAMPLE_RATE * 0.5)), feedbackGain(0.7), ptr(0), status(OFF)
{
    Effect();
}

Echo::Echo(float delayTimeSeconds, float feedbackGain) : delayTime((int)(SAMPLE_RATE * delayTimeSeconds)), feedbackGain(feedbackGain), ptr(0), status(OFF)
{
    Effect();
}

Echo::~Echo()
{

}

void Echo::setFeedbackGain(float _feedbackGain)
{
    feedbackGain = _feedbackGain;
}

void Echo::setDelayTime(float _delayTimeSeconds)
{
    delayTime = _delayTimeSeconds * SAMPLE_RATE;
}

void Echo::setStatus(int _status)
{
    status = _status;
}

float Echo::process(float in)
{
    input[ptr] = in;
    if(!status)
        return in;
    if((ptr-delayTime) < 0)
      output[ptr] = input[ptr] + feedbackGain * output[ptr+size-delayTime];
    else
      output[ptr] = input[ptr] + feedbackGain * output[ptr-delayTime];
    if (ptr >= size)
      ptr -= size;
    if(output[ptr] < 0.000001)
      output[ptr] = 0;
    return output[ptr++];
}
