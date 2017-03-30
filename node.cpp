#include "node.h"

Edge::Edge(int w, Node* s, Node* e){
	this->weight = w;
	this->start = s;
	this->end = e;
}
