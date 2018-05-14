// Confidence intervals
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
	CriticalZ.z99 = 2.576;
	CriticalZ.z95 = 1.960;
	CriticalZ.z90 = 1.645;
	CriticalZ.z85 = 1.440;
	CriticalZ.z80 = 1.282;

	Bound calculateConfidenceInterval_Z(float percent, double point_estimate, double sd);
	double getZcritical(float percent);

  public:
	const void displayZConfidenceInterval(float percent, double point_estimate, double sd);
	double calculateSamplingDistributionSd(double sd, int sample_size);
};
