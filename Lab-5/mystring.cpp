// FILE: mystring.cpp
// CLASS IMPLEMENTED: string (see mystring.h for documentation)

// INVARIANTS OF THE CLASS:
    // 

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cassert>
#include "mystring.h"

using std::cin;
using std::cout;
using std::endl;
using namespace coen79_lab5;

namespace coen79_lab5
{
    // CONSTRUCTOR, COPY CONSTRUCTOR, and DESTRUCTOR
    string::string(const char str[ ]) {
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

    string::string(char c) {
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

    string::string(const string& source) {
        current_length = source.current_length;
        allocated = source.allocated;
        characters = new char[current_length];
        strncpy(characters,source.characters,current_length);
    }

    string::~string() {
        // Since the class uses dynamic memory, we must implement a destructor:
        delete [] characters;

        // After getting rid of characters, we also need to reset the current length and allocated variables
        current_length = 0;
        allocated = 0;
    }
    
    // MODIFICATION MEMBER FUNCTIONS
    void string::operator +=(const string& addend) {
        current_length += addend.current_length;
        allocated += current_length + 1;
        reserve(allocated);
        strncat(characters, addend.characters, addend.current_length);
        return;
    }

    void string::operator +=(const char addend[ ]) {
        current_length += strlen(addend);
        allocated = current_length + 1;
        reserve(allocated);
        strncat(characters, addend, strlen(addend));
        return;
    }

    void string::operator +=(char addend) {
        current_length += 1;
        allocated = current_length + 1;
        reserve(allocated);
        characters[current_length-1] = addend;
    }

    void string::reserve(size_t n) {
        char* temp = new char[n];
        if (characters != NULL)
        {
            strncpy (temp, characters, current_length);
            delete [] characters;
        }
        characters = temp; //put temp back into characters
        return;
    }

    string& string::operator =(const string& source) {
        this->dlt(0,current_length); //to return string&
        current_length = source.current_length;
        allocated = source.allocated;
        reserve(allocated);
        strncpy(characters, source.characters, source.current_length);
        return *this;
    }

    void string::insert(const string& source, unsigned int position) {
        assert(position <= length());
        int i, j;
        string temp = source;
        //reserve(allocated);
        for(i = position; i < int(current_length); i++) //add characters from position into temp
        {
            temp += characters[i];
        }
        current_length += source.length();
        for(j = 0; j < int(temp.length()); position++, j++) //add temp back into characters
        {
            characters[position] = temp[j];
        }
        return;
    }

    void string::dlt(unsigned int position, unsigned int num) {
        assert((position + num) <= length( ));
        int i;
        for (i = position; i < int(current_length); i++)
        {
            characters[i] = characters[num + i]; //shift characters to the left
        }
        current_length-=num;
        return;
    }

    void string::replace(char c, unsigned int position) {
        assert(position < length());
        characters[position] = c;
        return;
    }

    void string::replace(const string& source, unsigned int position) {
        assert((position + source.length()) <= length());
        int i, j = 0;
        for (i = position; i < int((position + source.length())); i++, j++)
        {
            characters[i] = source[j];
        }
        return;
    }
    
    // CONSTANT MEMBER FUNCTIONS
    char string::operator [ ](size_t position) const {
        assert(position < length());
        return characters[position];
    }

    int string::search(char c) const {
        for(size_t i = 0; i < length();i++){						//traverse and if its the right char return index; if not found return -1
			if(characters[i] == c)
				return i;
		}
		return -1;
    }

    int string::search(const string& substring) const {
        for(size_t i = 0; i <= length() - int(substring.length());i++){
			bool flag = true;
			for(size_t j = 0;j< substring.length();i++){				//traverse the string and see if the first char matches the first char of the substring otherwise keep moving
				if(characters[i+j] != substring.characters[j]){
					flag = false;
					break;
				}
			}
			if(flag == true)
				return i;
		}
		return -1;
    }

    unsigned int string::count(char c) const {
        int i;
        unsigned int count = 0;
        for (i = 0; i < int(length()); i++)
        {
            if (c == characters[i])
                count++;
        }
        return count;
    }
    
    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source) {
        outs << source.characters;
        return outs;
    }

    bool operator ==(const string& s1, const string& s2) {
        return (strcmp(s1.characters,s2.characters) == 0);
    }

    bool operator !=(const string& s1, const string& s2) {
        return (strcmp(s1.characters,s2.characters) != 0);
    }

    bool operator > (const string& s1, const string& s2) {
        return (strcmp(s1.characters,s2.characters) > 0);
    }

    bool operator < (const string& s1, const string& s2) {
        return (strcmp(s1.characters,s2.characters) < 0);
    }

    bool operator >=(const string& s1, const string& s2) {
        return (strcmp(s1.characters,s2.characters) >= 0);
    }

    bool operator <=(const string& s1, const string& s2) {
        return (strcmp(s1.characters,s2.characters) <= 0);
    }

    // NON-MEMBER FUNCTIONS for the string class
    string operator +(const string& s1, const string& s2) {
        string temp;
        temp.reserve(s1.length() + s2.length() + 1);
        temp += s1;
        temp += s2;
        return temp;
    }

    string operator +(const string& s1, const char addend[ ]) {
        string temp;
        temp.reserve(s1.length() + strlen(addend) + 1);
        temp += s1;
        temp += addend;
        return temp;
    }

    std::istream& operator >> (std::istream& ins, string& target) {
        char temp;
		while(!ins.eof() && isspace(ins.peek())){						//if not end of file and theres a white space ignore the space
			ins.ignore();
		}
		target = "";
		while(!ins.eof() && !isspace(ins.peek())){						//if not end of file and theres not a white space read in the chars and add to string
			ins >> temp;
			target += temp;
		}
		return ins;
    }
}
