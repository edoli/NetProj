/*
 * Reposition.hpp
 *
 *  Created on: 2014. 12. 01.
 *      Author: SJ Jeon
 */

#ifndef Reposition_HPP_
#define Reposition_HPP_

#include <cmath>
#include <vector>

#include "Client.hpp"
#include "Wifi.hpp"

using namespace std;

class Reposition
{
public:
	static void kmean(vector<Wifi*>& wifiSet, vector<Client*>& clientSet);
	static void kmeanPenalty(vector<Wifi*>& wifiSet, vector<Client*>& clientSet);
	static void kmeanRandom(vector<Wifi*>& wifiSet, vector<Client*>& clientSet);
	static void gravity(vector<Wifi*>& wifiSet, vector<Client*>& clientSet);
	static void gravityPenalty(vector<Wifi*>& wifiSet, vector<Client*>& clientSet);
};



#endif /* Reposition_HPP_ */
