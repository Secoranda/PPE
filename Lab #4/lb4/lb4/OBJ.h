

#include <windows.h>
#include <cmath>
#define ID_TIMER 111


class OBJ
{

protected:
	COLORREF clr;
public:
	POINT center;
	int xSpeed, ySpeed;
	int counter = 0;

	OBJ(POINT center, const int &speed);
	bool OBJ_Accelerate(const int& deltaSpeedX, const int& deltaSpeedY);
	bool OBJ_Color(const COLORREF &clr);
	bool OBJ_Collision(const RECT &rect);
	bool OBJ_Shape(OBJ &ob);
	virtual bool OBJ_Action(const HDC &hdc, const RECT& rect, HBRUSH &hBrush) = 0;
};

class Circle : public OBJ {
public:
	Circle(POINT center, const int &speed) : OBJ(center, speed)
	{}
	bool OBJ_Action(const HDC &hdc, const RECT& rect, HBRUSH &hBrush);
};

bool OBJ_Interact(OBJ &a, OBJ &b);

