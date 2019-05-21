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

void displayDatasetXY(const std::vector<double>& datasetX, const std::vector<double>& datasetY) {
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
                                       const std::vector<double>& datasetY) {
	if (datasetX.size() != datasetY.size())
		throw std::runtime_error("dataset sizes do not match!");

	double sum = 0.0;
	double x = calculateMean(datasetX);
	double y = calculateMean(datasetY);
	double sdX = calculateStandardDeviation(datasetX).sample;
	double sdY = calculateStandardDeviation(datasetY).sample;

	if (sdX == 0 || sdY == 0)
		throw std::runtime_error("Attempted to divide by 0\n");

	for (size_t i = 0; i < datasetX.size(); i++) {
		sum += (((datasetX[i] - x) / sdX) * ((datasetY[i] - y) / sdY));
	}

	return (sum / (datasetX.size() - 1));
}

double calculateSlope(const std::vector<double>& datasetX,
                      const std::vector<double>& datasetY) {

	if (datasetX.size() != datasetY.size())
		throw std::runtime_error("dataset sizes do not match!");

	double top = 0.0;
	double bottom = 0.0;
	double x = calculateMean(datasetX);
	double y = calculateMean(datasetY);

	for (size_t i = 0; i < datasetX.size(); i++) {
		double temp = (datasetX[i] - x);
		bottom += (temp * temp);
		top += ((datasetX[i] - x) * (datasetY[i] - y));
	}

	if (bottom == 0)
		throw std::runtime_error("Attempted to divide by 0\n");

	return (top / bottom);
}

double calculateYintercept(const std::vector<double>& datasetX,
                           const std::vector<double>& datasetY) {
	double x = calculateMean(datasetX);
	double y = calculateMean(datasetY);
	double b = calculateSlope(datasetX, datasetY);

	return (y - b * x);
}

void displayLSRL(const std::vector<double>& datasetX,
                 const std::vector<double>& datasetY) {

	double b = calculateSlope(datasetX, datasetY);
	double a = calculateYintercept(datasetX, datasetY);
	double r = calculateCorrelationCoefficient(datasetX, datasetY);

	std::cout << "Correlation Coefficient report: " << '\n';
	std::cout << "MEAN (x values): " << calculateMean(datasetX) << '\n';
	std::cout << "MEAN (y values): " << calculateMean(datasetY) << '\n';
	std::cout << "SLOPE of LSRL: " << b << '\n';
	std::cout << "Y-INTERCEPT: " << a << '\n';
	std::cout << '\n' << "Your equation is: " << '\n';
	std::cout << "ŷ = " << a << " + " << b << "x" << '\n';
	std::cout << "CORRELATION COEFFICIENT: " << r << '\n';
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
