#ifndef OUT_OF_RANGE_LARGE_H
#define OUT_OF_RANGE_LARGE_H

#include <stdexcept>
using namespace std;

class OutOfRangeLarge : public out_of_range {
public:
	explicit OutOfRangeLarge(int value)                        //LIST!!!
		: out_of_range("Error: Out of bounds" + to_string(value)) {}
};

#endif
