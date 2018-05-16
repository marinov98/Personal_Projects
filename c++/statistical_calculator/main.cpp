#include "advanced.h"
#include "basics.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

// function that displays formula sheet to the user
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
	std::cout << "~~~**Welcome to the statisical calculator MPM(beta stage)!**~~~" << '\n';
	std::cout << "What would you like the calculator to do?" << '\n';
	std::cout
	    << "type \"basics\" for {min,max,mean,median,mode,range,standard deviation,percentiles}"
	    << '\n';
	std::cout << "type \"formulas\" view the formula sheet" << '\n';
	std::cout << "type \"correlation\" for finding correlation coefficients and LSRL(not finished!)"
	          << '\n';
	std::cout << "type \"advanced\" for confidence intervals and hypothesis testings" << '\n';
	std::string response;
	std::cin >> response;
	bool repeat = true;
	// for whether the user wants to repeat using a functions
	char answer;
	if (response == "basics")
	{
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
				std::cout << "Invalid input, terminating calulator..." << '\n';
				repeat = false;
			}
		}
	}
	else if (response == "formulas")
	{
		readFormulaSheet("formulas.txt");
	}
	else if (response == "advanced")
	{
		repeat = true;
		std::string answer_2;
		std::cout << "This function will allow you calculate confidence intervals and t,z and chi "
		             "test statistics!"
		          << '\n';
		while (repeat == true)
		{
			std::cout << "type \"ci\" for confidence interval or \"ht\" for hypothesis testing? "
			          << '\n';
			Cinterval ci;
			std::string choice;
			std::cin >> choice;
			if (choice == "ci")
			{
				std::cout << "type \"zinterval\" for z confidence interval" << '\n';
				std::cout << "type \"tinterval\" for t confidence interval" << '\n';
				std::cout << "type \"pinterval\" for Proportion confidence interval" << '\n';
				std::cin >> answer_2;
				if (answer_2 == "zinterval")
				{
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
					ci.displayCI_Z(percent, point_estimate, sd, sample_size);
				}
				else if (answer_2 == "tinterval")
				{
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
					ci.displayCI_T(point_estimate, sd, sample_size, tcrit);
				}
				else if (answer_2 == "pinterval")
				{
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
					ci.displayCI_Proportion(percent, p_hat, sample_size);
				}
			}
			else if (choice == "ht")
			{
				HypTest ht;
				std::cout << "type \"zscore\" for z-score (formula without sample size)" << '\n';
				std::cout << "type \"zstat\" for z test statistic(with sample size)" << '\n';
				std::cout << "type \"tscore\" for t-score/test-statistic" << '\n';
				std::cout << "type \"2zstat\" for two sample z test statistic" << '\n';
				std::cout << "type \"2tscore\" for two sample t-score/test-statistic" << '\n';
				std::cout << "type \"chi\" for chi-square test" << '\n';
				std::cin >> answer_2;
				if (answer_2 == "zscore")
				{
					double point_estimate;
					double mean;
					double sd;
					std::cout << "What is x̄?" << '\n';
					std::cin >> point_estimate;
					std::cout << "What is the population mean?" << '\n';
					std::cin >> mean;
					std::cout << "Finally, what is the standard deviation" << '\n';
					std::cin >> sd;
					ht.calculateZscore(point_estimate, mean, sd);
				}
				else if (answer_2 == "zstat")
				{
					double point_estimate;
					double mean;
					double sd;
					int sample_size;
					std::cout << "What is x̄?" << '\n';
					std::cin >> point_estimate;
					std::cout << "What is the population mean?" << '\n';
					std::cin >> mean;
					std::cout << "What is the sample size?" << '\n';
					std::cin >> sample_size;
					std::cout << "Finally, what is the standard deviation" << '\n';
					std::cin >> sd;
					ht.calculateZstat(point_estimate, mean, sd, sample_size);
				}
				else if (answer_2 == "tscore")
				{
					double point_estimate;
					double mean;
					double sd;
					int sample_size;
					std::cout << "What is x̄?" << '\n';
					std::cin >> point_estimate;
					std::cout << "What is the population mean?" << '\n';
					std::cin >> mean;
					std::cout << "What is the sample size?" << '\n';
					std::cin >> sample_size;
					std::cout << "Finally, what is the standard deviation" << '\n';
					std::cin >> sd;
					ht.calculateTscore(point_estimate, mean, sd, sample_size);
				}
			}
			std::cout << "Would you like to keep using this function? type 'y' or 'n'" << '\n';
			std::cin >> answer;
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
				std::cout << "Invalid input, terminating calulator..." << '\n';
				repeat = false;
			}
		}
	}
	else
	{
		std::cout << "Thank you for using this calculator. Come again soon!" << '\n';
	}
}
