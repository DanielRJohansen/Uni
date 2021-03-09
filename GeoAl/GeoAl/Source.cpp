
#include "Containers.h"
#include "Visuals.h"
#include "VisibleLines.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>

struct Test {
	int val;
	Test* next = NULL;
};

LineSegment* parseInput(std::string path, int* num_lines, Double2* centerpoint) {
	std::fstream newfile;
	std::vector<LineSegment> line_vector;

	double* buffer = new double[4];

	newfile.open(path, std::ios::in); //open a file to perform read operation using file object
	if (newfile.is_open()) {   //checking whether the file is open
		std::string line;
		int cnt = 0;
		std::string temp;
		double val;
		while (getline(newfile, line)) {  //read data from file object and put it into string.
			std::stringstream ss;
			ss << line;
			for (int i = 0; i < 4; i++) {
				ss >> temp;
				std::stringstream(temp) >> val;
				buffer[i] = val;
			}

			if (cnt++ == 0) {
				centerpoint->x = buffer[0];
				centerpoint->y = buffer[1];
			}
			else {
				LineSegment l(Double2(buffer[0], buffer[1]), Double2(buffer[2], buffer[3]));
				line_vector.push_back(l);
			}

		}
		newfile.close();   //close the file object.
	}


	*num_lines = line_vector.size();
	LineSegment* line_arr = new LineSegment[*num_lines];
	for (int i = 0; i < *num_lines; i++) {
		line_arr[i] = line_vector[i];
	}

	delete buffer;
	return line_arr;
}

void saveOutput(LineSegment* visible_lines, int num_visibles) {
	std::fstream newfile;
	newfile.open("../output.txt", std::ios::out);  
	if (newfile.is_open())     
	{	
		for (int i = 0; i < num_visibles; i++) {
			newfile << visible_lines[i].p1.x << " ";
			newfile << visible_lines[i].p1.y << " ";
			newfile << visible_lines[i].p2.x << " ";
			newfile << visible_lines[i].p2.y << " ";
			newfile << "\n";
		}
		newfile.close(); //close the file object
	}
}


int main() {
	std::string path = "../input.txt";
	Double2 windowsize(1920, 1080);



	int num_lines;
	Double2 centerpoint;
	LineSegment* inputlines = parseInput(path, &num_lines, &centerpoint);




	Visuals vis(windowsize);
	VisibleLines VL(&vis);
	LineSegment* swpline = new LineSegment;


	// Generate output
	int num_visible_lines = 0;
	LineSegment* visible_lines = VL.run(centerpoint, inputlines, num_lines, &num_visible_lines, swpline);
	saveOutput(visible_lines, num_visible_lines);

	return 1;
}	


/*
	const int ns = 15;
	LineSegment* segments = new LineSegment[ns];
	segments[0] = LineSegment(Double2(1600, 200), Double2(1700, 800));
	segments[1] = LineSegment(Double2(1500, 300), Double2(1600, 700));

	segments[2] = LineSegment(Double2(30, 200), Double2(400, 500));
	segments[3] = LineSegment(Double2(900, 1000), Double2(200, 550));
	segments[4] = LineSegment(Double2(1700, 900), Double2(1500, 950));

	// Many start overlap special case
	segments[5] = LineSegment(Double2(1800, 900), Double2(700, 700));
	segments[6] = LineSegment(Double2(1800, 900), Double2(500, 700));
	segments[7] = LineSegment(Double2(1800, 900), Double2(600, 700));

	// Messy start stop overlap special case
	segments[8] = LineSegment(Double2(300, 200), Double2(1100, 200));
	segments[9] = LineSegment(Double2(300, 200), Double2(500, 250));
	segments[10] = LineSegment(Double2(1100, 200), Double2(500, 250));
	segments[11] = LineSegment(Double2(500, 250), Double2(1000, 250));
	segments[12] = LineSegment(Double2(300, 150), Double2(1000, 150));


	// First point hidden by not yet found line
	segments[13] = LineSegment(Double2(600, 600), Double2(10, 10));


	Double2 p = Double2(1920 / 2, 1080 / 2);

	*/