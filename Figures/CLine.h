#ifndef CLINE_H
#define CLINE_H

#include "CFigure.h"

class CLine : public CFigure
{
private:
	Point Start;
	Point End;
	float len;

public:
	CLine(Point, Point, GfxInfo FigureGfxInfo, int);
	virtual void Draw(Output* pOut) const;
	void PrintInfo(Output* pOut);
	bool OnFig(int, int);
	void Save(ofstream &OutFile);
	void Load(ifstream& Infile);
	/////////////////////////////////
	virtual CFigure* copy();
	virtual CFigure* paste(int, int);
	virtual Point UpperPoint();
	virtual void Resize(float scale);
	virtual string GetType();
	float GetArea();

	~CLine();
};

#endif
