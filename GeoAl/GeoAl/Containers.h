#pragma once
#include "math.h"



struct Int2 {
	Int2() {};
	Int2(int x, int y) : x(x), y(y) {}
	int x, y;


	int dist(Int2 p) {
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}
};



struct LineSegment {
	LineSegment() {}
	LineSegment(Int2 p1, Int2 p2) : p1(p1), p2(p2) {}
	Int2 p1, p2;

	int len() {
		return p1.dist(p2);
	}
	int angle() {	// Degrees
		float r = atan2(p2.y - p1.y, p2.x - p1.x);
		return (r * 180) / 3.14;
	}


};