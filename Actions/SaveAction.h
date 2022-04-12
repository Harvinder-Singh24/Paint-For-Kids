#pragma once
#include "Action.h"
#include <fstream>

class SaveAction : public Action
{
private:
	string FileName;
	ofstream outputFile;
public:
	SaveAction(ApplicationManager* pApp);
	

	//Reads parameters
	virtual void ReadActionParameters();

	virtual void Execute();

	string GetColor(color);			//get color in form of string

	~SaveAction();
};