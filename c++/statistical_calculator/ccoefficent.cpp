// corelation coeficient
#include "basics.h"
#include <cmath>
#include <iostream>
#include <vector>

double Interval::getZcritical(float percent)
{
	CriticalZ zcrit;
	if (percent == .99)
	{
		return zcrit.z99;
	}
	else if (percent == .95)
	{
		return zcrit.z95;
	}
	else if (percent == .90)
	{
		return zcrit.z90;
	}
	else if (percent == .85)
	{
		return zcrit.z85;
	}
	else if (percent == .80)
	{
		return zcrit.z80;
	}
}

double Interval::calculateSamplingDistributionSd(double sd, int sample_size)
{
	double samplingsd = (sd / std::sqrt(sample_size));
	return samplingsd;
}

Bound Interval::calculateConfidenceInterval_Z(float percent,
                                              double point_estimate,
                                              double sd,
                                              int sample_size)
{
	Bound bound;
	const double zcrit = getZcritical(percent);
	double new_sd = calculateSamplingDistributionSd(sd, sample_size);
	bound.lower = (point_estimate - zcrit * new_sd);
	bound.upper = (point_estimate + zcrit * new_sd);
	return bound;
}

const void Interval::displayZConfidenceInterval(float percent, double point_estimate, double sd)
{
	const Bound bound =
	    calculateConfidenceInterval_Z(float percent, double point_estimate, double sd);
	std::cout << "Your Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}
