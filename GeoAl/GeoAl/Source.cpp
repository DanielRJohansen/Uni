
#include "Containers.h"
#include "Visuals.h"
#include "VisibleLines.h"


struct Test {
	int val;
	Test* next = NULL;
};

int main() {

	Test a;
	a.val = 1;

	Test b;
	b.val = 2;
	b.next = &a;

	Test c;
	c.val = 3;
	c.next = b.next;

	b.next = &c;


	//printf("%d    %d    %d", b.val, b.next->val, b.next->next->val);

	



	Visuals vis(Int2(1920, 1080));

	const int ns = 3;
	LineSegment* segments = new LineSegment[ns];
	segments[0] = LineSegment(Int2(-300, 200), Int2(2000, 200));
	segments[1] = LineSegment(Int2(300, 250), Int2(1700, 250));
	segments[2] = LineSegment(Int2(300, 300), Int2(1700, 300));

	/*
	segments[0] = LineSegment(Int2(1600, 200), Int2(1700, 800));
	segments[14] = LineSegment(Int2(1500, 300), Int2(1600, 700));

	segments[1] = LineSegment(Int2(30, 200), Int2(400, 500));
	segments[2] = LineSegment(Int2(900, 1000), Int2(200, 550));
	segments[3] = LineSegment(Int2(1700, 900), Int2(1500, 950));

	// Many start overlap special case
	segments[4] = LineSegment(Int2(1800, 900), Int2(700, 700));	
	segments[5] = LineSegment(Int2(1800, 900), Int2(500, 700));
	segments[6] = LineSegment(Int2(1800, 900), Int2(600, 700));

	// messy start stop overlap special case
	segments[7] = LineSegment(Int2(300, 200), Int2(1100, 200));
	segments[8] = LineSegment(Int2(1100, 200), Int2(400, 250));
	segments[11] = LineSegment(Int2(300, 200), Int2(400, 250));
	segments[12] = LineSegment(Int2(400, 250), Int2(1000, 250));
	segments[13] = LineSegment(Int2(300, 150), Int2(1000, 150));


	segments[9] = LineSegment(Int2(3, 15), Int2(10, 800));
	segments[10] = LineSegment(Int2(10, 220), Int2(30, 400));
	*/


	int num_segments = ns;
	Int2 p = Int2(1920 / 2, 1080 / 2);












	VisibleLines VL;
	LineSegment* swpline = new LineSegment;
	swpline->visibility = SWEEP;
	int num_visible_lines = 0;
	LineSegment* visible_lines = VL.run(p, segments, num_segments, &num_visible_lines, swpline);
	for (int i = 0; i < num_visible_lines; i++) {
		printf("Vissing");
		visible_lines[i].visible = true;
	}

	printf("Swpline from %d to %d", swpline->p1.x, swpline->p2.x);

	vis.draw(segments, num_segments, p, swpline);








	return 1;
}