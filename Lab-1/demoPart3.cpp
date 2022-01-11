/* COEN 79 - Lab #1
 * Madeleine Waldie
 * 1/7/21
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/*
 * Function: printUppercase - Prints text using format as shown on camino.
 * Parameters: string text
 * Return: void
 */
void printUppercase(string text) {
	// Initialize variables & iterators
	int k = 0;
	int length = text.length();	
	// Create an array of characters, which will hold the words to print
	char wordsToPrint[100];

	for(int i = 0; i < length; i++) { // Loop through the length of the text

		// c will be the character that we are currently on
		char c = text.at(i);

		// Search for any spaces in the text
		if(c != 32) {

			// If it's an uppercase alphabetic char, add to the wordsToPrint array
			if(c >= 'A' && c <= 'Z') {
				wordsToPrint[k] = c;
				k++;
			}

			// If it's lowercase, make the character uppercase and add to the wordsToPrint array
			else if(c >= 'a' && c <= 'z') 
			{
				wordsToPrint[k] = c - 32;
				k++;
			}

		// If the word is larger than 10 characters, print the word
		} else if(k >= 10) {

			for(int j = 0; j < k; j++)
			{
				cout << wordsToPrint[j];
			}
			
			cout << endl;
			k = 0; // Resets the words to print index

		} else {
			k = 0;
		}

	}

	return; // Return (you're done!)
}

/*
 * Function: main
 * Parameters: int argc, char *argv[]
 * Convert  to  uppercase  and  display  all  the  words  from  an  input  file  with  length  of  at  least  10 characters
 * All  punctuation  marks  are  removed  and  do  not  contribute  to  the  words' length
 * The name of the file to be read should be read in as a command line argument
 */
int main(int argc, char *argv[]) {

	char *fileName = argv[1]; // input of the file name
	string text; // Text of the file
	ifstream myFile(fileName); // Open file

	while(getline(myFile, text)) { // Go through file line by line and print out specified things
		printUppercase(text);
	}

	myFile.close(); // Close the file

	return 0; // Return (you're done)
}
