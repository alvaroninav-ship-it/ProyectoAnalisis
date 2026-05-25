#pragma once
#include <iostream>
#include <string>

class Edge
{
private:
	int to;
	double weight;
public:
	Edge(int destination, double w) : to(destination), weight(w) {}
	int getDestination() const { return to; }
	double getWeight() const { return weight; }
};

