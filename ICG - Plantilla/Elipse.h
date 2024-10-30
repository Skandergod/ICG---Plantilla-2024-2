#pragma once

#include "../src/Figure.h"

class CElipse : public CFigure
{
	public:
	public:
		CElipse();
		~CElipse();
		void display();
		void drawElipse(float** mVertices, int color, int form, int relleno);
		void pintar4(int x, int y, int x1, int y1, int relleno);
};