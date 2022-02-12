#include "ActionCheckValidity.h"




ActionCheckValidity::ActionCheckValidity(Registrar* pReg) :Action(pReg) {};



bool ActionCheckValidity::Execute() {

	GUI *pGUI = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlay();
	ofstream writein("E:\\CheckReport.txt");

	pReg->Check_Credits();
	pS->CheckStudyPlanCredits();

	pS->Check_Comp_Major_Studyplan(pReg);
	pS->Check_Comp_Track_Studyplan(pReg);
	pS->Check_Comp_Univ_Studyplan(pReg);
	pS->Check_Elective_Major_Studyplan(pReg);
	pS->Check_Elective_Univ_Studyplan(pReg);

	pS->Check_Coreq_studyplan();
	pS->Check_Prereq_studyplan();
	Warnings* planWarning = pS->getWarnings();
	pGUI->PrintMsg("Checking Validity");

	 int  x = 0;
	 int y = 0;
	 // Draw strings in check report
	 if (planWarning->Coreqwarning.empty() && planWarning->credits.empty() &&
		 planWarning->MajorCOMIssues.empty() && planWarning->Prereqwarning.empty() &&
		 planWarning->MajorElectiveIssues.empty() && planWarning->TrackCOMIssues.empty() &&
		 planWarning->uniCOMIssues.empty() && planWarning->UNIVelectiveIssues.empty())
		 pGUI->DrawString("Congratulation!, You Are Ready for Graduation",0,0);

	 pGUI->OpenCheckWindow();
	//##################################### Draw String of Moderate issues which is overload or underload
	for (auto index = 0; index < planWarning->moderate.size(); index++) {
		pGUI->DrawStringModerate(planWarning->moderate[index], x, y);
			y += 15;
		writein << planWarning->moderate[index] << " \n";

	}
	planWarning->moderate.clear();
	//##################################### Draw String of Critical issues of number of credits
	x = 0;
	for (auto index = 0; index < planWarning->credits.size(); index++) {
		x = 0;
		pGUI->DrawString(planWarning->credits[index], x, y);
		y += 15;
		writein << planWarning->credits[index] << " \n";
	}
	planWarning->credits.clear();



	//##################################### Draw String of Critical issues of university compulsory issues
	pGUI->DrawStringCritical(" You have to register these courses (University Complusory): ", x, y);
	y += 15;
	x = 0;
	for (auto index = 0; index < planWarning->uniCOMIssues.size(); index++) {
		
		pGUI->DrawString(planWarning->uniCOMIssues[index]+" , ", x, y);
		x += 40;
		if (index % 6 == 0 && index!=0)
			y += 15;
		writein <<" You have to register this course"<< planWarning->uniCOMIssues[index] << " \n";
	}
	planWarning->uniCOMIssues.clear();
	y += 15;
	//##################################### Draw String of Critical issues
	x = 0;
	pGUI->DrawStringCritical(" You have to register these courses (Track Complusory)",x,y);
	y += 15;
	x = 0;
	for (auto index = 0; index < planWarning->TrackCOMIssues.size(); index++) {
	
		pGUI->DrawString( planWarning->TrackCOMIssues[index]+" , ", x, y);
		x += 45;
		if (index % 6 == 0 && index != 0) {
			y += 15;
			x = 0;
		}
		writein << " You have to register this course" << planWarning->TrackCOMIssues[index] << " \n";
	}
	planWarning->TrackCOMIssues.clear();
	y += 15;
	x = 0;
	//##############################################3  MajorCOMIssues
	pGUI->DrawStringCritical(" You have to register these courses (Major Compulsory)", x, y);
	y += 15;
	x = 0;
	for (auto index = 0; index < planWarning->MajorCOMIssues.size(); index++) {
		
		pGUI->DrawString( planWarning->MajorCOMIssues[index]+" , ", x, y);
		x += 45;
		if (index % 6 == 0 && index != 0) {
			y += 15;
			x = 0;
		}
		writein << " You have to register this course" << planWarning->MajorCOMIssues[index] << " \n";
	}
	planWarning->MajorCOMIssues.clear();
	y += 15;
	x = 0;
	//##############################333  MajorElectiveIssues
	pGUI->DrawStringCritical(" You have to register these courses (Major Elective)", x, y);
	y += 15;
	x = 0;
	for (auto index = 0; index < planWarning->MajorElectiveIssues.size(); index++) {
		pGUI->DrawString( planWarning->MajorElectiveIssues[index]+" , ", x, y);
		x += 45;
		if (index % 6 == 0 && index != 0) {
			y += 15;
			x = 0;
		}
		writein << " You have to register this course" << planWarning->MajorElectiveIssues[index] << " \n";
	}
	planWarning->MajorElectiveIssues.clear();
	y += 15;
	x = 0;
	//############################### Prereqwarning #########################
	pGUI->DrawStringCritical(" You have to register Prerequisite of these Courses: ", x, y);
	y += 15;
	x = 0;


	for (auto index = 0; index < planWarning->Prereqwarning.size(); index++) {
		pGUI->DrawString( planWarning->Prereqwarning[index]+" , ", x, y);
		y += 15;
		writein << " You Should register The Prerequisite of course:" << planWarning->Prereqwarning[index] << " \n";
	}
	planWarning->Prereqwarning.clear();
	//################################## Coreqwarning
	pGUI->DrawStringCritical(" You have to register Corequisite of these Courses: ", x, y);
	y += 15;
	for (auto index = 0; index < planWarning->Coreqwarning.size(); index++) {
		pGUI->DrawString(" You Should register The Corequisite of course:" + planWarning->Coreqwarning[index], x, y);
		y += 15;
		writein << " You Should register The Corequisite of course:" << planWarning->Coreqwarning[index] << " \n";
	}
	planWarning->Coreqwarning.clear();
	writein.close();

	pGUI->CLoseCheckReport();

	return true;
}

ActionCheckValidity::~ActionCheckValidity() {

}