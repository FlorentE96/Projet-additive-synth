#include <cstdint>
#include <cmath>
#include "global.hpp"
#define MAX_DELAY (220500) // 5sec

class Echo{
private:
    uint32_t D;
    float Fb;
    float DryWet;
    void shiftSamples ( int16_t input);
    int16_t* delayed_sample;
public:
    uint32_t getD();
    float getFb();
    void setD(uint32_t _D);
    void setFb(float _Fb);

    Echo(uint32_t _D, float _Fb, float _DryWet);
    ~Echo();
    int16_t echoCompute (int16_t input);


};
