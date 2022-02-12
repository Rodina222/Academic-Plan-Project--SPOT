#include "Registrar.h"
#include "Courses/UnivCourse.h"
#include"DEFs.h"
#include<iostream>
#include<fstream>
#include"ActionSavePlan.h"
using namespace std;

ActionSavePlan::ActionSavePlan(Registrar* p) :Action(p)
{

}


bool ActionSavePlan::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Save plan: Please,enter the file name you want to save:  ");

	ofstream file;

	Course_Code filename = pGUI->GetSrting();


	file.open(filename);

	if (!file)
	{
		cout << "File open failure!";
	}
	else
	{
		pReg->SavePlan(file);
	}

	return true; //we should return true after the action is fully executed.

}

ActionSavePlan::~ActionSavePlan()
{
}