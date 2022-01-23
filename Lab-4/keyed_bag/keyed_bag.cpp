// FILE: keyed_bag.cpp
// CLASS IMPLEMENTED: keyed_bag (see keyed_bag.h for documentation)

// INVARIANTS OF THE CLASS:
    // If total == 0, the keyed_bag is empty
    // If total > 0, the keys are stored in keys[0] through keys[total - 1], and the data is stored in data[0] through data[total - 1]
    // We don't care what's stored in keys[total] through array[CAPACITY] or data[total] through data[CAPACITY]

#include <stdio.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4
{
    // MODIFICATION MEMBER FUNCTIONS
    void keyed_bag::erase() { // Empty keyed_bag of all its items and keys
        // Loop through the bag
        for (size_type i = 0; i < CAPACITY; i++) {
            keys[i] = "";   // Set all of the keys to an empty string
            data[i] = 0;    // Set all of the data to be 0
        }

        // Next, because the bag's empty, we need to set the total to 0
        total = 0;
    }

    bool keyed_bag::erase(const key_type& key) { // If there's a key that matches the given key in the keyed_bag, then remove the key & its value
        // First, check whether or not the key is present
        if(!has_key(key)) {
            return false; // If it's not present, we can exit the function right away & return false, as nothing was removed
        }

        // Loop through the entire array
        for(size_type i = 0; i < total; i++) {
            // If the key at i matches the given key
            if(key == keys[i]) {
                // Shift the rest of the elements over
                for(size_type j = i; j < total - 1; j++) {
                    keys[j] = keys[j+1]; // Shift the keys over one
                    data[j] = data[j+1]; // Shift the data over one
                }

                // Because we took out the key & its value, we need to decrement the total
                total--;
            }
        }

        // Finally, after erasing the key and its data, we can return true
        return true;
        
    }

    void keyed_bag::insert(const value_type& entry, const key_type& key) { // Insert a given entry to the keyed_bag with the corresponding key
        // First, we need to make sure the size is less than the capacity
        assert(size() < CAPACITY);

        // If the key is not already in bag, we can add it!
        if (!has_key(key)) {
            keys[total] = key;      // Insert the key into the end of the keys array
            data[total] = entry;    // Insert the entry into the end of the data array
            total++;                // Increment the total elements in the bag   
        }
    }

    void keyed_bag::operator +=(const keyed_bag& addend) { // Add each item and its key in addend to this keyed_bag
        // First, we need to make sure the total elements in this bag and the given bag is less than or equal to the capacity
        assert(size() + addend.size() <= CAPACITY);

        // Copy the data from addednd to the data of this bag
        copy(addend.data, addend.data + addend.total, data + total);

        // Copy the keys from addednd to the keys of this bag
        copy(addend.keys, addend.keys + addend.total, keys + total);
        
        // Add the two totals together, as well
        total += addend.total;
    }

    // CONSTANT MEMBER FUNCTIONS
    bool keyed_bag::has_key(const key_type& key) const { // Check whether or not the given key is in the keyed_bag's list of keys
        // Loop through the bag
        for (size_type i = 0; i < size(); i++) {
            // Check if the key at index i is equal to the given key
            if (keys[i] == key) {
                return true; // If so, then return true
            }
        }

        // Otherwise, return false
        return false;
    }

    keyed_bag::value_type keyed_bag::get(const key_type& key) const { // Return the data corresponding to the given key
        // First, make sure the key is present in the keyed_bag
        assert(has_key(key));

        // Loop through the bag
        for (size_type i = 0; i < size(); i++) {
            // If the key at i is equal to the given key, we know this is what we want to return
            if(keys[i] == key) {
                return data[i]; // So, return the data at the key
            }
        }
    }

    keyed_bag::size_type keyed_bag::size() const { // Return the total number of elements in the bag
        return total;
    }

    keyed_bag::size_type keyed_bag::count(const value_type& target) const { // Return the number of times the given target is in the bag
        // Count will keep track of the number of times the target is present
        size_type count = 0;

        // Loop through the bag
        for (size_type i = 0; i < size(); i++) {
            // If the target's present, increment the counter
            if (target == data[i]) {
                count++;
            }
        }

        // Return the number of times target is present
        return count;
    }

    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const { // Check if the bag has a duplicate key
        // Loop through the other bag
        for (size_type i = 0; i < otherBag.size(); i++) {
            // Loop through this bag
            for (size_type j = 0; j < size(); j++) {
                // If they share any keys, then return true, as there's a duplicate
                if (otherBag.keys[i] == keys[j]) {
                    return true;
                }
            }
        }

        // Otherwise, we know there aren't any duplicate keys, so we can return false
        return false;
    }

    // NONMEMBER FUNCTIONS for the keyed_bag class
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2) { // Add together two keyed_bags
        // First, we need to check the precondition that the size of both bags is less than the capacity
        assert((b1.size() + b2.size()) < keyed_bag::CAPACITY);

        // Create a new bag, which will store the sum of both the bags
        keyed_bag newBag;

        // Add each bag to the new bag        
        newBag += b1;
        newBag += b2;

        // Return the new bag
        return newBag;

    }
}