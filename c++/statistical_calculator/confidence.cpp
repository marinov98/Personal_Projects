// corelation coeficient
#include "confidence.h"
#include <cmath>
#include <iostream>
#include <vector>
// get the z critical score based on the percent inputed by the user
double Interval::getZcritical(std::string percent)
{
	if (percent == ".99")
	{
		return crit.z99;
	}
	else if (percent == ".95")
	{
		return crit.z95;
	}
	else if (percent == ".90")
	{
		return crit.z90;
	}
	else if (percent == ".85")
	{
		return crit.z85;
	}
	else if (percent == ".80")
	{
		return crit.z80;
	}
	return 0.0;
}

double Interval::calculateSamplingDistributionSd(double sd, const int sample_size)
{
	double samplingsd = (sd / std::sqrt(sample_size));
	return samplingsd;
}

Bound Interval::calculateCI_Z(std::string percent,
                              double point_estimate,
                              double sd,
                              const int sample_size)
{
	Bound bound;
	const double zcrit = getZcritical(percent);
	double new_sd = calculateSamplingDistributionSd(sd, sample_size);
	bound.lower = (point_estimate - zcrit * new_sd);
	bound.upper = (point_estimate + zcrit * new_sd);
	return bound;
}
Bound Interval::calculateCI_T(double point_estimate, double sd, const int sample_size, double tcrit)
{
	Bound bound;
	double new_sd = calculateSamplingDistributionSd(sd, sample_size);
	bound.lower = (point_estimate - tcrit * new_sd);
	bound.upper = (point_estimate + tcrit * new_sd);
	return bound;
}
Bound Interval::calculateCI_Proportion(std::string percent, double p_hat, const int sample_size)
{
	Bound bound;
	double q = 1 - p_hat;
	const double zcrit = getZcritical(percent);
	bound.lower = (p_hat - zcrit * std::sqrt((p_hat * q) / sample_size));
	bound.upper = (p_hat + zcrit * std::sqrt((p_hat * q) / sample_size));
	return bound;
}

const void Interval::displayCI_Z(std::string percent,
                                 double point_estimate,
                                 double sd,
                                 const int sample_size)
{
	const Bound bound = calculateCI_Z(percent, point_estimate, sd, sample_size);
	std::cout << "Your Z Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}

const void Interval::displayCI_T(double point_estimate,
                                 double sd,
                                 const int sample_size,
                                 double tcrit)
{
	const Bound bound = calculateCI_T(point_estimate, sd, sample_size, tcrit);

	std::cout << "Your T Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}

const void Interval::displayCI_Proportion(std::string percent, double p_hat, const int sample_size)
{
	const Bound bound = calculateCI_Proportion(percent, p_hat, sample_size);
	std::cout << "Your Proportion Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}

// TODO:IMPLEMENT TWO SAMPLE CONFIDENCE INTERVAL!!!
