#include ".\sprite.h"

sprite::sprite(void)
{
}

sprite::~sprite(void)
{
}
void sprite::setX(int tempX)
{
	x = tempX;
}
void sprite::setY(int tempY)
{
	y = tempY;
}
int sprite::getX()
{
	return x;
}
int sprite::getY()
{
	return y;
}
void sprite::setWidth(int tempWidth)
{
	width = tempWidth;
}
void sprite::setHeight(int tempHeight)
{
	height = tempHeight;
}
int sprite::getWidth()
{
	return width;
}
int sprite::getHeight()
{
	return height;
}
void sprite::setMoveX(int tempMoveX)
{
	movex = tempMoveX;
}
void sprite::setMoveY(int tempMoveY)
{
	movey = tempMoveY;
}
int sprite::getMoveX()
{
	return movex;
}
int sprite::getMoveY()
{
	return movey;
}
