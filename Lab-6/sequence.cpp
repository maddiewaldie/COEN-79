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

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence::sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence::sequence(const sequence& source)
    {
        init();
        *this = source;
    }

    sequence::~sequence( ) {
        // Clear the list
        list_clear(head_ptr);

        // Reset the variables (head_ptr, tail_ptr, cursor, and precursor to NULL and many_nodes to 0)
        init();
    }

    // MODIFICATION MEMBER FUNCTIONS
    void sequence::start( ) {
        cursor = head_ptr;
        precursor = NULL;
    }

    void sequence::end() {
        precursor = list_locate(head_ptr, many_nodes - 1);
        cursor = precursor->link();
    }

    void sequence::advance( ) {
        assert(is_item());
        precursor = cursor;
        cursor = cursor->link();
    }

    void sequence::insert(const value_type& entry) {
        if(cursor == NULL){
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
        }
        else if(precursor == NULL){
            list_head_insert(head_ptr,entry);
            cursor = head_ptr;
            precursor = NULL;
        }
        else{
            list_insert(precursor, entry);
            cursor = precursor->link();
        }
        many_nodes++;
    }

    void sequence::attach(const value_type& entry) {
        if(head_ptr == NULL){
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
        }
        else if(cursor == NULL){
            list_insert(tail_ptr, entry);
            cursor = tail_ptr->link();
            precursor = tail_ptr;
            tail_ptr = cursor;	
        }
        else{
            list_insert(cursor, entry);
            precursor = cursor;
            cursor = cursor->link();
            if(cursor->link() == NULL)
                tail_ptr = cursor;		
        }
        many_nodes++;
    }

    void sequence::operator =(const sequence& source) {
        //clean up existing data
        list_clear(head_ptr);
        //copy over new object
        if(source.cursor == NULL){
            list_copy(source.head_ptr, head_ptr,tail_ptr);
            cursor = NULL;
            precursor = NULL;
        }
        else if(source.cursor == source.head_ptr){
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            precursor = NULL;
            cursor = head_ptr;
        }	
        else{
            list_piece(source.head_ptr, source.precursor, head_ptr, precursor);
            list_piece(source.cursor, source.tail_ptr, cursor, tail_ptr);
            precursor->set_link(cursor);	
        }
        many_nodes = source.size();
    }

    void sequence::remove_current( ) {
        assert(is_item());
        if(precursor == NULL){
            list_head_remove(cursor);
            cursor = head_ptr;
        }
        else{
            list_remove(precursor);
            cursor = precursor->link();
            if(precursor->link() == NULL)
                precursor = NULL;
        }
        many_nodes--;
    }
    
    // CONSTANT MEMBER FUNCTIONS
    sequence::size_type sequence::size( ) const {
        return many_nodes;
    }

    bool sequence::is_item( ) const {
        if(cursor == NULL)
            return false;
        return true;	
    }

    sequence::value_type sequence::current( ) const {
        assert(is_item());	
        return cursor->data();
    }

    
}
