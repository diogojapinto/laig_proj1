

#ifndef MYPRIMITIVE_H_
#define MYPRIMITIVE_H_

#include "Node.h"


class MyPrimitive : public Node {
public:
	MyPrimitive();
	virtual void draw() = 0;
	virtual ~MyPrimitive();
	virtual void setAppearance(string appearance);
};

#endif /* MYPRIMITIVE_H_ */
