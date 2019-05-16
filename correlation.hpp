/* ########################

Name: Marin Pavlinov Marinov
file: correlation.hpp
purpose: correlation header file. Calculates slope, y-intercept, LSRL line and Correlation Coefficient

######################## */

#include "basics.hpp"
#include <iostream>
#include <vector>

// printing/sorting functions
void sortDatasetXY(std::vector<double>& datasetX, std::vector<double>& datasetY);
const void displayDatasetXY(const std::vector<double>& datasetX, const std::vector<double>& datasetY);
void displayLSRL(const std::vector<double>& datasetX,
			     const std::vector<double>& datasetY,
			     int terms);

// calculation functions
double calculateCorrelationCoefficient(const std::vector<double>& datasetX,
                                       const std::vector<double>& datasetY,
                                       int terms);
double calculateSlope(const std::vector<double>& datasetX,
		              const std::vector<double>& datasetY,
		              int terms);
double calculateYintercept(const std::vector<double>& datasetX,
                           const std::vector<double>& datasetY,
                           int terms);
