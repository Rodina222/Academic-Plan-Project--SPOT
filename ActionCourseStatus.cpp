#include "ActionCourseStatus.h"
#include"Registrar.h"
#include"Courses/UnivCourse.h"
#include <iostream>

ActionCourseStatus::ActionCourseStatus(Registrar* p) :Action(p)
{
}

bool ActionCourseStatus::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg(" get CourseStatus = S || set CourseStatus = G ");
	string act = pGUI->GetSrting();

	ActionData actData = pGUI->GetUserAction("Choose Course to set/get Course status");
	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		x = actData.x;
		y = actData.y;
		StudyPlan* pS = pReg->getStudyPlay();

		for (int i = 1; i <= 5; i++)
		{
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				SEMESTER sem2 = static_cast<SEMESTER>(sem);
				list<Course*> courses = pS->getCourses(i, sem2);
				for (auto it = courses.begin(); it != courses.end(); ++it)
				{
					graphicsInfo gInfo = (*it)->getGfxInfo();
					if (((x > gInfo.x) && (x < (gInfo.x + CRS_WIDTH))) && ((y > gInfo.y) && (y < (gInfo.y + CRS_HEIGHT))))
					{
						if (act == "S")
						{
							pGUI->PrintMsg("Write Course Status:");
							string status = pGUI->GetSrting();
							STATUS newstatus=Done_;
							if (status == "Done")
								newstatus = Done_;
							else if (status == "Progress")
								newstatus = Progress;
							else if (status == "Pending")
								newstatus = Pending;
							(*it)->SetCourseSTATUS(newstatus);
							break;
						}
						else if (act == "G")
						{
							STATUS status = (*it)->Get_course_STATUS();
							string newstatus;
							if (status == Done_)
								newstatus = "Done_";
							else if (status == Progress)
								newstatus = "Progress";
							else if (status == Pending)
								newstatus = "Pending";
							pGUI->PrintMsg(newstatus);
							string dummy = pGUI->GetSrting();
							break;
						}
					}
				}
			}
		}
	}
	return true;
}

ActionCourseStatus::~ActionCourseStatus()
{
}