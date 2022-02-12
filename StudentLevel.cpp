#include "StudentLevel.h"
#include"Registrar.h"
#include "Courses/Course.h"
#include <iostream>
#include <sstream>

StudentLevel::StudentLevel
(Registrar* p) :Action(p)
{
}

bool StudentLevel::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg(" Display Student Level ");
	StudyPlan* pS = pReg->getStudyPlay();
	int T_Crd = pS->getTotalCredits();

	if (T_Crd < 36)
		pS->set_student_level(Freshman);
	else if (T_Crd < 72)
		pS->set_student_level(Sophomore);
	else if (T_Crd < 108)
		pS->set_student_level(Junior);
	else
		pS->set_student_level(Senior);

	SLevel level = pS->get_student_level();
	string s_level;
	if (level == Freshman)
		s_level = "Freshman";
	else if (level == Sophomore)
		s_level = "Sophomore";
	else if (level == Junior)
		s_level = "Junior";
	else if (level == Senior)
		s_level = "Senior";

	pGUI->PrintMsg(" The status of the student is: " + s_level);
	string dummy = pGUI->GetSrting();
	return true;
}

StudentLevel::~StudentLevel()
{
}