#ifndef _NODE_H_
#define _NODE_H_

class Node{
	public:
		int threshold;
		Edge *in;
		Edge *out;
		Node(int, Edge*, Edge*);
};

class Edge{
	public:
		int weight;
		Node *start;
		Node *end;
		Edge(int, Node*, Node*);
};

#endif 
