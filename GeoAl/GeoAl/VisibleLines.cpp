#include "VisibleLines.h"




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
        

    delete Ld, Lp, Rd, Rp;
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
    delete copy;
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
    double min_angle = 99999;
    for (int i = 0; i < n_points; i++) {
        double angle = centerpoint.angle(lines[i].p2);
        if (angle < min_angle)
            min_angle = angle;
    }
    LineSegment future_sweepline = lineFromAngle(centerpoint, min_angle);


    // Now find all the intersects
    Double2* intersects = new Double2[n_points];
    for (int i = 0; i < n_points; i++) {
        intersects[i] = future_sweepline.intersect(lines[i]);
    }
    // Find dist to each intersect
    double* dists = new double[n_points];
    for (int i = 0; i < n_points; i++) {
        dists[i] = centerpoint.dist(intersects[i]);
    }
    mergeSort(dists, points, 0, n_points - 1);

    delete lines, intersects, dists;
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
                    sortByEndpointAngle(overlapping_points, n_overlaps);
                }
                n_overlaps = 0;
                break;
            }
        }   
        i = j;
    }
    delete overlapping_points;
}












LineSegment* VisibleLines::run(Double2 point, LineSegment* linesegments, int num_lines, int* num_visible_lines, LineSegment* swpline) {
    int n_points = num_lines * 2;
    centerpoint = point;


    // First get all points from all lines, sorted by angle.
    AngularPoint* points = new AngularPoint[n_points];
    for (int i = 0; i < num_lines; i++) {
        AngularPoint* lines_points = linesegments[i].getAngularPoints(point);          // First special case handled here
        points[i*2] = lines_points[0];
        points[i*2+1] = lines_points[1];
        delete lines_points;
    }
    mergeSort(points, 0, (num_lines * 2) - 1);


    // Handle all the special cases
    handleLinestartBeforeLinestop(points, n_points);
    handleIdenticalStartpoints(points, n_points);



    EventQueue started_lines;                      
    EventQueue visibles;                    // More efficient to use a tree, but that is more code...

    for (int iteration = 0; iteration < 2; iteration++) {   // First iteration to prep the event-queue, ONLY second iteration adds to the visible lines

        for (int i = 0; i < n_points; i++) {
            LineSegment sweepline = lineFromAngle(point, points[i].angle);


            *swpline = sweepline;
            swpline->visibility = SWEEP;

            if (points[i].type == START) {
                started_lines.addLine(points[i].line, &sweepline);
                if (!started_lines.empty() && iteration == 1) {
                    visibles.addLine(started_lines.front());
                }
            }
            else {
                started_lines.deleteLine(points[i].line);
                if (!started_lines.empty() && iteration == 1) {
                    visibles.addLine(started_lines.front());
                }
            }

            if (iteration == 1) {
                LineSegment* visible_lines = visibles.fetch();
                visualizer->draw(linesegments, num_lines, point, swpline);
                delete visible_lines;
            }
        }
    }


    delete points;

    *num_visible_lines = visibles.size;
    LineSegment* visible_lines = visibles.fetch();

    return visible_lines;
}
