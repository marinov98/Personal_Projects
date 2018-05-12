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

struct Percentile
{
  double q1;
  double q2;
  double q3;
};

//sorting printing functions
void sortDataset(std::vector <double> &dataset);
void displayDataset(std::vector<double> dataset);
void displayStandardDeviation(std::vector <double> dataset,int terms);
void displayMinMax(std::vector<double> dataset);
void displayPercentiles(std::vector<double> dataset);
//calculation and functionality functions
double calculateMean(std::vector <double> dataset,int terms);
double calculateRange(std::vector <double> dataset);
Percentile calculatePercentiles(std::vector <double> dataset);
double calculateMode(std::vector <double> dataset);
dataType calculateStandardDeviation(std::vector <double> dataset,int terms);
double calculateInterquartileRange(std::vector<double> dataset);
void findOutliers(std::vector<double> dataset);
