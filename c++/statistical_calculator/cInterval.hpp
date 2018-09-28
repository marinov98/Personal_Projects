// Confidence intervals  and hypothesis testing
// z-critical and t-critical
#pragma once
#include "basics.hpp"
#include <string>

struct Bound {
	double lower;
	double upper;
};

struct CriticalZ {
	double z99;
	double z95;
	double z90;
	double z85;
	double z80;
};

struct Chi {
	double observed;
	double expected;
};

// functionality for confidence intervals
class Cinterval {
  private:
	const CriticalZ crit = {2.576, 1.960, 1.645, 1.440, 1.282};
	const double getZcritical(std::string percent);
	Bound calculateCI_Z(std::string percent,
	                    double point_estimate,
	                    double sd,
	                    const int sample_size);

	Bound calculateCI_T(double point_estimate, double sd, const int sample_size, double tcrit);
	Bound calculateCI_Proportion(std::string percent, double p_hat, const int sample_size);
	// two sample proportion
	Bound calculateCI_2Proportions(std::string percent,
	                               double p_hat,
	                               double p_hat2,
	                               const int sample_size,
	                               const int sample_size2);
	Bound calculateCI2Sample_T(double tcrit,
	                           double mean1,
	                           double mean2,
	                           double sd1,
	                           double sd2,
	                           const int sample_size,
	                           const int sample_size2);
	Bound calculateCI2Sample_Z(std::string percent,
	                           double mean1,
	                           double mean2,
	                           double sd1,
	                           double sd2,
	                           const int sample_size,
	                           const int sample_size2);

  public:
	// Contructor
	Cinterval() = default;
	// display functions
	const void displayCI_Z();
	const void displayCI_T();
	const void displayCI_Proportion();
	// calculation functions
	double calculateSamplingDistributionSd(double sd, const int sample_size);
	const void displayCI_2Proportions();
	const void displayCI_2Z();
	const void displayCI_2T();
};
