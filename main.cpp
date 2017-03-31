#include <cmath>
#include <iostream>
#include <fstream>
#include "global.h"
#include "ADSR.h"

int main(void)
{
  float _length = 1.8f; // 1.8s of "sound"
  ADSR env1(0.3f, 0.5f, 0.8f, 0.5f);
  ofstream outputFile;
  outputFile.open("out.txt", std::ofstream::out | std::ofstream::trunc);
  if (outputFile.is_open())
  {
      for(int i=0; i<(int)(_length*SAMPLE_RATE); i++) // main sample calculation loop
      {
        if(i == (int)(0.1*SAMPLE_RATE)) // at 0.1s
          env1.gate(ON); // gate the envelope on
        if(i == (int)(1.0*SAMPLE_RATE)) // at 1.0s
          env1.gate(OFF); // gate the envelope off
        outputFile << env1.process() << endl;
      }
  }
  else
    cout << "Impossible d'ouvrir le fichier " << endl;

}
