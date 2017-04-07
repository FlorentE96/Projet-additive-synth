#include "modmatrix.hpp"

modMatrix::modMatrix()
{
    reset();
}

modMatrix::defineSrc()

void connect(Source _src, Dest _dst) {
    links[_src][_dst].state = true;
}

void disconnect(Source _src, Dest _dst) {
    links[_src][_dst].state = false;
}

template<typename T1>
float modMatrix::process(T1 * _dst);
void modMatrix::reset();
