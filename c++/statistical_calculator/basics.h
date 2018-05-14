#pragma once
#include <algorithm>
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

class Basics
{
  private:
	double mean;
	double sum;
	double mode;
	double range;
	double iqr;
	Percentile percentile;
	std::vector<double> outliers;

  public:
	// TODO:(sirflankalot): If the constructor is just going to initalize everything to zero, each
	// member in the class should just have = 0 next to it, so:
	// TODO:(sirflankalot): mean = 0 etc.
	Basics();
	// TODO:(sirflankalot): See my write up for conceptual/organizational issues.
	// TODO:(sirflankalot): never pass by value unless you know that you will need a copy anyway.
	// TODO:If you are just viewing the array, pass by const reference, if you're modifying, pass by
	// non-const reference sorting/printing functions
	void sortDataset(std::vector<double>& dataset);
	const void displayDataset(const std::vector<double> dataset);
	void displayStandardDeviation(std::vector<double> dataset, int terms);
	void displayMinMax(std::vector<double> dataset);
	void displayPercentiles(std::vector<double> dataset);
	// calculation and functionality functions
	double calculateMean(std::vector<double> dataset, int terms);
	double calculateRange(std::vector<double> dataset);
	Percentile calculatePercentiles(std::vector<double> dataset);
	double calculateMode(std::vector<double> dataset);
	DataType calculateStandardDeviation(std::vector<double> dataset, int terms);
	double calculateInterquartileRange(std::vector<double> dataset);
	void findOutliers(std::vector<double> dataset);
};
