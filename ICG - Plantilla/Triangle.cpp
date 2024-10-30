#include "Triangle.h"
#include "../src/Quad.h"
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

CTriangle::CTriangle()
{
	mVertices = new float* [3];
	for (int i = 0; i < 3; ++i)
		mVertices[i] = new float[2];

	mType = TRIANGLE;
}

CTriangle::~CTriangle()
{
	for (int i = 0; i < 3; ++i)
		delete[] mVertices[i];
}

void CTriangle::display()
{
	
	GLint* b[3];
	GLfloat* c[3];
	int xMax, yMax, xMin, yMin;
	for (int i = 0; i < 3; ++i) {
		b[i] = new GLint[2];
	}
	for (int i = 0; i < 3; ++i) {
		c[i] = new GLfloat[2];
	}

	if (!picked) {

		setMinAndMax();

	}
	//glColor3fv(mColor);

	b[0][0] = (int)mVertices[0][0];
	b[0][1] = (int)mVertices[0][1];
	b[1][0] = (int)mVertices[1][0];
	b[1][1] = (int)mVertices[1][1];
	b[2][0] = (int)mVertices[2][0];
	b[2][1] = (int)mVertices[2][1];

	c[0][0] = (int)mVertices[0][0];
	c[0][1] = (int)mVertices[0][1];
	c[1][0] = (int)mVertices[1][0];
	c[1][1] = (int)mVertices[1][1];
	c[2][0] = (int)mVertices[2][0];
	c[2][1] = (int)mVertices[2][1];

	glColor3fv(mColor);
	drawTriangle(mVertices, 0, 1);

	if(relleno)
	{
		
		bool ii, jj;
		//glColor3fv(mPaintColor);

		


		for (int w = 0; w < 2; w++) {
			
			//std::cout << "Cateto " << w << "Cateto " << w + 1 << std::endl;

			for (int i = 0; i < rectas[w].size(); ++i) {
				for (int j = 0; j < rectas[w + 1].size(); ++j) {
					
					if(  rectas[w][i]->second == rectas[w + 1][j]->second || rectas[w][i]->first == rectas[w + 1][j]->first)
						CTriangle::drawLinef(rectas[w][i]->first, rectas[w][i]->second, rectas[w + 1][j]->first, rectas[w + 1][j]->second, 0, 1);
					
				}
			}

			//std::cout << "Cambio" << std::endl;
			if (w == 1) {

				//std::cout << "Cateto " << w - 1 << "Cateto " << w + 1 << std::endl;

				for (int i = 0; i < rectas[w-1].size(); ++i) {
					for (int j = 0; j < rectas[w + 1].size(); ++j) {
						
						if (rectas[w-1][i]->second == rectas[w + 1][j]->second || rectas[w - 1][i]->first == rectas[w + 1][j]->first)
							CTriangle::drawLinef(rectas[w-1][i]->first, rectas[w-1][i]->second, rectas[w + 1][j]->first, rectas[w + 1][j]->second, 0, 1);
						
					}
				}
			}
		}

		
	}	

	drawTriangle(mVertices, 0, 0);

	if (picked) {

		glColor3fv(mBoundingColor);

		float xmax, xmin;
		float ymax, ymin;

		xmin = std::min(c[1][0], c[0][0]);
		xmin = std::min(c[2][0], xmin);

		xmax = std::max(c[1][0], c[0][0]);
		xmax = std::max(c[2][0], xmax);

		ymin = std::min(c[1][1], c[0][1]);
		ymin = std::min(c[2][1], ymin);

		ymax = std::max(c[1][1], c[0][1]);
		ymax = std::max(c[2][1], ymax);

		c[0][0] = xmin-2;
		c[0][1] = ymin-2;
		c[1][0] = xmax+2;
		c[1][1] = ymax+2;

		CQuad::drawQuad(c, 0, 0);
	}
	
	/*glBegin(GL_POLYGON);
	glVertex2fv(mVertices[0]);
	glVertex2f(mVertices[0][0], mVertices[1][1]);
	glVertex2fv(mVertices[1]);
	glVertex2f(mVertices[1][0], mVertices[0][1]);*/

	for (int k = 0; k < 3; ++k) {

		rectas[k].clear();

	}

	glEnd();
}

void CTriangle::drawTriangle(float** mVertices, int color, int form) {

	//glColor3f(0.0f,1.0f,0.0f);
	GLint* b[3];
	for (int i = 0; i < 3; ++i) {
		b[i] = new GLint[2];
	}

	b[0][0] = (int)mVertices[0][0];
	b[0][1] = (int)mVertices[0][1];
	b[1][0] = (int)mVertices[1][0];
	b[1][1] = (int)mVertices[1][1];
	b[2][0] = (int)mVertices[2][0];
	b[2][1] = (int)mVertices[2][1];

	drawLine(b[0][0], b[0][1], b[1][0], b[1][1], 0, 0, form);
	drawLine(b[1][0], b[1][1], b[2][0], b[2][1], 0, 1, form);
	drawLine(b[0][0], b[0][1], b[2][0], b[2][1], 0, 2, form);

}

void CTriangle::drawLine(int x1, int y1, int x2, int y2, int color, int id, int form) {

	GLint* b[2];
	GLint dx, dy;
	for (int i = 0; i < 2; ++i) {
		b[i] = new GLint[2];
	}

	//glColor3f(0.0f,1.0f,0.0f);

	b[0][0] = x1;
	b[0][1] = y1;
	b[1][0] = x2;
	b[1][1] = y2;

	dx = b[1][0] - b[0][0];
	dy = b[1][1] - b[0][1];

	if (b[0][1] < b[1][1]) {

		if (dx >= 0) {
			if (dy <= dx) {
				case1(b[0][0], b[0][1], b[1][0], b[1][1], 0, id, form);
			}
			else {
				case2(b[0][0], b[0][1], b[1][0], b[1][1], 0, id, form);
			}
		}
		else {
			if (-dx <= dy) {
				case4(b[1][0], b[1][1], b[0][0], b[0][1], 0, id, form);


			}
			else {
				case3(b[1][0], b[1][1], b[0][0], b[0][1], 0, id, form);
			}
		}

	}
	else {

		if (dx >= 0) {
			if (dx <= -dy) {
				case4(b[0][0], b[0][1], b[1][0], b[1][1], 0, id, form);
			}
			else {
				case3(b[0][0], b[0][1], b[1][0], b[1][1], 0, id, form);
			}
		}
		else {
			if (-dx <= -dy) {
				case2(b[1][0], b[1][1], b[0][0], b[0][1], 0, id, form);
			}
			else {
				case1(b[1][0], b[1][1], b[0][0], b[0][1], 0, id, form);
			}
		}

	}

}

void CTriangle::case1(int x1, int y1, int x2, int y2, int color, int id, int form) { //M En [0,1]

	int dx, dy, x0, y0, d, incrE, incrNE;

	dx = x2 - x1;
	dy = y2 - y1;

	d = dx - (dy << 1);
	incrE = -(dy << 1);
	incrNE = ((dx - dy) << 1);

	x0 = x1;
	y0 = y1;



	glBegin(GL_POINTS);
	glPointSize(1);
	//glColor3fv(mColor);
	glVertex2i(x1, y1);

	while (x0 < x2) {
		//std::cout << "hi" << std::endl;
		//Pintar noreste
		if (d <= 0) {
			d = d + incrNE;
			y0 = y0 + 1;
		}
		//Pintar este
		else {
			d = d + incrE;
		}
		x0 = x0 + 1;
		glVertex2i(x0, y0);
		if (form) {
			punto = new std::pair <float, float>(x0, y0);
			rectas[id].push_back(punto);
		}
	}

	//free(punto);
	glVertex2i(x2, y2);

	glPointSize(1);
	glEnd();

}

void CTriangle::case2(int x1, int y1, int x2, int y2, int color, int id, int form) { //M En [1,inf]

	int m, dx, dy, x0, y0, d, incrE, incrNE;

	dx = x2 - x1;
	dy = y2 - y1;

	//Funcion Inversa de la pendiente
	m = dy;
	dy = dx;
	dx = m;

	d = dx - (dy << 1);
	incrE = -(dy << 1);
	incrNE = ((dx - dy) << 1);

	x0 = x1;
	y0 = y1;


	glBegin(GL_POINTS);

	//glColor3fv(mColor);
	//glColor3fv(mColor);.
	glPointSize(1);
	glVertex2i(x1, y1);

	//glColor3fv(mFillColor);
	while (y0 < y2) {
		//std::cout << "hi" << std::endl;
		//Pintar noreste
		if (d <= 0) {
			d = d + incrNE;
			x0 = x0 + 1;
		}
		//Pintar este
		else {
			d = d + incrE;
		}
		y0 = y0 + 1;
		if (form) {
			punto = new std::pair <float, float>(x0, y0);
			rectas[id].push_back(punto);
		}
		glVertex2i(x0, y0);
	}

	//glColor3fv(mColor);
	//free(punto);
	glVertex2i(x2, y2);
	glPointSize(1);
	glEnd();

}

void CTriangle::case3(int x1, int y1, int x2, int y2, int color, int id, int form) {//m en [-1,0]

	int dx, dy, x0, y0, d, incrE, incrNE;

	dx = x2 - x1;
	dy = y2 - y1;

	d = dx + (dy << 1);
	incrE = (dy << 1);
	incrNE = ((dx + dy) << 1);

	x0 = x1;
	y0 = y1;


	glBegin(GL_POINTS);
	glPointSize(1);
	//glColor3fv(mColor);
	//glColor3fv(mColor);
	glVertex2i(x1, y1);

	//glColor3fv(mFillColor);
	while (x0 < x2) {
		//std::cout << "hi" << std::endl;
		//Pintar noreste
		if (d <= 0) {
			d = d + incrNE;
			y0 = y0 - 1;
		}
		//Pintar este
		else {
			d = d + incrE;
		}
		x0 = x0 + 1;
		if (form) {
			punto = new std::pair <float, float>(x0, y0);
			rectas[id].push_back(punto);
		}
		glVertex2i(x0, y0);
	}

	//glColor3fv(mColor);
	//free(punto);
	glVertex2i(x2, y2);
	glPointSize(1);
	glEnd();


}

void CTriangle::case4(int x1, int y1, int x2, int y2, int color, int id, int form) { //M En [-inf,-1]

	int m, dx, dy, x0, y0, d, incrE, incrNE;

	dx = x2 - x1;
	dy = y2 - y1;

	//Funcion Inversa de la pendiente
	m = dy;
	dy = dx;
	dx = m;

	d = -dx - (dy << 1);
	incrE = -(dy << 1);
	incrNE = ((-dx - dy) << 1);

	x0 = x1;
	y0 = y1;

	glBegin(GL_POINTS);

	//glColor3fv(mColor);

	//glColor3fv(mColor);
	glPointSize(1);
	glVertex2i(x1, y1);

	//glColor3fv(mFillColor);
	while (y2 < y0) {
		//std::cout << "hi" << std::endl;
		//Pintar noreste
		if (d <= 0) {
			d = d + incrNE;
			x0 = x0 + 1;
		}
		//Pintar este
		else {
			d = d + incrE;
		}
		y0 = y0 - 1;
		if (form) {
			punto = new std::pair <float, float>(x0, y0);
			rectas[id].push_back(punto);
		}
		glVertex2i(x0, y0);
	}

	//glColor3fv(mColor);
	//free(punto);
	
	glVertex2i(x2, y2);
	glPointSize(1);
	glEnd();

}

void CTriangle::drawLinef(int x1, int y1, int x2, int y2, int color, int form) {

	GLint* b[2];
	GLint dx, dy;
	for (int i = 0; i < 2; ++i) {
		b[i] = new GLint[2];
	}

	//glColor3f(0.0f,1.0f,0.0f);

	b[0][0] = x1;
	b[0][1] = y1;
	b[1][0] = x2;
	b[1][1] = y2;

	dx = b[1][0] - b[0][0];
	dy = b[1][1] - b[0][1];

	if (b[0][1] < b[1][1]) {

		if (dx >= 0) {
			if (dy <= dx) {
				case1f(b[0][0], b[0][1], b[1][0], b[1][1], 0, form);
			}
			else {
				case2f(b[0][0], b[0][1], b[1][0], b[1][1], 0, form);
			}
		}
		else {
			if (-dx <= dy) {
				case4f(b[1][0], b[1][1], b[0][0], b[0][1], 0, form);


			}
			else {
				case3f(b[1][0], b[1][1], b[0][0], b[0][1], 0, form);
			}
		}

	}
	else {

		if (dx >= 0) {
			if (dx <= -dy) {
				case4f(b[0][0], b[0][1], b[1][0], b[1][1], 0, form);
			}
			else {
				case3f(b[0][0], b[0][1], b[1][0], b[1][1], 0, form);
			}
		}
		else {
			if (-dx <= -dy) {
				case2f(b[1][0], b[1][1], b[0][0], b[0][1], 0, form);
			}
			else {
				case1f(b[1][0], b[1][1], b[0][0], b[0][1], 0, form);
			}
		}

	}

}

void CTriangle::case1f(int x1, int y1, int x2, int y2, int color, int form) { //M En [0,1]

	int dx, dy, x0, y0, d, incrE, incrNE;

	dx = x2 - x1;
	dy = y2 - y1;

	d = dx - (dy << 1);
	incrE = -(dy << 1);
	incrNE = ((dx - dy) << 1);

	x0 = x1;
	y0 = y1;




	glBegin(GL_POINTS);

	//glColor3fv(mColor);
	glColor3fv(mColor);
	glPointSize(3);
	glVertex2i(x1, y1);

	glPointSize(1);
	glColor3fv(mFillColor);
	while (x0 < x2 - 1) {
		//std::cout << "hi" << std::endl;
		//Pintar noreste
		if (d <= 0) {
			d = d + incrNE;
			y0 = y0 + 1;
		}
		//Pintar este
		else {
			d = d + incrE;
		}
		x0 = x0 + 1;


		glVertex2i(x0, y0);
	}

	glPointSize(3);
	glColor3fv(mColor);
	glVertex2i(x2, y2);

	glEnd();

}

void CTriangle::case2f(int x1, int y1, int x2, int y2, int color, int form) { //M En [1,inf]

	int m, dx, dy, x0, y0, d, incrE, incrNE;

	dx = x2 - x1;
	dy = y2 - y1;

	//Funcion Inversa de la pendiente
	m = dy;
	dy = dx;
	dx = m;

	d = dx - (dy << 1);
	incrE = -(dy << 1);
	incrNE = ((dx - dy) << 1);

	x0 = x1;
	y0 = y1;




	glBegin(GL_POINTS);

	//glColor3fv(mColor);
	glPointSize(3);
	glColor3fv(mColor);
	glVertex2i(x1, y1);

	glPointSize(1);
	glColor3fv(mFillColor);
	while (y0 < y2 - 1) {
		//std::cout << "hi" << std::endl;
		//Pintar noreste
		if (d <= 0) {
			d = d + incrNE;
			x0 = x0 + 1;
		}
		//Pintar este
		else {
			d = d + incrE;
		}
		y0 = y0 + 1;

		glVertex2i(x0, y0);
	}

	glPointSize(3);
	glColor3fv(mColor);
	glVertex2i(x2, y2);
	glEnd();

}

void CTriangle::case3f(int x1, int y1, int x2, int y2, int color, int form) {//m en [-1,0]

	int dx, dy, x0, y0, d, incrE, incrNE;

	dx = x2 - x1;
	dy = y2 - y1;

	d = dx + (dy << 1);
	incrE = (dy << 1);
	incrNE = ((dx + dy) << 1);

	x0 = x1;
	y0 = y1;

	glBegin(GL_POINTS);

	//glColor3fv(mColor);
	glPointSize(3);
	glColor3fv(mColor);
	glVertex2i(x1, y1);
	glPointSize(1);
	glColor3fv(mFillColor);
	while (x0 < x2 - 1) {
		//std::cout << "hi" << std::endl;
		//Pintar noreste
		if (d <= 0) {
			d = d + incrNE;
			y0 = y0 - 1;
		}
		//Pintar este
		else {
			d = d + incrE;
		}
		x0 = x0 + 1;

		glVertex2i(x0, y0);
	}
	glPointSize(3);
	glColor3fv(mColor);
	glVertex2i(x2, y2);
	glEnd();


}

void CTriangle::case4f(int x1, int y1, int x2, int y2, int color, int form) { //M En [-inf,-1]

	int m, dx, dy, x0, y0, d, incrE, incrNE;

	dx = x2 - x1;
	dy = y2 - y1;

	//Funcion Inversa de la pendiente
	m = dy;
	dy = dx;
	dx = m;

	d = -dx - (dy << 1);
	incrE = -(dy << 1);
	incrNE = ((-dx - dy) << 1);

	x0 = x1;
	y0 = y1;


	glBegin(GL_POINTS);

	//glColor3fv(mColor);
	glPointSize(3);
	glColor3fv(mColor);
	glVertex2i(x1, y1);
	glPointSize(1);
	glColor3fv(mFillColor);
	while (y2 < y0 - 1) {
		//std::cout << "hi" << std::endl;
		//Pintar noreste
		if (d <= 0) {
			d = d + incrNE;
			x0 = x0 + 1;

		}
		//Pintar este
		else {
			d = d + incrE;
		}
		y0 = y0 - 1;

		glVertex2i(x0, y0);
	}
	glPointSize(3);
	glColor3fv(mColor);
	glVertex2i(x2, y2);
	glEnd();

}