#ifndef _NODE_H_
#define _NODE_H_

class Edge{
	public:
		int weight;
		Edge *start;
		Edge *end;
		Edge(int, Edge*, Edge*);
};

#endif 
