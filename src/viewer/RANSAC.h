#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_RANSAC_VERTS 2

class RANSAC {
  public:
	RANSAC();
	virtual ~RANSAC();
	void draw();

  private:
	GLfloat verts[3 * MAX_RANSAC_VERTS];
	GLuint VBO, VAO;
	GLuint vertex_shader, fragment_shader, shader_prog;
	void init_shaders();
};
