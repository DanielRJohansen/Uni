#pragma once

#include "Types.h"
#include "Display.h"

class BSP
{
public:
	BSP(){}
	BSP(Wall* walls, int n_walls);

	void paint(Player* player, Display* display);

	int fragments = 0;
private:
	void shuffleWalls(Wall* walls, int n_walls);






	class Node {
	public:
		Node() {};
		Node(int max_n_walls, int* fragments_ptr) { walls = new Wall[max_n_walls]; fragments = fragments_ptr; };
		void partition();
		void painters(Player* player, Display* display);
		void determineWall(Wall* wall);

		void assign(Wall* wall) {
			walls[node_walls++] = *wall;
		}
		bool cleanNode();	// call parent to delete if empty!!

		Double2 origo, vector, normal_down;
		Node* down = NULL;
		Node* up = NULL;
		bool leaf = true;
		


		WallContainer* wallcontainer;

		

	private:
		void paint(Display* display);
		int* fragments;


		// Filled by parents before partitioning.
		Wall* walls;
		int node_walls = 0;
	};

	Node* root = NULL;

};

