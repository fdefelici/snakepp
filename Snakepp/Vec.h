#ifndef VEC_H
#define VEC_H

template<typename T>
struct vec_t {
	T x;
	T y;

	// implicit default ctor vec_t<T>()
	// implicit copy ctor vec_t<T>(const vec_t<T>&)

	//Copy Assign Oper
	vec_t<T>& operator =(const vec_t<T>& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	//Equals Ope
	bool operator ==(const vec_t<T>& other) {
		return x == other.x && y == other.y;
	}
};
#endif // !VEC_H