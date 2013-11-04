/*
 * DisplayList.h
 *
 *  Created on: Nov 4, 2013
 *      Author: diogo
 */

#ifndef DISPLAYLIST_H_
#define DISPLAYLIST_H_

#include <Node.h>

class DisplayList: public Node {
private:
	int list_id;
public:
	DisplayList();
	virtual ~DisplayList();
	virtual void processNode(stack<string> apps_stack, stack<string> ani_stack);
	virtual void drawPrims(string appearance);
	virtual void closeDefinition(stack<string> apps_stack);
	virtual int getType();
};

#endif /* DISPLAYLIST_H_ */
