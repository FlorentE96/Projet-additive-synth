#include <cstdint>
#include <cmath>
#include <iostream>
#include <fstream>
#include <ctime>
#include "global.hpp"
#define MAX_DELAY (220500) // 5sec

using namespace std;
class Echo{
private:
    uint32_t status;
    float Td; //in s
    uint32_t D;
    float Fb;
    float DryWet;
    int16_t* delayed_sample;
    void shiftSamples ( int16_t input);
    void storeSamples(int16_t input, uint32_t i);

public:
    void setStatus(uint32_t _status); // set status effect ON before using it
    uint32_t getStatus();
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
    int16_t echoCompute (int16_t input); // return echo samples
    int16_t echoComputev2 (int16_t input); // return echo samples -- optimized  (not working properly)
    int16_t echoEffect (int16_t input); // return echo samples + input with DryWet mixing factor


};
