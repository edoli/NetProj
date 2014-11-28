/*
 * Client.cpp
 *
 *  Created on: 2014. 11. 29.
 *      Author: 근홍
 */

#include "Client.hpp"
#include <cmath>
#include <cassert>

Client::Client(Real x, Real y) : Position(x,y)
{
	this->station = nullptr;
}

Client::~Client()
{

}

Real Client::getSNR()
{
	assert(this->station != nullptr);
	Real signal = this->station->getBaseSignal();
	signal = signal/Position::distanceSquare(*this, *this->station);
	Real noise = this->station->getBaseNoise();

	return signal/noise;
}
Real Client::getAlohaSpeed()
{
	assert(this->station != nullptr);
	Real N = this->station->getClientCount();

	Real lnResult = (N - 1.0) * log(1.0 - (1.0 / N)) - log(N);
	return exp(lnResult) * this->station->getBaseSpeed();
}
Real Client::getBER()
{
	assert(this->station != nullptr);
	Real snr = getSNR();

	return 0.5 * erfc(snr);
}
Real Client::getDropRate(const size_t& MTU)
{
	assert(this->station != nullptr);
	Real mtu = MTU;
	Real ber = getBER();
	return 1.0 - pow( (1 - ber) , mtu);
}
Real Client::getTCPSpeed(const size_t& MTU)
{
	assert(this->station != nullptr);
	Real mtu = MTU;
	Real rtt = getRTT(MTU);
	Real loss = getDropRate(MTU);
	Real alohaSpeed = getAlohaSpeed();

	return std::min(alohaSpeed, (1 -loss) * (mtu / ( rtt * sqrt(2 * loss / 3) )));
}
Real Client::getRTT(const size_t& MTU)
{
	assert(this->station != nullptr);
	Real mtu = MTU;
	return 4.0 * mtu / this->getAlohaSpeed();
}

Real Client::getStationDistance()
{
	return Position::distance(*this, *this->station);
}
