#pragma once
#include <string>

using namespace std;

class BusInfo
{
public:
	int id;
	bool is_in_depot;
	BusInfo(string driver_name, string route) {
		id = -1;
		is_in_depot = true;
		this->driver_name = driver_name;
		this->route = route;
	}
	string get_driver() {
		return driver_name;
	}
	string get_route() {
		return route;
	}
	string to_string() {
		return "Id: " + std::to_string(id) + "\tName: " + driver_name + "\tRoute : " + route + "\tIn depot: " + (is_in_depot ? "true" : "false") + "\n";
	}
private:
	string driver_name;
	string route;
};