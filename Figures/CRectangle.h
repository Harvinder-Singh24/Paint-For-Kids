#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
public:
	CRectangle(Point , Point, GfxInfo FigureGfxInfo, int);
	virtual void Draw(Output* pOut) const;
	void PrintInfo(Output* pOut);
	bool OnFig(int, int);
	void Save(ofstream &OutFile);
	void Load(ifstream& Infile);
	///////////////////////
	virtual CFigure* copy();
	virtual CFigure* paste(int, int);
	virtual Point UpperPoint();
	virtual void Resize(float scale);
	virtual string GetType();
	virtual float GetArea();

	~CRectangle();
};

#endif