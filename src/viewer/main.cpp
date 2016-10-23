#include <iostream>
#include "comms.hpp"
#include <cmath>
#include <pthread.h>

using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define NAME "arcs LIDAR viewer"

const GLchar *vertex_shader_src =
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main() {\n"
	"\tgl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\n\0";

const GLchar *fragment_shader_src = "#version 330 core\n"
									"out vec4 color;\n"
									"void main() {\n"
									"\tcolor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
									"}\n\0";

const GLuint WIDTH = 1280, HEIGHT = 720;
GLuint vertex_shader, fragment_shader, shader_prog;
GLuint VBO, VAO;
GLFWwindow *window;

// Triangle shape default
#define MAX_VERTS 1024
GLfloat verts[3 * MAX_VERTS] = {-.5, -.5, 0.0, .5, -.5, 0.0, 0.0, .5, 0.0};
int verts_len = 3;

const GLfloat bg_color[3] = {0.2, 0.3, 0.3};

void key_callback(GLFWwindow *w, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void verify_shader(GLuint shader, std::string str) {
	GLint ret;
	GLchar msg[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	if (!ret) {
		glGetShaderInfoLog(shader, 512, NULL, msg);
		std::cerr << str << " comilation error: " << msg << std::endl;
		exit(ret);
	}
}

void init_vao() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verts_len, verts, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
							  (GLvoid *)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}

void init_shaders() {
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
	glCompileShader(vertex_shader);
	verify_shader(vertex_shader, "Vertex shader");

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
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

void init_window() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, NAME, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
}

void init() {
	init_comms();
	init_window();
	init_shaders();
	init_vao();
}

void clear_screen() {
	glClearColor(bg_color[0], bg_color[1], bg_color[2], 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void add_vert(GLfloat x, GLfloat y) {
	if (verts_len >= MAX_VERTS) {
		std::cerr << "Exceded max verts" << std::endl;
		exit(1);
	}
	verts[verts_len * 3] = x;
	verts[verts_len * 3 + 1] = y;
	verts[verts_len * 3 + 2] = 0.0; // 2d
	verts_len++;
}

void update_verts() {
	verts_len = 0;

	for (int i = 0; i < 360; i++) {
		int32_t dist = lidar_data.dist[i];
		float f_dist = (float)dist;
		f_dist /= 1000.0; // to meters
		f_dist /= 5.0;	// scale size
		float x = f_dist * cos(((float)i) * (M_PI / 180.0));
		float y = f_dist * sin(((float)i) * (M_PI / 180.0));
		add_vert(x, y);
	}
}

void draw() {
	update_verts();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(shader_prog);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_LOOP, 0, verts_len);
	glBindVertexArray(0);
}

void update_title() {
	std::string title = NAME;
	title += " | RPM: ";
	title += to_string(lidar_data.speed / 64);
	glfwSetWindowTitle(window, title.c_str());
}

void loop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		update_title();
		clear_screen();
		draw();
		glfwSwapBuffers(window);
	}
}

void close() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	close_comms();
	exit(0);
}

int main() {
	init();
	loop();
	close();
}
