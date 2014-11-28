/*
 * Client.hpp
 *
 *  Created on: 2014. 11. 29.
 *      Author: 근홍
 */

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "Wifi.hpp"

class Client : public Position
{
private:
	Wifi* station;
public:
	Client(double x, double y);
	virtual ~Client();

	double getSNR();
	double getAlohaSpeed();
	double getBER();
	double getDropRate(const size_t& MTU);
	double getTCPSpeed(const size_t& MTU);
	double getRTT(const size_t& MTU);

	friend void Wifi::addClient(Client* client);
	friend void Wifi::removeClient(Client* client);
};



#endif /* CLIENT_HPP_ */
