#ifndef SCH_RNG_H
#define SCH_RNG_H

namespace sch {
	extern unsigned seed;

	// --------------------------------------------------------------------------------
	int rand_int(int a, int b);

	// --------------------------------------------------------------------------------
	bool chance_success(int percentage);
}

#endif // !SCH_RNG_H