#include "advanced.h"
#include <cmath>
#include <iostream>
#include <vector>

// Confidence interval section :
// get the z critical score based on the percent inputed by the user
const double Cinterval::getZcritical(std::string percent)
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

// calculates σ/n^1/2
double Cinterval::calculateSamplingDistributionSd(double sd, const int sample_size)
{
	double samplingsd = (sd / std::sqrt(sample_size));
	return samplingsd;
}

// Z one sample confidence interval
Bound Cinterval::calculateCI_Z(std::string percent,
                               double point_estimate,
                               double sd,
                               const int sample_size)
{
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
                               double tcrit)
{
	Bound bound;
	const double new_sd = calculateSamplingDistributionSd(sd, sample_size);
	bound.lower = (point_estimate - tcrit * new_sd);
	bound.upper = (point_estimate + tcrit * new_sd);
	return bound;
}

// Z proportion confidence interval
Bound Cinterval::calculateCI_Proportion(std::string percent, double p_hat, const int sample_size)
{
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
                                          const int sample_size2)
{
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
// TODO:TWO sample Z,T confidence intervals

// void functions that display the intervals to the user
const void Cinterval::displayCI_Z(std::string percent,
                                  double point_estimate,
                                  double sd,
                                  const int sample_size)
{
	const Bound bound = calculateCI_Z(percent, point_estimate, sd, sample_size);
	std::cout << "Your Z Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}

const void Cinterval::displayCI_T(double point_estimate,
                                  double sd,
                                  const int sample_size,
                                  double tcrit)
{
	const Bound bound = calculateCI_T(point_estimate, sd, sample_size, tcrit);

	std::cout << "Your T Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}

const void Cinterval::displayCI_Proportion(std::string percent, double p_hat, const int sample_size)
{
	const Bound bound = calculateCI_Proportion(percent, p_hat, sample_size);
	std::cout << "Your Proportion Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}
const void Cinterval::displayCI_2Proportions(std::string percent,
                                             double p_hat,
                                             double p_hat2,
                                             const int sample_size,
                                             const int sample_size2)
{
	// TODO: CIN STATEMENTS
	const Bound bound = calculateCI_2Proportions(percent, p_hat, p_hat2, sample_size, sample_size2);
	std::cout << "Your 2 Proportion Confidence interval is: "
	          << "(" << bound.lower << ", " << bound.upper << ")" << '\n';
}

// Hypothesis testing section :

// single sample
// calculates regular z score without including sample size
double HypTest::calculateZscore(double point_estimate, double mean, double sd)
{
	z_score = (point_estimate - mean) / sd;
	std::cout << "Your z-score is: " << '\n';
	return z_score;
}

// calculates z score with sample size factored in
double HypTest::calculateZstat(double point_estimate, double mean, double sd, const int sample_size)
{
	Cinterval calc;
	double new_sd = calc.calculateSamplingDistributionSd(sd, sample_size);
	z_stat = (point_estimate - mean) / new_sd;
	std::cout << "Your z test statistic is: " << '\n';
	return z_stat;
}

// calculates the t score
double HypTest::calculateTscore(double sampleMean, double popMean, double sd, const int sample_size)
{
	Cinterval calc;
	double new_sd = calc.calculateSamplingDistributionSd(sd, sample_size);
	t_score = (sampleMean - popMean) / new_sd;
	std::cout << "Your t-score/statistic is: " << '\n';
	return t_score;
}

// two-sample test statistics
double HypTest::calculate2sampleZstat(double mean1,
                                      double mean2,
                                      double hvalue,
                                      const int sample_size1,
                                      const int sample_size2,
                                      double sd1,
                                      double sd2)
{
	z_stat = ((mean1 - mean2) - hvalue)
	         / std::sqrt((sd1 * sd1) / sample_size1 + (sd2 * sd2) / sample_size2);
	return z_stat;
}

double HypTest::calculate2sampleTscore(double mean1,
                                       double mean2,
                                       double hvalue,
                                       const int sample_size1,
                                       const int sample_size2,
                                       double sd1,
                                       double sd2)
{
	t_score = ((mean1 - mean2) - hvalue)
	          / std::sqrt((sd1 * sd1) / sample_size1 + (sd2 * sd2) / sample_size2);
	return t_score;
}

double HypTest::calculate2T_DF(double sd, double sd2, const int sample_size, const int sample_size2)
{
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
                                             const int sample_size)
{
	Cinterval sd;
	const double new_sd = sd.calculateSamplingDistributionSd(sd_d, sample_size);
	t_score = (mean_difference - hvalue) / new_sd;
	return t_score;
}

double HypTest::calculatePhatC(double p_hat,
                               double p_hat2,
                               const int sample_size,
                               const int sample_size2)
{
	double p_c = (sample_size * p_hat + sample_size2 * p_hat2) / (sample_size + sample_size2);
	return p_c;
}
double HypTest::calculateProportion(double p_hat, double p, const int sample_size)
{
	double p_stat = (p_hat - p) / std::sqrt((p * (1 - p)) / sample_size);
	std::cout << "Your test statistics is: " << '\n';
	return p_stat;
}
double HypTest::calculate2zproportion(double p_hat,
                                      double p_hat2,
                                      double hvalue,
                                      const int sample_size,
                                      const int sample_size2)
{
	const double p_c = calculatePhatC(p_hat, p_hat2, sample_size, sample_size2);
	const double bottom =
	    std::sqrt((p_c * (1 - p_c) / sample_size) + (p_c * (1 - p_c) / sample_size2));
	double p_stat = (((p_hat - p_hat2) - hvalue) / bottom);
	return p_stat;
}

double HypTest::performChiSquare(std::vector<Chi> chitest)
{
	double test = 0;
	for (int i = 0; i < chitest.size(); i++)
	{
		double difference = (chitest[i].observed - chitest[i].expected);
		test += (difference * difference) / chitest[i].expected;
	}
	return test;
}

// Printing hypothesis report
void HypTest::printHypothesisReport_2Z()
{
	std::cout << "input your two means (Enter one at a time)" << '\n';
	double mean1;
	double mean2;
	std::cin >> mean1;
	std::cin >> mean2;
	std::cout << "what is the hypothesized value?" << '\n';
	double hvalue;
	std::cin >> hvalue;
	std::cout << " Next, input your two standard deviations(Enter one at a time)" << '\n';
	double sd;
	double sd2;
	std::cin >> sd;
	std::cin >> sd2;
	std::cout << "Now input your two sample sizes (Enter one at a time)" << '\n';
	int sample_size;
	int sample_size2;
	std::cin >> sample_size;
	std::cin >> sample_size2;
	double z_stat = calculate2sampleZstat(mean1, mean2, hvalue, sample_size, sample_size2, sd, sd2);
	std::cout
	    << "μ1 != μ2(nequal), μ1 < μ2 (less), or μ1 > μ2 (greater) type \"less\", \"nequal\", or "
	       "\"greater\""
	    << '\n';
	std::string choice;
	std::cin >> choice;
	std::cout << "Hypothesis Report: 2 Z" << '\n';
	if (choice == "less")
	{
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 < μ2 " << '\n';
	}
	else if (choice == "greater")
	{
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 > μ2 " << '\n';
	}
	else if (choice == "nequal")
	{
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 != μ2 " << '\n';
	}
	else
	{
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
void HypTest::printHypothesisReport_2T()
{
	std::cout << "input your two means (Enter one at a time)" << '\n';
	double mean1;
	double mean2;
	std::cin >> mean1;
	std::cin >> mean2;

	std::cout << "what is the hypothesized value?" << '\n';
	double hvalue;
	std::cin >> hvalue;

	std::cout << " Next, input your two standard deviations(Enter one at a time)" << '\n';
	double sd;
	double sd2;
	std::cin >> sd;
	std::cin >> sd2;

	std::cout << "Now input your two sample sizes (Enter one at a time)" << '\n';
	int sample_size;
	int sample_size2;
	std::cin >> sample_size;
	std::cin >> sample_size2;
	double t_stat =
	    calculate2sampleTscore(mean1, mean2, hvalue, sample_size, sample_size2, sd, sd2);
	std::cout
	    << "μ1 != μ2(nequal), μ1 < μ2 (less), or μ1 > μ2 (greater) type \"less\", \"nequal\", or "
	       "\"greater\""
	    << '\n';
	std::string choice;
	std::cin >> choice;
	std::cout << "Hypothesis Report: 2 T" << '\n';
	if (choice == "less")
	{
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 < μ2 " << '\n';
	}
	else if (choice == "greater")
	{
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 > μ2 " << '\n';
	}
	else if (choice == "nequal")
	{
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 != μ2 " << '\n';
	}
	else
	{
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

void HypTest::printHypothesisReport_pairedT()
{
	std::cout << "input your two means (Enter one at a time)" << '\n';
	double mean1;
	std::cin >> mean1;

	std::cout << "what is the hypothesized value?" << '\n';
	double hvalue;
	std::cin >> hvalue;

	std::cout << " Next, input your two standard deviations(Enter one at a time)" << '\n';
	double sd;
	std::cin >> sd;

	std::cout << "Now input your sample size" << '\n';
	int sample_size;
	std::cin >> sample_size;
	double t_stat = calculate2PairedsampleTscore(mean1, hvalue, sd, sample_size);
	std::cout
	    << "μ1 != μ2(nequal), μ1 < μ2 (less), or μ1 > μ2 (greater) type \"less\", \"nequal\", or "
	       "\"greater\""
	    << '\n';
	std::string choice;
	std::cin >> choice;
	std::cout << "Hypothesis Report: 2 T" << '\n';
	if (choice == "less")
	{
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 < μ2 " << '\n';
	}
	else if (choice == "greater")
	{
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 > μ2 " << '\n';
	}
	else if (choice == "nequal")
	{
		std::cout << "null hypothesis: μ1 - μ2 = 0" << '\n';
		std::cout << "alternative hypotheis: μ1 != μ2 " << '\n';
	}
	else
	{
		std::cout << "Invalid input no null and alternative hypothesis generated.." << '\n';
	}

	std::cout << "mean1: " << mean1 << '\n';
	std::cout << "sd: " << sd << '\n';
	std::cout << "sample size: " << sample_size << '\n';
	std::cout << "Hypothesized value: " << hvalue << '\n';
	std::cout << "degree(s) of freedom : " << (sample_size - 1) << '\n';
	std::cout << "T test statistic : " << t_stat << '\n';
}

void HypTest::printHypothesisReport_2P()
{
	std::cout << "Input the two p-hat values" << '\n';
	double p_hat;
	double p_hat2;
	std::cin >> p_hat;
	std::cin >> p_hat2;
	std::cout << "what is the hypothesized value (p1-p2)?" << '\n';
	double hvalue;
	std::cin >> hvalue;
	std::cout << "Now input your two sample sizes (Enter one at a time)" << '\n';
	int sample_size;
	int sample_size2;
	std::cin >> sample_size;
	std::cin >> sample_size2;
	const double p_stat = calculate2zproportion(p_hat, p_hat2, hvalue, sample_size, sample_size2);
	std::cout
	    << "p1 != p2(nequal), p1 < p2 (less), or p1 > p2 (greater) type \"less\", \"nequal\", or "
	       "\"greater\""
	    << '\n';
	std::string choice;
	std::cin >> choice;
	std::cout << "Hypothesis Report: 2 Proportions" << '\n';
	if (choice == "less")
	{
		std::cout << "null hypothesis: p1 - p2 = 0" << '\n';
		std::cout << "alternative hypotheis: p1 < p2 " << '\n';
	}
	else if (choice == "greater")
	{
		std::cout << "null hypothesis: p1 - p2 = 0" << '\n';
		std::cout << "alternative hypotheis: p1 > p2 " << '\n';
	}
	else if (choice == "nequal")
	{
		std::cout << "null hypothesis: p1 - p2 = 0" << '\n';
		std::cout << "alternative hypotheis: p1 != p2 " << '\n';
	}
	else
	{
		std::cout << "Invalid input no null and alternative hypothesis generated.." << '\n';
	}
	std::cout << "p1: " << p_hat << '\n';
	std::cout << "sample size: " << sample_size << '\n';
	std::cout << "p2: " << p_hat2 << '\n';
	std::cout << "sample size 2: " << sample_size2 << '\n';
	std::cout << "Hypothesized value: " << hvalue << '\n';
	std::cout << "Proportion test statistic : " << p_stat << '\n';
}

void HypTest::printChiTest()
{
	double obs;
	double ex;
	int n;
	int inputs = 0;
	std::cout << "how many terms? " << '\n';
	std::cin >> n;
	std::cout << " type in your observed values" << '\n';
	while (inputs != n)
	{
		std::cin >> obs;
		chi_values[inputs].observed = obs;
		inputs++;
	}
	inputs = 0;
	std::cout << " type in your expected values" << '\n';
	while (inputs != n)
	{
		std::cin >> ex;
		chi_values[inputs].expected = ex;
		inputs++;
	}
	double chi_test = performChiSquare(chi_values);
	std::cout << " Your input observed values are :" << '\n';
	for (int i = 0; i < n; i++)
	{
		std::cout << chi_values[i].observed;
	}
	std::cout << '\n';
	std::cout << " Your input expected values are :" << '\n';
	for (int j = 0; j < n; j++)
	{
		std::cout << chi_values[j].expected;
	}
	std::cout << '\n';
	std::cout << "χ^2 = " << chi_test << '\n';
	chi_values.clear();
}
