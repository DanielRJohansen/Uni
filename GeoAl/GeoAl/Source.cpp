
#include "Containers.h"
#include "Visuals.h"
#include "VisibleLines.h"


struct Test {
	int val;
	Test* next = NULL;
};

int main() {
	/*
	int* a = new int[2];
	a[0] = 1;
	a[1] = 2;
	
	printf("%d   %d\n", a[0], a[1]);


	int** b = new int* [2];
	b[0] = &a[0];
	b[1] = &a[1];


	int* c = new int[2];
	c[0] = *b[0];
	c[1] = *b[1];

	*b[0] = c[1];
	*b[1] = c[0];
	printf("%d   %d", a[0], a[1]);
	
	*/

	
	//printf("%d    %d    %d", b.val, b.next->val, b.next->next->val);

	



	Visuals vis(Double2(1920, 1080));

	const int ns = 15;
	LineSegment* segments = new LineSegment[ns];

	
	segments[0] = LineSegment(Double2(1600, 200), Double2(1700, 800));
	segments[14] = LineSegment(Double2(1500, 300), Double2(1600, 700));

	segments[1] = LineSegment(Double2(30, 200), Double2(400, 500));
	segments[2] = LineSegment(Double2(900, 1000), Double2(200, 550));
	segments[3] = LineSegment(Double2(1700, 900), Double2(1500, 950));

	// Many start overlap special case
	segments[4] = LineSegment(Double2(1800, 900), Double2(700, 700));	
	segments[5] = LineSegment(Double2(1800, 900), Double2(500, 700));
	segments[6] = LineSegment(Double2(1800, 900), Double2(600, 700));

	// messy start stop overlap special case
	segments[1] = LineSegment(Double2(300, 200), Double2(1100, 200));
	segments[0] = LineSegment(Double2(300, 200), Double2(500, 250));

	segments[8] = LineSegment(Double2(1100, 200), Double2(500, 250));
	segments[12] = LineSegment(Double2(500, 250), Double2(1000, 250));
	segments[13] = LineSegment(Double2(300, 150), Double2(1000, 150));


	segments[9] = LineSegment(Double2(3, 15), Double2(10, 800));
	segments[10] = LineSegment(Double2(10, 220), Double2(30, 400));
	


	int num_segments = 2;
	Double2 p = Double2(1920 / 2, 1080 / 2);












	VisibleLines VL(&vis);
	LineSegment* swpline = new LineSegment;
	swpline->visibility = SWEEP;
	int num_visible_lines = 0;
	LineSegment* visible_lines = VL.run(p, segments, num_segments, &num_visible_lines, swpline);



//	vis.draw(segments, num_segments, p, swpline);








	return 1;
}