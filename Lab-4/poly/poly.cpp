// FILE: poly.cpp
// CLASS IMPLEMENTED: poly (see poly.h for documentation)

// INVARIANTS OF THE CLASS:
    // 

#include <stdio.h>
#include <iostream>
#include <cassert>
#include <climits>
#include <cmath>
#include "poly.h"

using namespace std;

namespace coen79_lab4
{
    // CONSTRUCTOR
    polynomial::polynomial(double c, unsigned int exponent) {
        // First, we need to satify the precondition that the exponent is less than or equal to the max degree!
        assert(exponent <= MAXIMUM_DEGREE);

        // Loop through the array and set all coefficients to 0 (as there aren't any yet!)
        for(int i = 0; i <= int(MAXIMUM_DEGREE); i++) {
            array[i] = 0; // Set to 0
        }
        // Set the coefficient to c!
        array[exponent] = c;

        // Set the current degree to the exponent of the polynomial!
        currentDegree = exponent;
    }

    // HELPER MEMBER FUNCTIONS
    void polynomial::update_current_degree() { // Set the current degree to the highest exponent with a non-zero coefficient
        // First, set the current degree to 0
        currentDegree = 0;

        // Next, loop through the array of coefficients, from the highest degree to the lowest degree
        for (int i = int(polynomial::MAXIMUM_DEGREE); i > 0; i--) {
            // Check whether or not the coefficient is 0
            if (array[i] != 0) {
                // If the coefficient isn't 0, we need to set the current degree to the degree corresponding to the coefficient (i)
                currentDegree = i;
                // And, we don't need to keep searching, so we can break
                break;
            }
        }
    }

    // MODIFICATION MEMBER FUNCTIONS
    void polynomial::assign_coef(double coefficient, unsigned int exponent) { // Set the coefficient for the specified exponent
        // First, check that the given exponent is less than / equal to the max value it could be
        assert(exponent <= MAXIMUM_DEGREE);

        // Set the coefficient at the given exponent to the given coefficient
        array[exponent] = coefficient;

        // Set the current degree to the highest exponent with a non-zero coefficient
        update_current_degree();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent) { // Add the given amount to the coefficient of the specified exponent
        // First, check that the given exponent is less than / equal to the max value it could be
        assert(exponent <= MAXIMUM_DEGREE);

        // Add the given amount to the coefficient at the given exponent
        array[exponent] += amount;

        // Set the current degree to the highest exponent with a non-zero coefficient
        update_current_degree();
    }

    void polynomial::clear() { // Resets all the coefficients of the polynomial to zero
        // Set all the coefficients in the array to 0
        for(int i = 0; i < int(polynomial::MAXIMUM_DEGREE) + 1; i++) {
            array[i] = 0;
        }

        // Set the current degree to the highest exponent with a non-zero coefficient
        update_current_degree();
    }

    // CONSTANT MEMBER FUNCTIONS
    polynomial polynomial::antiderivative() const { // Return the antiderivative (indefinite integral) of the polynomial
        // First, make sure the degree is less than the max it could be
        assert(degree() < MAXIMUM_DEGREE);

        // Create a temporary polynomial to store the antiderivative (we will return this!)
        polynomial antiDeriv;

        // Loop through the polynomial and calculate the antiderivative
        for (int i = 0; i <= int(currentDegree); i++)
        {
            // Assign each term to its antiderivative
            antiDeriv.assign_coef(coefficient(i) * pow(i + 1, -1), i + 1);
        }

        // Return the antiderivative
        return antiDeriv;
    }

    double polynomial::coefficient(unsigned int exponent) const { // Return the coefficient at a specified exponent of the polynomial
        return array[exponent];
    }

    double polynomial::definite_integral(double x0, double x1) const { // Return the definite integral from x0 to x1
        // Because we already have a function to make the definite integral, all we have to do is
        // return the antiderivative at x1 minus the antiderivative at x0
        return (antiderivative()(x1) - antiderivative()(x0));
    }

    unsigned int polynomial::degree() const { // Return the value of the largest exponent with a non-zero coefficient
        return currentDegree;
    }

    polynomial polynomial::derivative( ) const { // Return the first derivative of the polynomial
        // First, we need to make sure the degree is less than the max it can be
        assert(degree() < MAXIMUM_DEGREE);

        // Next, we can make a temporary polynomial to store the derivative (we'll return this!)
        polynomial deriv;

        // Lop through the polynomial
        for (int i = 0;i <= int(currentDegree); i++) {
            deriv.array[i - 1] = (array[i] * i); //everything shifts left and coefficients are multiplied by their old exponent
        }

        // Set the current degree to the highest exponent with a non-zero coefficient
        deriv.update_current_degree();

        // Return the derivative!
        return deriv;
    }

    double polynomial::eval(double x) const { // Return the value of the polynomial with the given value for the variable x
        // First, we should make a variable to store the value of the polynomial (we'll return this!)
        double sum = 0.0;

        // Loop through the polynomial
        for (int i = 0; i < int(MAXIMUM_DEGREE) + 1 ; i++) {
            // Add up the elements of the polynomial, given x
            sum += array[i] * pow(x, i);
        }

        // Return the value of the polynomial, given x
        return sum;
    }

    bool polynomial::is_zero( ) const { // Check if the polynomial is the zero polynomial
        // If the polynomial's zero
        if ((currentDegree == 0) && (array[0] == 0)) {
            return true; // Then, we should return true!
        }

        // Otherwise, return false!
        return false;
    }

    unsigned int polynomial::next_term(unsigned int e) const { // Return the next exponent, n, which is LARGER than e such that coefficient(n) != 0
        // Loop through the polynomial from e to the max degree (as we don't care about anything less than e in this case)
        for(int i = e; i < int(polynomial::MAXIMUM_DEGREE); i++) {
            // If the next element isn't 0
            if(array[i + 1] != 0) {
                return i + 1; // Then, we should return i + 1!
            }
        }

        // Otherwise, return 0!
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const { // Return the next exponent, n, which is SMALLER than e such that coefficient(n) != 0
        // Loop through all the terms with an exponent less than e
        for(int i = int(e); i > 0; i--) {
            // If the previous element isn't 0
            if(array[i-1] != 0) {
                return i - 1; // Then we should return i - 1!
            }
        }

        // Otherwise, return UINT_MAX!
        return UINT_MAX;
    }

    // CONSTANT OPERATORS
    double polynomial::operator() (double x) const { // Same as eval
        return eval(x);
    }

    // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2) { // Return the sum of the two polynomials as a polynomial
        // First, we should make a temporary polynomial to store the sum of the two
        polynomial sum;

        // Next, we can loop through the polynomial and add the terms together
        for (int i = 0; i < int(polynomial::MAXIMUM_DEGREE) + 1; i++) {
            sum.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
        }
        
        // Finally, we can return the sum of the two polynomials, as a polynomial!
        return sum;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) { // Return the difference of the two polynomials as a polynomial 
        // Because we're going to subtract p2 from p1, we can set a the difference to p1
        polynomial diff = p1;

        // Next, we can loop through the polynomial and subtract the terms
        for (int i = 0; i < int(polynomial::MAXIMUM_DEGREE) + 1; i++) {
            diff.add_to_coef(-1 * p2.coefficient(i), i);
        }

        // Finally, we can return the difference, as a polynomial!
        return diff;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) { // Return the product of the two polynomials as a polynomial
        // First, we need to make sure the sum of the two polynomials' degrees is less than / equal to the max degree allowed
        assert((p1.degree() + p2.degree()) <= polynomial::MAXIMUM_DEGREE);

        // Next, we can make a temporary polynomial to store the product of the two polynomials
        polynomial product;

        // Loop through the first polynomial
        for (int i =0; i <= int(p1.degree()); i++) {
            // Loop through the second polynomial
            for(int j = 0;j <= int(p2.degree()); j++){
                // Multiply the coefficients together & add the degrees
                product.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
            }
        }

        // Finally, we can return the product of the two polynomials!
        return product;
    }
    
    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p) { // Print out the polynomial
    	int i;
        unsigned int d = p.degree();
        bool zero = true;
        for(i = int(d); i >= 0; i--){
            if(p.coefficient(i) != 0) {

                zero = false;
                if (p.coefficient(i) >= 0 && i != int(d)) {
                    out << "+ ";
                }
                if (p.coefficient(i) < 0) {
                    out << "- ";
                }

                out << abs (p.coefficient(i));

                if((p.coefficient(i) % 1) == 0) {
                    out << .0;
                }

                if (i != 0 && i != 1) {
                    out << "x^" << i << " ";
                } else if (i == 1) {
                    out << "x ";
                }
            }

        }

        if(zero) out << 0.0;

        return out;            
    }
}
