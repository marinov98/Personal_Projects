#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/basics.hpp"
#include "../src/cInterval.hpp"
#include "../src/correlation.hpp"
#include "../src/hypTest.hpp"

std::vector<double> test_vector {1,2,3,4,5};

TEST_CASE("TESTING CALCULATOR") {

	SUBCASE("Basics") {
		CHECK(calculateMean(test_vector,test_vector.size()) == 3);
	}

	SUBCASE("Hypothesis Testing") {

	}

	SUBCASE("Confidence Intervals") {

	}

	SUBCASE("Correlation Coefficient") {

	}
}
