/*
 * Position.hpp
 *
 *  Created on: 2014. 11. 28.
 *      Author: 근홍
 */

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <cmath>
typedef double Real;

class Position
{
private:
	Real x;
	Real y;

public:
	Position(Real x, Real y);
	virtual ~Position();

	void setPosition(Real x, Real y);

	Real getX();
	Real getY();

	static Real distance(const Position& a, const Position& b);
	static Real distanceSquare(const Position& a, const Position& b);
};


#endif /* POSITION_HPP_ */
