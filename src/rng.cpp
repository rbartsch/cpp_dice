/*
	author: rbartsch (richeinbartsch@outlook.com)
	random number generator
*/

#include "rng.h"
#include <random>
#include <chrono>

namespace sch {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine engine(seed);

	// (a) is inclusive, (b) is exclusive (i.e 0..4 can result in 0, 1, 2, or 3)
	// --------------------------------------------------------------------------------
	int rand_int(int a, int b) {
		std::uniform_int_distribution<int> distribution(a, b - 1);
		return distribution(engine);
	}

	// --------------------------------------------------------------------------------
	bool chance_success(int percentage) {
		if (rand_int(0, 101) <= percentage) {
			return true;
		}
		else {
			return false;
		}
	}
}