#include "VisibleLines.h"


Int2 intersect(Int2 point, double rad, LineSegment line) {
	int px = point.x + cos(rad) * 10000000;
	int py = point.y + sin(rad) * 10000000;
	LineSegment sweep = LineSegment(point, Int2(px, py));
	Int2 intersect = sweep.intersect(line);

	return intersect;
}





void merge(AngularPoint* points, int l, int m, int r)
{
    int Lsize = m - l + 1;
    int Rsize = r - m;
                                            // Copy data to temp arrays L[] and R[]
    AngularPoint* L = new AngularPoint[Lsize];
    AngularPoint* R = new AngularPoint[Rsize];
    for (int i = 0; i < Lsize; i++)
        L[i] = points[l + i];
    for (int j = 0; j < Rsize; j++)
        R[j] = points[m + 1 + j];

    int Li = 0;                             // left index
    int Ri = 0;                             // right index
    int index = l;                          // merged index

    while (Li < Lsize && Ri < Rsize) {
        if (L[Li].angle <= R[Ri].angle) {
            points[index++] = L[Li++];
        }
        else {
            points[index++] = R[Ri++];
        }
    }

                                            // Copy the remaining elements of L[] and R[]
    while (Li < Lsize) {
        points[index++] = L[Li++];
    } 
    while (Ri < Rsize) {                
        points[index++] = R[Ri++];
    }

    delete L, R;
}

void mergeSort(AngularPoint* points, int l, int r) {
    if (l >= r) {
        return; //returns recursively
    }
    int m = l + (r - l) / 2;
    mergeSort(points, l, m);
    mergeSort(points, m + 1, r);
    merge(points, l, m, r);
}

void assertFirstPointIsStart(AngularPoint* points, int num_points) {
    if (points[0].type == START)
        return;

    AngularPoint* queue = new AngularPoint[num_points]; // worst case size, can be optimized by /2 but lets not complicate "free" things
    int cnt = 0;
    for (int i = 0; i < num_points; i++) {
        if (points[i].type == STOP) {
            queue[cnt++] = points[i];
        }
        else 
            break;
    }

    int index_ = 0;
    for (int i = cnt; i < num_points; i++) {    // Move list starting at type==START forward
        queue[index_++] = points[i];            
    }
    for (int i = 0; i < cnt; i++) {             // Now append the numbers from the queue
        queue[index_++] = queue[i];
    }

    if (index_ != num_points) {
        printf("What");
        exit(-1);
    }
}

void swap(AngularPoint* p1, AngularPoint* p2) {
    AngularPoint temp = *p1;
    p1 = p2;
    p2 = &temp;
}

void assertLinestopBeforeLinestart(AngularPoint* points, int num_points) {
    for (int i = 0; i < num_points - 1; i++) {
        if (points[i].angle == points[i + 1].angle) {
            if (points[i].type == START && points[i + 1].type == STOP) {
                swap(&points[i], &points[i + 1]);
            }
        }
    }

}

void handleIdenticalStartpoints(AngularPoint* points, int num_points) {

}



LineSegment* VisibleLines::run(Int2 point, LineSegment* linesegments, int num_lines, int* num_visible_lines, LineSegment* swpline) {
    int n_points = num_lines * 2;
    AngularPoint* points = new AngularPoint[n_points];
    int index = 0;
    for (int i = 0; i < num_lines; i++) {
        AngularPoint* lines_points = linesegments[i].getPoints(point);
        points[index++] = lines_points[0];
        points[index++] = lines_points[1];
        delete lines_points;
    }
    mergeSort(points, 0, (num_lines * 2) - 1);



  //  assertFirstPointIsStart(points, n_points);
//    assertLinestopBeforeLinestart(points, n_points);

    for (int i = 0; i < num_lines * 2; i++) {
        printf("Angle: %f. Type %d \n", points[i].angle, points[i].type);
    }
    printf("\n");



    EventQueue started_lines;                      
    EventQueue visibles;                    // More efficient to use a tree, but that is more code...
    for (int i = 0; i < n_points; i++) {
        AngularPoint* p = &points[i];
        int px = point.x + cos(p->angle) * 10000000;
        int py = point.y + sin(p->angle) * 10000000;
        LineSegment* sweepline = new LineSegment(point, Int2(px, py));

        if (i == 0) {
            swpline = sweepline;
            printf("Swpline from %d to %d", swpline->p1.x, swpline->p2.x);
            return new LineSegment;
        }
            

        if (points[i].type == START) {
            printf("\nInserting:\n");
            started_lines.addLine(points[i].line, sweepline);
            if (!started_lines.empty()) {
                //visibles.addLine(started_lines.front());
            }
            //visibles.addLine(started_lines.front());
        }
        else {
            printf("\nDeleting\n");
            started_lines.deleteLine(points[i].line);
            if (!started_lines.empty()) {  
                visibles.addLine(started_lines.front());
            }
        }
    }

    *num_visible_lines = visibles.size;
    printf("%d visible lines found\n", visibles.size);
    LineSegment* visible_lines = visibles.fetch();

    return visible_lines;
}
