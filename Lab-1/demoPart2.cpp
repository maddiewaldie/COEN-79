/* COEN 79 - Lab #1
 * Madeleine Waldie
 * 1/7/21
 */

// Includes
#include <iostream>
#include <stdlib.h>
#include <stdio.h> 
#include <iomanip>

// Namespace
using namespace std;

/*
 * Function printNumsBackwards - print the numbers backwards
 * Parameters: char input[10]
 * Retun: void
 */
void printNumsBackwards(char nums[10]) {
	for(int i = 10; i >= 0; i--) 
	{
		cout << nums[i];
	}
}

/*
 * Function: printPattern - print numbers in pattern specified
 * Parameters: char nums[10]
 * Return: void
 */
void printPattern(char nums[10]) {
	// Print before pattern:
	cout << nums << endl; //Prints input foward

	// Print out pattern
	int leadingSpaces = 2;
	int middleSpaces = 15;
	for(int i = 0; i < 4; i++) 
	{
		cout << setw(leadingSpaces);
		printNumsBackwards(nums); // Print number going backwards
		cout << setw(middleSpaces);		
		cout << nums; // Print number going forward
		cout << endl; // End the line

		leadingSpaces += 2; //Increment leading spaces
		middleSpaces += 2; //Increment middle spaces
	}

	// Print after Pattern
	cout << setw(leadingSpaces);
	printNumsBackwards(nums);
	cout << endl; //Prints input foward
}

/*
 * Function: main
 * Prompts user for string of 10 digits.
 * Prints the number according to pattern
 */
int main() {
	char input[11]; // Initialize input
	cout << "Please type in the numbers 0 to 9 with no spaces in between: "; // Display message to user, asking them to input the nums
	cin.get(input, 11); // Get what the user typed

	printPattern(input); 	// Print the numbers in the pattern shown in Lab document

	// Return (you're done)
	return 0;
}
