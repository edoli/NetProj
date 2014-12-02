/*
 * Position.cpp
 *
 *  Created on: 2014. 11. 28.
 *      Author: 근홍
 */

#include "Position.hpp"

Position::Position(Real x, Real y)
{
	this->x = x;
	this->y = y;
}

Position::~Position()
{

}

void Position::setPosition(Real x, Real y)
{
	this->x = x;
	this->y = y;
}

Real Position::getX()
{
	return this->x;
}

Real Position::getY()
{
	return this->y;
}

Real Position::distanceSquare(const Position& a, const Position& b)
{
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

Real Position::distance(const Position& a, const Position& b)
{
	return sqrt(distanceSquare(a,b));
}
