/* ########################

Name: Marin Pavlinov Marinov
file: hypTest.hpp
purpose: hypothesis testing class performs 1/2 sample Z/T tests as well as Chi square tests

######################## */

#pragma once
#include "basics.hpp"
#include "cInterval.hpp"
#include <string>

// functionality for hypothesis testing
class HypTest : private Cinterval {
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
	// Constructor
	HypTest() = default;
	// printing
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
