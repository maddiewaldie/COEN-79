// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2
{

    // Constructor
    statistician::statistician(){
        // Set the count and total sum to 0, as the sequence is empty
        count = 0;
        totalSum = 0;
    }

    // Public modification member functions
    void statistician::next(double r){ // Add a number to the sequence
        // Because we're adding another number, increase the count of elements and the total sum of the sequence
        count ++;
        totalSum += r;

        // If the length is one, we know this number is BOTH the min & max of the sequence
        if(length() == 1)
        {
            min = r;
            max = r;
        }
        // Otherwise, check if the number is the min or max by comparing it against the current ones
        else
        {
            if(r > max) { // See if r is greater than max
                max = r;
            }
        	if(r < min) { // See if r is smaller than min
                min = r;
            }
        }
    }
 
    void statistician::reset(){ // Erase the sequence
        // Set the count and total sum to 0, as the sequence is empty
        count = 0;
        totalSum = 0;
    }
    
    // Public constant member functions
    int statistician::length() const { // Return the number of values in the sequence
        return count; 
    }     
    
    double statistician::sum() const { // Return the sum of the numbers in the sequence
        return totalSum; 
    }

    double statistician::mean() const{ // Return the mean of the numbers in the sequence
        assert(length() > 0);
        return sum()/length();
    }
    
    double statistician::minimum() const{ // Return the smallest number in the sequence
        assert(length() > 0);
        return min;
    }
    
    double statistician::maximum() const{ // Return the largest number in the sequence
        assert(length() > 0);
        return max;
    }
    
    // Non member functions for the statistician class
    statistician operator +(const statistician& s1, const statistician& s2) {
        statistician s;
        s.count = s1.count + s2.count;
        s.totalSum = s1.totalSum + s2.totalSum;
        s.min = (s1.min < s2.min) ? s1.min : s2.min; // Compare min of s1 and s2
        s.max = (s1.max > s2.max) ? s1.max : s2.max; // Compare max of s1 and s2
         
        return s;
    }
    
    statistician operator *(double scale, const statistician& s)
    {
        statistician u;
        u.count = s.count; // Contains the same numbers that s does
        u.totalSum = (scale*s.totalSum);
        u.min = (scale*s.min);
        u.max = (scale*s.max);
	
        if(scale < 0) // Check if negative scale and set min and max accordingly
        {
            u.min = (scale*s.max);
            u.max = (scale*s.min);
        }
            return u;
    }

    bool operator ==(const statistician& s1, const statistician& s2)
    {
        if(s1.length() == s2.length() &&
           s1.mean() == s2.mean() &&
           s1.minimum() == s2.minimum() &&
           s1.maximum() == s2.maximum() &&
           s1.sum() == s2.sum()) {
               return true;
        }
        
        // Else, they're not equal, so return false
        return false;
    }
    
}


