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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}



//int main(int argc, char* argv[]){
//    QApplication a(argc, argv);

//  Filter myFilter(LPF, 1764, 1.0f, 2);

//  /*for (int i = 0; i < 6; i++) {
//    cout << myLPF.getCoeff(i)/myLPF.getCoeff(3) << endl;
//  }*/
//  int lenArray = getLenArrayFromFile("values");
//  int16_t inputArray[lenArray];
//  loadArrayFromFile("values", inputArray, lenArray);


//  int16_t outputArray[lenArray];
////  myFilter.filterArrayCompute(inputArray, outputArray, lenArray);
//  for (int i = 0; i < lenArray; i++) {
//      outputArray[i] = myFilter.filterCompute(inputArray[i]);
//   }
//  saveArrayToFile("values_filtered", outputArray, lenArray);

//  return 0;
//}
