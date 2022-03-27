#pragma once
#include "LinkedList.h"
#include "BusInfo.cpp"

using namespace std;
class BusPark
{
public:
	BusPark();
	void add_bus(BusInfo* bus, bool from_in = true);
	void remove_bus(BusInfo*);
	BusInfo* select_bus(int);
	void print(bool*);
private:
	void print_list(LinkedList<BusInfo>*);
	LinkedList<BusInfo>* bus_depot;
	LinkedList<BusInfo>* bus_route;
};