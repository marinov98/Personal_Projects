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
	std::sort(dataSet.begin(), dataSet.end());
}

// displays all the elements in the vector
const void displayDataset(const std::vector<double>& dataSet) {
	std::cout << "The data set you inputted is: " << '\n';

	for (const auto& number : dataSet) {
		std::cout << " " << number;
	}
	std::cout << '\n';
}

// displays the minimum and maximum value to the user
const void displayMinMax(const std::vector<double>& dataSet) {
	std::cout << "The minimum value of the data set is: " << dataSet.front() << '\n';
	std::cout << "The maximum value of the data set is: " << dataSet.back() << '\n';
}

// displays 25th,50th, and 75th percentile to the user
const void displayPercentiles(const std::vector<double>& dataSet) {
	const Percentile& percentile = calculatePercentiles(dataSet);
	if (dataSet.size() <= 3) {
		std::cout << "The 50th percentile(MEDIAN) of the data set is: " << percentile.q2 << '\n';
	}
	else if (dataSet.size() >= 4) {
		std::cout << "The 25th percentile of the data set is: " << percentile.q1 << '\n';
		std::cout << "The 50th percentile(MEDIAN) of the data set is: " << percentile.q2 << '\n';
		std::cout << "The 75th percentile of the data set is: " << percentile.q3 << '\n';
	}
}

// displays standard deviation to the user
const void displayStandardDeviation(const std::vector<double>& dataSet, const int terms) {
	const DataType& sd = calculateStandardDeviation(dataSet, terms);

	std::cout << "The SAMPLE standard deviation (Sx) is: " << sd.sample << '\n';
	std::cout << "The SAMPLE variance (Sx^2) is: " << (sd.sample * sd.sample) << '\n';
	std::cout << "The POPULATION standard deviation (σ) is: " << sd.population << '\n';
	std::cout << "The POPULATION variance (σ^2) is: " << (sd.population * sd.population) << '\n';
}

// Functions for finding MEAN, MEDIAN, RANGE, and

double calculateMean(const std::vector<double>& dataSet, const int terms) {
	return  (std::accumulate(dataSet.begin(), dataSet.end(), 0.0) / terms);
}

double calculateRange(const std::vector<double>& dataSet) {
	return dataSet.back() - dataSet.front();
}

// calculates 25th,50th, and 75th percentile of the data set
Percentile calculatePercentiles(const std::vector<double>& dataSet) {
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

double calculateMode(const std::vector<double>& dataSet) {
	double mode = dataSet.front();
	int count = 1;
	int maxCount = 0;
	for (int i = 0; i < dataSet.size() - 1; i++) {
		if (dataSet[i] == dataSet[i + 1]) {
			count++;
			if (count > maxCount) {
				maxCount = count;
				mode = dataSet[i];
			}
		}
		else {
			count = 1;
		}
	}
	if (maxCount > 0) {
		return mode;
	}
	else {
		std::cout << "all numbers repeat equally, returning first term: ";
		return mode;
	}
}

// standard deviation and variance
DataType calculateStandardDeviation(const std::vector<double>& dataSet, int terms) {
	double mean = calculateMean(dataSet, terms);
	DataType sd;

	for (const auto& number : dataSet) {
		double temp = number - mean;
		sd.sample += (temp * temp);
		sd.population += (temp * temp);
	}

	sd.sample = std::sqrt(sd.sample / (terms - 1));
	sd.population = std::sqrt(sd.population / (terms));
	return sd;
}

// interquartile range and outliers

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
	if (!(outliers.empty())) {
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
