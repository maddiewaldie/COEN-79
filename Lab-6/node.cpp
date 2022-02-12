// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

	// NONMEMBER FUNCTIONS TO IMPLEMENT!
	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) {
		// First, set the head and tail to be NULL
		head_ptr = NULL;
		tail_ptr = NULL;
	
		// If the linked list is empty or 1 element, we don't want to proceed
		if(start_ptr == NULL || start_ptr == end_ptr) { 
			return;	// So, we can return
		}

		// Next, a node containing start_ptr->data() can be inserted after head_ptr
		list_head_insert(head_ptr, start_ptr -> data());

		// And, we can set the tail_ptr to the head_ptr
		tail_ptr = head_ptr;
		
		// Now, we just need to traverse the list and copy the nodes
		while((start_ptr -> link() != NULL) &&  (start_ptr -> link() != end_ptr)) {
			// Insert a node containing start_ptr -> link() -> data() after the current tail_ptr
			list_insert(tail_ptr, start_ptr -> link() -> data());
			// Move the tail_ptr over
			tail_ptr = tail_ptr -> link();
			// Move the start_ptr over
			start_ptr = start_ptr -> link();
		}
	}

    size_t list_occurrences(node* head_ptr, const node::value_type& target) {
		// First, set a counter to 0, which will keep track of the occurrences of the target
		size_t count = 0;

		// Go through the list
		while(head_ptr != NULL) {
			// If the current element in the linked list equals the target, we can increment our counter
			if(head_ptr -> data() == target) {
				count++;
			}

			// Move to the next element in the list
			head_ptr = head_ptr -> link();
		}

		// Return the number of occurrences of the target in the list
		return count;
	}

    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
		// First, we need to check the preconditions
		assert((position > 0) && (position <= list_length(head_ptr) + 1));
		
		// If the position is only one, we just need to insert the entry at the head_ptr and then return
		if(position == 1) {
			list_head_insert(head_ptr, entry);
			return;
		}
		
		// Create a temporary variable to keep track of the node we're at
		node* temp = head_ptr;
		// Create a temporary variable to keep track of the position we're at
		size_t positionNumber = 1;

		// Loop through the list to the position					
		while(positionNumber < (position - 1)) {
			// Go to the next element
			temp = temp -> link();
			// Increase the position
			positionNumber++;
		}

		// Insert the element at the desired position
		list_insert(temp, entry);
	}

    node::value_type list_remove_at(node*& head_ptr, size_t position) {
		// First, we need to check the preconditions
		assert((position > 0) && (position <= list_length(head_ptr)));
		
		// Create a variable to hold a copy of the data from the removed node (we'll return this)
		node::value_type value;

		// If the position is one, we just need to remove the head node
		if(position == 1) {
			value = head_ptr -> data();
			list_head_remove(head_ptr);
			return value;
		}

		// Create a temporary variable to keep track of the node we're at
		node* temp = head_ptr;
		// Create a temporary variable to keep track of the position we're at
		size_t positionNumber = 1;

		// Loop through the list to the position
		while(positionNumber < position - 1) {
			// Go to the next element
			temp = temp -> link();
			// Increase the position
			positionNumber++;
		}

		// Set value to the element we're about to remove
		value = temp -> data();

		// Remove the value from the list
		list_remove(temp);

		// Return a copy of the data from the removed node	
		return value;
	}

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
		// First, we need to check the preconditions
		assert((1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)));

		// Create a temporary list to hold the copy (this will be returned)
		node* copyList = NULL;

		// Go through the list to the start position
		for(size_t i = 1; i < start; i++) {
			head_ptr = head_ptr -> link();
		}

		//Insert head_ptr -> data() into copyList
		list_head_insert(copyList, head_ptr -> data());

		// Create a temporary variable for adding information to the list
		node* temp = copyList;
		
		// Loop through from start to finish
		for(size_t i = start + 1; i <= finish; i++) {
			head_ptr = head_ptr -> link();
			list_insert(temp, head_ptr -> data());
			temp = temp -> link();		
		}

		// Return the copy
		return copyList;
	}

    void list_print (const node* head_ptr) {
		// Go through the list
		while(head_ptr != NULL) {
			// Print out the data at the current position of head_ptr
			std::cout << head_ptr->data();

			// Move head_ptr to the next position
			head_ptr = head_ptr->link();

			// Print a "," when appropriate
			if(head_ptr) {
				std::cout<< ", "; 
			}
		}

		// After going through the list, end the line
		std::cout << std::endl;
	}

    void list_remove_dups(node* head_ptr) {
		// Create two pointers, which will assist in comparing the elements to find duplicates
		node* comparePtr1;
        node* comparePtr2;
		// Start comparePtr1 at the head of the list
        comparePtr1 = head_ptr;
		// Traverse all the elements in the list & compare them to all the other elements in the list
        while ((comparePtr1 != NULL) && (comparePtr1->link() != NULL)) {
			// Each time we assign comparePtr2, we can just assign it to comparePtr1, as it doesn't have to re-compare with the earlier elements
            comparePtr2 = comparePtr1;
            while (comparePtr2 -> link() != NULL) {
				// If the elements are duplicates
                if ((comparePtr1 -> data()) == (comparePtr2 -> link() -> data())) {
					// Then we need to remove the duplicate!
					list_remove(comparePtr2);
				}
                else {
					// Otherwise, move to the next element
					comparePtr2 = comparePtr2 -> link();
				}
            }
        }
		
        comparePtr1 = comparePtr1 -> link();
	}

    node* list_detect_loop (node* head_ptr) {
		// Use Floyd's Cycle Detection Algorithm from class!

		// We need a slow & fast variable to keep track of
		node* slow = head_ptr;
		node* fast = head_ptr;

		// Loop through the list. Slow and Fast will meet where there's a loop!
		while((fast != NULL) && ((fast -> link() -> link()) != NULL)) {
			// Slow will move one step
			slow = slow -> link();

			// Fast will move two steps
			fast = fast -> link() -> link();
			
			// Once slow and fast are at the same spot, we know there's a loop, so we can move on!
			if(slow == fast){
				break;
			}
		}
		
		// If any of these are true, then we can return NULL, as there is no loop in the list!
		if((fast == NULL) || ((fast->link()->link()) == NULL)) {
			return NULL;
		}

		// Now, we can reset slow to the head
		slow = head_ptr;
		
		// Loop through until slow = fast, as where they meet will be the start of the loop!
		while(slow != fast) {
			// Move on to next slow & fast
			slow = slow -> link();
			fast = fast -> link();
		}

		// Return a pointer to the start of the loop
		return slow;
	}   
}
