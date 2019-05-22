/* ########################

Name: Marin Pavlinov Marinov
file: correlation.hpp
purpose: correlation header file. Calculates slope, y-intercept, LSRL line and Correlation Coefficient

######################## */

#include "basics.hpp"
#include <iostream>
#include <vector>

// printing functions
void displayDatasetXY(const std::vector<double>& datasetX, const std::vector<double>& datasetY);
void displayLSRL(const std::vector<double>& datasetX,
			     const std::vector<double>& datasetY);

// calculation functions

// Correlation Coefficient
double calculateCorrelationCoefficient(const std::vector<double>& datasetX,
                                       const std::vector<double>& datasetY);
// Slope
double calculateSlope(const std::vector<double>& datasetX,
		              const std::vector<double>& datasetY);

// Y-intercept
double calculateYintercept(const std::vector<double>& datasetX,
                           const std::vector<double>& datasetY);
