#ifndef ECHO_HPP
#define ECHO_HPP

#include "effect.hpp"

class Echo : public Effect
{
public:
    Echo();
    Echo(double delayTimeSeconds, double feedbackGain);
    ~Echo();
    void setFeedbackGain(double _feedbackGain);
    void setDelayTime(double _delayTimeSeconds);
    void setStatus(int _status);
    double process(double in);
private:
    long delayTime; // in samples
    double feedbackGain;
    long ptr;
    int status;
};

#endif // ECHO_HPP
