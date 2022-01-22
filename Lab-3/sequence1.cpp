// FILE: sequence1.cpp
// CLASS IMPLEMENTED: sequence (see sequence1.h for documentation)

// INVARIANTS OF THE CLASS:
    // If used == 0, the sequence is empty
    // If used > 0,  the items are stored in array[0] through array[used - 1]
    // We don't care what's stored in array[used] through array[CAP]

#include <stdio.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include "sequence1.h"

using namespace std;

namespace coen79_lab3
{
    // MEMBER FUNCTIONS
    void sequence::start() { // The iterator is reset to position 0
        iterator = 0; // Set the iterator position to 0
    }

    void sequence::end() { // The iterator points to the last item in the sequence
        iterator = total - 1; // The last item in the sequence would be one less than the total number of elements
    }

    void sequence::last() // The iterator is reset to CAPACITY - 1, regardless of the numebr of items in the sequence
    {
        iterator = CAPACITY - 1; // The very last item would be one less than CAPACITY
    }

    void sequence::advance() { // Move to the next item in the list
        // First, we need to check that is_item() is true 
        assert(is_item());

        // Next, we check to see if we're at the end of the sequence
        if(iterator < (CAPACITY - 1)) {
            // If we're not at the end of the sequence, we can increase the iterator's value
            iterator++;
        }
    }

    void sequence::retreat() { // Move to the previous item in the list
   // The iterator's value is reduced by 1, unless it is already at the beginning of the sequence

        // First, we need to make sure we're not the first element in the sequence
        if(iterator > 0) {
            // If we're not at the beginning of the sequence, we can decrease the iterator
            iterator--;
        }
    }

    void sequence::insert(const value_type& entry) { // Insert a new item into the array sequence
        // First, we need to check that the total elements in the sequence is less than its capacity
        assert(size() < CAPACITY);

        // Check whether there are any items in the sequence already
        if(total == 0)
        {
            // If there are no elements, insert the new entry to the front of the sequence
            array[0] = entry;   // First element is the new entry
            iterator = 0;       // Set the iterator to 0
            total++;            // Increment the total number of elements in the array
        }
        // Otherwise, add the new element to array and then shift the other elements down
        else
        {
            // Loop through the elements in the sequence
            for(size_type i = total; i > iterator; i--)
            {
                // Shift the elements down, setting the element at i to the element at the previous i
                array[i] = array[i - 1];
            }
            
            // Insert the new element into the sequence at index "iterator"
            array[iterator] = entry;
            
            // Increment the total elements in the sequence
            total++;
        }
    }

    void sequence::attach(const value_type& entry) { // A new copy of entry has been inserted in the sequence after the current item
        // First, we need to make sure the total number of elements is less than the total capacity
        assert(size() < CAPACITY);
        
        // Check whether there are any items in the sequence already
        if(total == 0)
        {
            // If there aren't any items in the sequence, insert the entry to the beginning of the sequence
            array[0] = entry;   // First element is the new entry
            iterator = 0;       // Set the iterator to 0
            total++;            // Increment the total number of elements in the array
        }
        // If the item isn't a current item in the array, attach the new entry to the end
        else if(!is_item())
        {
            array[total] = entry;   // Last element is the new entry
            iterator = total;       // Set the iterator to the total number of elements
            total++;                // Increment the total number of elements in the array
        }
        // Otherwise, we know there IS a current item in the array
        // So, we can add the new element after the current item in the array & then shift the other elements
        else
        {
            // Loop through the elements in the sequence
            for(size_type i = total; i > iterator + 1; i--) {
                // Shift the elements down, setting the element at i to the element at the previous i
                array[i] = array[i - 1];
            }

            // Add the element after the current element
            array[iterator + 1] = entry;

            // Increment the iterator
            iterator++;

            // Increment the total number of elements in the array
            total++;
        }
    }

    void sequence::remove_current() { // Remove the current item from the sequence
        // First, we need to check that is_item() returns true
        assert(is_item());

        // Loop through the sequence
        for(size_type i = iterator;i < total - 1; i++) {
            // Shift the elements up one
            array[i] = array[i + 1];
        }
        
        // Decrement the total number of elements in the sequence
        total--;
    }

    void sequence::insert_front(const value_type& entry) { // Add a new entry to the beginning of the sequence
        // First, we need to make sure the total number of elements is less than the total capacity
        assert(size() < CAPACITY);

        // Next, check whether there are any items in the sequence already
        if(total == 0)
        {
            // If there aren't any items in the sequence, insert the entry to the beginning of the sequence
            array[0] = entry;   // First element is the new entry
            iterator = 0;       // Iterator is set to 0
            total++;            // Increment the total number of elements in the sequence
        }
        // Otherwise, we need to add in the new entry to the beginning of the existing sequence
        else
        {
            // Loop through sequence
            for(size_type i = total; i > iterator; i--)
            {
                // Shift down the elements in the sequence
                array[i] = array[i-1];
            }

            // Add the new entry to the front of the sequence
            array[iterator] = entry;
            total++;        // Increment the total number of elements
            iterator = 0;   // Reset the iterator to be zero
        }
        
    }

    void sequence::attach_back(const value_type& entry) { // Add a new entry to the back of the sequence
        // First, we need to make sure the total number of elements is less than the total capacity
        assert(size() < CAPACITY);

        // Next, we can add the new entry to the back of the sequence
        array[total++] = entry;

        // And then, we need to change the iterator to be equal to the total number of elements
        iterator = total;
    }

    void sequence::remove_front() { // Remove the first item from the sequence
        // Move to the first elt in the sequence
	start();
        // We need to make sure that is_item() returns true, as it's a precondition!!
        assert(is_item());
	// The current item is the first item of the sequence, so we can just remove current!
        remove_current();
    }

    void sequence::operator +=(const sequence& rhs) { // Add the items of rhs to the lhs
        // First, we need to check the precondition that the total number of elements in the rhs + the total number of elements in the lhs is less than the total capacity 
        assert((rhs.size()+total) < CAPACITY);

        // Copy the elements from the rhs to the lhs
        copy(rhs.array, rhs.array + rhs.total, array + total);
        total += rhs.total;
    }

    /* sequence operator+=(sequence& lhs, sequence& rhs) { // Add the items of rhs to the lhs
        // First, we need to make sure the lhs and rhs's number of elements combined is less than the total capacity
        assert((lhs.size() + rhs.size()) < sequence::CAPACITY);

        // If so, we can proceed with adding the two arrays
        //copy(rhs.array, rhs.array + rhs.total, lhs.array + lhs.total);
        //lhs.total += rhs.size();

        for(int i = 0; i < rhs.size(); i++) {
            lhs.attach_back(rhs.current());
            rhs.advance();
        }

        return lhs;
    } */ 

    sequence::size_type sequence::size() const { // Return the total # of elements in the sequence
        return total;
    }

    bool sequence::is_item() const { // Indicates whether there's a valid "current" item that can be retrieved by activating the current member function (listed below)
        // Check whether or not the iterator is less than the total
        if (iterator < total) {
            // If it is, then we know we can return true (it is an item!)
            return true;
        }
        // If not, we can return false
        return false;
    }

    sequence::value_type sequence::current() const { // Returns the item in the sequence at the current position of the iterator
        // First, make sure is_item returns true
        assert(is_item());

        // If it does, then we should be able to return the item in the sequence at the current position of the iterator 
        return array[iterator];
    }

    sequence::value_type sequence::operator[](int index) const { // Returns the item stored at "index"
        // First, we need to make sure the index is less than the total number of elements in the sequence
        assert(index < int(total));

        // If all is good, we can return the item stored at index!
        return array[index];
    }

    double sequence::mean() const { // Returns the mean of the values stored in the sequence
        // The counter variable will add together the values stored in each element of the sequence
        double sum = 0.0;

        // Loop through the sequence
        for (size_type i = 0; i < total; i++)
        {
            // For each value in the sequence, add the value to the sum
            sum += array[i];
        }
        // The mean is equal to the sum divided by the total number of elements, so we will return this!
        return (sum / total);
    }

    double sequence::standardDeviation() const { // Returns the standard deviation of the values stored in the sequence
        // The standardDeviation variable will store the standard deviation of all the values stored in the sequence
        double stdev = 0.0;

        // Loop through the sequence
        for(size_type i = 0; i < total; ++i) {
            // Calculate the standard deviation!
                // We know that a general formula for standard deviation is: √(∑|x-μ|^2)/N
                    // where where ∑ means "sum of", x is a value in the data set, 
                    // μ is the mean of the data set, and N is the number of data points in the population.
                // So, the first step in calculating the standard deviation is subtracting together 
                // the element by the mean, and squaring it
            stdev += pow(array[i] - mean(), 2);
        }

        // From the formula above, the next step in calculating the standard deviation is dividing by N (or the total number of elements)
        // We can return this value!
        return sqrt(stdev / total);
    }

    // NON-MEMBER FUNCTIONS
    sequence operator +(const sequence& lhs, const sequence& rhs) { // Returns a sequence that contains all the numbers of the sequences of lsh and rhs
       // First, we need to make sure the lhs and rhs's number of elements combined is less than the total capacity
        assert((lhs.size() + rhs.size()) < sequence::CAPACITY);

        // If so, we can proceed with adding together the two sequences. We can do this by making a new sequence and adding the lhs / rhs to it.
        sequence newSequence;   // Create an empty, new sequence
        newSequence += lhs;     // Add the lhs to the new sequence
        newSequence += rhs;     // Add the rhs to the new sequence
        newSequence.start();    // Make sure the new sequence is "started"
        return newSequence;     // Return the new sequence
    }

    sequence::value_type summation(const sequence &s) { // Returns the summation of the values stored in the sequence s
        // The sum variable will contain the sum of the values in the sequence
        double sum = 0.0;

        // Loop through the sequence
        for (sequence::size_type i = 0; i < s.size(); i++)
        {
            // Add each element of the sequence to the sum
            sum+=s[i];
        }
        
        // Afterwards, return the sum!
        return sum;
    }
}


