#pragma once

#include "string"
#include "fstream"
#include "vector"

#define GL_GLEXT_PROTOTYPES
#include "GL/gl.h"
#include "GL/glext.h"

#include "Errors.h"

class GLSLProgram {
public:
	GLSLProgram();
	~GLSLProgram();

	void compile(const std::string &vertexFilePath,
		const std::string &fragmentFilePath);

	void link();

	void addAttribute(const std::string &attrName);

	GLuint getUniformLocation(const std::string &name);

	void use();
	void unuse();

private:
	GLuint programId;
	GLuint vertexId;
	GLuint fragmentId;

	int attrCount;

	void compileShader(const std::string &filePath, GLuint id);
};
