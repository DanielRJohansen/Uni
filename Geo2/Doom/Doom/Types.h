#pragma once

#include <iostream>

using namespace std;


const double PI = 3.14;



struct Double2 {
	Double2() {};
	Double2(double x, double y) : x(x), y(y) {}
	double x, y;


	double dist(Double2 p) {
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}
	double angle(Double2 p) {// Rad
		return atan2(p.y - y, p.x - x);
	}
	bool equal(Double2 p) {
		return (x == p.x && y == p.y);
	}
	// These functions assume a vector is represented
	double len() {
		return sqrt(x * x + y * y);
	}
	double dot(Double2 vecb) {
		return this->len() * cos(vecb.angle(*this));
	}
	Double2 rotate(double angle) {
		Double2 v;
		v.x = x * cos(angle) - y * sin(angle);
		v.y = x * sin(angle) + y * cos(angle);
		return v;
	}


	Double2 operator*(const double a) { return Double2(x * a, y * a); }
	Double2 operator+(const Double2 a) { return Double2(x + a.x, y + a.y); }
	Double2 operator-(const Double2 a) { return Double2(x - a.x, y - a.y); }
	bool operator==(const Double2 a) { 
		printf("%f    %f     ==     %f     %f\n", x, y, a.x, a.y);
		return (x == a.x && y == a.y); }
};





struct Vec3d {
	Vec3d() {}
	Vec3d(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	double dot(const Vec3d vec) const {
		return x * vec.x + y * vec.y + z * vec.z;
	}
	Vec3d operator+(const Vec3d vec) const {
		return Vec3d(x + vec.x, y + vec.y, z + vec.z);
	}
	Vec3d operator-(const Vec3d vec) const {
		return Vec3d(x - vec.x, y - vec.y, z - vec.z);
	}
	Vec3d operator*(double s) const {
		return Vec3d(s * x, s * y, s * z);
	}
	Vec3d rotate(double angle) {	// Around z axis
		Vec3d v;
		v.x = x * cos(angle) - y * sin(angle);
		v.y = x * sin(angle) + y * cos(angle);
		v.z = z;
		return v;
	}

	double x, y, z;
};


struct Wall {
	Wall() {};
	Wall(Double2 p1, Double2 p2) : p1(p1), p2(p2) { len = p1.dist(p2); angle = p1.angle(p2); };
	Double2 p1;
	Double2 p2;
	double len;
	double angle;

	void bottomrightFirst() {	// Ensures p1 is bottom right
		if (p1.y > p2.y)
			swap();
		else if (p1.y == p2.y) {
			if (p1.x < p2.x)
				swap();
		}
	}
	void swap() {
		Double2 temp = p1;
		p1 = p2;
		p2 = temp;
	}
	Double2 getNormalDown() {
		bottomrightFirst();
		Double2 vector = p2 - p1;
		return vector.rotate(PI / 2);
	}
	Double2 intersect(Wall wall) {	// Assumin both walls are infinite in length
		double denominator = (p1.x - p2.x) * (wall.p1.y - wall.p2.y) - (p1.y - p2.y) * (wall.p1.x - wall.p2.x);
		if (denominator == 0) {
			std::cout << "Division by 0 in intersect";
			exit(-1);
		}
		double x = ((p1.x * p2.y - p1.y * p2.x) * (wall.p1.x - wall.p2.x) - (p1.x - p2.x) * (wall.p1.x * wall.p2.y - wall.p1.y * wall.p2.x)) / denominator;
		double y = ((p1.x * p2.y - p1.y * p2.x) * (wall.p1.y - wall.p2.y) - (p1.y - p2.y) * (wall.p1.x * wall.p2.y - wall.p1.y * wall.p2.x)) / denominator;
		return Double2(x, y);
	}
};

struct WallContainer {
	WallContainer(){}
	WallContainer(Wall wall): wall(wall) {}
	Wall wall;
	WallContainer* next = NULL;

	void add(Wall wall) {
		if (next == NULL)
			next = new WallContainer(wall);
		else
			next->add(wall);
	}
	void deleteList() {
		if (next != NULL) {
			next->deleteList();
		}
		delete next;
	}
	
};



struct Player {
	Player() { rotate(0); }
	Player(Double2 pos, double angle) { rotate(0); }

	void rotate(double delta_angle) {
		angle += delta_angle;
		focal_normal = Vec3d(focal_len, 0, 0).rotate(angle);
		focal_origo = pos + focal_normal;
	}


	double view_z= 50;
	Vec3d pos = Vec3d(400, 200, view_z);
	double focal_len = 1.5;
	
	double angle = 3* 3.14/4;
	Vec3d focal_normal = Vec3d(focal_len, 0, 0);
	Vec3d focal_origo;

	void move(double direction, double dt, bool move) {	// rad, ???
		if (!move)
			return;
		pos = pos + focal_normal.rotate(direction) * (1 / focal_len) * dt;
		focal_origo = pos + focal_normal;
	}
};




class Scanline {
public:
	Scanline() {}
	Scanline(int width) : width(width) { 
		scanline = new bool[width]; 
		clear();
	}

	Double2* request(Double2 from_to, int *n_segments) {
		if (from_to.x >= width)
			return NULL;

		Double2* split_segments = new Double2[width];	// Make large for worst case

		int index = from_to.x;
		bool state = scanline[index];

		while (index < width && index < from_to.y) {	// Outer while loop ensures we can get multiple segments
			switch (state) {
			case 0:		// Free state
				split_segments[*n_segments].x = index;
				while (index < width && index < from_to.y) {
					if (scanline[index] == 0)
						scanline[index++] = 1;
					else {
						state = 1;
						break;
					}

				}
				split_segments[*n_segments].y = index - 1;
				*n_segments+=1;
				break;

			case 1:		// Taken state
				while (index < width && index < from_to.y) {
					if (scanline[index] == 0) {
						state = 0;
						break;
					}
					else
						index++;				
				}
				break;

			}
		}
		



		return split_segments;
	}
	
	void clear() {
		for (int i = 0; i < width; i++)
			scanline[i] = 0;
	}

private:
	int width;
	bool *scanline;	// Free (false) by default
};



/*
class Scanline {

	enum AVAILABILITY { FREE, TAKEN };
	struct ScanlineSegment {
		ScanlineSegment() {}
		ScanlineSegment(int start, int end, AVAILABILITY avail) : start(start), end(end), avail(avail) {}

		void mergeChild() {
			ScanlineSegment* tmp = next->next;
			end = next->end;
			delete next;
			next = tmp;
		}

		int start, end;
		AVAILABILITY avail = FREE;
		ScanlineSegment* next = NULL;
	};


	Scanline(int width) : width(width) { slsegment = ScanlineSegment(0, width, FREE); }
	Double2* request(Double2 from_to) {
		Double2* split_segments = new Double2(width);	// Make large for worst case
		int n_segments = 1;


		return split_segments;
	}

	int width;
	ScanlineSegment slsegment;

	

	
};
*/