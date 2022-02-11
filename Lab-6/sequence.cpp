//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;

        //Initializing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    // CONSTRUCTORS and DESTRUCTOR
    sequence::sequence()
    {
        // Initialize the pointers / variables for the sequence
        init();
    }
    sequence::sequence(const sequence& source) {
        // Initialize the pointers / variables for the sequence
        init();

        // Set this sequence to the provided sequence
        *this = source;
    }
    sequence::~sequence() {
        // Clear the list
        list_clear(head_ptr);

        // And, set the number of nodes to 0
        many_nodes = 0;
    }

    // MODIFICATION MEMBER FUNCTIONS
    void sequence::start() {
        // When we go to the start, the precursor and cursor get set to each other! (the first item in the sequence becomes the current item)
        precursor = head_ptr;
        cursor = head_ptr;
    }

    void sequence::end() {
        // When we go to the end, the cursor is set to the tail_ptr
        cursor = tail_ptr;

        // In the case that there are 0 nodes, cursor and precursor are just NULL
        if(many_nodes == 0) {
            cursor = NULL;
            precursor = NULL;
            return;
        }

        // Additionally, if the head_ptr is equal to the tail_ptr, we know there's only one element, so the precursor would be NULL
        if(head_ptr == tail_ptr) {
            precursor = NULL;
            return;
        }

        // Set precursor to the first item in the list (so we can go from the beginning to cursor - 1)
        precursor = head_ptr;

        // Loop through the list and "increment" the precursor until it's one before the cursor
        while((precursor -> link()) != cursor) {
            precursor = precursor -> link();
        }
    }
    void sequence::advance() {
        // First, check the precondition that is_item is true
        assert(is_item());
        
        // If cursor's at the end, we know the next element would be NULL
        if (cursor == tail_ptr) {
            cursor = NULL;
            return;
        }
        
        // Set the precursor to the cursor & increment the cursor
        precursor = cursor;
        cursor = cursor -> link();
    }

    void sequence::insert(const value_type& entry) {
        // We can break this into a few different cases!

        // If the sequence is empty
        if(head_ptr == NULL) {
            // Add the element to the sequence
            list_head_insert(head_ptr, entry);
            // Update the tail, cursor, and precursor
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
        }
        else if(is_item() && (cursor == head_ptr)) {
            // Add the element to the sequence
            list_head_insert(head_ptr, entry);
            // Update the cursor and precursor
            cursor = head_ptr;
            precursor = NULL;
        }
        else if(is_item() && (cursor != head_ptr)) {
            // Add the element to the sequence
            list_insert(precursor, entry);
            // Update the cursor
            cursor = precursor->link();
        }
        else if (!is_item()) {
            // Add the element to the sequence
            list_head_insert(head_ptr, entry);
            // Update the tail, cursor, and precursor
            tail_ptr = precursor->link();
            cursor = head_ptr;
            precursor = NULL;
        }
        // Increment the number of nodes in the sequence
        many_nodes++;
    }
    void sequence::attach(const value_type& entry) {
        // We can split this into 6 different cases!

        // First, if the list is empty
        if(head_ptr == NULL) {
            // Add the element to the sequence
            list_head_insert(head_ptr, entry);
            // Set the precursor to NULL (there isn't any other element to point to)
            precursor = NULL;
            // And, the cursor and tail will also have to equal the head
            cursor = head_ptr;
            tail_ptr = head_ptr;
        }
        // If there's only one node in the sequence
        else if((is_item()) && (many_nodes == 1)) {
            // Add the element to the sequence
            list_insert(head_ptr, entry);
            // Set the precursor, tail, and cursor
            precursor = head_ptr;
            tail_ptr = precursor -> link();
            cursor = tail_ptr;
        }
        // If the cursor is equal to the head pointer
        else if((is_item()) && (cursor == head_ptr)) {
            // Add the element to the sequence
            list_insert(head_ptr, entry);
            // Set the precursor and cursor
            precursor = head_ptr;
            cursor = precursor -> link();
        }
        // If the item isn't the head or tail
        else if((is_item()) && (cursor != head_ptr) && (cursor != tail_ptr)) {
            // Add the element to the sequence
            list_insert(cursor, entry);
            advance();
        }
        // If the item isn't the head
        else if (is_item() && cursor != head_ptr) {
            // Add the element to the sequence
            list_insert(tail_ptr, entry);
            // Set the precursor, tail, and cursor
            tail_ptr = cursor -> link();
            precursor = cursor;
            cursor = tail_ptr;
        }
        else { // If it isn't the item!
        // Add the element to the sequence
            list_insert(tail_ptr, entry);
            // Set the precursor, tail, and cursor
            precursor = tail_ptr;
            cursor = precursor -> link();
            tail_ptr = cursor;
        }
        
        // Increment the number of nodes in the sequence
        many_nodes++;
    }

    void sequence::operator =(const sequence& source) {
        // If the source is the same as the object, we can just return (there's nothing more to do!!)
        if (this == &source) {
            return;
        }

        // Reset this sequence, getting ready to copy over the new sequence
        many_nodes = 0;
        list_clear(head_ptr);

        // Make a pointer, which will hold the tail of the copy
        node* newTail;

        // Copy over the provided sequence to this sequence
        list_copy(source.head_ptr, head_ptr, newTail);

        // Set the cursor and precursor to generic locations, which will be adjusted below
        cursor = head_ptr;
        tail_ptr = newTail;
        precursor = head_ptr;

        // Create a temporary pointer to keep track of location in while loop below
        node *tempPtr = source.head_ptr;

        // If the given sequence's cursor is NULL, we can set this cursor to NULL, and we know the precursor will have to be the tail
        if (source.cursor == NULL) {
            precursor = tail_ptr;
            cursor = NULL;
        }
        // Loop through and make sure the cursor and precursor are in the right location!
        else {
            // Move the precursor over until it's in the right place
            while (tempPtr != source.precursor) {
                precursor = precursor -> link();
                tempPtr = tempPtr -> link();
            }
            // Move the cursor over to the correct place
            if (precursor != NULL) {
                cursor = precursor -> link();
            }
        }

        // Set the number of nodes to the number of nodes in the given sequence
        many_nodes = source.many_nodes;
    }

    void sequence::remove_current() {
        // First, check the precondition that is_item is true
        assert(is_item());

        // We can split this into four different cases!

        // If we're deleting an item from a one item sequence
        if((head_ptr -> link()) == NULL)
        {
            // Delete the element
            delete cursor;
            // All the pointers will need to point to NULL
            head_ptr = NULL;
            tail_ptr = NULL;
            precursor = NULL;
            cursor = NULL;
        }
        // If the cursor is the head pointer, and there IS a next element in the sequence
        else if((cursor == head_ptr) && (head_ptr -> link() != NULL))
        {
            // Set the new cursor to be the next item in the sequence
            cursor = head_ptr -> link();
            // Remove the head_ptr
            list_head_remove(head_ptr);
            // Because it's at the beginning of the sequence, the precursor is just NULL
            precursor = NULL;
        }
        // If the cursor isn't at the beginning or end of the sequence
        else if((cursor != tail_ptr) && (cursor != head_ptr))
        {
            // Set the new precursor
            precursor -> set_link(cursor -> link());
            // Delete the current cursor
            delete cursor;
            // Update the cursor to be the element next to the precursor
            cursor = precursor -> link();
        }
        // If the cursor is at the end of the sequence, and there are multiple nodes in the sequence
        else if ((cursor == tail_ptr) && (many_nodes > 1))
        {
            // Set the new tail to the precursor (which will be the current second to last element)
            tail_ptr = precursor;
            // Set the tail pointer to NULL
            tail_ptr -> set_link(NULL);
            // Delete the cursor & set it to NULL
            delete cursor;
            cursor = NULL;
        }

        // Decrement the number of nodes, as we removed an element from the sequence
        many_nodes--;
    }

    // CONSTANT MEMBER FUNCTIONS
    sequence::size_type sequence::size() const {
        // Return the number of nodes in the sequence!
        return many_nodes;
    }

    bool sequence::is_item() const {
        // Check whether or not the cursor is NULL
        if(cursor == NULL) {
            return false; // If it is NULL, return false!
        }

        // Otherwise, we know it's an item so we can return true!
        return true;
    }

    sequence::value_type sequence::current() const {
        // First, check the precondition that the current spot is an item
        assert(is_item());

        // If it is, we can return cursor -> data()
        return cursor -> data();
    }
}
