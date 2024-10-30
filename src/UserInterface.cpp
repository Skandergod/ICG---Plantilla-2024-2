#include "UserInterface.h"

extern int gWidth, gHeight;

// Global static pointer used to ensure a single instance of the class.
CUserInterface * CUserInterface::mInterface = NULL;

/**
* Creates an instance of the class
*
* @return the instance of this class
*/
CUserInterface * CUserInterface::Instance() 
{
	if (!mInterface)   // Only allow one instance of class to be generated.
		 mInterface = new CUserInterface();
 
   return mInterface;
}

CUserInterface::CUserInterface()
{
	mUserInterface = TwNewBar("Figure");

	TwDefine("Figure refresh = '0.0001f'");
	TwDefine("Figure resizable = false");
	TwDefine("Figure fontresizable = false");
	TwDefine("Figure movable = false");
	TwDefine("Figure visible = true");
	TwDefine("Figure position = '20 20'");
	TwDefine("Figure size = '220 320'");

	TwAddVarRO(mUserInterface, "meshType", TW_TYPE_STDSTRING, &mFigureType, "label='Type' readonly=true");
	TwAddVarRW(mUserInterface, "color", TW_TYPE_COLOR3F, &mFigureColor[0], "label = 'Color Boder'");
	TwAddVarRW(mUserInterface, "color2", TW_TYPE_COLOR3F, &mBoundingColor[0], "label = 'Color Bounding'");
	TwAddVarRW(mUserInterface, "color3", TW_TYPE_COLOR3F, &mFillColor[0], "label = 'Color Fill'");
	TwAddVarRW(mUserInterface, "color4", TW_TYPE_COLOR3F, &fill[0], "label = 'Color Fondo'");
	TwAddVarRW(mUserInterface, "ObjRotation", TW_TYPE_QUAT4F, &g_Rotation,
		" label='Object rotation' opened=true help='Change the object orientation.' ");
}

CUserInterface::~CUserInterface()
{
}

void CUserInterface::reshape()
{
	TwWindowSize(gWidth, gHeight);
}

void CUserInterface::show()
{
	TwDefine("Figure visible = true");
}

void CUserInterface::hide()
{
	TwDefine("Figure visible = false");
}

void CUserInterface::setFigureColor(float *color)
{
	mFigureColor[0] = color[0];
	mFigureColor[1] = color[1];
	mFigureColor[2] = color[2];
}

float CUserInterface::getrF() {
	return mFigureColor[0];
}

float CUserInterface::getgF() {
	return mFigureColor[1];
}

float CUserInterface::getbF() {
	return mFigureColor[2];
}

float CUserInterface::getrB() {
	return mBoundingColor[0];
}

float CUserInterface::getgB() {
	return mBoundingColor[1];
}

float CUserInterface::getbB() {
	return mBoundingColor[2];
}

float CUserInterface::getrbackground() {
	return fill[0];
}

float CUserInterface::getgbackground() {
	return fill[1];
}

float CUserInterface::getbbackground() {
	return fill[2];
}

float CUserInterface::getrfill() {
	return mFillColor[0];
}

float CUserInterface::getgfill() {
	return mFillColor[1];
}

float CUserInterface::getbfill() {
	return mFillColor[2];
}

void CUserInterface::setBoundingColor(float* color) {

	mBoundingColor[0] = color[0];
	mBoundingColor[1] = color[1];
	mBoundingColor[2] = color[2];

}

void CUserInterface::setFillColor(float* color) {

	mFillColor[0] = color[0];
	mFillColor[1] = color[1];
	mFillColor[2] = color[2];

}

void CUserInterface::setFigureType(string type)
{
	mFigureType = type;
}

float* CUserInterface::getFigureColor()
{
	return mFigureColor;
}

float* CUserInterface::getBoundingColor()
{
	return mBoundingColor;
}

float* CUserInterface::getFillColor()
{
	return mFillColor;
}