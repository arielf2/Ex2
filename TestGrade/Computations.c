/* Functions that are used in calculating the average grade of a student */

#include "Computations.h"

int calc_average(float grades[]) {
	//add exercises value
	int max_index = -1;
	float average = 0;
	float grades_sum = 0;
	float highest_grades[HIGHEST_EXERCISES_GRADE] = { 0 };//
	float exercise_average = 0;
	int did_moed_b = 0;

	//mark if student did moed B
	if (grades[MOED_B] != 0) {
		did_moed_b = 1;
	}
	//change grades under 60 to 0 for calculation
	for (int i = 0; i < NUM_OF_FILES; i++) {
		if (grades[i] < 60) {
			grades[i] = 0;
		}
	}
	//find 8 highest grades
	for (int j = 0; j < HIGHEST_EXERCISES_GRADE; j++) {
		max_index = FindHighestGrades(grades);
		if (max_index == -1) {
			printf("Error while getting highest grade\n");
			return -1;
		}
		highest_grades[j] = grades[max_index];
		grades[max_index] = -1;

	}

	//calc average of exercises
	for (int j = 0; j < HIGHEST_EXERCISES_GRADE; j++) {
		grades_sum += highest_grades[j];
	}
	exercise_average = grades_sum / HIGHEST_EXERCISES_GRADE;

	//add exercises value
	average += 0.2*exercise_average;

	//add midterm value
	average += 0.2*grades[MIDTERM];

	//add final exam value
	if (did_moed_b == 1) {
		average += 0.6*grades[MOED_B];
	}
	else {
		average += 0.6*grades[MOED_A];
	}
	return ceil(average);
}

float FindHighestGrades(float grades[]) {
	int max = -1;
	int max_index = -1;
	for (int i = 0; i < NUM_OF_EXERCISES; i++) {
		if (grades[i] > max) {
			max = grades[i];
			max_index = i;
		}
	}
	return max_index;
}