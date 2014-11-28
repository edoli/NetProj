/*
 * Client.cpp
 *
 *  Created on: 2014. 11. 29.
 *      Author: 근홍
 */

#include "Client.hpp"
#include <cmath>
#include <cassert>

Client::Client(double x, double y) : Position(x,y)
{
	this->station = nullptr;
}

Client::~Client()
{

}

double Client::getSNR()
{
	assert(this->station != nullptr);
	double signal = this->station->getBaseSignal();
	signal = signal/Position::distanceSquare(*this, *this->station);
	double noise = this->station->getBaseNoise();

	return signal/noise;
}
double Client::getAlohaSpeed()
{
	assert(this->station != nullptr);
	double N = this->station->getClientCount();

	double lnResult = (N - 1.0) * log(1.0 - (1.0 / N)) - log(N);
	return exp(lnResult);
}
double Client::getBER()
{
	assert(this->station != nullptr);
	double snr = getSNR();

	return 0.5 * erfc(snr);
}
double Client::getDropRate(const size_t& MTU)
{
	assert(this->station != nullptr);
	double mtu = MTU;
	double ber = getBER();
	return 1.0 - pow( (1 - ber) , mtu);
}
double Client::getTCPSpeed(const size_t& MTU)
{
	assert(this->station != nullptr);
	double mtu = MTU;
	double rtt = getRTT(MTU);
	double loss = getDropRate(MTU);

	return mtu / ( rtt * sqrt(2 * loss / 3) );
}
double Client::getRTT(const size_t& MTU)
{
	assert(this->station != nullptr);
	double mtu = MTU;
	return mtu / this->station->getBaseSpeed();
}
