#pragma once

#include "Containers.h"
#include "Visuals.h"

class VisibleLines
{
public:
	VisibleLines(){}
	VisibleLines(Visuals* visuals) : visualizer(visuals) {}

	LineSegment* run(Double2 point, LineSegment* linesegments, int num_lines, int* num_visible_lines, LineSegment* swpline);


	Double2 centerpoint;
	
	Visuals* visualizer;



private:
	void sortByEndpointAngle(AngularPoint** points, int n_points);
	void handleIdenticalStartpoints(AngularPoint* points, int n_points);
	LineSegment lineFromAngle(Double2 point, double angle) {
		int px = point.x + cos(angle) * 10000000;
		int py = point.y + sin(angle) * 10000000;
		return LineSegment(point, Double2(px, py));
	}

};

