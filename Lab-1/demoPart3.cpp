/* COEN 79 - Lab 1
 * 1/7/22
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/*
 * Function: print
 * Parameters: string text
 * Return: void
 * Prints text using format as shown on camino.
 */
void printUppercase(string text) {
	// Initialize variables & iterators
	int k = 0;
	int length = text.length();	
	// Create an array of characters, which will hold the words to print
	char wordsToPrint[100];

	for(int i = 0; i < length; i++) { // Loop through the length of the text

		char c = text.at(i);

		if(c != 32) { //search for space in text

			if(c >= 'A' && c <= 'Z') { //if uppercase alphabetic add to char temp[]
				wordsToPrint[k] = c;
				k++;
			}

			else if(c >= 'a' && c <= 'z') //if lowercase alphabetic make uppercase and add to char temp[]
			{
				wordsToPrint[k] = c - 32;
				k++;
			}

		} else if(k >= 10) { //once space is found if temp is larger then 10 characters print temp.

			for(int j = 0; j < k; j++)
			{
				cout << wordsToPrint[j];
			}
			
			cout << endl;
			k = 0; //resets temp index

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
