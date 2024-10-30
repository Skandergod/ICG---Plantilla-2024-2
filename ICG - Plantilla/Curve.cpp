#pragma once

#include "../src/Figure.h"
#include "Curve.h"
#include "../src/Line.h"
#include <iostream>
#include "../src/Quad.h"

using namespace std;

CCurve::CCurve()
{
	mVertices = new float* [20];
	for (int i = 0; i < 20; ++i)
		mVertices[i] = new float[2];

	mType = CURVE;
}

CCurve::~CCurve()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CCurve::display()
{
	GLfloat* c[2];

	for (int i = 0; i < 2; ++i) {
		c[i] = new GLfloat[2];
	}

	c[0][0] = minx - 2;
	c[0][1] = miny - 2;
	c[1][0] = maxx + 2;
	c[1][1] = maxy + 2;

	glColor3fv(mColor);
	puntos.clear();
	for (int i = 0; i < nVer; i++) {
		agregarPunto(mVertices[i][0], mVertices[i][1]);
	}

	for (int i = 0; i < puntosControl.size(); i++) {
		punto = new std::pair <float, float>(puntosControl[i]->first, puntosControl[i]->second);
		puntos.push_back(punto);
	}
	setMinAndMax();
	drawCurve();

	glPointSize(5);
	glBegin(GL_POINTS);

		for (int i = 0; i < puntosControl.size(); i++) {
		
			glVertex2i(puntosControl[i]->first, puntosControl[i]->second);
		
		}

	glEnd();
	glPointSize(1);

	
	for (int i = 0; i < puntosControl.size()-1; i++) {

		glColor3fv(mFillColor);
		CLine::drawLine(puntosControl[i]->first, puntosControl[i]->second, puntosControl[i+1]->first, puntosControl[i+1]->second, 0, 0);

	}
	
	if (picked) {

		glColor3fv(mBoundingColor);
		CQuad::drawQuad(c, 0, 0);
	}
	
	puntosControl.clear();
	glEnd();

}

void CCurve::drawCurve() {
	int n = puntos.size();
	glBegin(GL_LINE_STRIP);
	for (double tt = 0.0; tt < 1.0; tt += paso)
	{
		for (int rr = 0; rr < (n - 1); rr++)
		{
			for (int ii = 0; ii < (n - 1) - rr; ii++)
			{
				puntos[ii]->first = float((1.0 - tt) * puntos[ii]->first) + float(tt * puntos[ii + 1]->first);
				puntos[ii]->second = float((1.0 - tt) * puntos[ii]->second) + float(tt * puntos[ii + 1]->second);
			}
		}
		VertXY1[0] = puntos[0]->first;
		VertXY1[1] = puntos[0]->second;
		glVertex2fv(VertXY1);
	}
	glEnd();
}

void CCurve::agregarPunto(float x, float y) {

	punto = new std::pair <float, float>(x, y);
	puntosControl.push_back(punto);

}