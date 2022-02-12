#pragma once
#include "Actions/Action.h"
//Class responsible for adding course action
class StudentLevel :
	public Action
{
public:
	StudentLevel(Registrar*);
	bool virtual Execute();
	virtual ~StudentLevel();
};
