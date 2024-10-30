#pragma once

#include "../headers/AntTweakBar.h"
#include <iostream>
#include <string>

using std::string;

//Singleton user interface class

class CUserInterface
{
private:
	static CUserInterface * mInterface; //Holds the instance of the class
	TwBar *mUserInterface;
	float mFigureColor[3];
	float mBoundingColor[3];
	float mFillColor[3];
	float fill[3];
	float g_Rotation[4];
	string mFigureType;

public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setFigureColor(float *color);
	void setBoundingColor(float *color);
	void setFillColor(float* color);
	void setFigureType(string type);
	float* getFigureColor();
	float* getFillColor();
	float* getBoundingColor();
	float getrF();
	float getgF();
	float getbF();
	float getrB();
	float getgB();
	float getbB();
	float getrfill();
	float getgfill();
	float getbfill();
	float getrbackground();
	float getgbackground();
	float getbbackground();

private:
	///Private constructor
	CUserInterface(); 
};