#include "Display.h"


Display::Display(Double2 window_size, Wall* walls, int n_walls, Player* player) {													// Setup window
	int width = window_size.x;
	int height = window_size.y;
	this->player = player;
	room_height = height * 2 / 3;
	this->window_size = window_size;
	this->center = window_size * 0.5;

	all_walls = walls;
	total_walls = n_walls;

	scanline = Scanline(width);

	visibleSegments = new sf::VertexArray[10000];


	// Make two identical views
	front_view = new sf::RenderWindow(sf::VideoMode(width, height), "Front View", sf::Style::Close);
	top_view = new sf::RenderWindow(sf::VideoMode(width, height), "Top view", sf::Style::Close);
	top_view->setPosition(sf::Vector2i(0, 300));
	front_view->setPosition(sf::Vector2i(width, 300));

	image = new sf::Image();															// Background color
	image->create(width, height, sf::Color(0xEB, 0xEB, 0xEB));
	texture.loadFromImage(*image);
	sprite.setTexture(texture, true);
	front_view->draw(sprite);
	top_view->draw(sprite);
}




void Display::renderTopView() {
	sf::VertexArray bg(sf::Quads, 4);
	bg[0].position = sf::Vector2f(0, 0);
	bg[1].position = sf::Vector2f(0, window_size.y);
	bg[2].position = sf::Vector2f(window_size.x, window_size.y);
	bg[3].position = sf::Vector2f(window_size.x, 0);
	for (int i = 0; i < 4; i++)
		bg[i].color = sf::Color(255, 255, 255, 255);
	top_view->draw(bg);

	for (int i = 0; i < total_walls; i++) {
		Wall wall = all_walls[i];
		sf::RectangleShape line(sf::Vector2f(wall.len, 3));
		line.setFillColor(sf::Color(250, 120, 50));
		if (i == 1)
			line.setFillColor(sf::Color(50, 120, 250));
		line.rotate(-wall.angle/(2*3.14)*360);
		line.setPosition((int)wall.p1.x, (int)(window_size.y - wall.p1.y));
		top_view->draw(line);
	}

	Vec3d leftnormal = player->focal_normal.rotate(3.14/2);
	Vec3d rightnormal = player->focal_normal.rotate(-3.14 / 2);

	Vec3d left = player->pos + player->focal_normal * 10000 * player->focal_len + leftnormal * 10000;
	Vec3d right = player->pos + player->focal_normal * 10000 * player->focal_len + rightnormal * 10000;

	sf::VertexArray triangle(sf::Triangles, 3);
	triangle[0].position = sf::Vector2f(player->pos.x, window_size.y - player->pos.y);
	triangle[1].position = sf::Vector2f(left.x, window_size.y - left.y);
	triangle[2].position = sf::Vector2f(right.x, window_size.y - right.y);
	for (int i = 0; i < 3; i++)
		triangle[i].color = sf::Color(0, 0, 50, 10);
	top_view->draw(triangle);
	top_view->display();
}

void Display::prepFront() {
	sf::VertexArray ground(sf::Quads, 4);
	ground[0].position = sf::Vector2f(0, window_size.y);
	ground[1].position = sf::Vector2f(window_size.x, window_size.y);
	ground[2].position = sf::Vector2f(window_size.x, window_size.y/2);
	ground[3].position = sf::Vector2f(0, window_size.y/2);
	for (int i = 0; i < 4; i++)	
		ground[i].color = sf::Color(50, 0, 0, 150);
	front_view->draw(ground);


	sf::VertexArray roof(sf::Quads, 4);
	roof[0].position = sf::Vector2f(0, 0);
	roof[1].position = sf::Vector2f(window_size.x, 0);
	roof[2].position = sf::Vector2f(window_size.x, window_size.y / 2);
	roof[3].position = sf::Vector2f(0, window_size.y / 2);
	for (int i = 0; i < 4; i++)
		roof[i].color = sf::Color(50, 50, 50, 200);
	front_view->draw(roof);

}


void Display::drawWallsegment(Wall* wallsegment) {
	addSegment(wallsegment);
}

void Display::clearWalls() {
	n_visible = 0;
	scanline.clear();
}



Vec3d intersectPoint(Vec3d rayVector, Vec3d rayPoint, Vec3d planeNormal, Vec3d planePoint) {
	Vec3d diff = rayPoint - planePoint;
	double prod1 = diff.dot(planeNormal);
	double prod2 = rayVector.dot(planeNormal);
	double prod3 = prod1 / prod2;
	return rayPoint - rayVector * prod3;
}

Double2 Display::projectOnFocalPlane(Vec3d point) {
	Vec3d wall_point, intersect, projection;
	//wall_point = Vec3d(point.x, point.y, 0);
	intersect = intersectPoint(player->pos - point, point, player->focal_normal, player->focal_origo);
	projection = (intersect - player->focal_origo).rotate(3.14 - player->angle);
	//printf("Projection: %f     %f     %f \n", projection.x, projection.y, projection.z);
	return Double2(center.x + projection.y * center.x, center.y + projection.z * center.x);
}

void Display::handleWallBehindPlayer(Vec3d* wall1, Vec3d* wall2, Wall* wallsegment) {
	Vec3d w1(wallsegment->p1.x, wallsegment->p1.y, 0);
	Vec3d w2(wallsegment->p2.x, wallsegment->p2.y, 0);

	bool behind1 = (player->pos - w1).dot(player->focal_normal) > 0;// && (player->pos - w2).dot(player->focal_normal);
	bool behind2 = (player->pos - w2).dot(player->focal_normal) > 0;

	if (behind1 && behind2)	// Wall is completely behind player.
		return;
	else if (behind1) {
		Vec3d wall_focalp_intersect = intersectPoint(w1 - w2, w2, player->focal_normal, player->focal_origo);
		w1.x = wall_focalp_intersect.x;
		w1.y = wall_focalp_intersect.y;
	}
	else if (behind2) {
		Vec3d wall_focalp_intersect = intersectPoint(w1 - w2, w2, player->focal_normal, player->focal_origo);
		w2.x = wall_focalp_intersect.x;
		w2.y = wall_focalp_intersect.y;
	}
	*wall1 = w1;
	*wall2 = w2;
}


void Display::handleFlipwall(Double2* bottomright, Double2* topright, Double2* bottomleft, Double2* topleft) {
	if (bottomright->x < bottomleft->x) {
		Double2 tmpbottom = *bottomright;
		Double2 tmptop = *topright;
		*bottomright = *bottomleft;
		*topright = *topleft;
		*bottomleft = tmpbottom;
		*topleft = tmptop;
	}
}





void Display::addSegment(Wall* wallsegment) {
	Vec3d wall_point, intersect, projection;
	double projection_scaling = center.x;

	// Handle some special cases
	Vec3d w1, w2;
	handleWallBehindPlayer(&w1, &w2, wallsegment);




	Double2 bottomleft = projectOnFocalPlane(Vec3d(w1.x, w1.y, 0));
	Double2 topleft = projectOnFocalPlane(Vec3d(w1.x, w1.y, 100));
	Double2 topright = projectOnFocalPlane(Vec3d(w2.x, w2.y, 100));
	Double2 bottomright = projectOnFocalPlane(Vec3d(w2.x, w2.y, 0));



	if (bottomleft.x == bottomright.x) {
		printf("VERY BAD\n");
		return;
	}




	//---------------------------------- Constrain wall vectors to the frame, and sort from left to right---------------------------------//
	handleFlipwall(&bottomright, &topright, &bottomleft, &topleft);

	Double2 bottom_unit = (bottomright - bottomleft);
	Double2 top_unit = (topright - topleft);
	bottom_unit = bottom_unit * (1 / bottom_unit.x);
	top_unit = top_unit * (1 / top_unit.x);


	if (bottomleft.x < 0) {
		double dif = 0 - bottomleft.x;
		bottomleft = bottomleft + bottom_unit * dif;
		topleft = topleft + top_unit * dif;
	}
	if (bottomright.x > window_size.x) {
		double dif = bottomright.x - window_size.x;
		bottomright = bottomright - bottom_unit * dif;
		topright = topright - top_unit * dif;
	}




	Double2 request_scanline(bottomleft.x, bottomright.x);
	int n_segments = 0;
	Double2* segmentlist = scanline.request(request_scanline, &n_segments);
	for (int i = 0; i < n_segments; i++) {
		sf::VertexArray segment(sf::Quads, 4);
		Double2 fromto = segmentlist[i];
		//printf("Permission: %f  ->  %f\n", fromto.x, fromto.y);
		
		double relative_start = fromto.x - bottomleft.x;
		double relative_end = fromto.y - bottomleft.x;
		Double2 bl = bottomleft + bottom_unit * relative_start;
		Double2 tl = topleft + top_unit * relative_start;
		Double2 br = bottomleft + bottom_unit * relative_end;
		Double2 tr = topleft + top_unit * relative_end;


		segment[0].position = sf::Vector2f(bl.x, window_size.y - bl.y);
		segment[1].position = sf::Vector2f(tl.x, window_size.y - tl.y);
		segment[2].position = sf::Vector2f(tr.x, window_size.y - tr.y);
		segment[3].position = sf::Vector2f(br.x, window_size.y - br.y);
		

		for (int i = 0; i < 4; i++)
			segment[i].color = sf::Color(250, 50 * i, 50, 255);
		visibleSegments[n_visible++] = segment;

	}
}

void Display::renderFront() {
	top_view->clear();
	renderTopView();
	front_view->clear();
	prepFront();
	for (int i = 0; i < n_visible; i++) {
		front_view->draw(visibleSegments[i]);
	}

	front_view->display();
}