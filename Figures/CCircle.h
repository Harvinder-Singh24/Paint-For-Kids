#ifndef CCIRC_H
#define CCIRC_H

#include "CFigure.h"
class CFigure;
class CCircle :public CFigure
{
private:
	Point Center;
	Point Border;
	float Radius;

public:
	CCircle(Point, Point, GfxInfo FigureGfxInfo, int);
	virtual void Draw(Output* pOut) const;
	void PrintInfo(Output* pOut);
	bool OnFig(int, int);
	void Save(ofstream &OutFile);
	void Load(ifstream& Infile);
	////////////////////////////
	virtual CFigure* copy();
	virtual CFigure* paste(int, int);
	virtual Point UpperPoint();
	virtual void Resize(float scale);
	virtual string GetType();
	virtual float GetArea();

	~CCircle();
};

#endif
