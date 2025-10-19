/*
 * Sin-Yaw Wang <swang24@scu.edu>
 * recipe for containers using C-style array
 */
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <string.h>
#include "bag.h"

namespace csen79 {
    // destructor
    Bag::~Bag() {
        std::cout << "destructor" <<  std::endl;
        if(data != nullptr){
            delete [] data;
            data = nullptr;
        }
    }
    
    // COPY assignment operator
    Bag &Bag::operator=(const Bag &rhs) {
        std::cout << "assign" << std::endl;
        if(this == &rhs) return *this;
        
        Data *newData = nullptr;
        if(rhs.size > 0) {
            try {
                newData = new Data[rhs.size];
            } catch(const std::bad_alloc &e) {
                throw;
            }
            memcpy(newData, rhs.data, rhs.last * sizeof(Data));
        }
        
        if(data != nullptr) delete [] data;
        data = newData;
        size = rhs.size;
        last = rhs.last;
        
        return *this;
    }

    // copy constructor
    Bag::Bag(const Bag &rhs) {
        std::cout << "copy; calling assignment" << std::endl;
        this->operator=(rhs);
    }    

    // MOVE assignment operator (note the &&)
    Bag &Bag::operator=(Bag &&rhs) {
        std::cout << "move; calling assign" << std::endl;
        if(this == &rhs) return *this;
        
        if(data != nullptr) delete [] data;
        
        data = rhs.data;
        size = rhs.size;
        last = rhs.last;
        
        rhs.data = nullptr;
        rhs.size = 0;
        rhs.last = 0;
        
        return *this;
    }

    // move constructor
    Bag::Bag(Bag &&rhs) {
        std::cout << "move constructor; calling assignment" << std::endl;
        this->operator=(std::move(rhs));  // ADD std::move here!
    }    

    void Bag::push(const Data &d) {
        if(last >= 2147483647 / 2){
            throw std::overflow_error("Stack overflow");
        }
        if(last >= size){
            resize();
        }
        data[last++] = d;
    };

    void Bag::resize() {
        if(size == 0){
            size = 1;
            try {
                data = new Data[size];
            } catch(const std::bad_alloc &e) {
                size = 0;
                throw;
            }
            return;
        }
        if(size > 2147483647 / 2){
            throw std::overflow_error("Cannot resize");
        }
        Data *temp = nullptr;
        try {
            temp = new Data[size * 2];
        } catch(const std::bad_alloc &e) {
            throw;
        }
        memcpy(temp, data, sizeof(Data) * size);
        delete [] data;
        data = temp;
        size = size * 2;
    }

    Bag::Data Bag::pop() {
        if(last <= 0){
            throw std::out_of_range("pop from empty bag");
        }
        return data[--last];
    };

    void Bag::print() const {
        if(last == 0){
            std::cout << "Nothing in bag to print" << std::endl;
            return;
        }
        std::cout << "Bag contents: ";
        for(int i = 0; i < last; i++){
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    };
}
