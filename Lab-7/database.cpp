// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...

        // Set this object's variables to the given object's variables
        aloc_slots = src.aloc_slots;
        used_slots = src.used_slots;

        // Set this object's company array to the given object's one
        company_array = new company[aloc_slots];
        *company_array = *src.company_array;
    }
    
    
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...

        // If this object equals the given object, we don't need to do anything
        if(this == &rhs) {
            // So, we can simply return this object!
            return *this;
        }
        // Get rid of the current company array, and then copy over the given company array into a new one
        delete [] company_array;
        company_array = new company[rhs.aloc_slots];
        std::copy(rhs.company_array, rhs.company_array + rhs.used_slots, company_array);

        // Set this object's variables to the given object's variables
        used_slots = rhs.used_slots;
        aloc_slots = rhs.aloc_slots;
        return *this;
    }
    
    
    database::~database() {
        // COMPLETE THE IMPLEMENTATION...

        // Deallocate the memory & reset the variables to 0
        delete [] company_array;
        aloc_slots = 0;
        used_slots = 0;
    }
    
    
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        // COMPLETE THE IMPLEMENTATION...
        // In a temporary variable, change the database's current capacity to the new_capacity
        company* temp = new company[new_capacity];
        // Copy over the elements
        std::copy(company_array, company_array + used_slots, temp);
        // Get rid of the current array
        delete[] company_array;
        
        // Set the company_array to the temp array
        company_array = temp;
        aloc_slots = new_capacity;
    }
    
    
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (int(pos) != COMPANY_NOT_FOUND) {
            return false;
        }

        // COMPLETE THE IMPLEMENTATION...
        reserve(aloc_slots+1);
        company_array[used_slots++] = company(entry);
        return true;
    }
    
    
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        if (search_company(company) < 0) {
            return false;
        }
        else {
            size_type pos = search_company(company);
            company_array[pos].insert(product_name, price); //insert from company
            return true;
        }
    }
    
    
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);
        
        // COMPLETE THE IMPLEMENTATION...
        // If the item's present, delete it, otherwise don't!
        if (int(company_index) == COMPANY_NOT_FOUND) {
            return false;
        }
        else {
            for (int i = int(company_index) + 1; i < int(used_slots); i++) {
                company_array[i - 1] = company_array[i]; //shift everything in array
            }
            used_slots--;
            return true;
        }
    }
    
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        // Search for the given item
        size_type c_index = search_company(cName);
        
        // If the item's present, delete it, otherwise don't!
        if (int(c_index) == COMPANY_NOT_FOUND)
            return false;
        else
        {
            company_array[c_index].erase(pName);
            return true;
        }
    }
    
    
    
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

        // COMPLETE THE IMPLEMENTATION...

        // Loop through the company
        for (int i = 0; i < int(used_slots); i++) {
            // See if the company is present
            if(company == company_array[i].get_name()) {
                // Return the index it was found at
                return i;
                break;
            }
        }
        // Otherwise, we know the company wasn't found
        return COMPANY_NOT_FOUND;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (int(c_index) == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < int(used_slots); i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
