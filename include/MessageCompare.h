#ifndef MESSAGECOMPARE
#define MESSAGECOMPARE

#include "message.h"

struct MessageCompare {
	bool operator()(const Message &a, const Message &b) const {
		return a.timestamp > b.timestamp;
	}
};

#endif // !MESSAGECOMPARE
