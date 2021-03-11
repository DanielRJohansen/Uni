#pragma once
#include <iostream>


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
struct LineSegment {									// ALL LINES ARE TREATED AS UNBOUNDED
	LineSegment() {}
	LineSegment(Double2 p1, Double2 p2) : p1(p1), p2(p2) {}
	Double2 p1, p2;
	bool visible = false;
	VISIBILITY visibility = UNSEEN;

	bool current = false;


	int len() {
		return p1.dist(p2);
	}
	double angle() {	// Degrees
		double r = atan2(p2.y - p1.y, p2.x - p1.x);
		return (r * 180) / 3.14;
	}
	Double2 intersect(LineSegment line) {	// No testing whether the lines to actually intersect. It is assumed they do.
		double denominator = (p1.x - p2.x)*(line.p1.y - line.p2.y) - (p1.y - p2.y)*(line.p1.x - line.p2.x);
		if (denominator == 0) {
			std::cout << "Division by 0 in intersect";
			exit(-1);
		}
		double x = (	(p1.x * p2.y - p1.y * p2.x) * (line.p1.x - line.p2.x) - (p1.x - p2.x) * (line.p1.x * line.p2.y - line.p1.y * line.p2.x)	   ) / denominator;
		double y = (    (p1.x * p2.y - p1.y * p2.x) * (line.p1.y - line.p2.y) - (p1.y - p2.y) * (line.p1.x * line.p2.y - line.p1.y * line.p2.x)    ) / denominator;
		return Double2(x, y);
	}
	void flip() {
		Double2 temp = p1;
		p1 = p2;
		p2 = temp;
	}
	void sortPointsByAngle(Double2 p) {
		if (p.angle(p2) < p.angle(p1)) {
			this->flip();
		}
		handleStartlineOverlapSpecialCase(p);
	}

	void handleStartlineOverlapSpecialCase(Double2 p) {
		Double2 leftof = Double2(p.x - 1, p.y);
		LineSegment flatline = LineSegment(leftof, p);
		if (p1.y < p.y && p2.y > p.y) {
			Double2 intersect_ = this->intersect(flatline);
			if (intersect_.x < p.x) {
				this->flip();
			}
		}
	}

	AngularPoint* getAngularPoints(Double2 p) {
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
				Double2 sweep_intersect_next = sweepline->intersect(*next->line);
				double dist_to_next_line = sweepline->p1.dist(sweep_intersect_next);
				double dist_to_insertion = sweepline->p1.dist(insertion->p1);
				if (dist_to_insertion < dist_to_next_line  && ! (insertion->p1.equal(next->line->p1)) ){	// Not sure if 2nd comparison is necessary
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
			if (next == NULL) {}
			else if (next->line == deletion) {
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






