/* COEN 79 - Lab #1
 * Madeleine Waldie
 * 1/7/21
 */

// Includes
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

// Namespace
using namespace std;

/*
 * Function: isCharAlphanumeric - checks if character is alphanumeric
 * 	Returns true if alphanumeric (otherwise, returns false)
 * Parameter: char c
 * Return: bool
 */

bool isCharAlphanumeric(char c) {
	// Check whether alphanumeric or not
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) 
	{ 
		// If this statement is true, then the character is alphanumeric
                // So, return true
		return true;
        }

	// The statement was false, so the character is nonalphanumeric. Return false
        return false;
}

/*
 * Function: countCharacters - counts the amount of alpha-numeric and non alpha-numeric characters in input
 * Parameter: char input[100]
 * Return: void
 */

void count(char input[100]) {
	// Initialize variables
    int i = 0;
	int numAlphanumeric = 0;
	int numNonalphanumeric = 0;
        
	// Loop through the phrase that was inputted (in cin)
	while(input[i] != '\0') {
                if(isCharAlphanumeric(input[i]))
                        numAlphanumeric++; //Increment alphanumeric character count
               
		 // Use "ispunct," a built in C function to check whether a character is punctuation
                // This excludes spaces, which is what we want!
		else if(ispunct(input[i]))
                        numNonalphanumeric++; //Increment nonalphanumeric character count
                // Increment the character
		i++;
        }

	// Print out according to format in the lab document
        cout << "\"" << input << "\"" << " has " << numAlphanumeric;
        cout << " alphanumeric characters and " << numNonalphanumeric;
        cout << " non-alphanumeric characters." << endl;

	// Return (you're done)
        return;
}

/*
 * Function: main
 * Gets an input from cin & counts the number of alpha & non alpha numeric characters in the phrase
 */
int main() {
	// initialize variable to hold input
        char input[100];
	
	// Display message to user, telling them to type a phrase
        cout << "Type a phrase ";
	// Get the user's input
        cin.get(input, 100);
	
	// Count & print the number of alphanumeric / non alphanumeric chars
        count(input);
 
	// Return (you're done)
	return 0;
}
