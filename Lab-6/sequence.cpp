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
    sequence::sequence(const sequence& source)
    {
        init();
        *this = source;
    }
    sequence::~sequence()
    {
        list_clear(head_ptr);
        many_nodes = 0;
    }

    // MODIFICATION MEMBER FUNCTIONS
    void sequence::start()
//     Postcondition: The precursor and cursor are adjusted such that the first
//     item in the sequence becomes the current item (but if the sequence is
//     empty, then there is no current item).
    {
        precursor = head_ptr;
        cursor = head_ptr;
    }
    void sequence::end()
//     Postcondition: The precursor and cursor are adjusted such that the last
//     item in the sequence becomes the current item (but if the sequence is
//     empty, then there is no current item).
    {
        cursor = tail_ptr;
        if(many_nodes == 0)
            cursor = precursor = NULL;
        if(head_ptr == tail_ptr)
            precursor = NULL;
        precursor = head_ptr;
        while(precursor->link() != cursor)
            precursor = precursor->link();
    }
    void sequence::advance()
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item in the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
    {
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

    void sequence::insert(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence
//     before the current item. If there was no current item, then the new entry
//     has been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
    {
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
    void sequence::attach(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
    {
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
    void sequence::operator =(const sequence& source)
    {
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

    void sequence::remove_current()
//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequence, and
//     the item after this (if there is one) is now the new current item.
    {
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
    sequence::size_type sequence::size() const
    {
        return many_nodes;
    }
    bool sequence::is_item() const
    {
        return (cursor != NULL);
    }
    sequence::value_type sequence::current() const
    {
        assert(is_item());
        return cursor->data();
    }

    
}
