#include "CLine.h"


CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo, int id) :CFigure(FigureGfxInfo)
{
	Start = P1;
	End = P2;
	len = CalcDist(Start, End);
	ID = id;
}


void CLine::Draw(Output* pOut) const
{
	if (isZoomed == true)
	{
		Point Center;
		Center.x = (Start.x + End.x) / 2;
		Center.y = (Start.y + End.y) / 2;
		Point TempStart, TempEnd;
		TempStart.x = Center.x + ZoomScale * (Start.x - Center.x);
		TempStart.y = Center.y + ZoomScale * (Start.y - Center.y);
		TempEnd.x = Center.x + ZoomScale * (End.x - Center.x);
		TempEnd.y = Center.y + ZoomScale * (End.y - Center.y);
		pOut->DrawLine(TempStart, TempEnd, FigGfxInfo, Selected);
	}
	else    //Call Output::DrawLine to draw a Line on the screen	
		pOut->DrawLine(Start, End, FigGfxInfo, Selected);
}

void CLine::PrintInfo(Output* pOut)
{
	string message = "Line, ID: " + to_string(ID) + ", Corner 1: (" + to_string(Start.x) + "," + to_string(Start.y)
		+ "), Corner 2: (" + to_string(End.x) + "," + to_string(End.y) + "), Length: "
		+ to_string(len);
	pOut->PrintMessage(message);
}

bool CLine::OnFig(int x, int y)
{
	//Creates a point P(x,y)
	Point P;
	P.x = x;
	P.y = y;
	//A is the start point and B is the end point >> we have AB which is the lenght of the line so we will Calculate AP, and PB 
	float AB = CalcDist(Start, End);
	double AP = CalcDist(Start, P);
	double PB = CalcDist(End, P);
	//P is on the line if AB = (AP+PB), and we will put error range = 0.2
	return (abs(AB - (AP + PB)) <= 0.2);
}

void CLine::Save(ofstream &OutFile)
{
	string Shape = "LINE";
	string Dclr = GetColorName(FigGfxInfo.DrawClr);
	OutFile << Shape << '\t' << ID << '\t' << Start.x << '\t' << Start.y << '\t' << End.x << '\t' << End.y << '\t' << Dclr << '\t' << endl;
}

void CLine::Load(ifstream& InFile)
{
	string Dclr;

	//read the info of the fig from the file
	InFile >> ID >> Start.x >> Start.y >> End.x >> End.y >> Dclr;
	FigGfxInfo.DrawClr = GetColor(Dclr);
	FigGfxInfo.BorderWdth = UI.PenWidth;

}

CFigure* CLine::copy()
{
	return new CLine(*this);
}

CFigure* CLine::paste(int transX, int transY)
{
	Start.x += transX;
	Start.y += transY;
	End.x += transX;
	End.y += transY;
	return new CLine(*this);
}

Point CLine::UpperPoint()
{
	if (Start.y < End.y)
		return Start;
	return End;
}

void CLine::Resize(float scale)
{
	Point Center;
	Center.x = (Start.x + End.x) / 2;
	Center.y = (Start.y + End.y) / 2;
	Start.x = Center.x + scale * (Start.x - Center.x);
	Start.y = Center.y + scale * (Start.y - Center.y);
	End.x = Center.x + scale * (End.x - Center.x);
	End.y = Center.y + scale * (End.y - Center.y);
}

string CLine::GetType()
{
	return "L";
}

float CLine::GetArea()
{
	return len;
}

CLine::~CLine()
{
}
