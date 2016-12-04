#include "gl_common.h"

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
