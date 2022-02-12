#pragma once
#include "..//SPOT/Actions/Action.h"
//Class responsible for adding course action
class GPAcalculator :
	public Action
{
public:
	GPAcalculator(Registrar*);
	bool virtual Execute();
	virtual ~GPAcalculator();
};


