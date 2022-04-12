#pragma once
#include "Action.h"
#include "..//Figures/CFigure.h"
#include "..//ApplicationManager.h"
#include <string> 

class ResizeAction : public Action
{
    float scale;
    CFigure* SelectedFig;

public:
    ResizeAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();

    ~ResizeAction();
};

