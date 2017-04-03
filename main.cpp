#include "mainwindow.h"
#include <QApplication>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdint>
#include "global.hpp"
#include "oscillators.hpp"
#include "LUTs.hpp"
#include "filter.hpp"
using namespace std;

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    //w.show();
//    float _length = 0.5f; // 1.8s of "sound"
//    Osc sine_osc(wavetable_saw3, DEFAULT_FREQ);
//    ofstream outputFile;
//    outputFile.open("out_wt.csv", std::ofstream::out | std::ofstream::trunc);
//    if (outputFile.is_open())
//    {
//        cout << "Fichier ouvert..." << endl;
//        for(int i=0; i<(int)(_length*SAMPLE_RATE); i++) // main sample calculation loop
//        {
//          outputFile << sine_osc.process() << endl;
//        }
//    }
//    else
//      cout << "Impossible d'ouvrir le fichier " << endl;
//    //return a.exec();
//}



int main(int argc, char* argv[]){
    QApplication a(argc, argv);

  Filter myFilter(LPF, 1764, 1.0f, 2);

  /*for (int i = 0; i < 6; i++) {
    cout << myLPF.getCoeff(i)/myLPF.getCoeff(3) << endl;
  }*/
  int lenArray = getLenArrayFromFile("values");
  int16_t inputArray[lenArray];
  loadArrayFromFile("values", inputArray, lenArray);


  int16_t outputArray[lenArray];
//  myFilter.filterArrayCompute(inputArray, outputArray, lenArray);
  for (int i = 0; i < lenArray; i++) {
      outputArray[i] = myFilter.filterCompute(inputArray[i]);
   }
  saveArrayToFile("values_filtered", outputArray, lenArray);

  return 0;
}
