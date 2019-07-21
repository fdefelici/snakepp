#ifndef MAP_H 
#define MAP_H

#include "Vec.h"

class Map {

public:
	Map(unsigned int w, unsigned int h) :
		width(w),
		height(h),
		cells(new unsigned int[w*h])
	{ }
	~Map() {
		delete[] cells;
	}
	void set(unsigned int x, unsigned int y, unsigned int value) {
		cells[y * width + x] = value;
	}

	unsigned int get(unsigned int x, unsigned int y) {
		return cells[y * width + x];
	}
	unsigned int get(const vec_t<unsigned int>& cell) {
		return cells[cell.y * width + cell.x];
	}

	unsigned int getWidth() {
		return width;
	}

	unsigned int getHeight() {
		return height;
	}

private:
	unsigned int *cells;
	unsigned int width = width;
	unsigned int height = height;
};

#endif