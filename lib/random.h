#ifndef RANDOM_H
#define RANDOM_H


#include <cstdlib>
#include <ctime>

#include "type.h"


namespace Benchmarking {

	void random_seed() {
		std::srand(std::time(0));
	}

	inline ll rand_64() {
		ll higher_bits = std::rand(), lower_bits = std::rand();
		return (higher_bits << 32) ^ lower_bits;
	}

}


#endif  // RANDOM_H
