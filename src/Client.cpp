/*
 * Client.cpp
 *
 *  Created on: 2014. 11. 29.
 *      Author: 근홍
 */

#include "Client.hpp"
#include <cmath>


Client::Client(double x, double y) : Position(x,y)
{
	this->station = nullptr;
}

Client::~Client()
{

}
