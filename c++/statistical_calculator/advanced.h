// Confidence intervals  and hypothesis testing 
// z-critical and t-critical
#include "basics.h"
#include <vector>
#include <string>
struct Bound
{
	double lower;
	double upper;
};

struct CriticalZ
{
	double z99;
	double z95;
	double z90;
	double z85;
	double z80;
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

  public:
	// display functions
	const void displayCI_Z(std::string percent,
	                       double point_estimate,
	                       double sd,
	                       const int sample_size);
	const void displayCI_T(double point_estimate, double sd, const int sample_size, double tcrit);
	const void displayCI_Proportion(std::string percent, double p_hat, const int sample_size);
	// calculation functions
	double calculateSamplingDistributionSd(double sd, const int sample_size);
};

// functionality for hypothesis testing

class HypTest
{
  private:
	double z_score;
	double z_stat;
	double t_score;

  public:
	// TODO: TWO sample, chi square , degrees of freedom, function to print a hypothesis tesing
	// report
	double calculateZscore(double point_estimate, double mean, double sd);
	double calculateZstat(double point_estimate, double mean, double sd, const int sample_size);
	double calculateTscore(double sampleMean, double popMean, double sd, const int sample_size);
};
