/*
 * Wifi.hpp
 *
 *  Created on: 2014. 11. 28.
 *      Author: 근홍
 */

#ifndef WIFI_HPP_
#define WIFI_HPP_

#include "Position.hpp"
#include <unordered_set>
#include <cstdint>
#include <cstddef>

class Client;

class Wifi : public Position
{
private:
	std::unordered_set<Client*> clients;
	double signal;
	double speed;
public:
	Wifi(double x, double y, double signal, double speed);
	virtual ~Wifi();

	void addClient(Client* client);
	void removeClient(Client* client);
	double getBaseSignal();
	double getBaseSpeed();
	size_t getClientCount();
};

#endif /* WIFI_HPP_ */
