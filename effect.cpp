#include "effect.hpp"
#include <cstring>

#define DEFAULT_SIZE (128000)

Effect::Effect() : size(DEFAULT_SIZE) {
    output = new float[size];
    input = new float[size];
    memset( output, 0, size * sizeof( float ));
    memset( input, 0, size * sizeof( float ));
}

Effect::Effect(int size) : size(DEFAULT_SIZE) {
    output = new float[size];
    input = new float[size];
    memset( output, 0, size * sizeof( float ));
    memset( input, 0, size * sizeof( float ));
}

Effect::~Effect() {
    delete output;
    delete input;
}
