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
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    // CONSTRUCTORS and DESTRUCTOR
    sequence::sequence()
    {
        init();
    }
    sequence::sequence(const sequence& source) {
        init();
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
        // SPECIAL CASES:
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
        //std::cout << "advance1" << endl;
        assert(is_item());
        
        if (cursor == tail_ptr)
        {
            cursor = NULL;
            return;
        }
        
        precursor = cursor;
        cursor = cursor->link();
    }

    void sequence::insert(const value_type& entry) {
        if(head_ptr == NULL)
        {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
            many_nodes++;
        }
        else if(is_item() && cursor == head_ptr)
        {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            many_nodes++;
        }
        else if(is_item() && cursor != head_ptr)
        {
            list_insert(precursor, entry);
            cursor = precursor->link();
            many_nodes++;
        }
        else if (!is_item())
        {
            list_head_insert(head_ptr, entry);
            tail_ptr = precursor->link();
            cursor = head_ptr;
            precursor = NULL;
            many_nodes++;
        }
    }
    void sequence::attach(const value_type& entry) {
        if(head_ptr == NULL)
        {
            list_head_insert(head_ptr, entry);
            precursor = NULL;
            cursor = head_ptr;
            tail_ptr = head_ptr;
            many_nodes++;
        }
        else if(is_item() && many_nodes == 1)
        {
            list_insert(head_ptr, entry);
            precursor = head_ptr;
            tail_ptr = precursor->link();
            cursor = tail_ptr;
            many_nodes++;
        }
        else if(is_item() && cursor == head_ptr)
        {
            list_insert(head_ptr, entry);
            precursor = head_ptr;
            cursor = precursor->link();
            many_nodes++;
        }
        else if(is_item() && cursor != head_ptr && cursor != tail_ptr)
        {
            list_insert(cursor, entry);
            advance();
            many_nodes++;
        }
        else if (is_item() && cursor != head_ptr)
        {
            list_insert(tail_ptr, entry);
            tail_ptr = cursor->link();
            precursor = cursor;
            cursor = tail_ptr;
            many_nodes++;
        }
        else //if(!is_item())
        {
            list_insert(tail_ptr, entry);
            precursor = tail_ptr;
            cursor = precursor->link();
            tail_ptr = cursor;
            many_nodes++;
        }
    }

    void sequence::operator =(const sequence& source) {
        list_clear(head_ptr);
        many_nodes = 0;
        node* tail;
        list_copy(source.head_ptr, head_ptr,tail);
        tail_ptr = tail;
        cursor = head_ptr;
        
        node* head = source.head_ptr;
        precursor = head_ptr;
    
        if(source.cursor == NULL)
        {
            cursor = NULL;
            precursor = tail_ptr;
        }
        else if(precursor != NULL)
            cursor = precursor->link();
        else
        {
            while(head != source.precursor)
            {
                head = head->link();
                precursor = precursor->link();
            }
        }
        many_nodes = source.many_nodes;
    }

    void sequence::remove_current() {
        assert(is_item());
        if(head_ptr->link() == NULL)
        {
            delete cursor;
            head_ptr = tail_ptr = precursor = cursor = NULL;
            many_nodes--;
        }
        else if(cursor == head_ptr && head_ptr ->link() !=NULL)
        {
            cursor = head_ptr->link();
            list_head_remove(head_ptr);
            precursor = NULL;
            many_nodes--;
        }
        else if(cursor != tail_ptr && cursor != head_ptr)
        {
            precursor->set_link(cursor->link());
            delete cursor;
            cursor = precursor->link();
            many_nodes--;
        }
        else if (cursor == tail_ptr && many_nodes > 1)
        {
            tail_ptr = precursor;
            tail_ptr->set_link(NULL);
            delete cursor;
            cursor = NULL;
            many_nodes--;
        }
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
