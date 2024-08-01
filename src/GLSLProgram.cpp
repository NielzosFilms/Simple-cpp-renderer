#include "GLSLProgram.h"

GLSLProgram::GLSLProgram() :
	programId(0), vertexId(0), fragmentId(0), attrCount(0) {

}

GLSLProgram::~GLSLProgram() {

}

void GLSLProgram::compile(const std::string &vertexFilePath,
	const std::string &fragmentFilePath) {
	programId = glCreateProgram();

	vertexId = glCreateShader(GL_VERTEX_SHADER);
	if (vertexId == 0) {
		fatalError("Failed to create vertex shader");
	}

	fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentId == 0) {
		fatalError("Failed to create fragment shader");
	}

	compileShader(vertexFilePath, vertexId);
	compileShader(fragmentFilePath, fragmentId);
}

void GLSLProgram::link() {
	glAttachShader(programId, vertexId);
	glAttachShader(programId, fragmentId);

	glLinkProgram(programId);

	GLint isLinked = 0;
	glGetProgramiv(programId, GL_LINK_STATUS, (int*) &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(programId, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(programId);
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);

		std::printf("%s\n", &errorLog[0]);
		fatalError("Failed to link shader program");
	}

	glDetachShader(programId, vertexId);
	glDetachShader(programId, fragmentId);
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void GLSLProgram::addAttribute(const std::string &attrName) {
	glBindAttribLocation(programId, attrCount++, attrName.c_str());
}

void GLSLProgram::use() {
	glUseProgram(programId);
	for (int i = 0; i < attrCount; i++) {
		glEnableVertexAttribArray(i);
	}
}
void GLSLProgram::unuse() {
	glUseProgram(0);
	for (int i = 0; i < attrCount; i++) {
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::compileShader(const std::string &filePath, GLuint id) {
	std::ifstream shaderFile(filePath);
	if (shaderFile.fail()) {
		perror(filePath.c_str());
		fatalError("Failed to open shader file [" + filePath + "]");
	}

	std::string fileContents = "";
	std::string line;
	while (std::getline(shaderFile, line)) {
		fileContents += line + "\n";
	}

	shaderFile.close();

	const char *contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		std::printf("%s\n", &errorLog[0]);
		fatalError("Failed to compile shader [" + filePath + "]");
	}
}

