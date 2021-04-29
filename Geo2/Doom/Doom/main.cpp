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
			if (line[0] == '*')
				break;
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

void runGame() {
	char use_default;
	std::string path;
	printf("Use default map? (y/n)\n");
	cin >> use_default;
	if (use_default == 'y')
		path = "../Maps/default.txt";
	else {
		printf("Please type map path \n");
		cin >> path;
	}
		
	int n_walls;
	Wall* walls = parseInput(path, &n_walls);

	Environment env(walls, n_walls);
	env.run();
}
void swap(double* a, double* b) {
	double temp = *a;
	*a = *b;
	*b = temp;
}
void generateRepetetiveMap() {
	std::string path = "../Maps/default.txt";
	int n_walls;
	Wall* walls = parseInput(path, &n_walls);
	int side_len = 2000;



	int rep_per_dimension;
	printf("How many repetitions would you like? (2-99) - press 0 to exit\n");
	std::cin >> rep_per_dimension;
	if (rep_per_dimension == 0)
		exit(0);

	ofstream out_file;
	std::string filename = "../Maps/" + std::to_string(rep_per_dimension) + ".txt";
	out_file.open(filename);

	for (int x = 0; x < rep_per_dimension; x++) {
		for (int y = 0; y < rep_per_dimension; y++) {
			bool flip_x = rand() % 2;
			bool flip_y = rand() % 2;

			for (int i = 0; i < n_walls; i++) {
				Wall w = walls[i];
				w.p1.x += x * side_len;
				w.p2.x += x * side_len;
				w.p1.y += y * side_len;
				w.p2.y += y * side_len;

				if (flip_x)
					swap(&w.p1.x, &w.p2.x);
				if (flip_y)
					swap(&w.p1.y, &w.p2.y);

				out_file << w.p1.x << " " << w.p1.y << " " << w.p2.x << " " << w.p2.y << "\n";
			}
		}
	}
	out_file.close();
}

Wall* copyWalls(Wall* walls, int n_walls) {
	Wall* copy = new Wall[n_walls];
	for (int i = 0; i < n_walls; i++)
		copy[i] = walls[i];
	return copy;
}

void runFragmentationStatistics() {
	int stop_at = 128;
	char def;
	printf("Runing statistics. Use default setup? (y/n)\n");
	cin >> def;
	if (def != 'y') {
		printf("Stop at file:\n");
		cin >> stop_at;
	}
	

	

	
	const int num_iterations = 5;
	double avg_fragments[500];
	int index = 0;
	for (int i = 1; i <= stop_at; i *= 2) {
		std::string path = "../Maps/" + to_string(i) + ".txt";
		int n_walls;
		Wall* walls = parseInput(path, &n_walls);

		double sum = 0;
		for (int iter = 0; iter < num_iterations; iter++) {
			Wall* copy = copyWalls(walls, n_walls);

			BSP bsp(copy, n_walls);
			sum += bsp.fragments;
			delete copy;
		}
		avg_fragments[index++] = sum / num_iterations;
		delete walls;
	}

	printf("MATLAB friendly statistics.");
	printf("Walls:\n");
	printf("[");
	for (int i = 1; i <= stop_at; i*= 2)
		printf("%d ", 21 * (i ) * (i));
	printf("];\n");
	
	printf("Average fragments:\n");
	printf("[");
	for (int i = 0; i < index; i++)
		printf("%f ", avg_fragments[i]);
	printf("];\n");
}


int main() {
	srand(time(0));


	int application;
	START:
	printf("Welcome to DOOM-replica 2021!\nPlease select an application to run: (1/2/3)\n  Play Game (1)\n  Generate repeating map (2)\n  Run fragmentation statistics (3)\n");
	std::cin >> application;
	switch (application) {
	case 1:
		runGame();
		break;
	case 2:
		while (true)
			generateRepetetiveMap();
		break;
	case 3:
		runFragmentationStatistics();
		break;
	default:
		printf("Illegal input, please write a number between 1-3\n");
		goto START;
	}
	

	return 1;
}