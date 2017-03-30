#ifndef _NODE_H_
#define _NODE_H_

/* Input is going to be the position of the reCaptcha */
class InNode{
	public:
		Edge *out;
		InNode(){
			out = NULL;
		};
		InNode(Edge*);
		sendInput(int input);
};

class HiddenNode{
	public:
		int threshold;
		Edge *in;
		Edge *out;
		HiddenNode(){
			threshold = 0;
			in = NULL;
			out = NULL;
		};
		HiddenNode(int, Edge*, Edge*);
		sendToHidden(int input);
};

class OutNode{
	public:
		Edge* in;
		OutNode(){
			in = NULL;
		}
		OutNode(Edge*);
		sendToOutput(int input);
		
};

class Edge{
	public:
		int weight;
		Node *start;
		Node *end;
		Edge(int, Node*, Node*);
};

#endif 
