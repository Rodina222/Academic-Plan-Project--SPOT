#pragma once

//This header file contains some defenitions to be used all over the application
#include <string>
using namespace std;
typedef string Course_Code;


//Semesters
enum SEMESTER
{
	FALL,
	SPRING,
	SUMMER,
	SEM_CNT	//number of semesters 
};

enum CourseType {
	UNIVC,                               // UNIVERSITY COMPULSURY        
	UNIVE,                                 // university elective
	MAJORE,                                  //Major elective 
	TRACKC,                              //Track compulsory
	TRACKE,                             //track elective
	MAJORC,                              //Major Compulsory
	CONC,                                 //Concentration compulsory
	CONE,                               // Concentration elective 
	MINOR
};


//All possible actions
enum ActionType
{
	ADD_CRS,	//Add a course to study plan
	DEL_CRS,	//Delete a course from study plan
	Drag_Drop,
	STU_LEVEL,      //STUdent level

	SAVE,		//Save a study plan to file
	LOAD,		//Load a study plan from a file

	DISPLAY_INFO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled
	ADD_NOTE,
	SHOW_NOTE,
	ADD_MINOR,		//Exit the application

	STATUS_BAR,	//A click on the status bar
	MENU_BAR,	//A click on an empty place in the menu bar
	DRAW_AREA,	//A click in the drawing area
	CHANGE_CODE,
	CANCEL,		//ESC key is pressed
	GPA_Calculator,
	CHECK_VALIDITY,
	COURSE_STATUS,

};

//to sotre data related to the last action
struct ActionData
{
	ActionType actType;
	int x, y;
	
};


