// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    // CONSTRUCTORS
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...

        // Assign the given company name to this company name
        this -> company_name = company_name;
        // Assign the head pointer to NULL initially
        this -> head_ptr = NULL;
        // Assign the tail pointer to NULL initially
        this -> tail_ptr = NULL;
    }
    
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...

        // Use the list_copy function to set head_ptr and tail_ptr to the head and tail pointers for the given list
        list_copy(src.head_ptr, head_ptr, tail_ptr);
        // Set the company name to the given company's  name
        company_name = src.company_name;
    }

    // ASSIGNMENT OPERATOR
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...

        // If this object and the given object are the same, we don't need to do anything!
        if(this == &src) {
            // So, just return this object
            return *this;
        }
        // Otherwise, use the list_copy function to set head_ptr and tail_ptr to the head and tail pointers for the given list
        list_copy(src.get_head(), head_ptr, tail_ptr);
        // Set this company name to the given object's company name
        company_name = src.company_name;

        // Return this object
        return *this;
    }
    
    // DESTRUCTOR
    company::~company() {
        list_clear(head_ptr);
    }
    
    // MEMBER FUNCTIONS
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            // COMPLETE THE IMPLEMENTATION...

            // Figure out the new head pointer
            node* head = new node(product_name, price);
            // Reassign the head & tail
            head_ptr = head;
            tail_ptr = head_ptr;
        }
        else {
            // COMPLETE THE IMPLEMENTATION...
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }

    
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...

        // Create a pointer to the product in the list
        node *product = list_search(head_ptr, product_name);

        // If the item was never found, we just return false
        if(product == NULL) {
            return false;
        }
        // Swt the product to the head & then remove the head (effectively removing the product)
        product->setName(head_ptr->getName());
        product->setPrice(head_ptr->getPrice());
        list_head_remove(head_ptr);
        // Return true, as we removed the product
        return true;
    }
    
    
}
