#include "GPAcalculator.h"
#include"Registrar.h"
#include "Courses/UnivCourse.h"
#include <iostream>
#include <vector>
#include <sstream>

GPAcalculator::GPAcalculator(Registrar* p) :Action(p)
{
}

bool GPAcalculator::Execute()
{
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg(" Calculating the GPA ");

	double GPA;
	double GPA_X_Crd = 0;
	StudyPlan* pS = pReg->getStudyPlay();
	for (int i = 1; i <= 5; i++)
	{
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			SEMESTER sem2 = static_cast<SEMESTER>(sem);
			list<Course*> courses = pS->getCourses(i, sem2);
			for (auto it = courses.begin(); it != courses.end(); ++it)
			{
				//GPA = (*it)->Get_Course_GPA();
				//if ((GPA > 4) || (GPA < 0))
				//{
				pGUI->PrintMsg(" Set the GPA for Course: " + (*it)->getTitle() + " ( " + (*it)->getCode() + " ) ");
				(*it)->SetCourseGPA(stod(pGUI->GetSrting()));
				GPA_X_Crd = GPA_X_Crd + ((*it)->Get_Course_GPA() * (*it)->getCredits());
				//}
			}
		}
	}

	int T_Crd = pS->getTotalCredits();
	double T_GPA = GPA_X_Crd / T_Crd;
	////////////////////////
	ostringstream strs;
	strs << T_GPA;
	string str = strs.str();
	/// ////////////////////
	pGUI->PrintMsg(str);
	string dummy = pGUI->GetSrting();

	return true;
}

GPAcalculator::~GPAcalculator()
{
}