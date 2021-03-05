#pragma once

#include "Containers.h"

class VisibleLines
{
public:


	LineSegment* run(Int2 point, LineSegment* linesegments, int num_lines, int* num_visible_lines, LineSegment* swpline);

};

