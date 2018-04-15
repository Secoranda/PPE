#include "OBJ.h"

OBJ::OBJ(POINT center, const int &speed)
{

	this->center = center;
	this->xSpeed = speed;
	this->ySpeed = speed;
	clr = RGB(
		(BYTE)(rand() % 255), // red component of color
		(BYTE)(rand() % 255), // green component of color
		(BYTE)(rand() % 255) // blue component of color
	);

}

bool OBJ::OBJ_Accelerate(const int& dX, const int& dY)
{
	xSpeed = dX;
	ySpeed = dY;
	return TRUE;
}

bool OBJ::OBJ_Color(const COLORREF &clr)
{
	this->clr = clr;
	return TRUE;
}
bool OBJ::OBJ_Shape(OBJ &ob)
{
	return TRUE;
}

bool Circle::OBJ_Action(const HDC &hdc, const RECT& rect, HBRUSH &hBrush)
{
	hBrush = CreateSolidBrush(clr);
	SelectObject(hdc, hBrush);

	OBJ_Collision(rect);

	center.x += xSpeed; center.y -= ySpeed;

	if (counter>0)
	{
		Rectangle(hdc, center.x - 25, center.y - 25, center.x + 25, center.y + 25);
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		DeleteObject(hBrush);
		return TRUE;
	}

	Ellipse(hdc, center.x - 25, center.y - 25, center.x + 25, center.y + 25);
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	DeleteObject(hBrush);
	return TRUE;

}

bool OBJ::OBJ_Collision(const RECT &rect)
{
	if (center.x + 25 > rect.right - 1)
	{
		xSpeed = -abs(xSpeed);
		counter = 1;
	}
	if (center.x - 25 < rect.left + 1)
	{
		xSpeed = abs(xSpeed);
		
	}
	if (center.y + 25 > rect.bottom - 1)
	{
		ySpeed = abs(ySpeed);
		counter = 1;
	}
	if (center.y - 25 < rect.top + 1)
	{
		ySpeed = -abs(ySpeed);
	}
	return TRUE;
}

bool OBJ_Interact(OBJ &obj1, OBJ &obj2) {

	double OBJ_dist;

	OBJ_dist = sqrt(pow(obj1.center.x - obj2.center.x, 2) + pow(obj1.center.y - obj2.center.y, 2));

	if (OBJ_dist < 60)
	{
		obj1.OBJ_Accelerate(-obj1.xSpeed, -obj1.ySpeed);
		obj2.OBJ_Accelerate(-obj2.xSpeed, -obj2.ySpeed);
		obj1.OBJ_Color(RGB(0, 0, 0));
	}

	return TRUE;
}
