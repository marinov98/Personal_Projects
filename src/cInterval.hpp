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
  private:
	double z99;
	double z95;
	double z90;
	double z85;
	double z80;

  public:
	CriticalZ() : z99(2.576), z95(1.960), z90(1.645), z85(1.440), z80(1.282) {}
};

struct Chi {
	double observed;
	double expected;
};

// functionality for confidence intervals
class Cinterval {
  private:
	double getZcritical(const std::string& percent) const;

	// Confidence interval with Z critical
	Bound calculateCI_Z(const std::string& percent,
	                    double point_estimate,
	                    double sd,
	                    int sample_size);

	// Confidence interval with T critical
	Bound calculateCI_T(double point_estimate, double sd, int sample_size, double tcrit);

	// Confidence interval of single sample size proportion
	Bound calculateCI_Proportion(const std::string& percent, double p_hat, int sample_size);

	// two sample proportion
	Bound calculateCI_2Proportions(const std::string& percent,
	                               double p_hat,
	                               double p_hat2,
	                               int sample_size,
	                               int sample_size2);

	// two sample T confidence interval
	Bound calculateCI2Sample_T(double tcrit,
	                           double mean1,
	                           double mean2,
	                           double sd1,
	                           double sd2,
	                           int sample_size,
	                           int sample_size2);

	// two sample Z confidence interval
	Bound calculateCI2Sample_Z(const std::string& percent,
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
	void displayCI_Z();
	void displayCI_T();
	void displayCI_Proportion();

	// calculation functions
	double calculateSamplingDistributionSd(double sd, int sample_size);
	void displayCI_2Proportions();
	void displayCI_2Z();
	void displayCI_2T();
};
