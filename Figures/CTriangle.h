#ifndef CTRI_H
#define CTRI_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point Corner1;
	Point Corner2;
	Point Corner3;

public:
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo, int);
	virtual void Draw(Output* pOut) const;
	double Area(int, int, int, int, int, int);
	void PrintInfo(Output* pOut);
	bool OnBorder(Point, Point, Point);
	bool OnFig(int, int);
	void Save(ofstream &OutFile);
	void Load(ifstream& Infile);
	//////////////////////////
	virtual CFigure* copy();
	virtual CFigure* paste(int, int);
	virtual Point UpperPoint();
	virtual void Resize(float scale);
	virtual string GetType();
	virtual float GetArea();

	~CTriangle();
};

#endif