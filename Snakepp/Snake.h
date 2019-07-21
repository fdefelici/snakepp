#ifndef SNAKE_H
#define SNAKE_H

#include "Vec.h"
struct snake_t {
	vec_t<float> pos{ 2.f, 2.f };
	vec_t<int> dir{ 1, 0 };
	vec_t<unsigned int> cell{ 2, 2 };
	float speed = 3;
	unsigned int score = 0;

	unsigned int tailMaxSize = 100;
	vec_t<unsigned int> tail[100];
	unsigned int tailSize = 0;
	bool isDead = false;
	bool hasMoved = false;
};

#endif