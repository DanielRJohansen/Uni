#include "BSP.h"
#include<time.h>




BSP::BSP(Wall* walls, int n_walls) {
	fragments = n_walls;
	root = new Node(n_walls, &fragments);
	shuffleWalls(walls, n_walls);
	for (int i = 0; i < n_walls; i++) {
		root->assign(&walls[i]);
	}
	root->partition();
	root->cleanNode();
	printf("BSP on %d walls finished, creating %d fragments.\n", n_walls, fragments);
}



void BSP::paint(Player* player, Display* display) {
	display->clearWalls();
	root->painters(player, display);
	display->renderFront();
}

void BSP::shuffleWalls(Wall* walls, int n_walls) {
	Wall* copy = new Wall[n_walls];
	for (int i = 0; i < n_walls; i++)
		copy[i] = walls[i];

	for (int i = 0; i < n_walls; i++) {
		int random_index = rand()%(n_walls-i);
		walls[i] = copy[random_index];
		copy[random_index] = copy[n_walls - 1 - i];
	}
	delete copy;
}




















void BSP::Node::painters(Player* player, Display* display) {
	Double2 relative_direction = (player->pos_2d - this->origo).normalize();
	double dp = relative_direction.dot(this->normal_down);
	Node* node_order[2];
	if (dp > 0) {
		node_order[0] = down;
		node_order[1] = up;
	}
	else {
		node_order[0] = up;
		node_order[1] = down;
	}
	

	if (node_order[0] != NULL) {
		node_order[0]->painters(player, display);
	}
	this->paint(display);
	if (node_order[1] != NULL) {
		node_order[1]->painters(player, display);
	}

}

void BSP::Node::paint(Display* display) {
	Wall* node_walls = wallcontainer->getWalls();
	for (int i = 0; i < wallcontainer->n_walls; i++) {
		display->drawWallsegment(&node_walls[i]);
	}
	delete node_walls;
}



void BSP::Node::partition() {
	if (node_walls == 0) // In case the parent put all walls in the other Node.
		return;
	

	wallcontainer = new WallContainer(walls[0]);
	normal_down = walls[0].getNormalDown();
	origo = walls[0].p1;


	if (node_walls > 1) {
		down = new Node(node_walls, fragments);
		up = new Node(node_walls, fragments);

		leaf = false;
		for (int i = 1; i < node_walls; i++) {	// The first wall is contained in this node, thus NOT distributed to children.
			determineWall(&walls[i]);
		}
		down->partition();
		up->partition();
	}
}


void BSP::Node::determineWall(Wall* wall) {					
	Double2 wall_nd = wall->getNormalDown();	

	double dotp_p1 = (wall->p1 - origo).normalize(true).dot(normal_down);
	double dotp_p2 = (wall->p2 - origo).normalize(true).dot(normal_down);

	// Handle the lack of precision when rotating vectors.
	dotp_p1 = (abs(dotp_p1) < 0.00001) ? 0 : dotp_p1;
	dotp_p2 = (abs(dotp_p2) < 0.00001) ? 0 : dotp_p2;

	if (dotp_p1 == 0 && dotp_p2 == 0) {	// Case where wall is inside and parallel with line.
		wallcontainer->add(*wall);
		return;
	}

	// This is a wierd maneuvrer but we want both booleans to contain a wall starting exactly on the line.
	bool p1_below =  dotp_p1 >= 0;
	bool p2_below = dotp_p2 >= 0;
	bool p1_above = dotp_p1 <= 0;
	bool p2_above = dotp_p2 <= 0;


	if (p1_below && p2_below) {
		down->assign(wall);
	}
	else if (p1_above && p2_above) {
		up->assign(wall);
	}
	else {
		Double2 splitpoint = wallcontainer->wall.intersect(*wall);
		Wall bottom_wall, top_wall;
		if (p1_below && p2_above) {							// I think dual checks is necessary
			top_wall = Wall(wall->p2, splitpoint);			
			bottom_wall = Wall(splitpoint, wall->p1);
		}
		else {
			top_wall = Wall(splitpoint, wall->p1);
			bottom_wall = Wall(wall->p2, splitpoint);
		}

		up->assign(&top_wall);
		down->assign(&bottom_wall);

		*fragments = *fragments + 1;	// One extra
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

	delete walls;	// Walls already distributed to child nodes.

	if (node_walls == 0) {	// If node is empty, let parent delete it
		return true;
	}
	else {
		return false;
	}
}






