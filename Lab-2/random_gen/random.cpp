// FILE: random.cpp
// CLASS IMPLEMENTED: random (see random.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "random.h"

using namespace std;

namespace coen79_lab2
{
    void rand_gen::set_seed(int newSeed) // Setter method to access the seed variable
    {
        // Change the value of the seed to the new seed
        seed = newSeed;
    }
    int rand_gen::next() // Getter method to return value of seed
    {
	// Check that mod isn't equal to 0 (it won't work!)
	assert(mod != 0);
        // Set seed to the equation specified in the lab document
        seed = (multiplier * seed + increment) % mod;

        // Return the new seed
        return seed;
    }
    void rand_gen::print_info()
    {
        // Print out the seed, multiplier, increment, and mod
        cout << "Seed: " << seed << endl;
        cout << "Multiplier: " << multiplier << endl;
        cout << "Increment: " << increment << endl;
        cout << "Modulus: " << mod << endl;
    }
}


