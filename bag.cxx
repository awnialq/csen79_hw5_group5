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
        }
    }
    
    // assignment
    Bag &Bag::operator=(const Bag &rhs) {
        std::cout << "assign" << std::endl;
        memcpy(this->data, rhs.data, size * sizeof(Data));
        return *this;
    }

    // move constructor
    Bag::Bag(Bag &&rhs) {
        std::cout << "move constructor; calling assignment" << std::endl;
        this->operator=(rhs);
    }    

    // copy constructor
    Bag::Bag(const Bag &rhs) {
        std::cout << "copy; calling assignment" << std::endl;
        this->operator=(rhs);
    }    

    // move
    Bag &Bag::operator=(Bag &&rhs) {
        std::cout << "move; calling assign" << std::endl;
        return this->operator=(rhs);
    }

    void Bag::push(const Data &d) {
        if(last >= size){
            resize();
        }
        data[last++] = d;
    };

    void Bag::resize() {
        if(size == 0){
            size = 1;
            data = new Data[size];
            return;
        }
        Data *temp = new Data[size * 2];
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