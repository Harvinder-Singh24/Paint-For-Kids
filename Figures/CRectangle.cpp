#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo, int id):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	ID = id;
}
	

void CRectangle::Draw(Output* pOut) const
{
	if (isZoomed == true)
	{
		Point Center;
		Center.x = (Corner1.x + Corner2.x) / 2;
		Center.y = (Corner1.y + Corner2.y) / 2;
		Point TempCorner1, TempCorner2;
		TempCorner1.x = Center.x + ZoomScale * (Corner1.x - Center.x);
		TempCorner1.y = Center.y + ZoomScale * (Corner1.y - Center.y);
		TempCorner2.x = Center.x + ZoomScale * (Corner2.x - Center.x);
		TempCorner2.y = Center.y + ZoomScale * (Corner2.y - Center.y);
		pOut->DrawRect(TempCorner1, TempCorner2, FigGfxInfo, Selected);
	}
	else //Call Output::DrawRect to draw a rectangle on the screen	
		pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

void CRectangle::PrintInfo(Output* pOut)
{
	
	string message = "Rectangle, ID: " + to_string(ID) + ", Corner 1: (" + to_string(Corner1.x) + "," + to_string(Corner1.y)
		+ "), Corner 2: (" + to_string(Corner2.x) + "," + to_string(Corner2.y) + "), Length: "
		+ to_string(abs(Corner1.x - Corner2.x)) + ", Width: " + to_string(abs(Corner1.y - Corner2.y));
	pOut->PrintMessage(message);
}

bool CRectangle::OnFig(int x, int y)
{

	//Checks if the x & y coordinates lie inside the rectangle or on the rectangle border
	return ((x >= Corner1.x && x <= Corner2.x) || (x <= Corner1.x && x >= Corner2.x))
		&& ((y >= Corner1.y && y <= Corner2.y) || (y <= Corner1.y && y >= Corner2.y));
}

void CRectangle::Save(ofstream &OutFile)
{
	string Shape = "RECT";
	string Dclr = GetColorName(FigGfxInfo.DrawClr);
	OutFile << Shape << '\t' << ID << '\t' << Corner1.x << '\t' << Corner1.y << '\t' << Corner2.x << '\t' << Corner2.y << '\t' << Dclr << '\t';
	if (FigGfxInfo.isFilled == true)
	{
		string Fclr = GetColorName(FigGfxInfo.FillClr);
		OutFile << Fclr << endl;
	}
	else {
		OutFile << "NO_FILL" << endl;
	}
}

void CRectangle::Load(ifstream& InFile)
{
	string Dclr;
	string Fclr;

	//read the info of the fig from the file
	InFile >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> Dclr >> Fclr;;
	FigGfxInfo.DrawClr = GetColor(Dclr);
	if (Fclr == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr = GetColor(Fclr);
	}
	FigGfxInfo.BorderWdth = UI.PenWidth;
}

CFigure* CRectangle::copy()
{
	return new CRectangle(*this);
}

CFigure* CRectangle::paste(int transX, int transY)
{
	Corner1.x += transX;
	Corner1.y += transY;
	Corner2.x += transX;
	Corner2.y += transY;
	return new CRectangle(*this);
}

Point CRectangle::UpperPoint()
{
	if (Corner1.y < Corner2.y)
		return Corner1;
	return Corner2;
}

void CRectangle::Resize(float scale)
{
	Point Center;
	Center.x = (Corner1.x + Corner2.x) / 2;
	Center.y = (Corner1.y + Corner2.y) / 2;
	Corner1.x = Center.x + scale * (Corner1.x - Center.x);
	Corner1.y = Center.y + scale * (Corner1.y - Center.y);
	Corner2.x = Center.x + scale * (Corner2.x - Center.x);
	Corner2.y = Center.y + scale * (Corner2.y - Center.y);
}

string CRectangle::GetType()
{
	return "R";
}

float CRectangle::GetArea()
{
	return abs((Corner1.x - Corner2.x) * (Corner1.y - Corner2.y));
}

CRectangle::~CRectangle()
{
}
