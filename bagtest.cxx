/*
 * Sin-Yaw Wang <swang24@scu.edu>
 * Test program
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include "bag.h"

using namespace std;
using namespace csen79;
enum Command { PUSH = 'P', POP = 'O', PRINT = 'D', QUIT = 'Q' };

int main(void) {
    Bag bag;
    string line;
    bool quit = false;
    while (!quit && std::getline(cin,line)) {
        switch (line[0]) {
        case PUSH: {
            int data;
            try {
                stringstream ss(line.substr(1));
                ss >> data;
            } catch (const out_of_range &e) {
                cerr << "Data out of range" << endl;
                continue;
            }
            try {
                bag.push(data);
            } catch (const bad_alloc &e) {
                cerr << "Memory allocation failed" << endl;
                continue;
            }
        }
            break;
        case POP:
            try{
                cout << "Value popped: " << bag.pop() << endl;
            } catch(std::out_of_range &e){
                cout << "Bag is empty" << endl;
            }
            break;
        case PRINT:
            bag.print();
            break;
        case QUIT:
            quit = true;
            break;
        default:
            cerr << "Unknown command: " << line << endl;
            break;
        }
    }
    
    return EXIT_SUCCESS;
}
