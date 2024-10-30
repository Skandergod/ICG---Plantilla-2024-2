#pragma once

#include "../src/Figure.h"
#include <vector>
#include <utility> 


class CCurve : public CFigure
{
public:
	std::vector<std::pair <float, float>* > puntosControl, puntos;
	std::pair <float, float>* punto;
	double paso = 0.0001;
	float VertXY1[2];
	float cPoint[3] = { 0.0,0.0,0.0 };
	float cLine[3] = { 1.0,0.0,0.0 };
	int numeroVertices = 3;

public:
	CCurve();
	~CCurve();
	void display();
	void drawCurve();
	void agregarPunto(float x, float y);
};