//
// Created by Ryan Lang on 3/26/25.
//

#ifndef TEE_H
#define TEE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Game.h"
#include "enums.hpp"
#include "tools.hpp"
#include <fstream>

class Tee {
private:
    ofstream file;

public:
    Tee(const string& filename) : file(filename) {
        if (!file.is_open()) {
            throw runtime_error("Failed to open output file");
        }
    }

    template<typename T>
    Tee& operator<<(const T& data) {
        cout << data;
        file << data;
        file.flush();
        return *this;
    }

    Tee& operator<<(std::ostream& (*manip)(std::ostream&)) {
        cout << manip;
        file << manip;
        file.flush();
        return *this;
    }

    ~Tee() {
        file.close();
    }
};



#endif //TEE_H
