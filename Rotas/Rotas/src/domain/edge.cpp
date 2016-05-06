#include "domain\edge.h"

double Edge::get_distance()
{
	return distance;
}

Vertex Edge::get_source() {
	return source;
}

Vertex Edge::get_destination() {
	return destination;
}