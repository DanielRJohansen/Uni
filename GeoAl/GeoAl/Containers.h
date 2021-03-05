#pragma once
#include "math.h"
#include <iostream>


struct Int2 {
	Int2() {};
	Int2(int x, int y) : x(x), y(y) {}
	int x, y;


	double dist(Int2 p) {
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}
	double angle(Int2 p) {// Rad
		return atan2(p.y - y, p.x - x);
	}
};



struct LineSegment;


enum TYPE {START, STOP};
struct AngularPoint {
	AngularPoint() {}
	AngularPoint(double angle, LineSegment* line, TYPE t) : angle(angle), line(line), type(t){}

	double angle;
	LineSegment* line;
	TYPE type;
};

enum VISIBILITY {SEEN, UNSEEN, SWEEP};
struct LineSegment {
	LineSegment() {}
	LineSegment(Int2 p1, Int2 p2) : p1(p1), p2(p2) {}
	Int2 p1, p2;
	double key;		// For sorting, represents angle between centerpoint and the lines start-point
	bool visible = false;
	VISIBILITY visibility = UNSEEN;

	int len() {
		return p1.dist(p2);
	}
	int angle() {	// Degrees
		double r = atan2(p2.y - p1.y, p2.x - p1.x);
		return (r * 180) / 3.14;
	}
	Int2 intersect(LineSegment line) {	// No testing whether the lines to actually intersect. It is assumed they do.
		double determinant = (p1.x - p2.x)*(line.p1.y, line.p2.y) - (p1.y - p2.y)*(line.p1.x - line.p2.x);
		if (determinant == 0) {
			std::printf("Illegal determinant in intersect");
			exit(-1);
		}
		double x = (	  (p1.x * p2.y - p1.y * p2.x) * (line.p1.x - line.p2.x) - (p1.x - p2.x) * (line.p1.x * line.p2.y - line.p1.y * line.p2.x)	) / determinant;
		double y = ((p1.x * p2.y - p1.y * p2.x) * (line.p1.y - line.p2.y) - (p1.y - p2.y) * (line.p1.x * line.p2.y - line.p1.y * line.p2.x)) / determinant;
		return Int2((int)x, (int)y);
	}
	void sortPointsByAngle(Int2 p) {
		if (p.angle(p2) < p.angle(p1)) {
			Int2 temp = p1;
			p1 = p2;
			p2 = temp;
		}
		key = p.angle(p1);
	}
	AngularPoint* getPoints(Int2 p) {
		sortPointsByAngle(p);
		AngularPoint* points = new AngularPoint[2];
		points[0] = AngularPoint(p.angle(p1), this, START);
		points[1] = AngularPoint(p.angle(p2), this, STOP);
		return points;
	}
		
};








struct EventQueue {			// The root contains no values, its just a simple implementation with minimal code
							// Val is line index, and key is the priority to the line start
	EventQueue() { root = new Node(); }


	bool empty() {
		return (root->next == NULL);
	}

	void addLine(LineSegment* insertion, LineSegment* sweepline) {
		root->addLine(insertion, sweepline);
	}
	void addLine(LineSegment* insertion) {	// temp
		size += root->addLine(insertion);	// Root not counted in size. Not correct if any lines are deleted!
	}
	LineSegment* front() {
		return root->next->line;
	}
	void deleteLine(LineSegment* deletion) {
		root->deleteLine(deletion);
	}
	LineSegment* fetch() {
		printf("Fetching size: %d\n", size);
		LineSegment* all_lines = new LineSegment[size];
		root->fetch(all_lines, 0);
		return all_lines;
	}


	struct Node {
		Node() {}
		Node(LineSegment* line): line(line){}
		LineSegment* line = NULL;

		Node* next = NULL;


		void addLine(LineSegment* insertion, LineSegment* sweepline) {		// For the priority queue
			if (next == NULL) {
				next = new Node(insertion);
			}
			else if (next->line == insertion) {		// Case where line already exist, temporary
				return;
			}
			else {
				Int2 sweep_intersect_next = sweepline->intersect(*next->line);
				double dist_to_next_line = sweepline->p1.dist(sweep_intersect_next);
				double dist_to_insertion = sweepline->p1.dist(insertion->p1);
				printf(" ins %f, next %f\n", dist_to_insertion, dist_to_next_line);
				if (dist_to_insertion < dist_to_next_line) {					// CAUTION: using <= here to deal with special case of many lines starting at same point
					Node* temp = next;
					next = new Node(insertion);
					next->next = temp;
				}
				else {
					next->addLine(insertion, sweepline);
				}
			}
		}
		void deleteLine(LineSegment* deletion) {
			if (next->line == deletion) {
				Node* temp = next->next;
				delete next;
				next = temp;
			}
			else {
				next->deleteLine(deletion);
			}

		}
		void fetch(LineSegment* lines, int index) {
			if (next != NULL) {
				printf("index_ %d\n", index);
				next->line->visible = true;			// Not critical for algo, but easy implementation for graphic visualization
				next->line->visibility = SEEN;
				lines[index] = *next->line;
				next->fetch(lines, index + 1);
			}
		}
		int addLine(LineSegment* insertion) {		// To keep track of visible lines only!
			if (next == NULL) {
				next = new Node(insertion);
				return 1;
			}
			else if (next->line == insertion) {		// Case where line already exist, temporary
				return 0;
			}
			else {
				return next->addLine(insertion);
			}		
		}
		

	};

	int size = 0;
	Node* root;
};






