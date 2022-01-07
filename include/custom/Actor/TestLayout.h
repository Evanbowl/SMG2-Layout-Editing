#pragma once

#include "Screen/LayoutActor.h"

class TestLayout : public LayoutActor {
public:
	TestLayout(const char* pName);

	virtual void init(const JMapInfoIter &rIter);
	virtual void movement();
};
