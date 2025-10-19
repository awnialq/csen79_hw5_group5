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
        Data *temp = new Data[size * 2];
        memcpy(temp, data, sizeof(Data) * size);
        delete [] data;
        data = temp;
        size = size * 2;
    }

    Bag::Data Bag::pop() {return 0;};
    void Bag::print() const {};
}