#include "Note.h"
#include<fstream>
#include <iostream>
#include <string>
#include "GUI/Drawable.h"
#include"GUI/GUI.h"

vector<string> Note::getmyNote() {
	fstream inFile("D:\\CIE-year 2\\CIE 202 _C++\\ProjectFiles\\Notes.txt", ios::in);
	vector<string> Note;
	string line;
	int i = 0;
	while (getline(inFile, line)) {
		Note.push_back(line);
	}
	inFile.close();
	return Note;
}
void Note::setmyNote(string s) {
	myNote = s+ " \n";
	fstream oFile("D:\\CIE-year 2\\CIE 202 _C++\\ProjectFiles\\Notes.txt", ios::app);
	oFile << myNote;
}
void Note::DrawMe(GUI* pNote) const {
}