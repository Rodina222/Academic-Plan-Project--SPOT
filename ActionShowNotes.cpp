#include "ActionShowNotes.h"

ActionShowNotes::ActionShowNotes(Registrar*p) :Action(p) {
}
bool ActionShowNotes::Execute() {

	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("Notes now are being displayed!");
	Note note;
	vector<string> myNote = note.getmyNote();
	pGUI->DrawNotes(myNote);

	return true;
}
ActionShowNotes::~ActionShowNotes(){};