#include "Elipse.h"
#include "../src/Line.h"
#include "../src/Quad.h"
#include <iostream>

using namespace std;

CElipse::CElipse()
{
	mVertices = new float* [2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = ELIPSE;
}

CElipse::~CElipse()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CElipse::display()
{
	glColor3fv(mColor);
	GLfloat* c[2];
	int a = abs(mVertices[1][0] - mVertices[0][0]), b = abs(mVertices[1][1] - mVertices[0][1]);

	minx = mVertices[0][0] - a - 2;
	miny = mVertices[0][1] - b - 2;
	maxx = mVertices[0][0] + a + 2;
	maxy = mVertices[0][1] + b + 2;

	for (int i = 0; i < 2; ++i) {
		c[i] = new GLfloat[2];
	}

	c[0][0] = minx;
	c[0][1] = miny;
	c[1][0] = maxx;
	c[1][1] = maxy;
	
	

	drawElipse(mVertices, 0, 0, relleno);

	if (picked) {

		glColor3fv(mBoundingColor);
		CQuad::drawQuad(c, 0, 0);

	}


	glEnd();
}

void CElipse::drawElipse(float** mVertices, int color, int form, int relleno)
{
	int a = abs(mVertices[1][0] - mVertices[0][0]), b = abs(mVertices[1][1] - mVertices[0][1]), x, y, d, aCuadrado, bCuadrado;
	int cx = mVertices[0][0], cy = mVertices[0][1];

	x = 0;
	y = b;
	aCuadrado = a * a;
	bCuadrado = b * b;
	d = b * ((b << 2) - (aCuadrado << 2)) + aCuadrado;

	pintar4(x, y, cx, cy, relleno);
	while (bCuadrado * ((x + 1) << 1) < aCuadrado * ((y << 1) - 1)) {

		if (d < 0)
			d = d + ((bCuadrado * ((x << 1) + 3)) << 2);
		else {
			d = d + ((bCuadrado * ((x << 1) + 3) + aCuadrado * (-(y << 1) + 2)) << 2);
			y = y - 1;
		}
		x = x + 1;

		pintar4(x, y, cx, cy, relleno);
	}

	d = bCuadrado * (((x * x) << 2) + (x << 2) + 1) + aCuadrado * (((y * y) << 2) - (y << 3) + 4) - ((aCuadrado * bCuadrado) << 2);
	while (y > 0) {

		if (d < 0) {

			d = d + ((bCuadrado * ((x + 2) << 1) + aCuadrado * (-(y << 1) + 3)) << 2);
			x = x + 1;
		}
		else {
			d = d + (aCuadrado * (-(y << 1) + 3) << 2);

		}
		y = y - 1;
		pintar4(x, y, cx, cy, relleno);
	}

}

void CElipse::pintar4(int x, int y, int x1, int y1, int relleno) {

	if (relleno) {

		glColor3fv(mFillColor);
		CLine::drawLine(x1 + x, y1 + y, x1 - x, y1 + y,0,0);
		CLine::drawLine(x1 + x, y1 - y, x1 - x, y1 - y,0,0);

	}

	glColor3fv(mColor);
	glBegin(GL_POINTS);

	glVertex2i(x1 + x, y1 + y);
	glVertex2i(x1 + x, y1 - y);
	glVertex2i(x1 - x, y1 + y);
	glVertex2i(x1 - x, y1 - y);

	glEnd();
}