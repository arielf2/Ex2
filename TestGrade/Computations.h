#pragma once

// Includes --------------------------------------------------------------------

#include <math.h>

// Constants -------------------------------------------------------------------

#define NUM_OF_FILES 13
#define MOED_A 11
#define MOED_B 12
#define MIDTERM	10
#define HIGHEST_EXERCISES_GRADE 8
#define NUM_OF_EXERCISES 10

// Function Declarations -------------------------------------------------------

/*	calc_average

	Description:	Compute the average grade of a student according to the different weights of each element (hw, midterm, exam)
	Parameters:		grades array: contains floating point numbers representing the grades for each element
	Returns:		integer value: the computed average according, rounded up to the nearest integer

*/
int calc_average(float grades[]);

/*	FindHighestGrades

	Description:	Finds the maximal grade from the array of grades for each student. Will be used to find the top 8 grades, since 
					only they will be taken into account when calculating the average
	Parameters:		grades array: array of grades of a given student
	Returns:		The index of the highest grade

*/
float FindHighestGrades(float grades[]);

