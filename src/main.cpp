/* ########################

Name: Marin Pavlinov Marinov
file: main.cpp
purpose: shows all the calculations as well as the formulas to the user

SPECIAL THANKS TO Ihor Kalnytskyi
termcolor project

######################## */

#include "basics.hpp"
#include "cInterval.hpp"
#include "correlation.hpp"
#include "hypTest.hpp"
#include "termcolor.hpp" // courtesy of Ihor Kalnytskyi's project
// #include <doctest/doctest.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

// function that displays formula sheet to the user
void readFormulaSheet(const std::string& text) {
	try {
		std::string s;
		std::ifstream formulas(text);

		while (getline(formulas, s)) {
			std::cout << s << '\n';
		}

		formulas.close();
	}
	catch (std::fstream::failure const& e) {
		std::cerr << "Error reading: " << text << '\n';
		std::cerr << "Reason: " << e.what() << '\n';
	}
}


int main(int argc, char* argv[]) {
	/*
	 *
	 * READING FILES SECTION
	 *
	*/
	if (argc == 2) {
		std::ifstream inputfile;
		char symbols;
		double num;
		unsigned int sets = 0;

		inputfile.open(argv[1]);

		if (inputfile.fail()) {
			std::cerr << "Unable to open" << argv[1] << "for reading";
			exit(1);
		}

		std::vector<double> dataset;
		// read through file and create a dataset
		while (inputfile >> num >> symbols) {
			dataset.emplace_back(num);
			if (symbols == ';') {
				sortDataset(dataset);
				std::cout << "Dataset " << ++sets << '\n';
				std::for_each(dataset.begin(), dataset.end(), [&](double data) {
					std::cout << data << " ";
				});

				std::cout << "\nMEAN: " << calculateMean(dataset) << '\n';
				if (dataset.size() > 3) {
					std::cout << "INTERQUARTILE RANGE: " << calculateInterquartileRange(dataset)
					          << '\n';
					displayPercentiles(dataset);
				}
				std::cout << "MODE: ";
				calculateMode(dataset);
				std::cout << "RANGE: " << calculateRange(dataset) << '\n';
				displayMinMax(dataset);
				findOutliers(dataset);
				displayStandardDeviation(dataset);
				std::cout << '\n';
				// erase terms once finished showing numbers of the current dataset to the user
				dataset.clear();
			}
		}

	} // function expects first arg as file and second arg as function
	else if (argc == 3) {
		std::ifstream inputfile;
		char symbols;
		double num;
		unsigned int sets = 0;

		inputfile.open(argv[1]);

		if (inputfile.fail()) {
			std::cerr << "Unable to open" << argv[1] << "for reading";
			exit(1);
		}

		// Should be either Mean Median,Mode,Range,Sd(standard deviation),Min, or Max
		std::string command(argv[2]);

		// ensure 3 argument is uppercase
		// this creates ease for users who do not want to use the makefile
		std::for_each(command.begin(), command.end(), [&](char& c) { c = toupper(c); });

		std::vector<double> dataset;
		// read through file and create a dataset
		while (inputfile >> num >> symbols) {
			dataset.emplace_back(num);
			if (symbols == ';') {
				sortDataset(dataset);
				std::cout << "Dataset " << ++sets << '\n';
				std::for_each(dataset.begin(), dataset.end(), [&](double data) {
					std::cout << data << " ";
				});

				if (command == "MEAN")
					std::cout << "\nMEAN: " << calculateMean(dataset) << '\n';

				if (command == "MEDIAN")
					std::cout << "MEDIAN: " << calculatePercentiles(dataset).q2 << '\n';

				if (command == "PERCENTILE") {
					std::cout << "INTERQUARTILE RANGE: " << calculateInterquartileRange(dataset) << '\n';
					displayPercentiles(dataset);
				}

				if (command == "MODE") {
					std::cout << "\nMODE: ";
					calculateMode(dataset);
				}

				if (command == "RANGE")
					std::cout << "RANGE: " << calculateRange(dataset) << '\n';

				if (command == "MIN")
					std::cout << "MIN: " << dataset.front() << '\n';

				if (command == "MAX")
					std::cout << "MAX: " << dataset.back() << '\n';

				if (command == "OUTLIERS") {
					std::cout << '\n';
					findOutliers(dataset);
				}

				if (command == "SD") {
					std::cout << '\n';
					displayStandardDeviation(dataset);
				}

				std::cout << '\n';
				// erase terms once finished showing numbers of the current dataset to the user
				dataset.clear();
			}
		}
	}
	/*
	 *
	 * DEFAULT INTERFACE SECTION
	 *
	*/
	else {
		bool backtrack = true;
		while (backtrack) {
			std::cout << termcolor::blue
			          << "~~~**Welcome to the statisical calculator MPM(beta stage)!**~~~"
			          << termcolor::reset << '\n';
			std::cout << termcolor::blue << "What would you like the calculator to do?" << '\n';
			std::cout << termcolor::yellow
			          << "type \"basics\" for {min,max,mean,median,mode,range,standard "
			             "deviation,percentiles}"
			          << termcolor::reset << '\n';
			std::cout << termcolor::green << "type \"formulas\" view the formula sheet" << '\n';
			std::cout << termcolor::magenta
			          << "type \"cc\" for finding correlation coefficients and LSRL"
			          << termcolor::reset << '\n';
			std::cout << termcolor::cyan
			          << "type \"advanced\" for confidence intervals and hypothesis testings"
			          << termcolor::reset << '\n';
			std::cout << termcolor::white << "type \"exit\" to quit the calculator" << '\n';
			std::string response;
			std::cin >> response;
			bool repeat = true;
			// for whether the user wants to repeat using a functions
			char answer;
			if (response == "basics") {
				while (repeat) {
					int terms;
					int trials = 0;
					double inputnumber;
					// gets the number of terms in the date set and fills the vector with them
					std::cout << "How many terms are there?" << '\n';
					std::cin >> terms;
					// Ensure # of terms is correct
					while (!std::cin || terms <= 1) {
						// notify user input is incorrect
						std::cout << "Invalid input! try again" << '\n';
						std::cout << "Expected one input that is greater than 1" << '\n';
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						std::cin >> terms;
					}
					std::cin.ignore(100000, '\n');
					// Perform calculations only when # of terms is valid
					if (terms > 1) {
						std::vector<double> dataset;
						dataset.reserve(terms);
						std::cout << "You may now type the numbers in your data set" << '\n';
						std::cout << " i) You can either input the data one by one (pressing enter "
						             "every time you enter a number)"
						          << '\n';
						std::cout << " ii) You can input the entire data with space in between "
						             "each number. You can even input a chunk of the data"
						          << '\n';
						std::cout << "Regardless the program will ask for input until it is not "
						             "equal to the terms you inputted"
						          << '\n';
						while (trials != terms) {
							std::cin >> inputnumber;
							if (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
							}
							else {
								dataset.emplace_back(inputnumber);
								trials++;
							}
						}

						// Ensure dataset is sorted so all functions work as intended
						sortDataset(dataset);
						// showcases the dataset's mean, mode, and range
						displayDataset(dataset);
						std::cout << termcolor::reset << '\n';
						std::cout << termcolor::underline << termcolor::red
						          << "Mean, Median, Mode, Range, Min/Max:" << termcolor::reset
						          << '\n';
						std::cout << termcolor::bold << termcolor::red
						          << "MEAN: " << calculateMean(dataset) << '\n';
						std::cout << "MODE: ";
						calculateMode(dataset);
						std::cout << "RANGE: " << calculateRange(dataset) << '\n';
						displayMinMax(dataset);
						std::cout << termcolor::reset;
						std::cout << termcolor::bold << termcolor::yellow;
						// prints the 25th,50th, and 75th percentile of the dataset
						std::cout << termcolor::underline << termcolor::yellow
						          << "\nPercentiles:" << termcolor::reset << '\n';
						std::cout << termcolor::bold << termcolor::yellow
						          << "INTERQUARTILE RANGE: " << calculateInterquartileRange(dataset)
						          << '\n';
						displayPercentiles(dataset);

						findOutliers(dataset);
						std::cout << termcolor::reset << '\n';
						// prints standard deviation and variance
						std::cout << termcolor::underline << termcolor::cyan
						          << "Standard deviation and Variance:" << termcolor::reset << '\n';
						std::cout << termcolor::bold << termcolor::cyan;
						displayStandardDeviation(dataset);
						std::cout << '\n';
						// erase terms once finished showing numbers to user
						dataset.clear();
					}
					// clear excessive inputs
					std::cin.ignore(100000, '\n');
					std::cout << termcolor::white
					          << "Would like to use this function again? Type 'y' or 'n' " << '\n';
					std::cin >> answer;
					if (answer == 'y') {
						repeat = true;
					}
					else if (answer == 'n') {
						repeat = false;
						std::cout << termcolor::reset;
					}
					else {
						std::cout << "Invalid input, going back to main page..." << '\n';
						repeat = false;
						std::cout << termcolor::reset;
					}
				}
			}
			else if (response == "formulas") {
				readFormulaSheet("formulas.txt");
			}
			else if (response == "advanced") {
				repeat = true;
				std::string answer_2;
				std::cout << termcolor::bold << termcolor::cyan
				          << "This function will allow you calculate confidence intervals and t,z "
				             "and chi "
				             "test statistics!"
				          << '\n';
				while (repeat) {
					std::cout
					    << R"(type "ci" for confidence interval or "ht" for hypothesis testing? )"
					    << '\n';
					Cinterval ci;
					std::string choice;
					std::cin >> choice;
					if (choice == "ci") {
						std::cout << "type \"zinterval\" for z confidence interval" << '\n';
						std::cout << "type \"2zinterval\" for  2 z confidence interval" << '\n';
						std::cout << "type \"tinterval\" for t confidence interval" << '\n';
						std::cout << "type \"2tinterval\" for 2 t confidence interval" << '\n';
						std::cout << "type \"pinterval\" for Proportion confidence interval"
						          << '\n';
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
						std::cout << "type \"zstat\" for z test statistic(with sample size)"
						          << '\n';
						std::cout << "type \"tscore\" for t-score/test-statistic" << '\n';
						std::cout << "type \"2zstat\" for two sample z test statistic" << '\n';
						std::cout << "type \"2tstat\" for two sample t-score/test-statistic"
						          << '\n';
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
							while (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> point_estimate;
							}
							std::cin.ignore(100000, '\n');
							std::cout << "What is the population mean?" << '\n';
							std::cin >> mean;
							while (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> mean;
							}
							std::cin.ignore(100000, '\n');
							std::cout << "Finally, what is the standard deviation" << '\n';
							std::cin >> sd;
							while (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> sd;
							}
							std::cin.ignore(100000, '\n');
							ht.calculateZscore(point_estimate, mean, sd);
						}
						else if (answer_2 == "zstat") {
							double point_estimate;
							double mean;
							double sd;
							int sample_size;
							std::cout << "What is x̄?" << '\n';
							std::cin >> point_estimate;
							while (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> point_estimate;
							}
							std::cin.ignore(100000, '\n');
							std::cout << "What is the population mean?" << '\n';
							std::cin >> mean;
							while (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> mean;
							}
							std::cin.ignore(100000, '\n');
							std::cout << "What is the sample size?" << '\n';
							std::cin >> sample_size;
							while (!std::cin || sample_size <= 0) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> sample_size;
							}
							std::cin.ignore(100000, '\n');
							std::cout << "Finally, what is the standard deviation" << '\n';
							std::cin >> sd;
							while (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> sd;
							}
							std::cin.ignore(100000, '\n');
							ht.calculateZstat(point_estimate, mean, sd, sample_size);
						}
						else if (answer_2 == "tscore") {
							double point_estimate;
							double mean;
							double sd;
							int sample_size;
							std::cout << "What is x̄?" << '\n';
							std::cin >> point_estimate;
							while (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> point_estimate;
							}
							std::cin.ignore(100000, '\n');
							std::cout << "What is the hypothesized value?" << '\n';
							std::cin >> mean;
							while (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> mean;
							}
							std::cin.ignore(100000, '\n');
							std::cout << "What is the sample size?" << '\n';
							std::cin >> sample_size;
							while (!std::cin || sample_size <= 0) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> sample_size;
							}
							std::cin.ignore(100000, '\n');
							std::cout << "Finally, what is the standard deviation" << '\n';
							std::cin >> sd;
							while (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> sd;
							}
							std::cin.ignore(100000, '\n');
							ht.calculateTscore(point_estimate, mean, sd, sample_size);
						}
						else if (answer_2 == "p") {
							double p_hat;
							double p;
							int sample_size;
							std::cout << "What is p̂?" << '\n';
							std::cin >> p_hat;
							while (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> p_hat;
							}
							std::cin.ignore(100000, '\n');
							std::cout << "What is p?" << '\n';
							std::cin >> p;
							while (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> p;
							}
							std::cin.ignore(100000, '\n');
							std::cout << "Finally, what is the sample size?" << '\n';
							std::cin >> sample_size;
							while (!std::cin || sample_size <= 0) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
								std::cin >> sample_size;
							}
							std::cin.ignore(100000, '\n');
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
						else {
							std::cout << "Invalid answer, type y when prompted to try again"
							          << '\n';
						}
					}
					// clear excessive inputs
					std::cin.ignore(100000, '\n');
					std::cout << '\n';
					std::cout << "Would you like to keep using this function? type 'y' or 'n'"
					          << '\n';
					std::cin >> answer;
					if (answer == 'y') {
						repeat = true;
					}
					else if (answer == 'n') {
						repeat = false;
						std::cout << termcolor::reset;
					}
					else {
						std::cout << "Invalid input, going back to main page..." << '\n';
						repeat = false;
						std::cout << termcolor::reset;
					}
				}
			}
			else if (response == "cc") {
				std::cout << termcolor::white;
				repeat = true;
				while (repeat) {
					int terms;
					int trials = 0;
					double inputnumbers;
					// gets the number of terms in the date set and fills the vector with them
					std::cout << "How many terms are there?" << '\n';
					std::cin >> terms;
					while (!std::cin || terms <= 1) {
						// notify user input is incorrect
						std::cout << "Invalid input! try again" << '\n';
						std::cout << "Expected one input that is greater than 1" << '\n';
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						std::cin >> terms;
					}
					std::cin.ignore(100000, '\n');
					if (terms > 1) {
						std::vector<double> datasetX;
						datasetX.reserve(terms);
						std::cout << "You may now type the numbers in your X data set" << '\n';
						while (trials != terms) {
							std::cin >> inputnumbers;
							if (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
							}
							else {
								datasetX.emplace_back(inputnumbers);
								trials++;
							}
						}
						trials = 0;
						std::cin.ignore(100000, '\n');
						std::vector<double> datasetY;
						datasetY.reserve(terms);
						std::cout << "You may now type the numbers in your Y data set" << '\n';
						while (trials != terms) {
							std::cin >> inputnumbers;
							if (!std::cin) {
								std::cout << "Invalid input! try again" << '\n';
								std::cin.clear();
								std::cin.ignore();
							}
							else {
								datasetY.emplace_back(inputnumbers);
								trials++;
							}
						}
						std::cout << termcolor::reset << termcolor::bold << termcolor::blue;
						displayDatasetXY(datasetX, datasetY);
						std::cout << termcolor::reset << '\n';
						std::cout << termcolor::bold << termcolor::cyan;
						displayLSRL(datasetX, datasetY);
					}
					// clear excessive inputs
					std::cin.ignore(100000, '\n');
					std::cout << "\n Would you like to keep using this function? type 'y' or 'n'"
					          << '\n';
					char decision;
					std::cin >> decision;
					if (decision == 'y') {
						repeat = true;
					}
					else if (decision == 'n') {
						repeat = false;
						std::cout << termcolor::reset;
					}
					else {
						std::cout << "Invalid input, going back to main page..." << '\n';
						repeat = false;
						std::cout << termcolor::reset;
					}
				}
			}
			else if (response == "exit") {
				std::cout << termcolor::bold << termcolor::white;
				std::cout << "Thank you for using this calculator. Come again soon!" << '\n';
				backtrack = false;
			}
			else {
				std::cout << "You have typed something incorrectly, please try again" << '\n';
				std::cout << termcolor::reset;
			}
		}
	}

	return 0;
}
