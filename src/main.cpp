/*
 * main.cpp
 *
 *  Created on: 2014. 11. 28.
 *      Author: 근홍
 */




#include <Reposition.hpp>
#include <unordered_map>
#include <cmath>
#include <random>
#include <ctime>
#include <vector>
#include <cstdio>
#include <limits>
#include <iostream>
#include <fstream>
#include "Position.hpp"

#include "Client.hpp"
#include "Wifi.hpp"

using namespace std;

void result(string testName, vector<Wifi*>& wifiSet, vector<Client*>& clientSet, size_t MTU)
{
	// Reconnect
	for(auto wifi : wifiSet)
	{
		wifi->clearClient();
	}
	for(size_t l=0; l<clientSet.size(); l++)
	{
		Client* client = clientSet[l];
		size_t selectedWifi = 0;

		Real shortest = numeric_limits<Real>::max();

		for(size_t m = 0; m < wifiSet.size(); m++)
		{
			Wifi* wifi = wifiSet[m];
			Real dist = Position::distance(*client, *wifi);

			if (dist < shortest)
			{
				shortest = dist;
				selectedWifi = m;
			}
		}
		wifiSet[selectedWifi]->addClient(client);
	}

	ofstream outfile;
	outfile.open("out/" + testName + "_test" + ".txt");
	for(auto wifi : wifiSet)
	{
		outfile << wifi->getX() << "," << wifi->getY() << "\n";
	}
	outfile << "-----\n";
	for(auto client : clientSet)
	{
		outfile << client->getX() << "," << client->getY() << "\n";
	}
	outfile.close();


	Real sumSpeed = 0;
	for(auto client : clientSet)
	{
		Real speed = client->getTCPSpeed(MTU);
		//Real drop = client->getDropRate(MTU);
		//printf("[%.9f] Client speed %.9f, drop %.9f\n", client->getStationDistance(), speed, drop);
		sumSpeed += speed;
	}
	printf("[%8s] Total speed %.9f\n", testName.c_str(), sumSpeed);
}

int main()
{
	default_random_engine engine(time(0));
	uniform_real_distribution<double> realDist(0,100);

	size_t clientCount = 30;
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

	size_t testCount = 10;

	Real minSpeed = numeric_limits<Real>::max();
	Real maxSpeed = numeric_limits<Real>::min();
	Real meanSpeed = 0;

	/*
	for(size_t k=0; k<testCount; k++)
	{
		for(auto wifi : wifiSet)
		{
			Real x = realDist(engine);
			Real y = realDist(engine);
			wifi->setPosition(x,y);
		}

		//Reposition::gravity(wifiSet, clientSet);
		//Reposition::kmean(wifiSet, clientSet);

		// Reconnect
		for(auto wifi : wifiSet)
		{
			wifi->clearClient();
		}
		for(size_t l=0; l<clientCount; l++)
		{
			Client* client = clientSet[l];
			size_t selectedWifi = 0;

			Real shortest = numeric_limits<Real>::max();

			for(size_t m = 0; m < wifiSet.size(); m++)
			{
				Wifi* wifi = wifiSet[m];
				Real dist = Position::distance(*client, *wifi);

				if (dist < shortest)
				{
					shortest = dist;
					selectedWifi = m;
				}
			}
			wifiSet[selectedWifi]->addClient(client);
		}

		ofstream outfile;
		outfile.open("out/" + testName + "_test" + to_string(k) + ".txt");
		for(auto wifi : wifiSet)
		{
			outfile << wifi->getX() << "," << wifi->getY() << "\n";
		}
		outfile << "-----\n";
		for(auto client : clientSet)
		{
			outfile << client->getX() << "," << client->getY() << "\n";
		}
		outfile.close();


		Real sumSpeed = 0;
		for(auto client : clientSet)
		{
			Real speed = client->getTCPSpeed(MTU);
			//Real drop = client->getDropRate(MTU);
			//printf("[%.9f] Client speed %.9f, drop %.9f\n", client->getStationDistance(), speed, drop);
			sumSpeed += speed;
		}
		//printf("Total speed %.9f\n", sumSpeed);
		minSpeed = min(minSpeed, sumSpeed);
		maxSpeed = max(maxSpeed, sumSpeed);
		meanSpeed += (sumSpeed / testCount);
	}
	*/

	Real xSet[4];
	Real ySet[4];

	for(size_t i = 0; i < wifiSet.size(); i++)
	{
		xSet[i] = realDist(engine);
		ySet[i] = realDist(engine);
	}


	for(size_t i = 0; i < wifiSet.size(); i++)
	{
		auto wifi = wifiSet[i];
		wifi->setPosition(xSet[i], ySet[i]);
	}
	result("normal", wifiSet, clientSet, MTU);


	for(size_t i = 0; i < wifiSet.size(); i++)
	{
		auto wifi = wifiSet[i];
		wifi->setPosition(xSet[i], ySet[i]);
	}
	Reposition::kmean(wifiSet, clientSet);

	result("kmean", wifiSet, clientSet, MTU);


	for(size_t i = 0; i < wifiSet.size(); i++)
	{
		auto wifi = wifiSet[i];
		wifi->setPosition(xSet[i], ySet[i]);
	}
	Reposition::gravity(wifiSet, clientSet);

	result("gravity", wifiSet, clientSet, MTU);


	/*
	printf("Min speed %.9f\n", minSpeed);
	printf("Max speed %.9f\n", maxSpeed);
	printf("Mean speed %.9f\n", meanSpeed);
	*/


	for(auto item : wifiSet)
		delete item;
	for(auto item : clientSet)
		delete item;
	return 0;
}
