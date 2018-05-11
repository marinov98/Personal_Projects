#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using std::cout;
using std::string;
using std::cin;

struct dataType
{
  double population;
  double sample;
};

//sorting printing functions
void sortDataset(std::vector <double> &dataset);
void displayDataset(std::vector<double> dataset);
void sd_printSampleAndPop(dataType func);
//calculation functions
double calculateMean(std::vector <double> dataset,int terms);
double calculateRange(std::vector <double> dataset);
double calculateMedian(std::vector <double> dataset);
double calculateMode(std::vector <double> dataset);
dataType calculateStandardDeviation(std::vector <double> dataset,int terms);
