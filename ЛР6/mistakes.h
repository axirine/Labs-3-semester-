#ifndef LABA_6_MISTAKES_H
#define LABA_6_MISTAKES_H

#include <stdexcept>
using namespace std;

class OutOfRangeLarge: public out_of_range {
public:
    explicit OutOfRangeLarge(int value)
    : out_of_range("Error: Out of bounds" + to_string(value)) {}
};

class OutOfRangeNegative: public out_of_range {
public:
    explicit OutOfRangeNegative(int value)
            : out_of_range("Error: Numbers should be positive" + to_string(value)) {}
};

class OutOfRangeNull: public out_of_range {
public:
    explicit OutOfRangeNull()
            : out_of_range("Error: Numbers should be more than 0") {}
};

#endif
