#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_VERTS 1024

class LidarPoints {
  public:
	LidarPoints();
	virtual ~LidarPoints();
	void draw();

  private:
	GLfloat verts[3 * MAX_VERTS];
	int verts_len;
	GLuint VBO, VAO;
	GLuint vertex_shader, fragment_shader, shader_prog;
	void init_shaders();
	void update_verts();
	void add_vert(GLfloat x, GLfloat y);
};
