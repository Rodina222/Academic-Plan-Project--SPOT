#include "ActionDeleteCourse.h"
#include <vector>
using namespace std;

bool ActionDeleteCourse::Execute() {
	SEMESTER Mysem;
	GUI* pGUI = pReg->getGUI();
	int i = 0;
	 StudyPlan *ps = pReg->getStudyPlay();
	ActionData myData = pGUI->GetUserAction("Select Course to delete from study plan:");
	int x = myData.x;
	int y = myData.y;
	Course* pCourse= ps->Check_Course_coordinates_SP(x, y);
	
	if (pCourse != nullptr) {
		MyYearAndSemester* yANdS = pReg->GetYearAndSem(pCourse->getGfxInfo().y);
		ps->DeleteCourseFromPlan(pCourse, yANdS->Year,yANdS->sem);
		pGUI->PrintMsg("Cousre has been deleted successfully");

			return true;
	}
	else {
		pGUI->PrintMsg("No Course in this place");
		return false;
	} 
}
