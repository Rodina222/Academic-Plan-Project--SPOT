#pragma once
#include "Actions/Action.h"
#include "Note.h"
#include"GUI/GUI.h"
#include"Registrar.h"
class ActionShowNotes :
    public Action
{
public:
	ActionShowNotes(Registrar*);
	bool virtual Execute();
	virtual ~ActionShowNotes();

};

