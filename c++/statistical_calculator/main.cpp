#include "basics.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

void readFormulaSheet(std::string textfile)
{
	std::string s;
	std::ifstream formula(textfile);
	while (getline(formula, s))
	{
		std::cout << s << '\n';
	}
}

int main()
{
	std::string response;

	std::cout << "~~~**Welcome to the statisical calculator MPM(beta stage)!**~~~" << '\n';
	std::cout << "What would you like the calculator to do?" << '\n';
	std::cout << "type 'basics' for {min,max,mean,median,mode,range,standard deviation,percentiles}"
	          << '\n';
	std::cout << "type 'formulas' view the formula sheet" << '\n';
	std::cout << "type 'other'for more functions(have not been made yet)" << '\n';
	std::cin >> response;
	if (response == "basics")
	{
		bool repeat = true;
		char answer;
		while (repeat == true)
		{
			std::vector<double> dataset;
			int terms;
			int trials = 0;
			double inputnumber;
			// gets the number of terms in the date set and fills the vector with them
			std::cout << "How many terms are there?" << '\n';
			std::cin >> terms;
			std::cout << "You may now type the numbers in your data set" << '\n';
			while (trials != terms)
			{
				std::cin >> inputnumber;
				dataset.push_back(inputnumber);
				trials++;
			}
			// TODO:NOTE(sirflankalot): don't calculate the percentiles more than once. There should
			// be a method that gives you both the percentiles and the IQR (keep the individual
			// methods though).

			// showcases the dataset's mean, mode, and range
			displayDataset(dataset);
			std::cout << "The MEAN of the dataset is: " << calculateMean(dataset, terms) << '\n';
			std::cout << "The MODE of your dataset is: " << calculateMode(dataset) << '\n';
			std::cout << "The RANGE of the dataset is: " << calculateRange(dataset) << '\n';
			displayMinMax(dataset);
			// prints the 25th,50th, and 75th percentile of the dataset
			if (dataset.size() > 3)
			{
				std::cout << '\n' << "Percentiles: " << '\n';
				std::cout << "The INTERQUARTILE RANGE of the dataset is: "
				          << calculateInterquartileRange(dataset) << '\n';
				displayPercentiles(dataset);
			}
			findOutliers(dataset);

			std::cout << '\n';
			// prints standard deviation and variance
			std::cout << "Standard deviation and Variance: " << '\n';
			displayStandardDeviation(dataset, terms);
			std::cout << '\n';
			// erase terms once finished showing numbers to user
			dataset.clear();
			// reset the trials
			trials = 0;
			std::cout << "Would like to use this function again? Type 'y' or 'n' " << '\n';
			std::cin >> answer;
			// TODO:NOTE(sirflankalot): this should check to see if y or n is the answer at all, it
			// should say invalid answer for the input "Uksajsdjakhoi"

			// TODO:NOTE(sirflankalot): repeat = answer == 'y';
			if (answer == 'y')
			{
				repeat = true;
			}
			else if (answer == 'n')
			{
				repeat = false;
			}
			else
			{
				std::cout << "Invalid input, terminating calulator" << '\n';
				repeat = false;
			}
		}
	}
	else if (response == "formulas")
	{
		readFormulaSheet("formulas.txt");
	}
	else
	{
		std::cout << "Thank you for using this statistical calculator! Come again!" << '\n';
	}
}
