#ifndef OUT_OF_RANGE_NULL_H
#define OUT_OF_RANGE_NULL_H

#include <string>
#include <stdexcept>
using namespace std;

class OutOfRangeNull : public out_of_range {
public:
	explicit OutOfRangeNull()                       
		: out_of_range("Numbers should be more than 0") {}
};

#endif