/* ########################

Name: Marin Pavlinov Marinov
file: correlation.cpp
purpose: implements the correlation class

######################## */

#include "basics.hpp"
#include <iostream>
#include <vector>

void sortDatasetXY(std::vector<double>& datasetX, std::vector<double>& datasetY) {
	std::sort(datasetX.begin(), datasetX.end());
	std::sort(datasetY.begin(), datasetY.end());
}

const void displayDatasetXY(const std::vector<double>& datasetX,
                            const std::vector<double>& datasetY) {
	std::cout << "The x values of this dataset are: " << '\n';
	for (const auto& numberX : datasetX) {
		std::cout << " " << numberX;
	}
	std::cout << '\n';
	std::cout << "The y values of this dataset are: " << '\n';
	for (const auto& numberY : datasetY) {
		std::cout << " " << numberY;
	}
}

double calculateCorrelationCoefficient(const std::vector<double>& datasetX,
                                       const std::vector<double>& datasetY,
                                       const int terms) {
	double sum = 0.0;
	double x = calculateMean(datasetX, terms);
	double y = calculateMean(datasetY, terms);
	double sdX = calculateStandardDeviation(datasetX, terms).sample;
	double sdY = calculateStandardDeviation(datasetY, terms).sample;

	for (int i = 0; i < terms; i++) {
		sum += (((datasetX[i] - x) / sdX) * ((datasetY[i] - y) / sdY));
	}

	return (sum / (terms - 1));
}

double calculateSlope(const std::vector<double>& datasetX,
		              const std::vector<double>& datasetY,
		              const int terms) {
	double top = 0.0;
	double bottom = 0.0;
	double x = calculateMean(datasetX, terms);
	double y = calculateMean(datasetY, terms);

	for (int i = 0; i < terms; i++) {
		double temp = (datasetX[i] - x);
		bottom += (temp * temp);
		top += ((datasetX[i] - x) * (datasetY[i] - y));
	}

	return (top / bottom);
}

double calculateYintercept(const std::vector<double>& datasetX,
                           const std::vector<double>& datasetY,
                           const int terms) {
	double x = calculateMean(datasetX, terms);
	double y = calculateMean(datasetY, terms);
	double b = calculateSlope(datasetX, datasetY, terms);

	return (y - b * x);
}

void displayLSRL(const std::vector<double>& datasetX,
		         const std::vector<double>& datasetY,
		         const int terms) {
	double x = calculateMean(datasetX, terms);
	double y = calculateMean(datasetY, terms);
	double b = calculateSlope(datasetX, datasetY, terms);
	double a = calculateYintercept(datasetX, datasetY, terms);
	double r = calculateCorrelationCoefficient(datasetX, datasetY, terms);

	std::cout << "Correlation Coefficient report: " << '\n';
	std::cout << "The Mean value of the x values is: " << x << '\n';
	std::cout << "The Mean value of the y values is: " << y << '\n';
	std::cout << "The slop of the LSRL is: " << b << '\n';
	std::cout << "The y intercept is: " << a << '\n';
	std::cout << '\n' << "Your equation is: " << '\n';
	std::cout << "ŷ = " << a << " + " << b << "x" << '\n';
	std::cout << "The Correlation Coefficient is: " << r << '\n';
	if (r >= -0.5 && r <= 0.5) {
		std::cout << "Weak correlation" << '\n';
	}
	else if ((r >= -0.8 && r < -0.5) || (r > 0.5 && r <= 0.8)) {
		std::cout << "Moderate correlation" << '\n';
	}
	else if ((r >= -1 && r < -0.8) || (r > 0.8 && r <= 1)) {
		std::cout << "Strong correlation" << '\n';
	}
	else {
		std::cout << " no correlation" << '\n';
	}
}
