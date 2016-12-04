#include "RANSAC.h"
#include <string.h>
#include "gl_common.h"

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

RANSAC::RANSAC() {
	memchr(&verts, 0, sizeof(verts));
	verts[0] = verts[1] = 0;
	verts[3] = verts[4] = .5;
	init_shaders();
	init_ransac_vao(&VAO, &VBO, verts);
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

void RANSAC::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(shader_prog);
	glBindVertexArray(VAO);
	glLineWidth(1);
	glDrawArrays(GL_LINES, 0, MAX_RANSAC_VERTS);
	glBindVertexArray(0);
}

RANSAC::~RANSAC() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
