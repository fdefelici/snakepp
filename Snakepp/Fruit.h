#ifndef FRUIT_H
#define FRUIT_H

#include "Vec.h"
struct fruit_t {
	vec_t<unsigned int> cell{ 0,0 };
	bool spawned = false;
	bool isTaken = false;
};

#endif