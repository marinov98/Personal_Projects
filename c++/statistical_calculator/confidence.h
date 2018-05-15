// Confidence const intervals
// z-critical and t-critical
#include "basics.h"
#include <vector>

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

class Interval
{
  private:
	CriticalZ crit = {2.576, 1.960, 1.645, 1.440, 1.282};
	double z_score;
	double t_score;
	double getZcritical(std::string percent);
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
