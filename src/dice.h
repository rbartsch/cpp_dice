#ifndef SCH_DICE_H
#define SCH_DICE_H

namespace sch {
	// --------------------------------------------------------------------------------
	int roll_dice_symmetric(int n_die, int n_sides, int constant_shift = 0);

	// --------------------------------------------------------------------------------
	int roll_dice_symmetric_dv(int n_die, int n_sides, int constant_shift = 0);

	// --------------------------------------------------------------------------------
	int roll_dice_asymmetric_higher_avg(int n_die, int n_sides, int n_rolls, int constant_shift = 0);

	// --------------------------------------------------------------------------------
	int roll_dice_asymmetric_lower_avg(int n_die, int n_sides, int n_rolls, int constant_shift = 0);

	// --------------------------------------------------------------------------------
	int roll_dice_critical(int percentage, int n_die, int n_sides, int constant_shift = 0);
}

#endif // !SCH_DICE_H