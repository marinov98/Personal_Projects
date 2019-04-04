/* ########################

Name: Marin Pavlinov Marinov
file: cInterval.cpp
purpose: implements the confidence interval class

######################## */

#include "cInterval.hpp"
#include <cmath>
#include <iostream>
#include <vector>

// Confidence interval section :
// get the z critical score based on the percent inputed by the user
const double Cinterval::getZcritical(std::string percent) {
	if (percent == ".99") {
		return crit.z99;
	}
	else if (percent == ".95") {
		return crit.z95;
	}
	else if (percent == ".90") {
		return crit.z90;
	}
	else if (percent == ".85") {
		return crit.z85;
	}
	else if (percent == ".80") {
		return crit.z80;
	}
	return 0.0;
}

// calculates σ/n^1/2
double Cinterval::calculateSamplingDistributionSd(double sd, const int sample_size) {
	double samplingsd = (sd / std::sqrt(sample_size));
	return samplingsd;
}

// Z one sample confidence interval
Bound Cinterval::calculateCI_Z(std::string percent,
                               double point_estimate,
                               double sd,
                               const int sample_size) {
	Bound bound;
	const double zcrit = getZcritical(percent);
	const double new_sd = calculateSamplingDistributionSd(sd, sample_size);
	bound.lower = (point_estimate - zcrit * new_sd);
	bound.upper = (point_estimate + zcrit * new_sd);
	return bound;
}

// T one sample confidence interval
Bound Cinterval::calculateCI_T(double point_estimate,
                               double sd,
                               const int sample_size,
                               double tcrit) {
	Bound bound;
	const double new_sd = calculateSamplingDistributionSd(sd, sample_size);
	bound.lower = (point_estimate - tcrit * new_sd);
	bound.upper = (point_estimate + tcrit * new_sd);
	return bound;
}

// Z proportion confidence interval
Bound Cinterval::calculateCI_Proportion(std::string percent, double p_hat, const int sample_size) {
	Bound bound;
	double q = 1 - p_hat;
	const double zcrit = getZcritical(percent);
	bound.lower = (p_hat - zcrit * std::sqrt((p_hat * q) / sample_size));
	bound.upper = (p_hat + zcrit * std::sqrt((p_hat * q) / sample_size));
	return bound;
}

Bound Cinterval::calculateCI_2Proportions(std::string percent,
                                          double p_hat,
                                          double p_hat2,
                                          const int sample_size,
                                          const int sample_size2) {
	Bound bound;
	double q = 1 - p_hat;
	double q2 = 1 - p_hat2;
	const double zcrit = getZcritical(percent);
	bound.lower = ((p_hat - p_hat2)
	               - zcrit * std::sqrt((p_hat * q) / sample_size + ((p_hat2 * q2) / sample_size2)));
	bound.upper = ((p_hat - p_hat2)
	               + zcrit * std::sqrt((p_hat * q) / sample_size + ((p_hat2 * q2) / sample_size2)));
	return bound;
}
// TWO sample Z,T confidence intervals
Bound Cinterval::calculateCI2Sample_Z(std::string percent,
                                      double mean1,
                                      double mean2,
                                      double sd1,
                                      double sd2,
                                      const int sample_size,
                                      const int sample_size2) {
	Bound bound;
	const double zcrit = getZcritical(percent);
	bound.lower =
	    (mean1 - mean2) - zcrit * std::sqrt(sd1 * sd1 / sample_size + sd2 * sd2 / sample_size2);
	bound.upper =
	    (mean1 - mean2) + zcrit * std::sqrt(sd1 * sd1 / sample_size + sd2 * sd2 / sample_size2);
	return bound;
}

Bound Cinterval::calculateCI2Sample_T(double tcrit,
                                      double mean1,
                                      double mean2,
                                      double sd1,
                                      double sd2,
                                      const int sample_size,
                                      const int sample_size2) {
	Bound bound;
	bound.lower =
	    (mean1 - mean2) - tcrit * std::sqrt(sd1 * sd1 / sample_size + sd2 * sd2 / sample_size2);
	bound.upper =
	    (mean1 - mean2) + tcrit * std::sqrt(sd1 * sd1 / sample_size + sd2 * sd2 / sample_size2);
	return bound;
}
// void functions that display the intervals to the user
const void Cinterval::displayCI_Z() {
	std::string percent;
	double point_estimate;
	double sd;
	int sample_size;

	std::cout << "What is the percentage (type in decimal form!)" << '\n';
	std::cout << "Your options are : .99, .95, .90, .85, .80" << '\n';
	std::cin >> percent;
	std::cout << "What is x̄?" << '\n';
	std::cin >> point_estimate;
	std::cout << "What is the standard deviation?" << '\n';
	std::cin >> sd;
	std::cout << "Finally, what is the sample size" << '\n';
	std::cin >> sample_size;
	const Bound bound = calculateCI_Z(percent, point_estimate, sd, sample_size);
	std::cout << "Your Z Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}

const void Cinterval::displayCI_T() {
	double tcrit;
	double point_estimate;
	double sd;
	int sample_size;

	std::cout << "What is the t-critical? " << '\n';
	std::cin >> tcrit;
	std::cout << "What is x̄?" << '\n';
	std::cin >> point_estimate;
	std::cout << "What is the standard deviation?" << '\n';
	std::cin >> sd;
	std::cout << "Finally, what is the sample size" << '\n';
	std::cin >> sample_size;
	const Bound bound = calculateCI_T(point_estimate, sd, sample_size, tcrit);

	std::cout << "Your T Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}

const void Cinterval::displayCI_Proportion() {
	std::string percent;
	double p_hat;
	int sample_size;

	std::cout << "What is the percentage (type in decimal form!)" << '\n';
	std::cout << "Your options are : .99, .95, .90, .85, .80" << '\n';
	std::cin >> percent;
	std::cout << "What is p̂?" << '\n';
	std::cin >> p_hat;
	std::cout << "Finally, what is the sample size?" << '\n';
	std::cin >> sample_size;
	const Bound bound = calculateCI_Proportion(percent, p_hat, sample_size);
	std::cout << "Your Proportion Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}
const void Cinterval::displayCI_2Proportions() {
	std::string percent;
	double p_hat;
	double p_hat2;
	int sample_size;
	int sample_size2;

	std::cout << "What is the percentage (type in decimal form!)" << '\n';
	std::cout << "Your options are : .99, .95, .90, .85, .80" << '\n';
	std::cin >> percent;
	std::cout << "What is p̂?" << '\n';
	std::cin >> p_hat;
	std::cout << "What is p̂2?" << '\n';
	std::cin >> p_hat2;
	std::cout << "What is the  first sample size?" << '\n';
	std::cin >> sample_size;
	std::cout << "Finally, what is the  second sample size?" << '\n';
	std::cin >> sample_size2;
	const Bound bound = calculateCI_2Proportions(percent, p_hat, p_hat2, sample_size, sample_size2);
	std::cout << "Your 2 Proportion Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}

const void Cinterval::displayCI_2Z() {
	std::string percent;
	double mean1;
	double mean2;
	double sd1;
	double sd2;
	int sample_size;
	int sample_size2;

	std::cout << "What is the percentage (type in decimal form!)" << '\n';
	std::cout << "Your options are : .99, .95, .90, .85, .80" << '\n';
	std::cin >> percent;
	std::cout << "What is x̄1?" << '\n';
	std::cin >> mean1;
	std::cout << "What is x̄2?" << '\n';
	std::cin >> mean2;
	std::cout << "What is the first standard deviation?" << '\n';
	std::cin >> sd1;
	std::cout << "What is the second standard deviation?" << '\n';
	std::cin >> sd2;
	std::cout << "What is the  first sample size?" << '\n';
	std::cin >> sample_size;
	std::cout << "Finally, what is the  second sample size?" << '\n';
	std::cin >> sample_size2;
	const Bound bound =
	    calculateCI2Sample_Z(percent, mean1, mean2, sd1, sd2, sample_size, sample_size2);
	std::cout << "Your 2 Z Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}

const void Cinterval::displayCI_2T() {
	double tcrit;
	double mean1;
	double mean2;
	double sd1;
	double sd2;
	int sample_size;
	int sample_size2;

	std::cout << "What is the t critical value?" << '\n';
	std::cin >> tcrit;
	std::cout << "What is x̄1?" << '\n';
	std::cin >> mean1;
	std::cout << "What is x̄2?" << '\n';
	std::cin >> mean2;
	std::cout << "What is the first standard deviation?" << '\n';
	std::cin >> sd1;
	std::cout << "What is the second standard deviation?" << '\n';
	std::cin >> sd2;
	std::cout << "What is the  first sample size?" << '\n';
	std::cin >> sample_size;
	std::cout << "Finally, what is the  second sample size?" << '\n';
	std::cin >> sample_size2;
	const Bound bound =
	    calculateCI2Sample_T(tcrit, mean1, mean2, sd1, sd2, sample_size, sample_size2);
	std::cout << "Your 2 T Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}
// Hypothesis testing section :
