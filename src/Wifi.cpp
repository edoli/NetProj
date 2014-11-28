/*
 * Wifi.cpp
 *
 *  Created on: 2014. 11. 29.
 *      Author: 근홍
 */

#include "Wifi.hpp"
#include "Client.hpp"
#include <cassert>

Wifi::Wifi(double x, double y, double signal, double speed) : Position(x,y)
{
	this->signal = signal;
	this->speed = speed;
}
Wifi::~Wifi()
{

}

void Wifi::addClient(Client* client)
{
	assert(client->station == nullptr);
	this->clients.insert(client);
}
void Wifi::removeClient(Client* client)
{
	assert(client->station == this);
	this->clients.erase(client);
}
double Wifi::getBaseSignal()
{
	return this->signal;
}
double Wifi::getBaseSpeed()
{
	return this->speed;
}
size_t Wifi::getClientCount()
{
	return this->clients.size();
}
