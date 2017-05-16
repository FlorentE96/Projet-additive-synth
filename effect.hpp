#ifndef EFFECT_HPP
#define EFFECT_HPP

#define MAX_DELAY (220500) // 5sec
#include <cstdint>

using namespace std;

class Effect {
public:
    Effect();
    Effect(int size);
    ~Effect();
protected:
    float * output;
    float * input;
    int size;
};

#endif
