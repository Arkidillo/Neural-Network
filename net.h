#ifndef _NET_H_
#define _NET_H_

#include "node.h"

class Net {
	public:
		InNode* inputs;
		HiddenNode* hidden;
		OutNode* outputs;
		Net();
}

#endif _NET_H_