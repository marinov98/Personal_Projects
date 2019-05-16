// Confidence intervals  and hypothesis testing
// z-critical and t-critical

/* ########################

Name: Marin Pavlinov Marinov
file: cInterval.hpp
purpose: Confidence intervals class, calculates z,t,proportion,performs

######################## */

#pragma once
#include "basics.hpp"
#include <string>

struct Bound {
	double lower;
	double upper;

	Bound() : lower(0.0), upper(0.0) {}
};

struct CriticalZ {
	double z99;
	double z95;
	double z90;
	double z85;
	double z80;

	CriticalZ() : z99(2.576), z95(1.960), z90(1.645), z85(1.440), z80(1.282) {}
};

struct Chi {
	double observed;
	double expected;
};

// functionality for confidence intervals
class Cinterval {
  private:
	const double getZcritical(std::string percent);
	Bound calculateCI_Z(std::string percent,
	                    double point_estimate,
	                    double sd,
	                    int sample_size);

	Bound calculateCI_T(double point_estimate, double sd, int sample_size, double tcrit);
	Bound calculateCI_Proportion(std::string percent, double p_hat, int sample_size);
	// two sample proportion
	Bound calculateCI_2Proportions(std::string percent,
	                               double p_hat,
	                               double p_hat2,
	                               int sample_size,
	                               int sample_size2);
	Bound calculateCI2Sample_T(double tcrit,
	                           double mean1,
	                           double mean2,
	                           double sd1,
	                           double sd2,
	                           int sample_size,
	                           int sample_size2);
	Bound calculateCI2Sample_Z(std::string percent,
	                           double mean1,
	                           double mean2,
	                           double sd1,
	                           double sd2,
	                           int sample_size,
	                           int sample_size2);

	const CriticalZ crit;

  public:
	// Constructor and destructor
	Cinterval() = default;
	~Cinterval() = default;

	// CANNOT be copied
	Cinterval(const Cinterval& other) = delete;
	Cinterval& operator=(const Cinterval& other) = delete;

	// display functions
	const void displayCI_Z();
	const void displayCI_T();
	const void displayCI_Proportion();
	// calculation functions
	double calculateSamplingDistributionSd(double sd, int sample_size);
	const void displayCI_2Proportions();
	const void displayCI_2Z();
	const void displayCI_2T();
};
