/*
 * Wifi.hpp
 *
 *  Created on: 2014. 11. 28.
 *      Author: 근홍
 */

#ifndef WIFI_HPP_
#define WIFI_HPP_

#include "Position.hpp"

class Client;

class Wifi : public Position
{
public:
	Wifi(double x, double y);
	virtual ~Wifi();

	void addClient();
	void getClientCount();
};

#endif /* WIFI_HPP_ */
