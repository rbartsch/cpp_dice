/*
	author: rbartsch (richeinbartsch@outlook.com)
	my implementation of https://www.redblobgames.com/articles/probability/damage-rolls.html

	n_die			: amount of dice
	n_sides			: amount of sides per dice
	n_rolls			: how many times to roll
	constant_shift	: optional shift of entire distribution left or right whether it's negative or positive
	
	constant shift is useful for doings things such as a damage bonus with 2d12 + 3
	or damage blocked with 2d12 - 3
*/

#include "dice.h"
#include "rng.h"

namespace sch {
	// basic roll. scale is from 1 to x
	// --------------------------------------------------------------------------------
	int roll_dice_symmetric(int n_die, int n_sides, int constant_shift) {
		int result = 0;
		for (int i = 0; i < n_die; i++) {
			result += 1 + rand_int(0, n_sides);
		}

		// Prevent from becoming negative on scale, otherwise just return result + constantShift. Only matters depending on desire of constantShift.
		return result + constant_shift < 0 ? 0 : result + constant_shift;
	}

	// roll with distribution variance. scale is from 0 to x
	// --------------------------------------------------------------------------------
	int roll_dice_symmetric_dv(int n_die, int n_sides, int constant_shift) {
		int result = 0;
		for (int i = 0; i < n_die; i++) {
			result += rand_int(0, n_sides + 1);
		}

		return result + constant_shift < 0 ? 0 : result + constant_shift;
	}

	// drop lowest, thus resulting in higher-than-average values being more common
	// --------------------------------------------------------------------------------
	int roll_dice_asymmetric_higher_avg(int n_die, int n_sides, int n_rolls, int constant_shift) {
		int result = 0;
		int * rolls = new int[n_rolls];

		for (int i = 0; i < n_rolls; i++) {
			rolls[i] = roll_dice_symmetric_dv(n_die, n_sides, constant_shift);
			result += rolls[i];
		}

		// get the minimum of rolls
		int min = rolls[0];
		for (int i = 0; i < n_rolls; i++) {
			if (min > rolls[i]) {
				min = rolls[i];
			}
		}
		delete[] rolls;

		return result = result - min;
	}

	// drop highest, thus resulting in lower-than-average values being more common
	// --------------------------------------------------------------------------------
	int roll_dice_asymmetric_lower_avg(int n_die, int n_sides, int n_rolls, int constant_shift) {
		int result = 0;
		int * rolls = new int[n_rolls];

		for (int i = 0; i < n_rolls; i++) {
			rolls[i] = roll_dice_symmetric_dv(n_die, n_sides, constant_shift);
			result += rolls[i];
		}

		// get the maximum of rolls
		int max = rolls[0];
		for (int i = 0; i < n_rolls; i++) {
			if (max < rolls[i]) {
				max = rolls[i];
			}
		}
		delete[] rolls;

		return result = result - max;
	}

	// roll with a bonus result added x% of the time
	// --------------------------------------------------------------------------------
	int roll_dice_critical(int percentage, int n_die, int n_sides, int constant_shift) {
		int result = roll_dice_symmetric_dv(n_die, n_sides, constant_shift);
		if (chance_success(percentage)) {
			result += roll_dice_symmetric_dv(n_die, n_sides, constant_shift);
		}

		return result;
	}
}