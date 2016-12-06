#include "RANSAC.h"
#include <string.h>
#include <float.h>
#include <random>
#include <algorithm>
#include "gl_common.h"
#include "RANSACLine.h"
#include "RANSACPoint.h"

const GLchar *ransac_vertex_shader_src =
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main() {\n"
	"\tgl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\n\0";

const GLchar *ransac_fragment_shader_src =
	"#version 330 core\n"
	"out vec4 color;\n"
	"void main() {\n"
	"\tcolor = vec4(0.11f, 0.74f, 0.95f, 1.0f);\n"
	"}\n\0";

int random_index(int max) {
	static std::default_random_engine rng{};
	static std::uniform_int_distribution<int> dist{0, max};
	return dist(rng);
}

void init_ransac_vao(GLuint *VAO, GLuint *VBO, GLfloat verts[]) {
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glBindVertexArray(*VAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, *VBO);
		glBufferData(GL_ARRAY_BUFFER, MAX_RANSAC_VERTS, verts, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
							  (GLvoid *)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}

RANSAC::RANSAC(int max_itterations, double model_fit_error_max,
			   int model_fit_points_min) {
	memchr(&verts, 0, sizeof(verts));
	verts[0] = verts[1] = 0;
	verts[3] = verts[4] = .5;
	init_shaders();
	init_ransac_vao(&VAO, &VBO, verts);
	this->max_itterations = max_itterations;
	this->model_fit_error_max = model_fit_error_max;
	this->model_fit_points_min = model_fit_points_min;
}

void RANSAC::init_shaders() {
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &ransac_vertex_shader_src, NULL);
	glCompileShader(vertex_shader);
	verify_shader(vertex_shader, "Vertex shader");

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &ransac_fragment_shader_src, NULL);
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

RANSACLine *RANSAC::run_ransac(std::vector<RANSACPoint> &points) {
	if (points.size() < 4) {
		std::cout << "Skipping RANSAC due to insufficient data: "
				  << points.size() << " points" << std::endl;
		return nullptr;
	}

	int iterations = 0;
	RANSACLine *bestfit = nullptr;
	double best_error = DBL_MAX; // Something really large
	int points_size = points.size();
	while (iterations < max_itterations) {
		// Guess
		int index1 = random_index(points_size - 1);
		int index2 = index1;
		while (index1 == index2)
			index2 = random_index(points_size - 1);

		RANSACPoint p1 = points[index1];
		RANSACPoint p2 = points[index2];

		std::vector<RANSACPoint> others(points);
		// Delete chosen two two by index
		others.erase(others.begin() + std::max(index1, index2));
		others.erase(others.begin() + std::min(index1, index2));

		RANSACLine *model = new RANSACLine(p1, p2);
		std::vector<RANSACPoint> in_model;
		for (RANSACPoint p : others) {
			if (model->distance(p) < model_fit_error_max)
				in_model.push_back(p);
		}

		if (in_model.size() >= model_fit_points_min) {
			double current_error = 0;
			//			for (RANSACPoint p : in_model) {
			//				double tmp = model->distance(p);
			//				if (tmp > 2 * model_fit_error_max)
			//					continue;
			//				current_error += tmp;
			//			}

			current_error = 1.0 / (double)in_model.size();

			if (best_error > current_error) {
				best_error = current_error;
				bestfit = model;
			} else {
				delete model;
			}
		} else {
			delete model;
		}

		iterations++;
	}

	std::cout << "Best error: " << 1 / best_error << std::endl;
	return bestfit;
}

void RANSAC::draw_line(RANSACLine *line) {
	line->scale(50);
	verts[0] = line->x1;
	verts[1] = line->y1;
	verts[3] = line->x2;
	verts[4] = line->y2;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(shader_prog);
	glBindVertexArray(VAO);
	glLineWidth(3);
	glDrawArrays(GL_LINES, 0, MAX_RANSAC_VERTS);
	glBindVertexArray(0);
}

void RANSAC::draw(std::vector<RANSACPoint> &points) {
	RANSACLine *best_guess = run_ransac(points);

	if (best_guess == nullptr)
		return;

	draw_line(best_guess);

	delete best_guess;
}

RANSAC::~RANSAC() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
