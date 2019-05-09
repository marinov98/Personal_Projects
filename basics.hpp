
/* ########################

Name: Marin Pavlinov Marinov
file: basics.hpp
purpose: all the functions that perform basic functions such as mean,median,mode, standard deviation
	     and has methods that display them to the user

######################## */

#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

struct DataType {
	double population;
	double sample;
};

struct Percentile {
	double q1;
	double q2;
	double q3;
};

// sorting and printing functions
void sortDataset(std::vector<double>& dataSet);
const void displayDataset(const std::vector<double> dataSet);
const void displayStandardDeviation(std::vector<double> dataSet, int terms);
const void displayMinMax(std::vector<double> dataSet);
const void displayPercentiles(std::vector<double> dataSet);
// calculation and functionality functions
double calculateMean(std::vector<double> dataSet, int terms);
double calculateRange(std::vector<double> dataset);
bool isEvenSize(std::vector<double> dataSet);
Percentile calculatePercentiles(std::vector<double> dataSet);
double calculateMode(std::vector<double> dataSet);
DataType calculateStandardDeviation(std::vector<double> dataSet, int terms);
double calculateInterquartileRange(std::vector<double> dataSet);
void findOutliers(std::vector<double> dataSet);
