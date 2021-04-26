#include "BSP.h"





BSP::BSP(Wall* walls, int n_walls) {
	root = new Node(n_walls);
	for (int i = 0; i < n_walls; i++) {
		root->assign(&walls[i]);
	}
	root->partition();
	root->cleanNode();
	printf("BSP finished!\n");
}



void BSP::paint(Player* player, Display* display) {
	display->clearWalls();
	root->painters(player, display);
	display->renderFront();
}


void BSP::Node::painters(Player* player, Display* display) {
	Double2 relative_direction = (player->pos_2d - this->origo).normalize();
	double dp = relative_direction.dot(this->normal_down);
	Node* node_order[2];
	printf("%f\n", dp);
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
}



void BSP::Node::partition() {
	printf("Partitioning %d walls\n", node_walls);
	if (node_walls == 0) // In case the parent put all walls in the other Node.
		return;
	

	wallcontainer = new WallContainer(walls[0]);
	normal_down = walls[0].getNormalDown();
	origo = walls[0].p1;


	if (node_walls > 1) {
		down = new Node(node_walls);
		up = new Node(node_walls);

		leaf = false;
		for (int i = 1; i < node_walls; i++) {	// The first wall is contained in this node, thus NOT distributed to children.
			determineWall(&walls[i]);
		}
		down->partition();
		up->partition();
	}
}


void BSP::Node::determineWall(Wall* wall) {					// FIX CASE WHERE POINTS ARE IN THE VECTOR-LINE
	Double2 wall_nd = wall->getNormalDown();	// Case where wall is inside and parallel with line.

	double dotp_p1 = (wall->p1 - origo).normalize().dot(normal_down);
	double dotp_p2 = (wall->p2 - origo).normalize().dot(normal_down);
	if (abs(dotp_p1) < 0.00001 && abs(dotp_p2) < 0.00001) {	// Sadly we can't compare with 0 as we are not presize enough when rotating the normal_down.
		printf("Wall in line!\n");
		wallcontainer->add(*wall);
		return;
	}

	bool p1_below =  dotp_p1 > 0;
	bool p2_below = dotp_p2 > 0;

	if (p1_below && p2_below) {
		down->assign(wall);
	}
	else if (!p1_below && !p2_below) {
		up->assign(wall);
	}
	else {
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

	delete walls;	// Walls already distributed to child nodes.

	if (node_walls == 0) {	// If node is empty, let parent delete it
		return true;
	}
	else {
		return false;
	}
}






