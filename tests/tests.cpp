#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/basics.hpp"
#include "../src/cInterval.hpp"
#include "../src/correlation.hpp"
#include "../src/hypTest.hpp"

// OPERATOR overloads
bool operator==(const Percentile& lhs, const Percentile& rhs) {
	return (lhs.q1 == rhs.q1 && lhs.q2 == rhs.q2 && lhs.q3 == rhs.q3);
}

bool operator==(const DataType& lhs, const DataType& rhs) {
	return (lhs.sample == rhs.sample && rhs.population == rhs.population);
}

bool operator==(const Bound& lhs, const Bound& rhs) {
	return (lhs.lower == rhs.lower && lhs.upper == rhs.upper);
}

// MUCH MORE TESTING TO BE DONE IN THE FUTURE


std::vector<double> test_vector {1,2,3,4,5};

TEST_CASE("TESTING CALCULATOR") {

	SUBCASE("Basics") {
		// MEAN
		CHECK(calculateMean(test_vector,test_vector.size()) == 3);
		// MEDIAN
		CHECK(calculatePercentiles(test_vector).q2 == 3);
		// RANGE
		CHECK(calculateRange(test_vector) == 4);
	}

	SUBCASE("Hypothesis Testing") {

	}

	SUBCASE("Confidence Intervals") {

	}

	SUBCASE("Correlation Coefficient") {

	}
}
