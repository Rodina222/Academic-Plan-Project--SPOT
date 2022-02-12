#include "ActionChangeCode.h"
#include"Registrar.h"

ActionChangeCode::ActionChangeCode(Registrar* p) :Action(p) {
//	Execute();
}

bool ActionChangeCode::Execute() {
	string newCode;
	GUI * pGUI= pReg->getGUI();

	ActionData myData=pGUI->GetUserAction("Select Course to change its code");
	

	StudyPlan* pS = pReg->getStudyPlay();
	Course*myOldCourse=pS->Check_Course_coordinates_SP(myData.x, myData.y);
	if (myOldCourse == nullptr) {
		pGUI->PrintMsg("NO Course in This place ");
		return true;
	}
	if (myOldCourse != nullptr) {
		pGUI->PrintMsg("Write new Course Code :");
		string newCode = pGUI->GetSrting();
		MyYearAndSemester* yearSem=pReg->GetYearAndSem(myData.y);
		///#########################Deleting Course#########################

		pS->DeleteCourseFromPlan(myOldCourse, yearSem->Year, yearSem->sem);

		//##########################  Adding Course###########################
		CourseInfo newCourse = pReg->getCourseInfo(newCode);
		if (newCourse.Code == "000") {
			pGUI->PrintMsg(" No Course With this code");
			return true;
		}
		else {
			Course* newC = new Course(newCode, newCourse.Title, newCourse.Credits);     ///////////// new Course 
			pS->AddCourse(newC, yearSem->Year, yearSem->sem);
			newC->setGfxInfo(myOldCourse->getGfxInfo());
			newC->setX(myOldCourse->getX());
			newC->setY(myOldCourse->getY());
			pReg->setCourseType(newC);
			
			return true;
		}
	}

}
ActionChangeCode::~ActionChangeCode(){	
}
