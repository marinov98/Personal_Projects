// First personal project:
// aim: create a statistical calculator that provides basic functions for
// beginner statistics project will become more advanced as I learn new concepts
// in statistics
#include "basics.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

// sorts the vector
void sortDataset(std::vector<double>& dataset) {
	std::sort(dataset.begin(), dataset.end());
}

// displays all the elements in the vector
const void displayDataset(std::vector<double> dataset) {
	sortDataset(dataset);
	std::cout << "The dataset you inputted is: " << '\n';

	for (const auto& number : dataset) {
		std::cout << " " << number;
	}
	std::cout << '\n';
}

// displays the minimum and maximu value to the user
const void displayMinMax(std::vector<double> dataset) {
	sortDataset(dataset);
	std::cout << "The minimum value of the dataset is: " << dataset.front() << '\n';
	std::cout << "The maximum value of the dataset is: " << dataset.back() << '\n';
}

// displays 25th,50th, and 75th percentile to the user
const void displayPercentiles(std::vector<double> dataset) {
	const Percentile percentile = calculatePercentiles(dataset);
	if (dataset.size() <= 3) {
		std::cout << "The 50th percentile(MEDIAN) of the dataset is: " << percentile.q2 << '\n';
	}
	else if (dataset.size() >= 4) {
		std::cout << "The 25th percentile of the dataset is: " << percentile.q1 << '\n';
		std::cout << "The 50th percentile(MEDIAN) of the dataset is: " << percentile.q2 << '\n';
		std::cout << "The 75th percentile of the dataset is: " << percentile.q3 << '\n';
	}
}

// displays standard deviation to the user
const void displayStandardDeviation(std::vector<double> dataset, const int terms) {
	const DataType sd = calculateStandardDeviation(dataset, terms);

	std::cout << "The SAMPLE STANDARD DEVIATION (Sx) is: " << sd.sample << '\n';
	std::cout << "The SAMPLE VARIANCE (Sx^2) is: " << (sd.sample * sd.sample) << '\n';
	std::cout << "The POPULATION STANDARD DEVIATION (σ) is: " << sd.population << '\n';
	std::cout << "The POPULATION VARIANCE (σ^2) is: " << (sd.population * sd.population) << '\n';
}

// Functions for finding MEAN, MEDIAN, RANGE, and

double calculateMean(std::vector<double> dataset, const int terms) {
	double sum = std::accumulate(dataset.begin(), dataset.end(), 0);
	return sum / terms;
}

double calculateRange(std::vector<double> dataset) {
	sortDataset(dataset);
	return dataset.back() - dataset.front();
}

bool isEvenSize(std::vector<double> dataset) {
	return (dataset.size() % 2 == 0);
}
// calculates 25th,50th, and 75th percentile of the data set
Percentile calculatePercentiles(std::vector<double> dataset) {
	Percentile percentile;
	sortDataset(dataset);
	if (!(isEvenSize(dataset))) {
		if ((dataset.size() / 2) % 2 == 1) {
			percentile.q1 = dataset[(dataset.size() - 1) / 4];
			percentile.q2 = dataset[(dataset.size() - 1) / 2];
			percentile.q3 = dataset[dataset.size() * 3 / 4];
		}
		else {
			percentile.q1 = ((dataset[dataset.size() / 4] + dataset[dataset.size() / 4 - 1]) / 2);
			percentile.q2 = dataset[(dataset.size() - 1) / 2];
			percentile.q3 =
			    ((dataset[dataset.size() * 3 / 4] + dataset[dataset.size() * 3 / 4 + 1]) / 2);
		}
		return percentile;
	}
	if ((dataset.size() / 2) % 2 == 1) {
		percentile.q1 = dataset[(dataset.size() - 1) / 4];
		percentile.q2 = ((dataset[dataset.size() / 2] + dataset[dataset.size() / 2 - 1]) / 2);
		percentile.q3 = dataset[dataset.size() * 3 / 4];
	}
	else {
		percentile.q1 = ((dataset[dataset.size() / 4] + dataset[dataset.size() / 4 - 1]) / 2);
		percentile.q2 = ((dataset[dataset.size() / 2] + dataset[dataset.size() / 2 - 1]) / 2);
		percentile.q3 =
		    ((dataset[dataset.size() * 3 / 4] + dataset[dataset.size() * 3 / 4 - 1]) / 2);
	}
	return percentile;
}

double calculateMode(std::vector<double> dataset) {
	sortDataset(dataset);
	double mode = dataset.front();
	int count = 1;
	int maxCount = 0;
	for (int i = 1; i < dataset.size() - 1; i++) {
		if (dataset[i] == dataset[i + 1]) {
			count++;
			if (count > maxCount) {
				maxCount = count;
				mode = dataset[i];
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
DataType calculateStandardDeviation(std::vector<double> dataset, int terms) {
	double mean = calculateMean(dataset, terms);
	DataType sd;
	sd.population = 0;
	sd.sample = 0;

	for (double number : dataset) {
		double temp = number - mean;
		sd.sample += (temp * temp);
		sd.population += (temp * temp);
	}

	sd.sample = std::sqrt(sd.sample / (terms - 1));
	sd.population = std::sqrt(sd.population / (terms));
	return sd;
}

// interquartile range and outliers

double calculateInterquartileRange(std::vector<double> dataset) {
	const Percentile percentile = calculatePercentiles(dataset);
	const double iqr = percentile.q3 - percentile.q1;
	return iqr;
}

void findOutliers(std::vector<double> dataset) {
	const Percentile percentile = calculatePercentiles(dataset);
	const double iqr = calculateInterquartileRange(dataset);
	const double lower = percentile.q1 - (iqr * 1.5);
	const double upper = percentile.q3 + (iqr * 1.5);
	std::vector<double> outliers;

	for (double number : dataset) {
		if ((number > upper && number > lower) || (number < lower && number < upper)) {
			outliers.push_back(number);
		}
	}
	// if outliers found, print them to the user
	if (!(outliers.empty())) {
		std::cout << "The OUTLIER(S) of this dataset is(are): ";
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
