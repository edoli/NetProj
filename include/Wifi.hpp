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
	Real signal;
	Real speed;
	Real baseNoise;
public:
	Wifi(Real x, Real y, Real signal, Real speed, Real baseNoise);
	virtual ~Wifi();

	void addClient(Client* client);
	void removeClient(Client* client);
	void clearClient();
	Real getBaseSignal();
	Real getBaseSpeed();
	size_t getClientCount();
	Real getBaseNoise();
};

#endif /* WIFI_HPP_ */
