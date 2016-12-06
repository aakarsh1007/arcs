#pragma once
#include "RANSACPoint.h"

class RANSACLine {
  public:
	RANSACLine(double x1, double y1, double x2, double y2);
	RANSACLine(RANSACPoint p1, RANSACPoint p2);
	virtual ~RANSACLine();
	double x1, y1, x2, y2;
	double distance(double x, double y);
	double distance(RANSACPoint p);
	void scale(double scalar);
	void draw();
};
