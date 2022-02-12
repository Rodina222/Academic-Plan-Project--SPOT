#pragma once
#include"Actions/Action.h"
class ActionCourseStatus :
    public Action
{
public:
	ActionCourseStatus(Registrar*);
	bool virtual Execute();
	virtual ~ActionCourseStatus();
};

