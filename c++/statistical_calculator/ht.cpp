// Hypothesis testing
#include <confidence.h>
#include <iostream>

double Interval::calculateZscore(double point_estimate, double mean, double sd)
{
	z_score = (point_estimate - mean) / sd;
	std::cout << "Your z-score is: " << '\n';
	return z_score;
}
// TODO:ADD Z SCORE SAMPLE
double Interval::calculateTscore(double sampleMean,
                                 double popMean,
                                 double sd,
                                 const int sample_size)
{
	double new_sd = calculateSamplingDistributionSd(sd, sample_size);
	t_score = (sampleMean - popMean) / new_sd;
	std::cout << "Your t-score is: " << '\n';
	return t_score;
}
