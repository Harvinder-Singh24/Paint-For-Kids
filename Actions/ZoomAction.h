#pragma once
#include "Action.h"
#include "..//ApplicationManager.h"
#include "..//Figures/CFigure.h"
#include <string>

class ZoomAction : public Action
{
    float scale;
    CFigure* Fig;
public:
    ZoomAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();

    ~ZoomAction();
};


