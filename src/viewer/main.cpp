#include <iostream>
#include "comms.hpp"
#include <cmath>
#include <cstdlib>
#include <pthread.h>
#include <vector>
#include "LidarPoints.h"
#include "RANSAC.h"
#include "RANSACPoint.h"

using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NAME "arcs LIDAR viewer"

const GLuint WIDTH = 1280, HEIGHT = 720;
GLFWwindow *window;

const GLfloat bg_color[3] = {0.2, 0.3, 0.3};

LidarPoints *lidar_points;
RANSAC *ransac;

void key_callback(GLFWwindow *w, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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
	lidar_points = new LidarPoints();
	ransac = new RANSAC(1000, .05 / 5.0, 25);
}

void clear_screen() {
	glClearColor(bg_color[0], bg_color[1], bg_color[2], 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void draw() {
	std::vector<RANSACPoint> points;
	lidar_points->draw(points);
	ransac->draw(points);
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
	delete lidar_points;
	glfwTerminate();
	close_comms();
	exit(0);
}

int main() {
	init();
	loop();
	close();
}
