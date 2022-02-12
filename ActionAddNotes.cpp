#include "ActionAddNotes.h"
#include"Registrar.h"
#include"GUI/GUI.h"
#include "GUI/Drawable.h"
#include<iostream>
#include<fstream>
#include"Note.h"
using namespace std;
ActionAddNotes::ActionAddNotes(Registrar* p) :Action(p) 
{
}
bool ActionAddNotes::Execute() {
	Note myNote;
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Write your notes");
	string note= pGUI->GetSrting();
	myNote.setmyNote(note);
	return true;
}
ActionAddNotes::~ActionAddNotes() {};