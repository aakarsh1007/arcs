#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "RANSACPoint.h"
#include "RANSACLine.h"

#define MAX_RANSAC_VERTS 2

class RANSAC {
  public:
	RANSAC(int max_itterations, double model_fit_error_max,
		   int model_fit_points_min);
	virtual ~RANSAC();
	void draw(std::vector<RANSACPoint> &points);

  private:
	GLfloat verts[3 * MAX_RANSAC_VERTS];
	GLuint VBO, VAO;
	GLuint vertex_shader, fragment_shader, shader_prog;
	void init_shaders();

	RANSACLine *run_ransac(std::vector<RANSACPoint> &points);
	void draw_line(RANSACLine *line);

	int max_itterations;
	double model_fit_error_max;
	int model_fit_points_min;
};
