#include"GUI/Drawable.h"
#pragma once
#include "Actions/Action.h"
class ActionAddNotes:public Action
{
	public:
	ActionAddNotes(Registrar*);
	bool virtual Execute();
	virtual ~ActionAddNotes();

};

