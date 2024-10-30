#include "Quad.h"
#include <iostream>

CQuad::CQuad()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = QUAD;
}

CQuad::~CQuad()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CQuad::display()
{
	
	GLint* b[2];
	GLfloat* c[2];
	
	setMinAndMax();

	for (int i = 0; i < 2; ++i) {
		b[i] = new GLint[2];
	}

	for (int i = 0; i < 2; ++i) {
		c[i] = new GLfloat[2];
	}

	if (!picked) {

		//setMinAndMax();

	}
	//glColor3fv(mColor);

	b[0][0] = (int)mVertices[0][0];
	b[0][1] = (int)mVertices[0][1];
	b[1][0] = (int)mVertices[1][0];
	b[1][1] = (int)mVertices[1][1];

	

	if (relleno) {

		glColor3fv(mFillColor);
		for (int i = minx; i <= maxx; i++) {
			CLine::drawLine(i, miny, i, maxy, 0, 0);
		}
	}
	
	glColor3fv(mColor);
	drawQuad(mVertices, 0, 0);

	if (picked) {


		c[0][0] = minx - 2;
		c[0][1] = miny - 2;
		c[1][0] = maxx + 2;
		c[1][1] = maxy + 2;

		glColor3fv(mBoundingColor);
		CQuad::drawQuad(c, 0, 0);

	}

	/*glBegin(GL_POLYGON);
	glVertex2fv(mVertices[0]);
	glVertex2f(mVertices[0][0], mVertices[1][1]);
	glVertex2fv(mVertices[1]);
	glVertex2f(mVertices[1][0], mVertices[0][1]);*/


	glEnd();
}

void CQuad::drawQuad(float **mVertices, int color, int form) {

	//glColor3f(0.0f,1.0f,0.0f);
	GLint* b[2];
	for (int i = 0; i < 2; ++i) {
		b[i] = new GLint[2];
	}

	b[0][0] = (int)mVertices[0][0];
	b[0][1] = (int)mVertices[0][1];
	b[1][0] = (int)mVertices[1][0];
	b[1][1] = (int)mVertices[1][1];

	CLine::drawLine(b[0][0], b[0][1], b[1][0], b[0][1], 0, 0);
	CLine::drawLine(b[0][0], b[0][1], b[0][0], b[1][1], 0, 0);
	CLine::drawLine(b[1][0], b[0][1], b[1][0], b[1][1], 0, 0);
	CLine::drawLine(b[0][0], b[1][1], b[1][0], b[1][1], 0, 0);

}