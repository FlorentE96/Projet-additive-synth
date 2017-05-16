#ifndef ECHO_HPP
#define ECHO_HPP

#include "effect.hpp"

class Echo : public Effect
{
public:
    Echo();
    Echo(float delayTimeSeconds, float feedbackGain);
    ~Echo();
    void setFeedbackGain(float _feedbackGain);
    void setDelayTime(float _delayTimeSeconds);
    void setStatus(int _status);
    float process(float in);
private:
    int delayTime; // in samples
    float feedbackGain;
    int ptr;
    int status;
};

#endif // ECHO_HPP
