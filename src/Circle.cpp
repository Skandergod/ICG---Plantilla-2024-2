#include "Circle.h"
#include "Quad.h"
#include "Line.h"
#include <stdlib.h>

Ccircle::Ccircle()
{
	mVertices = new float* [2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = CIRCLE;
}

Ccircle::~Ccircle()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void Ccircle::display()
{

	GLfloat* b[2], x, y, r;
	GLfloat* c[2];

	for (int i = 0; i < 2; ++i) {
		b[i] = new GLfloat[2];
	}
	for (int i = 0; i < 2; ++i) {
		c[i] = new GLfloat[2];
	}

	glColor3fv(mColor);

	b[0][0] = (int)mVertices[0][0];
	b[0][1] = (int)mVertices[0][1];
	b[1][0] = (int)mVertices[1][0];
	b[1][1] = (int)mVertices[1][1];

	rx = mVertices[0][0] - mVertices[1][0];
	if (rx < 0) {
		rx = rx * -1;
	}
	ry = mVertices[0][1] - mVertices[1][1];
	if (ry < 0) {
		ry = ry * -1;
	}

	r = rx;
	if (ry > rx) {
		r = ry;
	}
	x = 0;
	y = r;

	minx = c[0][0] = mVertices[0][0] - r - 2;
	miny = c[0][1] = mVertices[0][1] - r - 2;

	maxx = c[1][0] = mVertices[0][0] + r + 2;
	maxy = c[1][1] = mVertices[0][1] + r + 2;


	drawCircle(b[0][0], b[0][1], x, y, r, 0);

	if (picked) {

		glColor3fv(mBoundingColor);
		CQuad::drawQuad(c, 0, 0);

	}

}

void Ccircle::drawCircle(int x1, int y1, int x2, int y2, int r, int fill) {

	int d = 1 - r;

	if (fill) {
		CLine::drawLine(x1 - r, y1, x2 + r, y1, 0, 0);
	}
	draw8points(x1, y1, x2, y2, fill);

	while (y2 > x2) {

		if (d < 0) {
			d = d + (x2 << 1) + 3;
		}
		else {
			d += ((x2 - y2) << 1) + 5;
			y2 = y2 - 1;
		}
		
		x2 = x2 + 1;
		draw8points(x1, y1, x2, y2, fill);
	}
	

}

void Ccircle::draw8points(int x1, int y1, int x2, int y2, int fill) {
	
	if (relleno) {

		glColor3fv(mFillColor);
		drawLine(x1 - x2, x1 + x2 + 1, y1 + y2 - 1);
		drawLine(x1 - y2 + 1, x1 + y2, y1 + x2);
		drawLine(x1 - y2 + 1, x1 + y2, y1 - x2);
		drawLine(x1 - x2, x1 + x2 + 1, y1 - y2 + 1);
	}

	//glColor3f(0.0f,1.0f,0.0f);

	glColor3fv(mColor);
	glBegin(GL_POINTS);
	glVertex2i(x1 + x2, y1 + y2);
	glVertex2i(x1 + x2, y1 - y2);
	glVertex2i(x1 - x2, y1 + y2);
	glVertex2i(x1 - x2, y1 - y2);
	glVertex2i(x1 + y2, y1 + x2);
	glVertex2i(x1 + y2, y1 - x2);
	glVertex2i(x1 - y2, y1 + x2);
	glVertex2i(x1 - y2, y1 - x2);
	glEnd();

}

void Ccircle::drawLine(int xmin, int xmax, int y) {
	glBegin(GL_POINTS);
	for (int x = xmin; x <= xmax; ++x)
		glVertex2i(x, y);
	glEnd();
}