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
            bag.push(data);
        }
            break;
        case POP:
        case PRINT:
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
