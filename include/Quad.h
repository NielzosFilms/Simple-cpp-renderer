#pragma once

#define GL_GLEXT_PROTOTYPES
#include "GL/gl.h"
#include "GL/glext.h"

#include "cstddef"

#include "Vertex.h"

class Quad {
public:
	Quad();
	~Quad();

	void init(float x, float y, float width, float height);

	void draw();

	void setX(float x);

private:
	float x;
	float y;
	float width;
	float height;
	GLuint vboId;
};
