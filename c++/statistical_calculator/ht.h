#include "confidence.h"
#include <iostream>

double calculateZscore(double point_estimate, double mean, double sd);
double calculateTscore(double sampleMean, double popMean, double sd, const int sample_size);
