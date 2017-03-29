#include "node.h"

Edge::Edge(int w, Edge* s, Edge* e){
	this->weight = w;
	this->start = s;
	this->end = e;
}
