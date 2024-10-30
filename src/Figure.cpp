#include "Figure.h"
#include <iostream>

CFigure::CFigure()
{
	mColor[0] =  1.0f;
	mColor[1] = mColor[2] = 0.f;
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

void CFigure::setColorFill(float r, float g, float b)
{
	mFillColor[0] = r;
	mFillColor[1] = g;
	mFillColor[2] = b;
}

void CFigure::setColorBounding(float r, float g, float b)
{
	mBoundingColor[0] = r;
	mBoundingColor[1] = g;
	mBoundingColor[2] = b;
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

float* CFigure::getColorFill()
{
	return mFillColor;
}

float* CFigure::getColorBounding()
{
	return mBoundingColor;
}

void CFigure::move(int x, int y) {

	for (int i = 0; i < nVer; i++) {
		mVertices[i][0] += x;
		//std::cout << "ax: " << mVertices[i][0] + x << std::endl;
		mVertices[i][1] += y;
		//std::cout << "ay: " << mVertices[i][1] + y << std::endl;
	}

};

void CFigure::setMinAndMax() {

	minx = mVertices[0][0];
	miny = mVertices[0][1];

	maxx = mVertices[0][0];
	maxy = mVertices[0][1];

	for (int i = 0; i < nVer; i++) {
		minx = MIN(mVertices[i][0], minx);
	}

	for (int i = 1; i < nVer; i++) {
		miny = MIN(mVertices[i][1], miny);
	}

	for (int i = 1; i < nVer; i++) {
		maxx = MAX(mVertices[i][0], maxx);
	}

	for (int i = 1; i < nVer; i++) {
		maxy = MAX(mVertices[i][1], maxy);
	}

}


void CFigure::setpicked(bool a) {

	picked = a;

}

void CFigure::setfill(bool a) {

	relleno = a;
}