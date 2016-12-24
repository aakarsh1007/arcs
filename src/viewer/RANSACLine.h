#pragma once
#include <vector>
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

	int points_within(const std::vector<RANSACPoint> &points, double distance);
	int points_within(const std::vector<RANSACPoint> &points, double distance,
					  std::vector<RANSACPoint> &within);
	int points_within_limited(const std::vector<RANSACPoint> &points,
							  double distance);
	int points_within_limited(const std::vector<RANSACPoint> &points,
							  double distance,
							  std::vector<RANSACPoint> &within);
	int points_not_within(const std::vector<RANSACPoint> &points,
						  double distance);
	int points_not_within(const std::vector<RANSACPoint> &points,
						  double distance, std::vector<RANSACPoint> &within);
	double distance_from_midpoint(const RANSACPoint &point);
	double length();
};
