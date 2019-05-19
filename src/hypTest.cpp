/* ########################

Name: Marin Pavlinov Marinov
file: hypTest.cpp
purpose: implements the hypothesis testing class

######################## */

#include "hypTest.hpp"
#include <cmath>
#include <iostream>
#include <vector>

// single sample
// calculates regular z score without including sample size
double HypTest::calculateZscore(double point_estimate, double mean, double sd) {
	this->z_score = (point_estimate - mean) / sd;
	std::cout << "Your z-score is: " << '\n';
	return this->z_score;
}

// calculates z score with sample size factored in
double HypTest::calculateZstat(double point_estimate,
                               double mean,
                               double sd,
                               const int sample_size) {
	double new_sd = calculateSamplingDistributionSd(sd, sample_size);
	this->z_stat = (point_estimate - mean) / new_sd;

	std::cout << "Your z test statistic is: " << '\n';
	return this->z_stat;
}

// calculates the t score
double HypTest::calculateTscore(double sampleMean,
                                double popMean,
                                double sd,
                                const int sample_size) {
	if (sample_size <= 0)
		throw std::runtime_error("Invalid sample size");

	double new_sd = calculateSamplingDistributionSd(sd, sample_size);
	this->t_score = (sampleMean - popMean) / new_sd;

	std::cout << "Your t-score/statistic is: " << '\n';
	return this->t_score;
}

// two-sample test statistics
double HypTest::calculate2sampleZstat(double mean1,
                                      double mean2,
                                      double hvalue,
                                      const int sample_size1,
                                      const int sample_size2,
                                      double sd1,
                                      double sd2) {
	if (sample_size1 <= 0 || sample_size2 <= 0)
		throw std::runtime_error("Invalid sample size");

	this->z_stat = ((mean1 - mean2) - hvalue)
	               / std::sqrt((sd1 * sd1) / sample_size1 + (sd2 * sd2) / sample_size2);
	return this->z_stat;
}

double HypTest::calculate2sampleTscore(double mean1,
                                       double mean2,
                                       double hvalue,
                                       const int sample_size1,
                                       const int sample_size2,
                                       double sd1,
                                       double sd2) {
	if (sample_size1 <= 0 || sample_size2 <= 0)
		throw std::runtime_error("Invalid sample size");

	this->t_score = ((mean1 - mean2) - hvalue)
	                / std::sqrt((sd1 * sd1) / sample_size1 + (sd2 * sd2) / sample_size2);

	return this->t_score;
}

double HypTest::calculate2T_DF(double sd,
                               double sd2,
                               const int sample_size,
                               const int sample_size2) {
	if (sample_size <= 0 || sample_size2 <= 0)
		throw std::runtime_error("Invalid sample size");

	double v1 = (sd * sd) / sample_size;
	double v2 = (sd2 * sd2) / sample_size2;

	double top = (v1 + v2) * (v1 + v2);
	double bottom = (v1 * v1) / (sample_size - 1) + (v2 * v2) / (sample_size2 - 1);
	double df = top / bottom;

	return df;
}

double HypTest::calculate2PairedsampleTscore(double mean_difference,
                                             double hvalue,
                                             double sd_d,
                                             const int sample_size) {
	if (sample_size <= 0)
		throw std::runtime_error("Invalid sample size");

	const double new_sd = calculateSamplingDistributionSd(sd_d, sample_size);
	this->t_score = (mean_difference - hvalue) / new_sd;
	return this->t_score;
}

double HypTest::calculatePhatC(double p_hat,
                               double p_hat2,
                               const int sample_size,
                               const int sample_size2) {
	if (sample_size <= 0 || sample_size2 <= 0)
		throw std::runtime_error("Invalid sample size");

	return ((sample_size * p_hat + sample_size2 * p_hat2) / (sample_size + sample_size2));
}
double HypTest::calculateProportion(double p_hat, double p, const int sample_size) {
	if (sample_size <= 0)
		throw std::runtime_error("Invalid sample size");

	std::cout << "Your test statistics is: " << '\n';
	return ((p_hat - p) / std::sqrt((p * (1 - p)) / sample_size));
}
double HypTest::calculate2zproportion(double p_hat,
                                      double p_hat2,
                                      double hvalue,
                                      const int sample_size,
                                      const int sample_size2) {
	if (sample_size <= 0 || sample_size2 <= 0)
		throw std::runtime_error("Invalid sample size");

	const double p_c = calculatePhatC(p_hat, p_hat2, sample_size, sample_size2);
	const double bottom =
	    std::sqrt((p_c * (1 - p_c) / sample_size) + (p_c * (1 - p_c) / sample_size2));

	if (bottom == 0)
		throw std::runtime_error("Attempt to divide by zero");

	return (((p_hat - p_hat2) - hvalue) / bottom);
}

double HypTest::performChiSquare(const std::vector<Chi>& chitest) {
	double test = 0.0;

	for (const auto& data : chitest) {
		double difference = (data.observed - data.expected);
		test += (difference * difference) / data.expected;
	}

	return test;
}

// Printing hypothesis report
void HypTest::printHypothesisReport_2Z() {
	std::cout << "input your two means (Enter one at a time)" << '\n';
	double mean1;
	double mean2;
	std::cin >> mean1;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> mean1;
	}
	std::cin >> mean2;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> mean2;
	}

	std::cout << "what is the hypothesized value?" << '\n';
	double hvalue;
	std::cin >> hvalue;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> hvalue;
	}

	std::cout << " Next, input your two standard deviations (Enter one at a time)" << '\n';
	double sd;
	double sd2;
	std::cin >> sd;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sd;
	}
	std::cin.ignore(100000, '\n');
	std::cin >> sd2;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sd2;
	}
	std::cin.ignore(100000, '\n');

	std::cout << "Now input your two sample sizes (Enter one at a time)" << '\n';
	int sample_size;
	int sample_size2;
	std::cin >> sample_size;
	while (!std::cin || sample_size <= 0) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sample_size;
	}
	std::cin.ignore(100000, '\n');
	std::cin >> sample_size2;
	while (!std::cin || sample_size2 <= 0) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sample_size2;
	}
	std::cin.ignore(100000, '\n');

	double z_stat = calculate2sampleZstat(mean1, mean2, hvalue, sample_size, sample_size2, sd, sd2);

	std::cout
	    << "μ1 != μ2(nequal), μ1 < μ2 (less), or μ1 > μ2 (greater) type \"less\", \"nequal\", or "
	       "\"greater\""
	    << '\n';
	std::string choice;
	std::cin >> choice;

	std::cout << "Hypothesis Report: 2 Z" << '\n';
	if (choice == "less") {
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypothesis: μ1 < μ2 " << '\n';
	}
	else if (choice == "greater") {
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypothesis: μ1 > μ2 " << '\n';
	}
	else if (choice == "nequal") {
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypothesis: μ1 != μ2 " << '\n';
	}
	else {
		std::cout << "Invalid, input no null and alternative hypothesis generated.." << '\n';
	}

	std::cout << "mean1: " << mean1 << '\n';
	std::cout << "sd: " << sd << '\n';
	std::cout << "sample size: " << sample_size << '\n';
	std::cout << "mean2: " << mean2 << '\n';
	std::cout << "sd2: " << sd2 << '\n';
	std::cout << "sample size 2: " << sample_size2 << '\n';
	std::cout << "Hypothesized value: " << hvalue << '\n';
	std::cout << "Z test statistic : " << z_stat << '\n';
}
void HypTest::printHypothesisReport_2T() {
	std::cout << "input your two means (Enter one at a time)" << '\n';
	double mean1;
	double mean2;
	std::cin >> mean1;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> mean1;
	}
	std::cin.ignore(100000, '\n');
	std::cin >> mean2;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> mean2;
	}
	std::cin.ignore(100000, '\n');

	std::cout << "what is the hypothesized value?" << '\n';
	double hvalue;
	std::cin >> hvalue;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> hvalue;
	}
	std::cin.ignore(100000, '\n');

	std::cout << " Next, input your two standard deviations(Enter one at a time)" << '\n';
	double sd;
	double sd2;
	std::cin >> sd;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sd;
	}
	std::cin.ignore(100000, '\n');
	std::cin >> sd2;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sd2;
	}
	std::cin.ignore(100000, '\n');

	std::cout << "Now input your two sample sizes (Enter one at a time)" << '\n';
	int sample_size;
	int sample_size2;
	std::cin >> sample_size;
	while (!std::cin || sample_size <= 0) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sample_size;
	}
	std::cin.ignore(100000, '\n');

	std::cin >> sample_size2;
	while (!std::cin || sample_size2 <= 0) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sample_size2;
	}
	std::cin.ignore(100000, '\n');

	double t_stat =
	    calculate2sampleTscore(mean1, mean2, hvalue, sample_size, sample_size2, sd, sd2);
	std::cout
	    << "μ1 != μ2(nequal), μ1 < μ2 (less), or μ1 > μ2 (greater) type \"less\", \"nequal\", or "
	       "\"greater\""
	    << '\n';
	std::string choice;
	std::cin >> choice;
	std::cout << "Hypothesis Report: 2 T" << '\n';
	if (choice == "less") {
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 < μ2 " << '\n';
	}
	else if (choice == "greater") {
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 > μ2 " << '\n';
	}
	else if (choice == "nequal") {
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 != μ2 " << '\n';
	}
	else {
		std::cout << "Invalid input no null and alternative hypothesis generated.." << '\n';
	}
	const double df = calculate2T_DF(sd, sd2, sample_size, sample_size2);
	std::cout << "mean1: " << mean1 << '\n';
	std::cout << "sd: " << sd << '\n';
	std::cout << "sample size: " << sample_size << '\n';
	std::cout << "mean2: " << mean2 << '\n';
	std::cout << "sd2: " << sd2 << '\n';
	std::cout << "sample size 2: " << sample_size2 << '\n';
	std::cout << "Hypothesized value: " << hvalue << '\n';
	std::cout << "Degree(s) of freedom " << df << '\n';
	std::cout << "T test statistic : " << t_stat << '\n';
}

void HypTest::printHypothesisReport_pairedT() {
	std::cout << "input your two means (Enter one at a time)" << '\n';
	double mean1;
	std::cin >> mean1;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> mean1;
	}
	std::cin.ignore(100000, '\n');

	std::cout << "what is the hypothesized value?" << '\n';
	double hvalue;
	std::cin >> hvalue;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> hvalue;
	}
	std::cin.ignore(100000, '\n');

	std::cout << " Next, input your two standard deviations(Enter one at a time)" << '\n';
	double sd;
	std::cin >> sd;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sd;
	}
	std::cin.ignore(100000, '\n');

	std::cout << "Now input your sample size" << '\n';
	int sample_size;
	std::cin >> sample_size;
	while (!std::cin || sample_size <= 0) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sample_size;
	}
	std::cin.ignore(100000, '\n');

	double t_stat = calculate2PairedsampleTscore(mean1, hvalue, sd, sample_size);
	std::cout
	    << "μ1 != μ2(nequal), μ1 < μ2 (less), or μ1 > μ2 (greater) type \"less\", \"nequal\", or "
	       "\"greater\""
	    << '\n';
	std::string choice;
	std::cin >> choice;
	std::cout << "Hypothesis Report: 2 T" << '\n';
	if (choice == "less") {
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 < μ2 " << '\n';
	}
	else if (choice == "greater") {
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 > μ2 " << '\n';
	}
	else if (choice == "nequal") {
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 != μ2 " << '\n';
	}
	else {
		std::cout << "Invalid input no null and alternative hypothesis generated.." << '\n';
	}

	std::cout << "mean1: " << mean1 << '\n';
	std::cout << "sd: " << sd << '\n';
	std::cout << "sample size: " << sample_size << '\n';
	std::cout << "Hypothesized value: " << hvalue << '\n';
	std::cout << "degree(s) of freedom : " << (sample_size - 1) << '\n';
	std::cout << "T test statistic : " << t_stat << '\n';
}

void HypTest::printHypothesisReport_2P() {
	std::cout << "Input the two p-hat values" << '\n';
	double p_hat;
	double p_hat2;
	std::cin >> p_hat;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> p_hat;
	}
	std::cin.ignore(100000, '\n');

	std::cin >> p_hat2;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> p_hat2;
	}
	std::cin.ignore(100000, '\n');

	std::cout << "what is the hypothesized value (p1-p2)?" << '\n';
	double hvalue;
	std::cin >> hvalue;
	while (!std::cin) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> hvalue;
	}
	std::cin.ignore(100000, '\n');

	std::cout << "Now input your two sample sizes (Enter one at a time)" << '\n';
	int sample_size;
	int sample_size2;
	std::cin >> sample_size;
	while (!std::cin || sample_size <= 0) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sample_size;
	}
	std::cin.ignore(100000, '\n');

	std::cin >> sample_size2;
	while (!std::cin || sample_size2 <= 0) {
		std::cout << "Invalid input! try again" << '\n';
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sample_size2;
	}
	std::cin.ignore(100000, '\n');

	const double p_stat = calculate2zproportion(p_hat, p_hat2, hvalue, sample_size, sample_size2);
	std::cout
	    << "p1 != p2(nequal), p1 < p2 (less), or p1 > p2 (greater) type \"less\", \"nequal\", or "
	       "\"greater\""
	    << '\n';
	std::string choice;
	std::cin >> choice;
	std::cout << "Hypothesis Report: 2 Proportions" << '\n';
	if (choice == "less") {
		std::cout << "null hypothesis: p1 - p2 = 0" << '\n';
		std::cout << "alternative hypotheis: p1 < p2 " << '\n';
	}
	else if (choice == "greater") {
		std::cout << "null hypothesis: p1 - p2 = 0" << '\n';
		std::cout << "alternative hypotheis: p1 > p2 " << '\n';
	}
	else if (choice == "nequal") {
		std::cout << "null hypothesis: p1 - p2 = 0" << '\n';
		std::cout << "alternative hypotheis: p1 != p2 " << '\n';
	}
	else {
		std::cout << "Invalid input no null and alternative hypothesis generated.." << '\n';
	}
	std::cout << "p1: " << p_hat << '\n';
	std::cout << "sample size: " << sample_size << '\n';
	std::cout << "p2: " << p_hat2 << '\n';
	std::cout << "sample size 2: " << sample_size2 << '\n';
	std::cout << "Hypothesized value: " << hvalue << '\n';
	std::cout << "Proportion test statistic : " << p_stat << '\n';
}

void HypTest::printChiTest() {
	double obs;
	double ex;
	int n;
	int inputs = 0;

	std::cout << "how many terms? " << '\n';
	std::cin >> n;
	// Ensure # of terms is correct
	while (!std::cin || n <= 1) {
		// notify user input is incorrect
		std::cout << "Invalid input! try again" << '\n';
		std::cout << "Expected one input that is greater than 1" << '\n';
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cin >> n;
	}
	std::cin.ignore(100000, '\n');

	this->chi_values.reserve(n);

	std::cout << "Type in your observed values" << '\n';
	while (inputs != n) {
		std::cout << "Type in observed value #" << (inputs + 1) << '\n';
		std::cin >> obs;
		while (!std::cin) {
			std::cout << "Invalid input! try again" << '\n';
			std::cin.clear();
			std::cin.ignore();
			std::cin >> obs;
		}
		std::cin.ignore(100000, '\n');

		std::cout << "Type in expected value #" << (inputs + 1) << '\n';
		std::cin >> ex;
		while (!std::cin || ex == 0) {
			std::cout << "Invalid input! try again" << '\n';
			std::cin.clear();
			std::cin.ignore();
			std::cin >> ex;
		}
		std::cin.ignore(100000, '\n');

		this->chi_values.emplace_back(Chi{obs, ex});
		inputs++;
	}

	double chi_test = performChiSquare(this->chi_values);
	std::cout << "The observed values you inputted are :" << '\n';
	for (const auto& value : this->chi_values) {
		std::cout << " " << value.observed;
	}
	std::cout << '\n';

	std::cout << "The expected values you inputted are :" << '\n';
	for (const auto& value : this->chi_values) {
		std::cout << " " << value.expected;
	}
	std::cout << '\n';

	std::cout << "χ^2 = " << chi_test << '\n';
	chi_values.clear();
}
