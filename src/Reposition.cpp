/*
 * Kmean.cpp
 *
 *  Created on: 2014. 12. 01.
 *      Author: SJ Jeon
 */

#include <Reposition.hpp>
#include <cmath>
#include <vector>
#include <cassert>
#include <cstdio>
#include <limits>

#include "Client.hpp"
#include "Wifi.hpp"
#include "Vec2d.hpp"

using namespace std;

void Reposition::kmean(vector<Wifi*>& wifiSet, vector<Client*>& clientSet)
{
	size_t clusterCount = wifiSet.size();

	vector<vector<int>> clusters;

	for(size_t i = 0; i < clusterCount; i++) {
		vector<int> a;
		a.push_back(1);
		clusters.push_back(a);
	}

	while(true)
	{
		for(auto cluster : clusters)
		{
			cluster.clear();
		}

		for (size_t i = 0; i < clientSet.size(); i++)
		{
			Client* client = clientSet[i];
			Real shortest = numeric_limits<Real>::max();
			size_t index = 0;

			for (size_t j = 0; j < wifiSet.size(); j++)
			{
				Wifi* wifi = wifiSet[j];
				Real dist = Position::distance(*client, *wifi);

				if (dist < shortest)
				{
					shortest = dist;
					index = j;
				}
			}

			clusters[index].push_back(i);
		}


		int stop = 1;


		for (size_t i = 0; i < wifiSet.size(); i++)
		{
			Wifi* wifi = wifiSet[i];

			Real prevX = wifi->getX();
			Real prevY = wifi->getY();

			Real totalX = 0;
			Real totalY = 0;

			auto cluster = clusters[i];


			for(int index : cluster)
			{
				Client* client = clientSet[index];
				totalX += client->getX();
				totalY += client->getY();
			}

			Real meanX = totalX / cluster.size();
			Real meanY = totalY / cluster.size();

			wifi->setPosition(meanX, meanY);

			if((abs(meanX - prevX) + abs(meanY - prevY)) > 0.5f)
			{
				stop = 0;
			}
		}

		if (stop) {
			break;
		}
	}
}

void Reposition::gravity(vector<Wifi*>& wifiSet, vector<Client*>& clientSet)
{
	vector<Vec2d> forces;
	vector<int> counts;

	for(size_t i = 0; i < wifiSet.size(); i++) {
		Vec2d vec;
		forces.push_back(vec);

		counts.push_back(0);
	}

	while(true)
	{
		for(size_t i = 0; i < forces.size(); i++)
		{
			forces[i].x = 0;
			forces[i].y = 0;
		}
		for (size_t i = 0; i < counts.size(); i++)
		{
			counts[i] = 0;
		}

		for (size_t i = 0; i < clientSet.size(); i++)
		{
			Client* client = clientSet[i];
			Real shortest = numeric_limits<Real>::max();
			size_t index = 0;

			for (size_t j = 0; j < wifiSet.size(); j++)
			{
				Wifi* wifi = wifiSet[j];
				Real dist = Position::distance(*client, *wifi);

				if (dist < shortest)
				{
					shortest = dist;
					index = j;
				}
			}

			Wifi* wifi = wifiSet[index];
			Real dx = wifi->getX() - client->getX();
			Real dy = wifi->getY() - client->getY();

			forces[index].x -= dx;
			forces[index].y -= dy;

			counts[index] += 1;
		}


		int stop = 1;


		for (size_t i = 0; i < wifiSet.size(); i++)
		{
			if (counts[i] == 0) {
				continue;
			}

			Wifi* wifi = wifiSet[i];

			Real prevX = wifi->getX();
			Real prevY = wifi->getY();

			Real nextX = prevX + (forces[i].x / counts[i]);
			Real nextY = prevY + (forces[i].y / counts[i]);


			wifi->setPosition(nextX, nextY);

			if((abs(nextX - prevX) + abs(nextY - prevY)) > 0.5f)
			{
				stop = 0;
			}
		}

		if (stop) {
			break;
		}
	}

}

