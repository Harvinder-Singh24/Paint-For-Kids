#pragma once
#include "Action.h"
#include <fstream>

class LoadAction : public Action
{
private:
	string FileName;
	ifstream inputFile;
public:
	LoadAction(ApplicationManager* pApp);

	//Reads parameters
	virtual void ReadActionParameters();

	//Execute the action
	virtual void Execute();

	color GetColor(string);			//Take color name and return the color

	~LoadAction();
};
