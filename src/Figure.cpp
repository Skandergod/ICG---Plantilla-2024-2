#include "Figure.h"
#include <iostream>

CFigure::CFigure(int nVertices)
{
	mColor[0] =  1.0f;
	mColor[1] = mColor[2] = 0.f;
	mType = 0;

	mVertices = new float*[1];
	for (int i = 0; i < 1; ++i)
	{
		mVertices[i] = new float[2];
	}
}

CFigure::~CFigure()
{
	delete[] mVertices;
}

void CFigure::setVertex(int id, float x, float y)
{
	mVertices[id][0] = x;
	mVertices[id][1] = y;
	nVer = id+1;
}

void CFigure::setColor(float r, float g, float b)
{
	mColor[0] = r;
	mColor[1] = g;
	mColor[2] = b;
}

int CFigure::getType()
{
	return mType;
}

float* CFigure::getVertex(int id)
{
	return mVertices[id];
}

float* CFigure::getColor()
{
	return mColor;
}

void CFigure::draw()
{
	glBegin(GL_POINTS);
	glColor3f(255.0, 0.0, 0.0);
	glPointSize(5);
	glVertex2i((int) mVertices[0][0], (int) mVertices[0][1]);
	glEnd();
}

