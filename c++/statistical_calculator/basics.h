#pragma once
#include "advanced.h"
#include "correlation.h"
#include <vector>

struct DataType
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

// sorting and printing functions
void sortDataset(std::vector<double>& dataset);
const void displayDataset(const std::vector<double> dataset);
const void displayStandardDeviation(std::vector<double> dataset, int terms);
const void displayMinMax(std::vector<double> dataset);
const void displayPercentiles(std::vector<double> dataset);
// calculation and functionality functions
double calculateMean(std::vector<double> dataset, int terms);
double calculateRange(std::vector<double> dataset);
bool isEvenSize(std::vector<double> dataset);
Percentile calculatePercentiles(std::vector<double> dataset);
double calculateMode(std::vector<double> dataset);
DataType calculateStandardDeviation(std::vector<double> dataset, int terms);
double calculateInterquartileRange(std::vector<double> dataset);
void findOutliers(std::vector<double> dataset);
