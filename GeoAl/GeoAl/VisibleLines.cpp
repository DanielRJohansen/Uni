#include "VisibleLines.h"


Double2 intersect(Double2 point, double rad, LineSegment line) {
	int px = (point.x + cos(rad) * 1000000);
	int py = (point.y + sin(rad) * 1000-000);
	LineSegment sweep = LineSegment(point, Double2(px, py));
	Double2 intersect = sweep.intersect(line);

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
        if (L[Li].angle <= R[Ri].angle) 
            points[index++] = L[Li++];        
        else 
            points[index++] = R[Ri++];      
    }

                                            // Copy the remaining elements of L[] and R[]
    while (Li < Lsize) 
        points[index++] = L[Li++];    
    while (Ri < Rsize)                 
        points[index++] = R[Ri++];

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




void merge(double* dists, AngularPoint** points , int l, int m, int r)
{
    int Lsize = m - l + 1;
    int Rsize = r - m;
    // Copy data to temp arrays L[] and R[]
    AngularPoint* Lp = new AngularPoint[Lsize];
    AngularPoint* Rp = new AngularPoint[Rsize];
    double* Ld = new double[Lsize];
    double* Rd = new double[Rsize];
    for (int i = 0; i < Lsize; i++) {
        Lp[i] = *points[l + i];
        Ld[i] = dists[l + i];
    }
        
    for (int j = 0; j < Rsize; j++) {
        Rp[j] = *points[m + 1 + j];
        Rd[j] = dists[m + 1 + j];
    }
        

    int Li = 0;                             // left index
    int Ri = 0;                             // right index
    int index = l;                          // merged index

    while (Li < Lsize && Ri < Rsize) {
        if (Ld[Li] <= Rd[Ri]) {
            dists[index] = Ld[Li];
            *points[index++] = Lp[Li++];
        }
        else {
            printf("Did that shit\n");
            dists[index] = Rd[Ri];
            *points[index++] = Rp[Ri++];
        }            
    }

    // Copy the remaining elements of L[] and R[]
    while (Li < Lsize) {
        dists[index] = Ld[Li];
        *points[index++] = Lp[Li++];
    }
        
    while (Ri < Rsize) {
        dists[index] = Rd[Ri];
        *points[index++] = Rp[Ri++];
    }
        

    //delete Ld, Lp, Rd, Rp;
}

void mergeSort(double* dists, AngularPoint** points, int l, int r) {
    if (l >= r) {
        return; //returns recursively
    }
    int m = l + (r - l) / 2;
    mergeSort(dists, points, l, m);
    mergeSort(dists, points, m + 1, r);
    merge(dists, points, l, m, r);
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

void startBeforeStop(AngularPoint** points, int n_points) {
    AngularPoint* copy = new AngularPoint[n_points];
    for (int i = 0; i < n_points; i++) {
        copy[i] = *points[i];
    }

    int front = 0;
    for (int i = 0; i < n_points; i++) {    // Insert starts
        if (copy[i].type == START) {
            *points[front++] = copy[i];
        }
    }
    for (int i = 0; i < n_points; i++) {    // Insert stops;
        if (copy[i].type == STOP) {
            *points[front++] = copy[i];
        }
    }
}

void handleLinestartBeforeLinestop(AngularPoint* points, int n_points) {
    int i = 0;
    AngularPoint** overlapping_points = new AngularPoint * [n_points];
    int n_overlaps = 0;
    while (i < n_points - 1) {
        int j = i + 1;
        overlapping_points[n_overlaps++] = &points[i];
        while (j < n_points - 1) {
            if (points[i].angle == points[j].angle) {
                overlapping_points[n_overlaps++] = &points[j++];
            }
            else {
                if (n_overlaps > 1) {
                    startBeforeStop(overlapping_points, n_overlaps);
                }
                break;
            }
        }
        i = j;
        n_overlaps = 0;
    }
}

void VisibleLines::sortByEndpointAngle(AngularPoint** points, int n_points) {
    LineSegment* lines = new LineSegment[n_points];
    for (int i = 0; i < n_points; i++) {
        lines[i] = *points[i]->line;
    }

    // First find the angle we will use
    double min_angle = -99999;
    for (int i = 0; i < n_points; i++) {
        double angle = centerpoint.angle(lines[i].p2);
        printf("Angle: %f\n", angle);
        if (angle > min_angle)
            min_angle = angle;
    }
    printf("Minangle %f\n", min_angle);
    LineSegment future_sweepline = lineFromAngle(centerpoint, min_angle);

    // Now find all the intersects
    Double2* intersects = new Double2[n_points];
    for (int i = 0; i < n_points; i++) {
        intersects[i] = future_sweepline.intersect(lines[i]);
        printf("Intersect: %f   %f\n", intersects[i].x, intersects[i].y);
    }
    // Find dist to each intersect
    printf("Dists: ");
    double* dists = new double[n_points];
    for (int i = 0; i < n_points; i++) {
        dists[i] = centerpoint.dist(intersects[i]);
        printf("%f  ", dists[i]);
    }
    printf("\n\n");
    mergeSort(dists, points, 0, n_points - 1);
    printf("\n\n");

}

void VisibleLines::handleIdenticalStartpoints(AngularPoint* points, int n_points) {
    int i = 0;
    AngularPoint** overlapping_points = new AngularPoint*[n_points];
    int n_overlaps = 0;
    while (i < n_points - 1) {
        int j = i + 1;
        overlapping_points[n_overlaps++] = &points[i];
        while (j < n_points - 1) {
            if (points[i].angle == points[j].angle && points[i].type == START && points[j].type == START) {
                overlapping_points[n_overlaps++] = &points[j++];               
            }
            else {
                if (n_overlaps > 1) {
                    printf("Rearranging %d start points from point %d\n", n_overlaps, i);
                    sortByEndpointAngle(overlapping_points, n_overlaps);
                }
                n_overlaps = 0;
                break;
            }
        }   
        i = j;
    }

}



LineSegment* VisibleLines::run(Double2 point, LineSegment* linesegments, int num_lines, int* num_visible_lines, LineSegment* swpline) {
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




    // Handle all the special cases
    assertFirstPointIsStart(points, n_points);
    handleLinestartBeforeLinestop(points, n_points);
    handleIdenticalStartpoints(points, n_points);

    /*
    for (int i = 0; i < num_lines * 2; i++) {
        printf("Angle: %f. Type %d \n", points[i].angle, points[i].type);
    }
    printf("\n");
    */


    EventQueue started_lines;                      
    EventQueue visibles;                    // More efficient to use a tree, but that is more code...
    for (int i = 0; i < n_points; i++) {
        printf("\nCurrent point: %d\n", i);
        AngularPoint* p = &points[i];
        /*int px = point.x + cos(p->angle) * 10000000;
        int py = point.y + sin(p->angle) * 10000000;
        LineSegment* sweepline = new LineSegment(point, Double2(px, py));*/
        LineSegment sweepline = lineFromAngle(point, p->angle);


        *swpline = sweepline;
        swpline->visibility = SWEEP;
        
        points[i].line->current = true;

        if (points[i].type == START) {
            printf("Inserting:\n");
            started_lines.addLine(points[i].line, &sweepline);
            if (!started_lines.empty()) {
                visibles.addLine(started_lines.front());
            }
            //visibles.addLine(started_lines.front());
        }
        else {
            printf("Deleting\n");
            started_lines.deleteLine(points[i].line);
            if (!started_lines.empty()) {  
                visibles.addLine(started_lines.front());
            }
        }

        LineSegment* visible_lines = visibles.fetch();
        visualizer->draw(linesegments, num_lines, point, swpline);

        delete visible_lines;
        points[i].line->current = false;
    }

    *num_visible_lines = visibles.size;
    printf("%d visible lines found\n", visibles.size);
    LineSegment* visible_lines = visibles.fetch();

    return visible_lines;
}
