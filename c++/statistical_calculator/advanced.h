// Confidence intervals  and hypothesis testing
// z-critical and t-critical
#pragma once
#include "basics.h"
#include <string>

struct Bound
{
	double lower;
	double upper;
};

struct CriticalZ
{
	// TODO: add more options in case users need them
	double z99;
	double z95;
	double z90;
	double z85;
	double z80;
};

struct Chi
{
	double observed;
	double expected;
};

// functionality for confidence intervals
class Cinterval
{
  private:
	const CriticalZ crit = {2.576, 1.960, 1.645, 1.440, 1.282};
	const double getZcritical(std::string percent);
	Bound calculateCI_Z(std::string percent,
	                    double point_estimate,
	                    double sd,
	                    const int sample_size);

	Bound calculateCI_T(double point_estimate, double sd, const int sample_size, double tcrit);
	Bound calculateCI_Proportion(std::string percent, double p_hat, const int sample_size);
	// TODO: two sample proportion
	// TODO: IMPLEMENT THESE:
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

// functionality for hypothesis testing

class HypTest
{
  private:
	double z_score;
	double z_stat;
	double t_score;
	std::vector<Chi> chi_values;
	double calculate2sampleZstat(double mean1,
	                             double mean2,
	                             double hvalue,
	                             const int sample_size1,
	                             const int sample_size2,
	                             double sd1,
	                             double sd2);
	double calculate2T_DF(double sd, double sd2, const int sample_size, const int sample_size2);
	double calculate2sampleTscore(double mean1,
	                              double mean2,
	                              double hvalue,
	                              const int sample_size1,
	                              const int sample_size2,
	                              double sd1,
	                              double sd2);
	double calculate2PairedsampleTscore(double mean_difference,
	                                    double hvalue,
	                                    double sd_d,
	                                    const int sample_size);
	double calculate2zproportion(double p_hat,
	                             double p_hat2,
	                             double hvalue,
	                             const int sample_size,
	                             const int sample_size2);
	double calculatePhatC(double p_hat,
	                      double p_hat2,
	                      const int sample_size,
	                      const int sample_size2);
	double performChiSquare(std::vector<Chi> chitest);

  public:
	// TODO: TWO sample, chi square , degrees of freedom, function to print a hypothesis tesing
	// report
	// print hypothesis test report
	// TODO:HAVE THE REPORT SHOW WHAT FORMULAS WERE USED AND HAVE THEM TAKE INPUT
	void printHypothesisReport_2Z();
	void printHypothesisReport_2T();
	void printHypothesisReport_pairedT();
	void printHypothesisReport_2P();
	void printChiTest();
	// calculations
	double calculateZscore(double point_estimate, double mean, double sd);
	double calculateZstat(double point_estimate, double mean, double sd, const int sample_size);
	double calculateTscore(double sampleMean, double popMean, double sd, const int sample_size);
	double calculateProportion(double p_hat, double p, const int sample_size);
};
