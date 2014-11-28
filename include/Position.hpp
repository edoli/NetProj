/*
 * Position.hpp
 *
 *  Created on: 2014. 11. 28.
 *      Author: 근홍
 */

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <cmath>

class Position
{
private:
	double x;
	double y;

public:
	Position(double x, double y);
	~virtual Position();

	static double distance(const Position& a, const Position& b);
	static double distanceSquare(const Position& a, const Position& b);
};


#endif /* POSITION_HPP_ */
