#include "Registrar.h"
#include"GPAcalculator.h"
#include "Actions/ActionAddCourse.h"
#include"ActionAddNotes.h"
#include "ActionShowNotes.h"
#include "ActionDeleteCourse.h"
#include "Actions/Import.h"
#include "Actions/DragDrop.h"
#include"ActionCheckValidity.h"
#include"ActionChangeCode.h"
#include"ActionDisplayCourseInfo.h"
#include"ActionSavePlan.h"
#include"ActionCourseStatus.h"
#include"StudentLevel.h"

Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
	LoadCatalog();
	YandS = new  MyYearAndSemester;
	LoadRules();
}

//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

//returns the study plan
StudyPlan* Registrar::getStudyPlay() 
{
	return pSPlan;
}

Action* Registrar::CreateRequiredAction() 
{	
	ActionData actData = pGUI->GetUserAction("Pick an action...");
	Action* RequiredAction = nullptr;

	switch (actData.actType)
	{
	case ADD_CRS:	//add_course action
		RequiredAction = new ActionAddCourse(this);
		break;
	case Drag_Drop:	//add_course action
		RequiredAction = new DragDrop(this);
		break;
	case STU_LEVEL:
		RequiredAction = new StudentLevel(this);
		break;
	case ADD_NOTE: //
		RequiredAction = new ActionAddNotes(this);
		break;
	case SHOW_NOTE: //
		RequiredAction = new ActionShowNotes(this);
		break;
	case DEL_CRS: //delete course
		RequiredAction = new ActionDeleteCourse(this);
		break;
	case SAVE: //save course
		RequiredAction = new ActionSavePlan(this);
		break;
	case DISPLAY_INFO:
		RequiredAction = new ActionDisplayCourseInfo(this);
		break;
	case REDO:
		RequiredAction = new ActionAddCourse(this);
		break;
	case CHANGE_CODE:
		RequiredAction = new ActionChangeCode(this);
		break;
	case CHECK_VALIDITY:
		RequiredAction = new ActionCheckValidity(this);
		break;
	case GPA_Calculator:
		RequiredAction = new GPAcalculator(this);
		break;
	case COURSE_STATUS:
		RequiredAction = new ActionCourseStatus(this);
		break;
	case LOAD:
		RequiredAction = new Import(this);
		break;
	case ADD_MINOR:
		RequiredAction = new Import(this);
		break;
		
	}
	return RequiredAction;
}

//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action* pAct)
{
	bool done = pAct->Execute();
	delete pAct;	//free memory of that action object (either action is exec or cancelled)
	return done;
}

void Registrar::Run()
{
	while (true)
	{
		//update interface here as CMU Lib doesn't refresh itself
		//when window is minimized then restored
		
		UpdateInterface();

		Action* pAct = CreateRequiredAction();
		if (pAct)	//if user doesn't cancel
		{
			if (ExecuteAction(pAct)) {	//if action is not cancelled
				UpdateInterface();
			}
		}
	}
}


void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	SetCoursesCoordinates();
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}


CourseInfo Registrar::getCourseInfo(string code) {
	CourseInfo myCourse;
	int index = -1;
	vector<CourseInfo> Catalog =getCourseCatalog();
	for (int i = 0; i < Catalog.size(); i++) {
		if (code == Catalog[i].Code) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << " I can not find this course" << endl;
		myCourse.Code = "000";
		return myCourse;
	}
	else {
		myCourse = Catalog[index];
		return myCourse;
	}
}

void Registrar::LoadCatalog()
{

	CourseInfo cinfo;
	string LineOfCode = "";
	string restofline = "";
	string CRDS = "";
	int crds = 0;
	string Code;
	string Title;
	string temp;
	string  num;
	string coursecode;
	string newtemp;
	ifstream file;
	file.open("E:\\CourseCatalog.txt");
	if (!file.is_open())
	{
		cout << "File open failure!";
	}
	while (getline(file, LineOfCode))
	{
      //###################################################
		// this part for code and title and credits
		stringstream cc(LineOfCode);
		getline(cc, Code, ',');       // get the code of the course
		cinfo.Code = Code;
		getline(cc, Title, ',');      //get Course Title
		cinfo.Title=Title;
		getline(cc, CRDS, ',');
		stringstream Crd(CRDS);   //we declared the line as a string so this function makes casting for the number of credits to be an integer.
		Crd >> crds;
		cinfo.Credits = crds;
		//###################################################

		getline(cc, restofline, ',');
		///  Case of there is no corequisite for The course and there is a prerequisite or there is no corequisite nor prerequisite
		if (restofline.empty()) {
			getline(cc, restofline, ',');
			if (restofline.empty()) {
				RegRules.CourseCatalog.push_back(cinfo);
			   continue;
			}
			else if (!restofline.empty()) {
				stringstream preline(restofline);        // Put prerequisite list in preline 
				preline >> newtemp;
				if (newtemp == "Prereq:") {
					preline >> Code;
					preline >> num;
					coursecode = Code + " " + num;
					cinfo.PreReqList.push_back(coursecode);       // first prerequisite course

					newtemp = "";
					preline >> newtemp;
					if (newtemp.empty()) {             // only one prerequisite
						RegRules.CourseCatalog.push_back(cinfo);
						cinfo.PreReqList.clear();
						cinfo.CoReqList.clear();
						continue;
					}

					while (newtemp == "And") {                // multiiple prerequisite
						preline >> Code;
						preline >> num;
						coursecode = Code + " " + num;
						cinfo.PreReqList.push_back(coursecode);
						newtemp = "";
						preline >> newtemp;

					}

				}
				RegRules.CourseCatalog.push_back(cinfo);
				cinfo.PreReqList.clear();
				cinfo.CoReqList.clear();
			}
			}


		// case of there is a corequisite put the list of corequisite in restofline
		stringstream ss(restofline);
		ss >> temp;
		
		if (temp == "Coreq:") {
			ss >> Code;
			ss >> num;
			coursecode = Code + " " + num;
			cinfo.CoReqList.push_back(coursecode);
		}

		restofline = "";
		getline(cc, restofline);
		

		//######################################################
		// in case of there is no prereq  only coreq for the course

		if (restofline.empty()) {
			RegRules.CourseCatalog.push_back(cinfo);
			cinfo.PreReqList.clear();
			cinfo.CoReqList.clear();
			continue;
		}
		/// #####################################################
		//Case of there is a prerequisite and corequisite
		stringstream preline(restofline);        // Put prerequisite list in preline 
		preline >> newtemp;
		if (newtemp == "Prereq:") {
			preline >> Code;
			preline >> num;
			coursecode = Code + " " + num;
			cinfo.PreReqList.push_back(coursecode);       // first prerequisite course
			
			newtemp = "";
			preline >> newtemp;
			if (newtemp.empty()) {             // only one prerequisite
				RegRules.CourseCatalog.push_back(cinfo);
				cinfo.PreReqList.clear();
				cinfo.CoReqList.clear();
				continue;
			}
		
			while (newtemp == "And") {                // multiiple prerequisite
				preline >> Code;
				preline >> num;
				coursecode = Code + " " + num;
				cinfo.PreReqList.push_back(coursecode);
				newtemp = "";
				preline >> newtemp;
				
			}

		}
		RegRules.CourseCatalog.push_back(cinfo);
		cinfo.PreReqList.clear();
		cinfo.CoReqList.clear();
	}


	file.close();
}


MyYearAndSemester* Registrar::GetYearAndSem( int y) {
	
	if (y < 540 && y >= 450) {
		if (y <= 540 && y >= Fall1Y) {
			
			YandS->Year = 1;
			YandS->sem = FALL;
			
			return YandS;
		}
		if (y < Fall1Y && y >= Spring1Y) {

			YandS->Year = 1;
			YandS->sem = SPRING;
			
			return YandS;
		}
			
		if (y < Spring1Y && y >= Summer1Y) {

			YandS->Year = 1;
			YandS->sem = SUMMER;
			
			return YandS;
		}
		
	}
	else if (y < Summer1Y && y >= Summer2Y)
	{
		if (y <= Summer1Y && y >= Fall2Y) {

			YandS->Year = 2;
			YandS->sem = FALL;
			
			return YandS;
		}
		
		if (y < Fall2Y && y >= Spring2Y) {

			YandS->Year = 2;
			YandS->sem = SPRING;
			
			return YandS;
		}
			
		if (y < Spring2Y && y >= Summer2Y) {

			YandS->Year = 2;
			YandS->sem = SUMMER;
			
			return YandS;
		}
		
	}
	else if (y < Summer2Y && y >= Summer3Y) {
		if (y < Summer2Y && y >= Fall3Y) {

			YandS->Year = 3;
			YandS->sem = FALL;
			
			return YandS;
		}
			
		if (y < Fall3Y && y >= Spring3Y) {

			YandS->Year = 3;
			YandS->sem = SPRING;
			
			return YandS;
		}
			
		if (y < Spring3Y && y >= Summer3Y) {

			YandS->Year = 3;
			YandS->sem = SUMMER;
			
			return YandS;
		}
			
	}
	else if (y < Summer3Y && y >= Summer4Y) {
		if (y < Summer3Y && y >= Fall4Y) {

			YandS->Year = 4;
			YandS->sem = FALL;
			
			return YandS;
		}
			
		if (y < Fall4Y && y >= Spring4Y) {

			YandS->Year = 4;
			YandS->sem = SPRING;
			
			return YandS;
		}
		if (y < Spring4Y && y >= Summer4Y) {

			YandS->Year = 4;
			YandS->sem = SUMMER;
			
			return YandS;
		}
			
	}
	else if (y < Summer4Y && y >= Summer5Y) {
		if (y < Summer4Y && y >= Fall5Y)
		{

			YandS->Year = 5;
			YandS->sem = FALL;
			
			return YandS;
		}
		if (y < Fall5Y && y >= Spring5Y)
		{

			YandS->Year = 5;
			YandS->sem = SPRING;
			
			return YandS;
		}
		if (y < Spring5Y && y >= Summer5Y)
		{
			YandS->Year = 5;
			YandS->sem = SUMMER;
		
			return YandS;
		}
		
	}
}

void Registrar::setCourseType(Course* pCourse) {
	vector<CourseInfo> Catalog = getCourseCatalog();

		for (int j = 0; j < RegRules.UnivCompulsory.size(); j++) {
			if (pCourse->getCode() == RegRules.UnivCompulsory[j]){
				pCourse->setType(UNIVC);
			break;
		}
		}
		for (int j = 0; j < RegRules.UnivElective.size(); j++) {
			if (pCourse->getCode() == RegRules.UnivElective[j]){
				pCourse->setType(UNIVE);
			break;
		}
		}
		for (int j = 0; j < RegRules.TrackCompulsory.size(); j++) {
			if (pCourse->getCode() == RegRules.TrackCompulsory[j]){
				pCourse->setType( TRACKC);
			break;
		}
	}
		for (int j = 0; j < RegRules.TrackElective.size(); j++) {
			if (pCourse->getCode() == RegRules.TrackElective[j]) {
				pCourse->setType(TRACKE);
				break;
			}
		}
		for (int j = 0; j < RegRules.MajorCompulsory.size(); j++) {
			if (pCourse->getCode() == RegRules.MajorCompulsory[j]) {
				pCourse->setType(MAJORC);
				break;
			}
		}
		for (int j = 0; j < RegRules.MajorElective.size(); j++){
			if (pCourse->getCode() == RegRules.MajorElective[j]) {
				pCourse->setType(MAJORE);
				break;
			}

		}
	}

graphicsInfo* Registrar::getNewCoordinates(int year, SEMESTER sem,Course* pCourse) {
	graphicsInfo* Gfx = new graphicsInfo;
	vector<AcademicYear*> A=pSPlan->getPplan();
	int num =A.at(year - 1)->getIndex(pCourse);
	Gfx->x = CommonX + (num) * CRS_WIDTH;

	if((year==1 )&&( sem==FALL))
	Gfx->y = Fall1Y;
	if ((year == 1) && (sem == SPRING))
		Gfx->y = Spring1Y+1;
	if ((year == 1) && (sem == SUMMER))
		Gfx->y = Summer1Y + 1;

	if ((year == 2) && (sem == FALL))
		Gfx->y = Fall2Y + 1;
	if ((year == 2) && (sem == SPRING))
		Gfx->y = Spring2Y + 1;
	if ((year == 2) && (sem == SUMMER))
		Gfx->y = Summer2Y + 1;

	if ((year == 3) && (sem == FALL))
		Gfx->y = Fall3Y + 1;
	if ((year == 3) && (sem == SPRING))
		Gfx->y = Spring3Y + 1;
	if ((year == 3) && (sem == SUMMER))
		Gfx->y = Summer3Y + 1;

	if ((year == 4) && (sem == FALL))
		Gfx->y = Fall4Y + 1;
	if ((year == 4) && (sem == SPRING))
		Gfx->y = Spring4Y + 1;
	if ((year == 4) && (sem == SUMMER))
		Gfx->y = Summer4Y + 1;
	if ((year == 5) && (sem == FALL))
		Gfx->y = Fall5Y + 1;
	if ((year == 5) && (sem == SPRING))
		Gfx->y = Spring5Y + 1;
	if ((year == 5) && (sem == SUMMER))
		Gfx->y = Summer5Y + 1;
	return Gfx;
	
}

///####################################  Rodina Part                 ####################################3

void Registrar::Check_Credits() const
{
	string result_Univ_Crds;
	string result_Track_Crds;
	string result_Major_Crds;
	string result_Conc_Crds;
	string Total_Crds;


	int Univcrds = pSPlan->getTotalUnivCredits();
	int TrackCrds = pSPlan->getTotalTrackCredits();
	int MajorCrds = pSPlan->getTotalMajorCredits();
	int ConcCrds = pSPlan->getTotalConcentrationCredits();
	int MinorCrds = pSPlan->getTotalMinorCredits();

	if ((RegRules.ReqUnivCredits + RegRules.ElectiveUnivCredits) != Univcrds) //Checking the total university credits (compulsory & elective)
	{
		result_Univ_Crds = "University credits are incomplete!";
		pSPlan->getWarnings()->credits.push_back(result_Univ_Crds);
	}
	else
	{
		result_Univ_Crds = " University credits are complete";
	}

	if (RegRules.ReqTrackCredits != TrackCrds)  //Checking the compulsory Track credits
	{
		result_Track_Crds = "Track credits are  incomplete!";
		pSPlan->getWarnings()->credits.push_back(result_Track_Crds);
	}
	else
	{
		result_Track_Crds = " Track credits are complete";
	}

	if ((RegRules.ReqMajorCredits + RegRules.ElectiveMajorCredits) != MajorCrds)  //Checking the total Major credits
	{
		result_Major_Crds = "Major credits are  incomplete!";
		pSPlan->getWarnings()->credits.push_back(result_Major_Crds);
	}
	else
	{
		result_Major_Crds = " Major credits are complete";
	}

	if (RegRules.ConcentrationCredits != ConcCrds)  //Checking the total concentration credits
	{
		result_Conc_Crds = "Concentration credits are  incomplete!";
		pSPlan->getWarnings()->credits.push_back(result_Conc_Crds);
	}
	else
	{
		result_Major_Crds = " Concentration credits are complete";
	}


	if (RegRules.TotalCredits != (Univcrds + MajorCrds + TrackCrds + ConcCrds)) //Checking the total credits (all types together)
	{
		Total_Crds = "Total credits are  incomplete!";
		pSPlan->getWarnings()->credits.push_back(Total_Crds);
	}
	else
	{
		Total_Crds = "Total  credits are complete";
	}


}


void Registrar::SetCoursesCoordinates() {
	pSPlan->setCourseCoordinate(this);
}

Rules& Registrar::getRegRules()
{
	return RegRules;

}

vector<CourseInfo>& Registrar::getCourseCatalog() {
	return (RegRules.CourseCatalog);
}
void Registrar::SavePlan(ofstream& file)
{
	pSPlan->SAVE(file);

}

void Registrar::LoadRules() {
	string line;
	vector<string> lines;
	string item;
	vector<string> items;

	pGUI->PrintMsg("Importing Rules");
	ifstream inFile;
	pGUI->PrintMsg("Choose your Major: NAN or CIE ");
	string mjr = pGUI->GetSrting();

	while (mjr != "CIE" && mjr != "NAN") {
		pGUI->PrintMsg("Invalid Input, Please Enter NAN or CIE");
		 mjr = pGUI->GetSrting();
	}
	if (mjr == "NAN")
	{
		inFile.open("E:\\\\NANENG-Requirements.txt");
	}
	else if (mjr == "CIE")
	{
		inFile.open("E:\\CIE-Requirements.txt");
	}

	while (getline(inFile, line, '\n'))
	{
		lines.push_back(line);
	}
	/////////////////////////////////////////////////////////////
	RegRules.TotalCredits = stoi(lines[0]);
	
	stringstream s1(lines[1]);
	items.clear();
	while (s1.good())
	{
		string substr;
		getline(s1, substr, ',');
		items.push_back(substr);
	}
	RegRules.ReqUnivCredits = stoi(items[0]);
	RegRules.ElectiveUnivCredits = stoi(items[1]);

	RegRules.ReqTrackCredits = stoi(lines[2]);

	stringstream s3(lines[3]);
	items.clear();
	while (s3.good())
	{
		string substr;
		getline(s3, substr, ',');
		items.push_back(substr);
		
	}
	RegRules.ReqMajorCredits = stoi(items[0]);
	RegRules.ElectiveMajorCredits = stoi(items[1]);

	stringstream s6(lines[6]);
	RegRules.UnivCompulsory.clear();
	while (s6.good())
	{
		string substr;
		getline(s6, substr, ',');
		RegRules.UnivCompulsory.push_back(substr);
		
	}
	
	stringstream s7(lines[7]);
	RegRules.UnivElective.clear();
	while (s7.good())
	{
		string substr;
		getline(s7, substr, ',');
		RegRules.UnivElective.push_back(substr);
		
	}

	////////////////
	stringstream s8(lines[8]);
	RegRules.TrackCompulsory.clear();
	while (s8.good())
	{
		string substr;
		getline(s8, substr, ',');
		RegRules.TrackCompulsory.push_back(substr);
	}


	RegRules.TrackElective;   ////// not found

	stringstream s9(lines[9]);
	RegRules.MajorCompulsory.clear();
	while (s9.good())
	{
		string substr;
		getline(s9, substr, ',');
		RegRules.MajorCompulsory.push_back(substr);
	
	}
	
	stringstream s10(lines[10]);
	RegRules.MajorElective.clear();
	while (s10.good())
	{
		string substr;
		getline(s10, substr, ',');
		RegRules.MajorElective.push_back(substr);
	}
	


	////////////////////////////////
	if (mjr == "NAN")
	{
		pGUI->PrintMsg("Choose your Concentration: V => VLSI , M => MEMS , P => Photonics");
		string conc = pGUI->GetSrting();
		if (conc == "V")
		{
			stringstream s11(lines[11]);
			while (s11.good())
			{
				string substr;
				getline(s11, substr, ',');
				RegRules.Concentration.push_back(substr);
			}
		}
		else if (conc == "M")
		{
			stringstream s13(lines[13]);
			while (s13.good())
			{
				string substr;
				getline(s13, substr, ',');
				RegRules.Concentration.push_back(substr);
			}
		}
		else if (conc == "P")
		{
			stringstream s15(lines[15]);
			while (s15.good())
			{
				string substr;
				getline(s15, substr, ',');
				RegRules.Concentration.push_back(substr);
			}
		}

		stringstream s17(lines[17]);
		items.clear();
		while (s17.good())
		{
			string substr;
			getline(s17, substr, ',');
			items.push_back(substr);
		}
		RegRules.SemMinCredit = stoi(items[0]);
		RegRules.SemMaxCredit = stoi(items[1]);
	}
	else if (mjr == "CIE")
	{
		stringstream s17(lines[11]);
		items.clear();
		while (s17.good())
		{
			string substr;
			getline(s17, substr, ',');
			items.push_back(substr);
		}
		RegRules.SemMinCredit = stoi(items[0]);
		RegRules.SemMaxCredit = stoi(items[1]);
	}
	pGUI->PrintMsg("Importing Rules Done Successfully");
	inFile.close();
}

Registrar::~Registrar()
{
	delete pGUI;
	delete pSPlan;
	delete YandS;
}
