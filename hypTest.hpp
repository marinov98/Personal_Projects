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
	double calculate2sampleZstat(double mean1,
	                             double mean2,
	                             double hvalue,
	                             int sample_size1,
	                             int sample_size2,
	                             double sd1,
	                             double sd2);
	double calculate2T_DF(double sd, double sd2, int sample_size, int sample_size2);
	double calculate2sampleTscore(double mean1,
	                              double mean2,
	                              double hvalue,
	                              int sample_size1,
	                              int sample_size2,
	                              double sd1,
	                              double sd2);
	double calculate2PairedsampleTscore(double mean_difference,
	                                    double hvalue,
	                                    double sd_d,
	                                    int sample_size);
	double calculate2zproportion(double p_hat,
	                             double p_hat2,
	                             double hvalue,
	                             int sample_size,
	                             int sample_size2);
	double calculatePhatC(double p_hat,
	                      double p_hat2,
	                      int sample_size,
	                      int sample_size2);
	double performChiSquare(const std::vector<Chi>& chitest);

	double z_score = 0.0;
	double z_stat = 0.0;
	double t_score = 0.0;
	std::vector<Chi> chi_values;

  public:
	// Constructor and destructor
	HypTest() = default;
	~HypTest() = default;

	// CANNOT be copied
	HypTest(const HypTest& other) = delete;
	HypTest& operator=(const HypTest& other) = delete;

	// printing
	void printHypothesisReport_2Z();
	void printHypothesisReport_2T();
	void printHypothesisReport_pairedT();
	void printHypothesisReport_2P();
	void printChiTest();
	// calculations
	double calculateZscore(double point_estimate, double mean, double sd);
	double calculateZstat(double point_estimate, double mean, double sd, int sample_size);
	double calculateTscore(double sampleMean, double popMean, double sd, int sample_size);
	double calculateProportion(double p_hat, double p, int sample_size);
};
