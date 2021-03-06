// First personal project:
// aim: create a statistical calculator that provides basic functions for
// beginner statistics project will become more advanced as I learn new concepts
// in statistics

/* ########################

Name: Marin Pavlinov Marinov
file: basic.cpp
purpose: implements the functions defined in the basics.hpp file

######################## */

#include "basics.hpp"

// sorts the vector
void sortDataset(std::vector<double>& dataSet) {
	if (dataSet.empty())
		throw std::underflow_error("Empty dataset");
	std::sort(dataSet.begin(), dataSet.end());
}

// displays all the elements in the vector
void displayDataset(const std::vector<double>& dataSet) {
	std::cout << "The data set you inputted (in sorted order) is: " << '\n';

	for (const auto& number : dataSet) {
		std::cout << " " << number;
	}
	std::cout << '\n';
}

// displays the minimum and maximum value to the user
void displayMinMax(const std::vector<double>& dataSet) {
	if (dataSet.empty())
		throw std::underflow_error("Empty dataset");

	// Assumes vector is in sorted ascending order
	// sortDataset should be called before using this function
	std::cout << "MIN value: " << dataSet.front() << '\n';
	std::cout << "MAX value: " << dataSet.back() << '\n';
}

// displays 25th,50th, and 75th percentile to the user
void displayPercentiles(const std::vector<double>& dataSet) {
	const Percentile& percentile = calculatePercentiles(dataSet);
	if (dataSet.size() <= 3) {
		std::cout << "MEDIAN: " << percentile.q2 << '\n';
	}
	else if (dataSet.size() >= 4) {
		std::cout << "25th PERCENTILE: " << percentile.q1 << '\n';
		std::cout << "50th PERCENTILE(MEDIAN): " << percentile.q2 << '\n';
		std::cout << "75th PERCENTILE: " << percentile.q3 << '\n';
	}
}

// displays standard deviation to the user
void displayStandardDeviation(const std::vector<double>& dataSet) {
	const DataType& sd = calculateStandardDeviation(dataSet);

	std::cout << "SAMPLE standard deviation (Sx): " << sd.sample << '\n';
	std::cout << "SAMPLE variance (Sx^2): " << (sd.sample * sd.sample) << '\n';
	std::cout << "POPULATION standard deviation (σ): " << sd.population << '\n';
	std::cout << "POPULATION variance (σ^2): " << (sd.population * sd.population) << '\n';
}

// Functions for finding MEAN, MEDIAN, RANGE, and

double calculateMean(const std::vector<double>& dataSet) {
	// Safety
	if (dataSet.empty())
		throw std::runtime_error("Empty Dataset");

	return (std::accumulate(dataSet.begin(), dataSet.end(), 0.0) / dataSet.size());
}

double calculateRange(const std::vector<double>& dataSet) {
	if (dataSet.empty())
		throw std::underflow_error("Empty dataset");

	return dataSet.back() - dataSet.front();
}

// calculates 25th,50th, and 75th percentile of the data set
Percentile calculatePercentiles(const std::vector<double>& dataSet) {
	if (dataSet.empty())
		throw std::underflow_error("Empty dataset");

	Percentile percentile;

	if (dataSet.size() % 2 != 0) {
		if ((dataSet.size() / 2) % 2 == 1) {
			percentile.q1 = dataSet[(dataSet.size() - 1) / 4];
			percentile.q2 = dataSet[(dataSet.size() - 1) / 2];
			percentile.q3 = dataSet[dataSet.size() * 3 / 4];
		}
		else {
			percentile.q1 = ((dataSet[dataSet.size() / 4] + dataSet[dataSet.size() / 4 - 1]) / 2);
			percentile.q2 = dataSet[(dataSet.size() - 1) / 2];
			percentile.q3 =
			    ((dataSet[dataSet.size() * 3 / 4] + dataSet[dataSet.size() * 3 / 4 + 1]) / 2);
		}
		return percentile;
	}
	if ((dataSet.size() / 2) % 2 == 1) {
		percentile.q1 = dataSet[(dataSet.size() - 1) / 4];
		percentile.q2 = ((dataSet[dataSet.size() / 2] + dataSet[dataSet.size() / 2 - 1]) / 2);
		percentile.q3 = dataSet[dataSet.size() * 3 / 4];
	}
	else {
		percentile.q1 = ((dataSet[dataSet.size() / 4] + dataSet[dataSet.size() / 4 - 1]) / 2);
		percentile.q2 = ((dataSet[dataSet.size() / 2] + dataSet[dataSet.size() / 2 - 1]) / 2);
		percentile.q3 =
		    ((dataSet[dataSet.size() * 3 / 4] + dataSet[dataSet.size() * 3 / 4 - 1]) / 2);
	}
	return percentile;
}

void calculateMode(const std::vector<double>& dataSet) {
	if (dataSet.empty())
		throw std::underflow_error("Empty dataset");

	// will keep track of each number and how many times it is repeated
	std::unordered_map<double, int> tracker;

	tracker.reserve(dataSet.size());

	int maxCount = 1;

	for (const auto& num : dataSet) {
		if (tracker.find(num) == tracker.end()) {
			tracker.emplace(num, 1);
		}
		else {
			tracker.find(num)->second++;
			if (tracker.find(num)->second > maxCount) {
				maxCount = tracker.find(num)->second;
			}
		}
	}

	if (maxCount == 1)
		std::cout << "all numbers repeat once" << '\n';
	else {
		for (const auto& item : tracker) {
			if (item.second == maxCount)
				std::cout << item.first << " ";
		}
		std::cout << "repeat(s) " << maxCount << " times";
		std::cout << '\n';
	}
}

// standard deviation and variance
DataType calculateStandardDeviation(const std::vector<double>& dataSet) {
	// Safety
	if (dataSet.empty())
		throw std::runtime_error("Invalid number of terms or vector size");

	double mean = calculateMean(dataSet);
	DataType sd;

	for (const auto& number : dataSet) {
		double temp = number - mean;
		sd.sample += (temp * temp);
		sd.population += (temp * temp);
	}

	sd.sample = std::sqrt(sd.sample / (dataSet.size() - 1));
	sd.population = std::sqrt(sd.population / (dataSet.size()));
	return sd;
}

// Interquartile range and outliers

double calculateInterquartileRange(const std::vector<double>& dataSet) {
	const Percentile& percentile = calculatePercentiles(dataSet);
	const double iqr = percentile.q3 - percentile.q1;
	return iqr;
}

void findOutliers(const std::vector<double>& dataSet) {
	const Percentile percentile = calculatePercentiles(dataSet);
	const double iqr = calculateInterquartileRange(dataSet);
	const double lower = percentile.q1 - (iqr * 1.5);
	const double upper = percentile.q3 + (iqr * 1.5);
	std::vector<double> outliers;

	for (const auto& number : dataSet) {
		if ((number > upper && number > lower) || (number < lower && number < upper)) {
			outliers.emplace_back(number);
		}
	}
	// if outliers found, print them to the user
	if (!outliers.empty()) {
		std::cout << "The OUTLIER(S) of this dataSet is(are): ";
		for (const auto& outlier : outliers) {
			std::cout << outlier << " ";
		}
	}
	// if no outliers are found, notify the user
	else {
		std::cout << "No outliers found in the data set";
	}

	std::cout << '\n';
}
