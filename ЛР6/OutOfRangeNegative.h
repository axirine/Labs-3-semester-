#ifndef OUT_OF_RANGE_NEGATIVE_H
#define OUT_OF_RANGE_NEGATIVE_H

#include <string>
#include <stdexcept>
using namespace std;

class OutOfRangeNegative : public out_of_range {
public:
	explicit OutOfRangeNegative(int value)
		: out_of_range("Error: Numbers should be positive" + to_string(value)) {}
};

#endif