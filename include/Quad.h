#ifndef INCLUDE_QUAD_H_
#define INCLUDE_QUAD_H_
#pragma once

#define GL_GLEXT_PROTOTYPES
#include "GL/gl.h"
#include "GL/glext.h"

class Quad {
public:
	Quad();
	~Quad();

	void init(float x, float y, float width, float height);

	void draw();

private:
	float x;
	float y;
	float width;
	float height;
	GLuint vboId;
};

#endif /* INCLUDE_QUAD_H_ */
