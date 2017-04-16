#include <cstdint>
#include <cmath>
#include <iostream>
#include <fstream>
#include "global.hpp"
#define MAX_DELAY (220500) // 5sec

using namespace std;
class Echo{
private:
    float Td; //in s
    uint32_t D;
    float Fb;
    float DryWet;
    int16_t* delayed_sample;
    void shiftSamples ( int16_t input);

public:
    void setTd(float _Td);
    float getTd();
    void setD(uint32_t _D);
    uint32_t getD();
    float getFb();
    void setFb(float _Fb);
    float getDryWet();
    void setDryWet(float _DryWet);

    Echo(float _Td, float _Fb, float _DryWet);
    Echo(uint32_t D, float _Fb, float _DryWet);
    ~Echo();
    int16_t echoCompute (int16_t input);


};
