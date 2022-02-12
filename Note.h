#pragma once
#include<string>
#include"GUI/Drawable.h"
#include<vector>
using namespace std;

class Note :public Drawable
{
	string myNote;
public:
	void setmyNote(string);
	vector<string> getmyNote();
	void virtual DrawMe(GUI*) const;
};

