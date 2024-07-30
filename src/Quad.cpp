#include "Quad.h"

Quad::Quad() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	vboId = 0;
};

void Quad::init(float x, float y, float width, float height) {
	Quad::x = x;
	Quad::y = y;
	Quad::width = width;
	Quad::height = height;


	if (vboId == 0) {
		glGenBuffers(1, &vboId);
	}

	float vertexData[12];

	// Triangle 1
	vertexData[0] = x + width;
	vertexData[1] = y + height;

	vertexData[2] = x;
	vertexData[3] = y + height;

	vertexData[4] = x;
	vertexData[5] = y;

	// Triangle 2
	vertexData[6] = x;
	vertexData[7] = y;

	vertexData[8] = x + width;
	vertexData[9] = y;

	vertexData[10] = x + width;
	vertexData[11] = y + height;

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
};

Quad::~Quad() {
	if (vboId != 0) {
		glDeleteBuffers(1, &vboId);
	}
}

void Quad::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Quad::setX(float x) {
	Quad::x = x;
}
