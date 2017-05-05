#include "effect.hpp"
#include <cstring>

#define DEFAULT_SIZE (128000)

Effect::Effect() : size(DEFAULT_SIZE) {
    output = new double[size];
    input = new double[size];
    memset( output, 0, size * sizeof( double ));
    memset( input, 0, size * sizeof( double ));
}

Effect::Effect(long size) : size(DEFAULT_SIZE) {
    output = new double[size];
    input = new double[size];
    memset( output, 0, size * sizeof( double ));
    memset( input, 0, size * sizeof( double ));
}

Effect::~Effect() {
    delete output;
    delete input;
}
