#include "BSP.h"





BSP::BSP(Wall* walls, int n_walls) {
	root = new Node(n_walls);
	for (int i = 0; i < n_walls; i++) {
		root->assign(&walls[i]);
	}
	root->partition();
	root->cleanNode();
}



void BSP::paint(Player* player, Display* display) {

}







void BSP::Node::partition() {
	printf("Partitioning %d walls\n", node_walls);
	wallcontainer = new WallContainer(walls[0]);
	origo = walls[0].p1;
	normal_down = walls[0].getNormalDown();

	if (node_walls > 1) {
		down = new Node(node_walls);
		up = new Node(node_walls);

		leaf = false;
		for (int i = 1; i < node_walls; i++) {
			determineWall(&walls[i]);
		}
	}
}


void BSP::Node::determineWall(Wall* wall) {					// FIX CASE WHERE POINTS ARE IN THE VECTOR-LINE

	Double2 wall_nd = wall->getNormalDown();	// Case where wall is inside and parallel with line.
	if (normal_down == wall_nd) {
		wallcontainer->add(*wall);
		return;
	}

	bool p1_below = (wall->p1 - origo).dot(normal_down) < 0;
	bool p2_below = (wall->p2 - origo).dot(normal_down) < 0;
	if (p1_below && p2_below) {
		down->assign(wall);
	}
	else if (!p1_below && !p2_below) {
		up->assign(wall);
	}
	else {
		printf("Creating fragment\n");
		Double2 splitpoint = wallcontainer->wall.intersect(*wall);
		Wall top_wall = Wall(wall->p2, splitpoint);			// We already did getNormalDown, so we know p2 is top.
		Wall bottom_wall = Wall(splitpoint, wall->p1);
		up->assign(&top_wall);
		down->assign(&bottom_wall);
	}
}

bool BSP::Node::cleanNode() {
	if (up != NULL) {
		if (up->cleanNode()) {
			delete up;
			up = NULL;
		}
			
	}
	if (down != NULL) {
		if (down->cleanNode()) {
			delete down;
			down = NULL;
		}		
	}

	if (node_walls == 0)	// If node is empty, let parent delete it
		return true;
	else {
		delete walls;
		return false;
	}
}






