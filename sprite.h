#pragma once

class sprite
{
    int x,y;
    int width,height;
    int movex,movey;
    int curframe,lastframe;
    int animdelay,animcount;
    int scalex, scaley;
    int rotation, rotaterate;
	
	int hitPoints;
public:
	sprite(void);
	~sprite(void);
	void setX(int);
	void setY(int);
	int getX();
	int getY();
	void setWidth(int);
	void setHeight(int);
	int getWidth();
	int getHeight();
	void setMoveX(int);
	void setMoveY(int);
	int getMoveX();
	int getMoveY();
	void atack();
	void beDestroyed();
};
