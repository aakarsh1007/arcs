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

void RANSACLine::draw() {}

double RANSACLine::distance(double x, double y) {
	double denominator = sqrt(pow(y1 - y2, 2) + pow(x1 - x2, 2));
	double numerator =
		std::abs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1);
	return numerator / denominator;
}

RANSACLine::~RANSACLine() {}
