#include "Quad.h"

Quad::Quad() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	vboId = 0;
}
;

void Quad::init(float x, float y, float width, float height) {
	Quad::x = x;
	Quad::y = y;
	Quad::width = width;
	Quad::height = height;

	if (vboId == 0) {
		glGenBuffers(1, &vboId);
	}

	Vertex vertexData[6];

	// Triangle 1
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;
	vertexData[0].color.r = 168;
	vertexData[0].color.g = 39;
	vertexData[0].color.b = 93;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;
	vertexData[1].color.r = 217;
	vertexData[1].color.g = 98;
	vertexData[1].color.b = 151;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;
	vertexData[2].color.r = 136;
	vertexData[2].color.g = 201;
	vertexData[2].color.b = 209;

// Triangle 2
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;
	vertexData[3].color.r = 136;
	vertexData[3].color.g = 201;
	vertexData[3].color.b = 209;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;
	vertexData[4].color.r = 10;
	vertexData[4].color.g = 104;
	vertexData[4].color.b = 116;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;
	vertexData[5].color.r = 168;
	vertexData[5].color.g = 39;
	vertexData[5].color.b = 93;

	for (int i = 0; i < 6; i++) {
		vertexData[i].color.a = 255;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
		GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
;

Quad::~Quad() {
	if (vboId != 0) {
		glDeleteBuffers(1, &vboId);
	}
}

void Quad::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glEnableVertexAttribArray(0);

	// Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*) offsetof(Vertex, position));
	// Color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
		(void*) offsetof(Vertex, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Quad::setX(float x) {
	Quad::x = x;
}
