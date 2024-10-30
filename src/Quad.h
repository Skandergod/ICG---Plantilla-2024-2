#pragma once

#include "Line.h"

class CQuad : public CFigure
{
	CLine lines[4];
	public:
		CQuad();
		~CQuad();
		void display();
		static void drawQuad(float** mVertices, int color, int form);
};

