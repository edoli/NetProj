/*
 * Position.cpp
 *
 *  Created on: 2014. 11. 28.
 *      Author: 근홍
 */

#include "Position.hpp"

Position::Position(double x, double y)
{
	this->x = x;
	this->y = y;
}

Position::~Position()
{

}

double Position::distanceSquare(const Position& a, const Position& b)
{
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

double Position::distance(const Position& a, const Position& b)
{
	return sqrt(distanceSquare(a,b));
}
