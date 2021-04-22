#include <iostream>

#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "Display.h"
#include "Environment.h"

Wall* parseInput(std::string path, int* n_walls) {
	std::fstream newfile;
	std::vector<Wall> wall_vector;

	double* buffer = new double[4];

	newfile.open(path, std::ios::in);
	if (newfile.is_open()) {
		std::string line;
		std::string temp;
		double val;
		while (getline(newfile, line)) {  //read data from file object and put it into string.
			std::stringstream ss;
			if (line[0] == '#' || line[0] == '\n' || line[0] == ' ')	// Skip comments
				continue;
			//cout << line << endl;
			ss << line;
			for (int i = 0; i < 4; i++) {
				ss >> temp;
				std::stringstream(temp) >> val;
				buffer[i] = val;
			}


			Wall w(Double2(buffer[0], buffer[1]), Double2(buffer[2], buffer[3]));
			wall_vector.push_back(w);

		}
		newfile.close();
	}
	delete buffer;


	Wall* walls = new Wall[wall_vector.size()];
	*n_walls = wall_vector.size();
	for (int i = 0; i < wall_vector.size(); i++) {
		walls[i] = wall_vector[i];
	}
	wall_vector.clear();
	return walls;
}





int main() {
	std::cout << "Program started \n\n";
	std::string path = "../input.txt";


	int n_walls;
	Wall* walls = parseInput(path, &n_walls);
	std::cout << "Number of walls input: "<< n_walls << endl;

	Environment env(walls, n_walls);
	env.run();

	return 1;





	return 1;
}