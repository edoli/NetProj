/*
 * main.cpp
 *
 *  Created on: 2014. 11. 28.
 *      Author: 근홍
 */




#include <unordered_map>
#include <cmath>
#include <random>
#include <ctime>
#include <vector>
#include <cstdio>
#include "Position.hpp"

#include "Client.hpp"
#include "Wifi.hpp"

using namespace std;

int main()
{
	default_random_engine engine(time(0));
	uniform_real_distribution<double> realDist(0,100);

	size_t clientCount = 50;
	size_t wifiCount = 4;
	size_t MTU = 1500;
	Real defaultSignal = 10000;
	Real defaultNoise = 1;
	Real defaultSpeed = 54*1000*1000;

	uniform_int_distribution<size_t> wifiDist(0, wifiCount-1);

	vector<Wifi*> wifiSet;
	vector<Client*> clientSet;

	for(size_t k=0; k<wifiCount; k++)
	{
		Real x = realDist(engine);
		Real y = realDist(engine);

		wifiSet.push_back(new Wifi(x,y,defaultSignal, defaultSpeed, defaultNoise));
	}
	for(size_t k=0; k<clientCount; k++)
	{
		Real x = realDist(engine);
		Real y = realDist(engine);

		Client* client = new Client(x,y);

		size_t selectedWifi = wifiDist(engine);
		printf("[%.9f, %.9f] Wifi %lu selected\n", x,y, selectedWifi);

		wifiSet[selectedWifi]->addClient(client);
		clientSet.push_back(client);
	}

	Real minSpeed = numeric_limits<Real>::max();
	Real maxSpeed = numeric_limits<Real>::min();
	for(int k=0; k<1000; k++)
	{
		for(auto wifi : wifiSet)
		{
			Real x = realDist(engine);
			Real y = realDist(engine);
			wifi->setPosition(x,y);
		}

		Real sumSpeed = 0;
		for(auto client : clientSet)
		{
			Real speed = client->getTCPSpeed(MTU);
			//Real drop = client->getDropRate(MTU);
			//printf("[%.9f] Client speed %.9f, drop %.9f\n", client->getStationDistance(), speed, drop);
			sumSpeed += speed;
		}
		printf("Total speed %.9f\n", sumSpeed);
		minSpeed = min(minSpeed, sumSpeed);
		maxSpeed = max(maxSpeed, sumSpeed);
	}

	printf("Min speed %.9f\n", minSpeed);
	printf("Max speed %.9f\n", maxSpeed);


	for(auto item : wifiSet)
		delete item;
	for(auto item : clientSet)
		delete item;
	return 0;
}
