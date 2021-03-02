
#include "Containers.h"
#include "Visuals.h"



int main() {
	Visuals vis(Int2(1920, 1080));

	LineSegment* segments = new LineSegment[5];
	segments[0] = LineSegment(Int2(30, 200), Int2(400, 500));
	segments[1] = LineSegment(Int2(1600, 200), Int2(1700, 800));
	segments[2] = LineSegment(Int2(900, 1000), Int2(200, 550));
	segments[3] = LineSegment(Int2(1800, 900), Int2(500, 700));
	segments[4] = LineSegment(Int2(1700, 900), Int2(1500, 950));
	int num_segments = 5;
	Int2 p = Int2(1920 / 2, 1080 / 2);
	vis.draw(segments, num_segments, p);







	return 1;
}