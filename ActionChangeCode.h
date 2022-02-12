#pragma once
#include "Actions/Action.h"
class ActionChangeCode :
    public Action
{
public:
	ActionChangeCode(Registrar* p);
	
	bool virtual Execute();
	virtual ~ActionChangeCode();


};

