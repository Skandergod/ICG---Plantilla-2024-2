#pragma once

#include "Figure.h"

class CLine : public CFigure
{
	public:
		CLine();
		~CLine();
		void display();
		static void drawLine(int x1, int y1, int x2, int y2, int color, int form);
		static void case1(int x1, int y1, int x2, int y2, int color, int form);
		static void case2(int x1, int y1, int x2, int y2, int color, int form);
		static void case3(int x1, int y1, int x2, int y2, int color, int form);
		static void case4(int x1, int y1, int x2, int y2, int color, int form);

};

