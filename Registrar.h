#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"
#include <iostream>
#include<sstream>
#include<string>
using namespace std;



struct MyYearAndSemester {
	int Year;
	SEMESTER sem;
};


//The maestro class for the application
class Registrar
{

	const int Fall1Y = 512, Spring1Y = 482, Summer1Y = 450,
		Fall2Y = 420, Spring2Y = 390, Summer2Y = 360,
		Fall3Y = 330, Spring3Y = 300, Summer3Y = 270,
		Fall4Y = 240, Spring4Y = 210, Summer4Y = 180,
		Fall5Y = 150, Spring5Y = 120, Summer5Y = 90,
		CommonX = 130;

	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;              	//Registration rules
	StudyPlan* pSPlan;
	MyYearAndSemester* YandS;            // this struct have the year of a course and semester
	void LoadCatalog();

public:
	Registrar();
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlay();
	vector<CourseInfo>& getCourseCatalog();
	CourseInfo getCourseInfo(string code);
	MyYearAndSemester* GetYearAndSem(int y);  // This function return Year and Semester of the courses based on x and y on the Window 
	void Run();
	void setCourseType(Course* pCourse);
	graphicsInfo* getNewCoordinates(int year, SEMESTER sem, Course* pCourse);
	void Check_Credits()  const;
	Rules& getRegRules();
	void SavePlan(ofstream& filename);
	void LoadRules();
	void SetCoursesCoordinates();
	~Registrar();
};

