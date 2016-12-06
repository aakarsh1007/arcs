#include "RANSACLine.h"
#include <cmath>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

RANSACLine::RANSACLine(double x1, double y1, double x2, double y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

RANSACLine::RANSACLine(RANSACPoint p1, RANSACPoint p2) {
	this->x1 = p1.x;
	this->y1 = p1.y;
	this->x2 = p2.x;
	this->y2 = p2.y;
}

void RANSACLine::draw() {}

double RANSACLine::distance(RANSACPoint p) { return distance(p.x, p.y); }

double RANSACLine::distance(double x, double y) {
	double denominator = sqrt(pow(y1 - y2, 2) + pow(x1 - x2, 2));
	double numerator =
		sqrt(pow(((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1), 2));
	return numerator / denominator;
}

int RANSACLine::points_within(const std::vector<RANSACPoint> &points,
							  double distance) {
	int out = 0;
	for (RANSACPoint p : points)
		if (this->distance(p) <= distance)
			out++;
	return out;
}
int RANSACLine::points_within(const std::vector<RANSACPoint> &points,
							  double distance,
							  std::vector<RANSACPoint> &within) {
	int out = 0;
	for (RANSACPoint p : points)
		if (this->distance(p) <= distance) {
			out++;
			within.push_back(p);
		}
	return out;
}

int RANSACLine::points_not_within(const std::vector<RANSACPoint> &points,
								  double distance) {
	int out = 0;
	for (RANSACPoint p : points)
		if (this->distance(p) > distance)
			out++;
	return out;
}
int RANSACLine::points_not_within(const std::vector<RANSACPoint> &points,
								  double distance,
								  std::vector<RANSACPoint> &within) {
	int out = 0;
	for (RANSACPoint p : points)
		if (this->distance(p) > distance) {
			out++;
			within.push_back(p);
		}
	return out;
}

void RANSACLine::scale(double scalar) {
	RANSACPoint midpoint = RANSACPoint((x1 + x2) / 2.0, (y1 + y2) / 2.0);
	x1 -= midpoint.x;
	y1 -= midpoint.y;
	x2 -= midpoint.x;
	y2 -= midpoint.y;

	x1 *= scalar;
	y1 *= scalar;
	x2 *= scalar;
	y2 *= scalar;

	x1 += midpoint.x;
	y1 += midpoint.y;
	x2 += midpoint.x;
	y2 += midpoint.y;
}

RANSACLine::~RANSACLine() {}
