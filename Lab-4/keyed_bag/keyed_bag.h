// FILE: keyed_bag.h
// CLASS PROVIDED: keyed_bag (part of the namespace coen79_lab4)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// TYPEDEF and MEMBER CONSTANTS for the keyed_bag class:
//   typedef ____ value_type
//     keyed_bag::value_type is the data type of the items in the keyed_bag. It may be any of
//     the C++ built-in types (int, char, etc.), or a class with a default
//     constructor, an assignment operator, and operators to
//     test for equality (x == y) and non-equality (x != y).
//
//   typedef ____ key_type
//     keyed_bag::key_type is the data type of the items used as keys for the items
//     in the keyed_bag. It may be any of the C++ built-in types (int, char, etc.),
//     or a class with a default constructor, an assignment operator, and
//     operators to test for equality (x == y) and non-equality (x != y).
//
//   typedef ____ size_type
//     keyed_bag::size_type is the data type of any variable that keeps track of how many items
//     are in a keyed_bag.
//
//   static const size_type CAPACITY = _____
//     keyed_bag::CAPACITY is the maximum number of items that a keyed_bag can hold.
//
// CONSTRUCTOR for the keyed_bag class:
//   keyed_bag( )
//     Postcondition: The keyed_bag has been initialized as an empty keyed_bag.
//
//
// MODIFICATION MEMBER FUNCTIONS for the keyed_bag class:
//   void erase();
//     Postcondition: This keyed_bag is emptied of all items and keys.
//
//   bool erase(const key_type& key);
//     Postcondition: If key was in the keyed_bag, then the key and its value have been removed;
//     otherwise the keyed_bag is unchanged. A true return value indicates that an
//     item was removed; false indicates that nothing was removed.
//
//   void insert(const value_type& entry, const key_type& key)
//     Precondition:  size( ) < CAPACITY, and the keyed_bag does not yet contain
//     the given key.
//     Postcondition: A new copy of entry has been added to the keyed_bag with
//     the corresponding key.
//
//   void operator +=(const keyed_bag& addend)
//     Precondition:  size( ) + addend.size( ) <= CAPACITY.
//     The intersection of the keyed_bags' key tables is empty (i.e. the keyed_bags)
//     share no keys.
//     Postcondition: Each item and its key in addend has been added to this keyed_bag.
//
//
// CONSTANT MEMBER FUNCTIONS for the keyed_bag class:
//   bool has_key(const key_type& key) const
//     Postcondition: The return value is whether or not the given key is in
//     the keyed_bag's list of keys.
//
//   value_type get(const key_type& key) const;
//     Precondition: has_key returns true for the given key.
//     Postcondtion: the data value corresponding to the given key is returned.
//
//   size_type size( ) const
//     Postcondition: The return value is the total number of items in the keyed_bag.
//
//   size_type count(const value_type& target) const
//     Postcondition: The return value is number of times target is in the keyed_bag.
//
//   bool hasDuplicateKey(const keyed_bag& otherBag) const
//     Postcondition: The return value is true if there is at least one key used by both this bag and the "otherBag". In other words, this function checks if there is any shared key by the two bags.
//
// NONMEMBER FUNCTIONS for the keyed_bag class:
//   keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2)
//     Precondition:  b1.size( ) + b2.size( ) <= keyed_bag::CAPACITY.
//                    The intersection of the keyed_bags' key tables is empty.
//                    (i.e. The two keyed_bag's have no keys in common.)
//     Postcondition: The keyed_bag returned is the union of b1 and b2.
//
//
// VALUE SEMANTICS for the keyed_bag class:
//    Assignments and the copy constructor may be used with keyed_bag objects.



#ifndef COEN79_KEYBAG_H
#define COEN79_KEYBAG_H

#include <cstdlib>  // Provides size_t
#include <string>

using namespace std;

namespace coen79_lab4
{
    class keyed_bag
    {
    public:
        // TYPEDEFS and MEMBER CONSTANTS
        typedef int value_type;
        typedef string key_type;
        typedef std::size_t size_type;
        static const size_type CAPACITY = 30;

        // CONSTRUCTOR
        keyed_bag() {
            // First, we need to set the total number of elements to 0, as the keyed_bag is empty
            total = 0;

            // Next, we need to loop through the keys and data arrays to assign them "blank" values, as there aren't any keys or data yet
            for (int i = 0; i < int(CAPACITY); i++)
            {
                keys[i] = "";   // The keys are of key_type string, so we can set each element to an empty string
                data[i] = 0;    // The data is of value_type int, so we can set each element to the int 0
            }
        }

        // MODIFICATION MEMBER FUNCTIONS
        void erase();                                               // Empty keyed_bag of all its items and keys
        bool erase(const key_type& key);                            // If there's a key that matches the given key in the keyed_bag, then remove the key & its value
        void insert(const value_type& entry, const key_type& key);  // Insert a given entry to the keyed_bag with the corresponding key
        void operator +=(const keyed_bag& addend);                  // Add each item and its key in addend to this keyed_bag

        // CONSTANT MEMBER FUNCTIONS
        bool has_key(const key_type& key) const;                // Check whether or not the given key is in the keyed_bag's list of keys
        value_type get(const key_type& key) const;              // Return the data corresponding to the given key
        size_type size() const;                                 // Return the total number of elements in the bag
        size_type count(const value_type& target) const;        // Return the number of times the given target is in the bag
        bool hasDuplicateKey(const keyed_bag& otherBag) const;  // Check if the bag has a duplicate key

    private:
        size_type total;            // The total number of elements in the bag
        key_type keys[CAPACITY];    // The array to store the keys 
        value_type data[CAPACITY];  // The array to store items
    };

    // NONMEMBER FUNCTIONS for the keyed_bag class
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2); // Add together two keyed_bags
}

#endif
