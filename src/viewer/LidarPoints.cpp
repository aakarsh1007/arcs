#include "LidarPoints.h"
#include "comms.hpp"
#include <string.h>
#include <iostream>
#include <cmath>
#include "gl_common.h"

const GLchar *lidar_vertex_shader_src =
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main() {\n"
	"\tgl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\n\0";

const GLchar *lidar_fragment_shader_src =
	"#version 330 core\n"
	"out vec4 color;\n"
	"void main() {\n"
	"\tcolor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

void LidarPoints::update_verts() {
	verts_len = 0;

	for (int i = 0; i < 360; i++) {
		int32_t dist = lidar_data.dist[i];
		float f_dist = (float)dist;
		f_dist /= 1000.0; // to meters
		f_dist /= 5.0;	// scale size
		float x = f_dist * cos(((float)i + 90) * (M_PI / 180.0));
		float y = f_dist * sin(((float)i + 90) * (M_PI / 180.0));
		add_vert(x, y);
	}
}

void LidarPoints::add_vert(GLfloat x, GLfloat y) {
	if (verts_len >= MAX_LIDAR_VERTS) {
		std::cerr << "Exceded max verts" << std::endl;
		exit(1);
	}
	verts[verts_len * 3] = x;
	verts[verts_len * 3 + 1] = y;
	verts[verts_len * 3 + 2] = 0.0; // 2d
	verts_len++;
}

void LidarPoints::init_shaders() {
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &lidar_vertex_shader_src, NULL);
	glCompileShader(vertex_shader);
	verify_shader(vertex_shader, "Vertex shader");

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &lidar_fragment_shader_src, NULL);
	glCompileShader(fragment_shader);
	verify_shader(fragment_shader, "Fragment shader");

	shader_prog = glCreateProgram();
	glAttachShader(shader_prog, vertex_shader);
	glAttachShader(shader_prog, fragment_shader);
	glLinkProgram(shader_prog);

	GLint ret;
	glGetProgramiv(shader_prog, GL_LINK_STATUS, &ret);
	if (!ret) {
		std::cerr << "Linking shader failed" << std::endl;
		exit(ret);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void init_vao(GLuint *VAO, GLuint *VBO, GLfloat verts[], int &verts_len) {
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glBindVertexArray(*VAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, *VBO);
		glBufferData(GL_ARRAY_BUFFER, verts_len, verts, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
							  (GLvoid *)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}

LidarPoints::LidarPoints() {
	verts_len = 0;
	memchr(&verts, 0, sizeof(verts));
	init_shaders();
	init_vao(&VAO, &VBO, verts, verts_len);
}

LidarPoints::~LidarPoints() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void LidarPoints::draw() {
	update_verts();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(shader_prog);
	glBindVertexArray(VAO);
	glPointSize(3);
	glDrawArrays(GL_POINTS, 0, verts_len);
	glBindVertexArray(0);
}
