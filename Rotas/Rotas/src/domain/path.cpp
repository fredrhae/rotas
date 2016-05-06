#include "domain\path.h"

Vertex Path::get_source()
{
	return route.front().get_source();
}

Vertex Path::get_destination()
{
	return route.back().get_destination();
}

double Path::get_total_distance()
{
	double total_distance = 0.0;
	for each (Edge element in route)
	{
		total_distance += element.get_distance();
	}

	return total_distance;
}