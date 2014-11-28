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

	friend void Wifi::addClient(Client* client);
	friend void Wifi::removeClient(Client* client);
};



#endif /* CLIENT_HPP_ */
