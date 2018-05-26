#include "basics.h"
#include <iostream>
#include <vector>

// printing/sorting functions
void sortDatasetXY(std::vector<double>& datasetX, std::vector<double>& datasetY);
const void displayDatasetXY(const std::vector<double> datasetX, const std::vector<double> datasetY);
void displayLSRL(std::vector<double> datasetX, std::vector<double> datasetY, const int terms);

// calculationfunctions
double calculateCorrelationCoefficient(std::vector<double> datasetX,
                                       std::vector<double> datasetY,
                                       const int terms);
double calculateSlope(std::vector<double> datasetX, std::vector<double> datasetY, const int terms);
double calculateYintercept(std::vector<double> datasetX,
                           std::vector<double> datasetY,
                           const int terms);
