#include "ActionDisplayCourseInfo.h"
#include "ActionDisplayCourseInfo.h"
#include "Registrar.h"
#include "Courses/UnivCourse.h"
#include<iostream>
using namespace std;


ActionDisplayCourseInfo::ActionDisplayCourseInfo(Registrar* p) :Action(p)
{

}

bool ActionDisplayCourseInfo::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Display Course Information: Please,choose the course you want to know its information  ");

	int x, y;
	ActionData actData = pGUI->GetUserAction("Select a course to display its Information:");//get coord where user clicked

	if (actData.actType == DRAW_AREA) //user clicked inside drawing area
	{
		x = actData.x;
		y = actData.y;
		StudyPlan* pS = pReg->getStudyPlay();
		Course* Pcourse = pS->Check_Course_coordinates_SP(x, y);
		if (Pcourse != nullptr)
		{
			pS->UnselectCourses_SP(Pcourse);
			pGUI->DrawCourse(Pcourse);
			pGUI->Info_Window(Pcourse);
			Pcourse->setSelected(false);
			return true;
		}
		else
			return false;

	}

	return false;
}


ActionDisplayCourseInfo::~ActionDisplayCourseInfo()
{

}
