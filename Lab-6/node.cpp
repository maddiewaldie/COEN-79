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
		head_ptr = NULL;
		tail_ptr = NULL;
	
		if(start_ptr == NULL || start_ptr == end_ptr)
			return;

		
		list_head_insert(head_ptr, start_ptr->data());
		tail_ptr = head_ptr;
									//copy the nodes and traverse the list
		while(start_ptr->link() != NULL &&  start_ptr->link() != end_ptr){
			list_insert(tail_ptr, start_ptr->link()->data());
			tail_ptr = tail_ptr->link();
			start_ptr = start_ptr->link();
		}
	}

    size_t list_occurrences(node* head_ptr, const node::value_type& target) {
		size_t count = 0;
		while(head_ptr != NULL){				//traverse to end of list
			if(head_ptr->data() == target)
				count++;
			head_ptr = head_ptr->link();
		}
		return count;
	}

    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
		assert(position > 0);
		assert(position <= list_length(head_ptr)+1);
		
		if(position == 1){
			list_head_insert(head_ptr, entry);
			return;
		}
		
		node* temp = head_ptr;
		size_t pos_count = 1;
								//iterate to position						
		while(pos_count < position -1){
			temp = temp->link();
			pos_count++;
		}
		list_insert(temp, entry);
	}

    node::value_type list_remove_at(node*& head_ptr, size_t position) {
		assert(position >0);
		assert(position <= list_length(head_ptr));
		
		node::value_type value;
		if(position == 1){
			value = head_ptr->data();
			list_head_remove(head_ptr);
			return value;
		}

		node* temp = head_ptr;
		size_t pos_count = 1;
								//iterate to position
		while(pos_count < position - 1){
			temp = temp->link();
			pos_count++;
		}
		value = temp->data();
		list_remove(temp);		
		return value;
	}

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
		assert(1 <= start);
		assert(start <= finish);
		assert(finish <= list_length(head_ptr));

		node* temp_head = NULL;
								//traverse to start pos
		for(int i = 1; i < start; i++){
			head_ptr =head_ptr->link();
		}
		list_head_insert(temp_head,head_ptr->data());
		//std::cout << list_length(temp_head) << endl;
		node* temp_trav = temp_head;
								//copy and traverse to finish
		for(int i = start + 1; i<=finish; i++){
			head_ptr = head_ptr->link();
			list_insert(temp_trav, head_ptr->data());
			temp_trav = temp_trav->link();		
		} 
		return temp_head;
	}

    void list_print (const node* head_ptr) {
		while(head_ptr != NULL){
			std::cout << head_ptr->data() ;
			head_ptr = head_ptr->link();
			if(head_ptr)
				std::cout<< ", "; 
		}
		std::cout << std::endl;
	}

    void list_remove_dups(node* head_ptr) {
		if(head_ptr->link() == NULL)
			return;
									//traverse and check for multiple occurences. If present remove the head
		
		while(head_ptr != NULL){
			int occ = (list_occurrences(head_ptr, head_ptr->data()));
			//std::cout <<"occ " << occ<<std::endl;
			while (occ >1){
				node* to_del= list_search(head_ptr->link(), head_ptr->data());
				node* cursor;
				for(cursor = head_ptr; cursor->link() != to_del; cursor = cursor->link());
					list_remove(cursor);
				
				//std::cout <<  "removed " << list_length(head_ptr) << std::endl;
				occ--;
			}
			head_ptr = head_ptr->link();			
		}
	}

    node* list_detect_loop (node* head_ptr) {
		node* slow = head_ptr;
		node* fast = head_ptr;
									//go through and if slow and fast meet there is a loop		
		while(fast != NULL && fast->link()->link() != NULL){
			slow = slow->link();
			fast = fast->link()->link();
			
			if(slow == fast){
				break;
			}
		}
		
		if(fast == NULL || fast->link()->link() == NULL)
			return NULL;

		slow = head_ptr;					//where slow and fast meet is the start of the loop
		while(slow != fast){
			slow = slow->link();
			fast = fast->link();
		}
		return slow;
	}
    
}
