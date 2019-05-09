/* ########################

Name: Marin Pavlinov Marinov
file: main.cpp
purpose: shows all the calculations as well as the formulas to the user

######################## */

#include "basics.hpp"
#include "cInterval.hpp"
#include "correlation.hpp"
#include "hypTest.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

// function that displays formula sheet to the user
void readFormulaSheet(const std::string& text) {
	std::string s;
	std::ifstream formula(text);
	while (getline(formula, s)) {
		std::cout << s << '\n';
	}
}

int main() {
	bool backtrack = true;
	while (backtrack) {
		std::cout << "~~~**Welcome to the statisical calculator MPM(beta stage)!**~~~" << '\n';
		std::cout << "What would you like the calculator to do?" << '\n';
		std::cout
		    << "type \"basics\" for {min,max,mean,median,mode,range,standard deviation,percentiles}"
		    << '\n';
		std::cout << "type \"formulas\" view the formula sheet" << '\n';
		std::cout << "type \"cc\" for finding correlation coefficients and LSRL" << '\n';
		std::cout << "type \"advanced\" for confidence intervals and hypothesis testings" << '\n';
		std::cout << "type \"exit\" to quit the calculator" << '\n';
		std::string response;
		std::cin >> response;
		bool repeat = true;
		// for whether the user wants to repeat using a functions
		char answer;
		if (response == "basics") {
			while (repeat == true) {
				int terms;
				int trials = 0;
				double inputnumber;
				// gets the number of terms in the date set and fills the vector with them
				std::cout << "How many terms are there?" << '\n';
				std::cin >> terms;
				if (terms < 1) {
					std::cout << "Invalid number of terms!" << '\n';
				}
				else {
					std::vector<double> dataset;
					dataset.reserve(terms);
					std::cout << "You may now type the numbers in your data set" << '\n';
					while (trials != terms) {
						std::cin >> inputnumber;
						dataset.emplace_back(inputnumber);
						trials++;
					}
					// showcases the dataset's mean, mode, and range
					displayDataset(dataset);
					std::cout << "The MEAN of the data set is: " << calculateMean(dataset, terms)
					          << '\n';
					std::cout << "The MODE of your data set is: " << calculateMode(dataset) << '\n';
					std::cout << "The RANGE of the data set is: " << calculateRange(dataset)
					          << '\n';
					displayMinMax(dataset);
					// prints the 25th,50th, and 75th percentile of the dataset
					if (dataset.size() > 3) {
						std::cout << '\n' << "Percentiles: " << '\n';
						std::cout << "The INTERQUARTILE RANGE of the data set is: "
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
				}
				// reset the trials
				trials = 0;
				std::cout << "Would like to use this function again? Type 'y' or 'n' " << '\n';
				std::cin >> answer;
				if (answer == 'y') {
					repeat = true;
				}
				else if (answer == 'n') {
					repeat = false;
				}
				else {
					std::cout << "Invalid input, going back to main page..." << '\n';
					repeat = false;
				}
			}
		}
		else if (response == "formulas") {
			readFormulaSheet("formulas.txt");
		}
		else if (response == "advanced") {
			repeat = true;
			std::string answer_2;
			std::cout
			    << "This function will allow you calculate confidence intervals and t,z and chi "
			       "test statistics!"
			    << '\n';
			while (repeat) {
				std::cout
				    << "type \"ci\" for confidence interval or \"ht\" for hypothesis testing? "
				    << '\n';
				Cinterval ci;
				std::string choice;
				std::cin >> choice;
				if (choice == "ci") {
					std::cout << "type \"zinterval\" for z confidence interval" << '\n';
					std::cout << "type \"2zinterval\" for  2 z confidence interval" << '\n';
					std::cout << "type \"tinterval\" for t confidence interval" << '\n';
					std::cout << "type \"2tinterval\" for 2 t confidence interval" << '\n';
					std::cout << "type \"pinterval\" for Proportion confidence interval" << '\n';
					std::cout << "type \"2pinterval\" for 2 Proportions confidence interval"
					          << '\n';
					std::cin >> answer_2;
					if (answer_2 == "zinterval") {
						ci.displayCI_Z();
					}
					else if (answer_2 == "tinterval") {
						ci.displayCI_T();
					}
					else if (answer_2 == "pinterval") {
						ci.displayCI_Proportion();
					}
					else if (answer_2 == "2zinterval") {
						ci.displayCI_2Z();
					}
					else if (answer_2 == "2tinterval") {
						ci.displayCI_2T();
					}
					else if (answer_2 == "2pinterval") {
						ci.displayCI_2Proportions();
					}
				}
				else if (choice == "ht") {
					HypTest ht;
					std::cout << "type \"zscore\" for z-score (formula without sample size)"
					          << '\n';
					std::cout << "type \"zstat\" for z test statistic(with sample size)" << '\n';
					std::cout << "type \"tscore\" for t-score/test-statistic" << '\n';
					std::cout << "type \"2zstat\" for two sample z test statistic" << '\n';
					std::cout << "type \"2tstat\" for two sample t-score/test-statistic" << '\n';
					std::cout << "type \"2tpair\" for paired two sample t-score/test-statistic"
					          << '\n';
					std::cout << "type \"p\" for single proportion test" << '\n';
					std::cout << "type \"twop\" for 2 proportion test" << '\n';
					std::cout << "type \"chi\" for chi-square test" << '\n';
					std::cin >> answer_2;
					if (answer_2 == "zscore") {
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
					else if (answer_2 == "zstat") {
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
					else if (answer_2 == "tscore") {
						double point_estimate;
						double mean;
						double sd;
						int sample_size;
						std::cout << "What is x̄?" << '\n';
						std::cin >> point_estimate;
						std::cout << "What is the hypothesized value?" << '\n';
						std::cin >> mean;
						std::cout << "What is the sample size?" << '\n';
						std::cin >> sample_size;
						std::cout << "Finally, what is the standard deviation" << '\n';
						std::cin >> sd;
						ht.calculateTscore(point_estimate, mean, sd, sample_size);
					}
					else if (answer_2 == "p") {
						double p_hat;
						double p;
						int sample_size;
						std::cout << "What is p̂?" << '\n';
						std::cin >> p_hat;
						std::cout << "What is p?" << '\n';
						std::cin >> p;
						std::cout << "Finally, what is the sample size?" << '\n';
						std::cin >> sample_size;
						ht.calculateProportion(p_hat, p, sample_size);
					}
					else if (answer_2 == "2zstat") {
						ht.printHypothesisReport_2Z();
					}
					else if (answer_2 == "2tstat") {
						ht.printHypothesisReport_2T();
					}
					else if (answer_2 == "2tstat") {
						ht.printHypothesisReport_2T();
					}
					else if (answer_2 == "2tpair") {
						ht.printHypothesisReport_pairedT();
					}
					else if (answer_2 == "twop") {
						ht.printHypothesisReport_2P();
					}
					else if (answer_2 == "chi") {
						ht.printChiTest();
					}
				}
				std::cout << "Would you like to keep using this function? type 'y' or 'n'" << '\n';
				std::cin >> answer;
				if (answer == 'y') {
					repeat = true;
				}
				else if (answer == 'n') {
					repeat = false;
				}
				else {
					std::cout << "Invalid input, going back to main page..." << '\n';
					repeat = false;
				}
			}
		}
		else if (response == "cc") {
			repeat = true;
			while (repeat) {
				int terms;
				int trials = 0;
				double inputnumbers;
				// gets the number of terms in the date set and fills the vector with them
				std::cout << "How many terms are there?" << '\n';
				std::cin >> terms;
				if (terms < 1) {
					std::cout << "invalid number of terms!" << '\n';
				}
				else {
					std::vector<double> datasetX;
					datasetX.reserve(terms);
					std::cout << "You may now type the numbers in your X data set" << '\n';
					while (trials != terms) {
						std::cin >> inputnumbers;
						datasetX.emplace_back(inputnumbers);
						trials++;
					}
					trials = 0;
					std::vector<double> datasetY;
					datasetY.reserve(terms);
					std::cout << "You may now type the numbers in your Y data set" << '\n';
					while (trials != terms) {
						std::cin >> inputnumbers;
						datasetY.emplace_back(inputnumbers);
						trials++;
					}
					sortDatasetXY(datasetX, datasetY);
					displayDatasetXY(datasetX, datasetY);
					std::cout << '\n';
					displayLSRL(datasetX, datasetY, terms);
				}
				std::cout << "Would you like to keep using this function? type 'y' or 'n'" << '\n';
				char decision;
				std::cin >> decision;
				if (decision == 'y') {
					repeat = true;
				}
				else if (decision == 'n') {
					repeat = false;
				}
				else {
					std::cout << "Invalid input, going back to main page..." << '\n';
					repeat = false;
				}
			}
		}
		else if (response == "exit") {
			std::cout << "Thank you for using this calculator. Come again soon!" << '\n';
			backtrack = false;
		}
		else {
			std::cout << "You have typed something incorrectly, please try again" << '\n';
		}
	}

	return 0;
}