// FILE: mystring.cpp
// CLASS IMPLEMENTED: string (see mystring.h for documentation)

// INVARIANTS OF THE CLASS:
    // *characters points to an array of chars that ends in '\0'
    // allocated gives the size of characters
    // current_length gives the number of chars in characters

// INCLUDES
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cassert>
#include "mystring.h"

// NAMESPACES
using std::cin;
using std::cout;
using std::endl;
using namespace coen79_lab5;

namespace coen79_lab5
{
    // CONSTRUCTOR, COPY CONSTRUCTOR, and DESTRUCTOR
    string::string(const char str[]) { // Creates a new string
        // The total number of characters prior to the null character is stored in current_length, which is always less than allocated
            // So, we can set the current length to the length of the string.
        current_length = strlen(str);

        // The total length of the dynamic array is stored in the member variable allocated
        allocated = current_length + 1;

        // The string is stored as a null-terminated string in the dynamic array that characters points to
        // So, we can allocate memory for the null-terminated string
        characters = new char[allocated];

        // Finally, we can use "strcpy" to copy the null-terminated string from the parameter str to the dynamic array characters
        strncpy(characters,str,allocated);
    }

    string::string(char c) { // Creates a new string from one specified character
        // For this configuration, we can just set the current_length to be 1
        current_length = 1;
        
        // Allocated is always 1 more than current_length, so it would be 2 in this context
        allocated = 2;

        // Allocate memory for the null-terminated string
        characters = new char[allocated];

        // We know the char given will be at element 0 
        characters[0] = c;

        // And the element at 1 will be '\0'
        characters[1] = '\0';
    }

    string::string(const string& source) { // Creates a new string from an existing string
        // Set the current_length to the current_length of the source string
        current_length = source.current_length;

        // Set allocated to the source's allocated
        allocated = source.allocated;

        // allocate memory for the null-terminated string "characters"
        characters = new char[current_length];

        // Copy source to the characters array
        strncpy(characters,source.characters,current_length);
    }

    string::~string() { // Destructor - gets rid of any heap memory left over
        // Get rid of the characters array
        delete [] characters;

        // After getting rid of characters, we also need to reset the current length and allocated variables
        current_length = 0;
        allocated = 0;
    }
    
    // MODIFICATION MEMBER FUNCTIONS
    void string::operator +=(const string& addend) { // Adds a string to the end of the current string
        // Add the current lengths together
        current_length += addend.current_length;

        // Update allocated to be the new current length + 1
        allocated += current_length + 1;

        // Call the reserve function - All functions will now work efficiently (without allocating new memory) until n characters are in the string
        reserve(allocated);

        // Append the characters of the new string to old string, plus a terminating null-character
        strncat(characters, addend.characters, addend.current_length);
    }

    void string::operator +=(const char addend[]) { // Adds a string of chars to the end of the current string
        // Add the current lengths together
        current_length += strlen(addend);
        
        // Update allocated to be the new current length + 1
        allocated = current_length + 1;

        // Call the reserve function - All functions will now work efficiently (without allocating new memory) until n characters are in the string
        reserve(allocated);

        // Append the characters of the new string to old string, plus a terminating null-character
        strncat(characters, addend, strlen(addend));
    }

    void string::operator +=(char addend) { // Adds a char to the end of the current string
        // Add the current lengths together
        current_length += 1;

        // Update allocated to be the new current length + 1
        allocated = current_length + 1;

        // Call the reserve function - All functions will now work efficiently (without allocating new memory) until n characters are in the string
        reserve(allocated);

        // Add the character to the end of the string
        characters[current_length - 1] = addend;

        // Make the last character a null terminating char
        characters[current_length] = '\0';
    }

    void string::reserve(size_t n) { // Reserve more memory if a larger amount is needed
        // Create a temporary array of characters
        char* temp = new char[n];

        // If characters isn't null, then copy the characters to the new array of characters & delete the characters memory
        if (characters != NULL) {
            strncpy (temp, characters, current_length);
            delete [] characters;
        }

        // Put the temporary characters back into the characters array
        characters = temp;
    }

    string& string::operator =(const string& source) { // Set the current string to a specified string
        // Delete the number of characters after 0 in this string (basically clearing the string)
        this -> dlt(0, current_length);

        // Set the current length to the new string's length
        current_length = source.current_length;

        // Set allocated to the new string's allocated variable
        allocated = source.allocated;

        // Call the reserve function - All functions will now work efficiently (without allocating new memory) until n characters are in the string
        reserve(allocated);

        // Copy the new string to this string
        strncpy(characters, source.characters, source.current_length);

        // Return this string
        return *this;
    }

    void string::insert(const string& source, unsigned int position) { // Insert a new string before the specified position
        // First, we need to check the precondition that position <= length()
        assert(position <= length());

        // Create a temporary string, which holds the string to be inserted
        string temp = source;

        // Loop through the characters from the specified position to the end of this string
        for(int i = position; i < int(current_length); i++) {
            // Add the back end of this string to the temp string
            temp += characters[i];
        }

        // Add the length of the specified string to this string
        current_length += source.length();

        // Loop through the temp string and add it to the current string, before the specified position to the end of the string
        for(int j = 0; j < int(temp.length()); position++, j++) {
            characters[position] = temp[j];
        }
    }

    void string::dlt(unsigned int position, unsigned int num) {
        // First, we need to check the precondition that (position + num) <= length()
        assert((position + num) <= length());

        // Loop through the string and shift the characters over to the left, "deleting" the characters necessary
        for (int i = position; i < int(current_length); i++) {
            characters[i] = characters[num + i];
        }

        // Because we deleted the number of chars after the position, we need to remove the num from the current length
        current_length -= num;
    }

    void string::replace(char c, unsigned int position) { // Replace a specified char with another character
        // First, make sure the position is a possible position
        assert(position < length());

        // Set the character at the position to the new character
        characters[position] = c;
    }

    void string::replace(const string& source, unsigned int position) { // Replace a specified part of the character string with another string
        // First, we need to check the precondition that (position + source.length()) <= length()
        assert((position + source.length()) <= length());

        // Take the character at the position and replace it with the first character of the specified string (and keep going to end of string)
        int j = 0;
        for (int i = position; i < int((position + source.length())); i++, j++) {
            characters[i] = source[j];
        }
    }
    
    // CONSTANT MEMBER FUNCTIONS
    char string::operator [ ](size_t position) const { // Returns a character at a specified position
        // Make sure the string is a valid string
        assert(position < length());

        // Return the character at the specified position
        return characters[position];
    }

    int string::search(char c) const { // Search the string for a given character
        // Loop through the characters
        for(size_t i = 0; i < length(); i++) {
            // If the character at the current index is the character we're searching for, return the index
			if(characters[i] == c) {
                return i;
            }
		}

        // If we get here, we know the character isn't in the string. So, we can return -1
		return -1;
    }

    int string::search(const string& substring) const { // Search the string for a given substring
        // Create a variable we can iterate while going through the while loop
        int i = 0;

        // Loop through the array of characters (until we get to the null char indicating the end)
        while (characters[i] != '\0') {
            // If the character at the current index is equal to the substring's first character
            if (characters[i] == substring[0]) {

                // The substring may be present, so we can set a bool variable to keep track of whether or not it's present
                bool isPresent = true;

                // Now, we need to see if the following characters complete the substrin
                for (size_t j = 0; j < substring.length(); j++) {
                    // If the subsequent characters aren't a part of the substring, we know the substring isn't present here. So, we need to set the flag to not present
                    if (characters[i + j] != substring[j]) {
                        isPresent = false;
                        j = substring.length();
                    }
                }
                
                // If the substring is present, we don't need to continue the while loop
                if (isPresent) {
                    return i; // So, we can return the index of the substring!
                }
            }

            // Iterate i
            i++;
        }

        // If we get here, we know the substring isn't present. So, we can return -1
        return -1;
    }

    unsigned int string::count(char c) const { // Count the number of times a given character's present
        // Create a variable to keep track of the count
        unsigned int count = 0;

        // Loop through the characters array
        for (int i = 0; i < int(length()); i++)
        {
            // Increase the count if the char is at the current position
            if (c == characters[i]) {
                count++;
            }
        }

        // Return the count
        return count;
    }
    
    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source) {
        // Add the string to the output stream
        outs << source.characters;

        // Return the output stream
        return outs;
    }

    bool operator ==(const string& s1, const string& s2) {
        // Compare the two given strings to see if they're equal
        return (strcmp(s1.characters,s2.characters) == 0);
    }

    bool operator !=(const string& s1, const string& s2) {
        // Compare the two given strings to see if they're not equal
        return (strcmp(s1.characters,s2.characters) != 0);
    }

    bool operator > (const string& s1, const string& s2) {
        // Compare the two given strings to see if s1 is greater than s2
        return (strcmp(s1.characters,s2.characters) > 0);
    }

    bool operator < (const string& s1, const string& s2) {
        // Compare the two given strings to see if s1 is less than s2
        return (strcmp(s1.characters,s2.characters) < 0);
    }

    bool operator >=(const string& s1, const string& s2) {
        // Compare the two given strings to see if s1 is greater than or equal to s2
        return (strcmp(s1.characters,s2.characters) >= 0);
    }

    bool operator <=(const string& s1, const string& s2) {
        // Compare the two given strings to see if s1 is less than or equal to s2
        return (strcmp(s1.characters,s2.characters) <= 0);
    }

    // NON-MEMBER FUNCTIONS for the string class
    string operator +(const string& s1, const string& s2) {
        // Create a temporary string, which will hold the addition of the two strings
        string temp;

        // Call the reserve function - All functions will now work efficiently (without allocating new memory) until n characters are in the string
        temp.reserve(s1.length() + s2.length() + 1);

        // Add s1 to the temp string
        temp += s1;

        // Add s2 to the temp string
        temp += s2;

        // Return the temp string
        return temp;
    }

    string operator +(const string& s1, const char addend[ ]) {
        // Create a temporary string, which will hold the addition of the two
        string temp;

        // Call the reserve function - All functions will now work efficiently (without allocating new memory) until n characters are in the string
        temp.reserve(s1.length() + strlen(addend) + 1);

        // Add s1 to the temp string
        temp += s1;

        // Add the char to the temp string
        temp += addend;

        // Return the temp string
        return temp;
    }

    std::istream& operator >> (std::istream& ins, string& target) {
        // Create a temporary character
        char temp;

        // Loop through the input stream
		while(!ins.eof() && isspace(ins.peek())){
            // If we're not at the end of the file and theres a white space, then we should ignore the space
			ins.ignore(); 
		}

        // Set the target to an empty character before we go through the next while loop
		target = "";

		while(!ins.eof() && !isspace(ins.peek())){
            // If we're not at the end of the file and theres not a white space, then we should read in the chars and add them to target
			ins >> temp;
			target += temp;
		}

        // Return the new input stream
		return ins;
    }
}
