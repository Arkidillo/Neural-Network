#include "node.h"

/* Create an node, which holds a threshold of whether or, initializing its weight, and starting and ending nodes */
Node::Node(int threshold, Edge* in, Edge *out){
	this->threshold = threshold;
	this->in = in;
	this->out = out;
}

/* Create an edge, initializing its weight, and starting and ending nodes */
Edge::Edge(int weight, Node* start, Node* end){
	this->weight = weight;
	this->start = start;
	this->end = end;
}
