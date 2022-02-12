#pragma once
#include "..//SPOT/Actions/Action.h"

//Class responsible for saving current plan
class ActionSavePlan : public  Action
{
public:

	ActionSavePlan(Registrar*);
	bool virtual Execute();
	virtual ~ActionSavePlan();


};

