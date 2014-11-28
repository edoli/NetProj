/*
 * Client.hpp
 *
 *  Created on: 2014. 11. 29.
 *      Author: 근홍
 */

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "Position.hpp"
#include "Wifi.hpp"

class Client : public Position
{
private:
	Wifi* station;
public:
	Client(Real x, Real y);
	virtual ~Client();

	Real getSNR();
	Real getAlohaSpeed();
	Real getBER();
	Real getDropRate(const size_t& MTU);
	Real getTCPSpeed(const size_t& MTU);
	Real getRTT(const size_t& MTU);
	Real getStationDistance();

	friend void Wifi::addClient(Client* client);
	friend void Wifi::removeClient(Client* client);
};



#endif /* CLIENT_HPP_ */
