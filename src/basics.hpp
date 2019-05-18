
/* ########################

Name: Marin Pavlinov Marinov
file: basics.hpp
purpose: all the functions that perform basic functions such as mean,median,mode, standard deviation
         and has methods that display them to the user

######################## */

#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

struct DataType {
	double population;
	double sample;

	DataType() : population(0.0), sample(0.0) {}
};

struct Percentile {
	double q1;
	double q2;
	double q3;

	Percentile() : q1(0.0), q2(0.0), q3(0.0) {}
};

// sorting and printing functions
void sortDataset(std::vector<double>& dataSet);
void displayDataset(const std::vector<double>& dataSet);
void displayStandardDeviation(const std::vector<double>& dataSet, int terms);
void displayMinMax(const std::vector<double>& dataSet);
void displayPercentiles(const std::vector<double>& dataSet);
// calculation and functionality functions
double calculateMean(const std::vector<double>& dataSet, int terms);
double calculateRange(const std::vector<double>& dataset);
Percentile calculatePercentiles(const std::vector<double>& dataSet);
void calculateMode(const std::vector<double>& dataSet);
DataType calculateStandardDeviation(const std::vector<double>& dataSet, int terms);
double calculateInterquartileRange(const std::vector<double>& dataSet);
void findOutliers(const std::vector<double>& dataSet);
