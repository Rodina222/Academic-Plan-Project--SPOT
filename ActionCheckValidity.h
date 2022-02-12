#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
#include <fstream>
#include <iostream>
#include <string>
#include<sstream>

class ActionCheckValidity :
    public Action
{
public:
    ActionCheckValidity(Registrar* pReg);
    bool virtual Execute();
    ~ActionCheckValidity();
};

