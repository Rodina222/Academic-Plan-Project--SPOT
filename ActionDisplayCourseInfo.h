#pragma once
#include"StudyPlan/StudyPlan.h"
#include "..//SPOT/Actions/Action.h"
    //Class responsible for displaying course information  action
    class ActionDisplayCourseInfo : public Action
    {
    public:
        ActionDisplayCourseInfo(Registrar*);
        bool virtual Execute();
        virtual ~ActionDisplayCourseInfo();

    };

