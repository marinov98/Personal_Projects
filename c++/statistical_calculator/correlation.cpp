#include "basics.h"
#include <iostream>
#include <vector>

void sortDatasetXY(std::vector<double>& datasetX, std::vector<double>& datasetY)
{
	std::sort(datasetX.begin(), datasetX.end());
	std::sort(datasetY.begin(), datasetY.end());
}

const void displayDatasetXY(const std::vector<double> datasetX, const std::vector<double> datasetY)
{
	std::cout << "The x values of this dataset are: " << '\n';
	for (int i = 0; i < datasetX.size(); i++)
	{
		std::cout << datasetX[i];
	}
	std::cout << "The y values of this dataset are: " << '\n';
	for (int j = 0; j < datasetY.size(); j++)
	{
		std::cout << datasetY[j];
	}
}

double calculateCorrelationCoefficient(std::vector<double> datasetX,
                                       std::vector<double> datasetY,
                                       const int terms)
{
	double sum = 0;
	double x = calculateMean(datasetX, terms);
	double y = calculateMean(datasetY, terms);
	double sdX = calculateStandardDeviation(datasetX, terms).sample;
	double sdY = calculateStandardDeviation(datasetY, terms).sample;
	for (int i = 0; i < terms; i++)
	{
		sum += (((datasetX[i] - x) / sdX) * ((datasetY[i] - y) / sdY));
	}
	double r = sum / (terms - 1);
	return r;
}

double calculateSlope(std::vector<double> datasetX, std::vector<double> datasetY, const int terms)
{
	double top = 0;
	double bottom = 0;
	double x = calculateMean(datasetX, terms);
	double y = calculateMean(datasetY, terms);
	for (int i = 0; i < terms; i++)
	{
		double temp = (datasetX[i] - x);
		bottom += (temp * temp);
		top += ((datasetX[i] - x) * (datasetY[i] - y));
	}
	double b = top / bottom;
	return b;
}

double calculateYintercept(std::vector<double> datasetX,
                           std::vector<double> datasetY,
                           const int terms)
{
	double x = calculateMean(datasetX, terms);
	double y = calculateMean(datasetY, terms);
	double b = calculateSlope(datasetX, datasetY, terms);

	double a = y - b * x;

	return a;
}

void displayLSRL(std::vector<double> datasetX, std::vector<double> datasetY, const int terms)
{
	double x = calculateMean(datasetX, terms);
	double y = calculateMean(datasetY, terms);
	double b = calculateSlope(datasetX, datasetY, terms);
	double a = calculateYintercept(datasetX, datasetY, terms);
	double r = calculateCorrelationCoefficient(datasetX, datasetY, terms);

	std::cout << "Correlation Coefficient report: " << '\n';
	std::cout << "The Mean value of the x values is: " << x << '\n';
	std::cout << "The Mean value of the y values is: " << y << '\n';
	std::cout << "The slop of the LSRL is: " << b << '\n';
	std::cout << "The y intercept is: " << a << '\n';
	std::cout << '\n' << "Your equation is: " << '\n';
	std::cout << "ŷ = " << a << " + " << b << "x" << '\n';
	std::cout << "The Correlation Coefficient is: " << r << '\n';
	if (r >= -0.5 && r <= 0.5)
	{
		std::cout << "Weak correlation" << '\n';
	}
	else if ((r >= -0.8 && r < -0.5) || (r > 0.5 && r <= 0.8))
	{
		std::cout << "Moderate correlation" << '\n';
	}
	else if ((r >= -1 && r < -0.8) || (r > 0.8 && r <= 1))
	{
		std::cout << "Strong correlation" << '\n';
	}
	else
	{
		std::cout << " no correlation" << '\n';
	}
}
