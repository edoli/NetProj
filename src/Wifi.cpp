/*
 * Wifi.cpp
 *
 *  Created on: 2014. 11. 29.
 *      Author: 근홍
 */

#include "Wifi.hpp"
#include "Client.hpp"
#include <cassert>

Wifi::Wifi(Real x, Real y, Real signal, Real speed, Real baseNoise) : Position(x,y)
{
	this->signal = signal;
	this->speed = speed;
	this->baseNoise = baseNoise;
}
Wifi::~Wifi()
{

}

void Wifi::addClient(Client* client)
{
	assert(client->station == nullptr);
	this->clients.insert(client);
	client->station = this;
}
void Wifi::removeClient(Client* client)
{
	assert(client->station == this);
	this->clients.erase(client);
	client->station = nullptr;
}
void Wifi::clearClient()
{
	for (auto client : this->clients)
	{
		client->clearStation();
	}
	this->clients.clear();
}
Real Wifi::getBaseSignal()
{
	return this->signal;
}
Real Wifi::getBaseSpeed()
{
	return this->speed;
}
size_t Wifi::getClientCount()
{
	return this->clients.size();
}

Real Wifi::getBaseNoise()
{
	return this->baseNoise;
}
