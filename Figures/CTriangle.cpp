#include "CTriangle.h"

CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo, int id) :CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
	ID = id;
}


void CTriangle::Draw(Output* pOut) const
{
	if (isZoomed == true)
	{
		Point Center;
		Center.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
		Center.y = (Corner1.y + Corner2.y + Corner3.y) / 3;
		Point TempCorner1, TempCorner2, TempCorner3;
		TempCorner1.x = Center.x + ZoomScale * (Corner1.x - Center.x);
		TempCorner1.y = Center.y + ZoomScale * (Corner1.y - Center.y);
		TempCorner2.x = Center.x + ZoomScale * (Corner2.x - Center.x);
		TempCorner2.y = Center.y + ZoomScale * (Corner2.y - Center.y);
		TempCorner3.x = Center.x + ZoomScale * (Corner3.x - Center.x);
		TempCorner3.y = Center.y + ZoomScale * (Corner3.y - Center.y);
		pOut->DrawTri(TempCorner1, TempCorner2, TempCorner3, FigGfxInfo, Selected);
	}
	else   //Call Output::DrawTri to draw a Triangle on the screen	
		pOut->DrawTri(Corner1, Corner2, Corner3, FigGfxInfo, Selected);
}

// calculate the area of the triangle, we will use it to print info, and also to check if a givein point lie in the area of the triangle
double CTriangle::Area(int x1, int y1, int x2, int y2, int x3, int y3)
{
	return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

void CTriangle::PrintInfo(Output* pOut)
{
	string message = "Triangle, ID: " + to_string(ID) + ", Corner 1: (" + to_string(Corner1.x) + "," + to_string(Corner1.y)
		+ "), Corner 2: (" + to_string(Corner2.x) + "," + to_string(Corner2.y) + "), Corner 3: (" + to_string(Corner3.x)
		+ "," + to_string(Corner3.y) + ")";
	pOut->PrintMessage(message);
}

bool CTriangle::OnBorder(Point A, Point B, Point P)
{
	/* this function will check if the point is on one of the three lines that the triangle has
	it will take 2 corners of the triangle and the point clicked by the user and chech if this point lie on the line of those two corners
	we can sent corner 1 and 2, or 1 and 3, or 2 and 3  */
	double AB = CalcDist(A, B);
	double AP = CalcDist(A, P);
	double PB = CalcDist(B, P);
	//P is on the line if AB = (AP+PB), and we will put error range = 0.2
	return (abs(AB - (AP + PB)) <= 0.2);
}

bool CTriangle::OnFig(int x, int y)
{
	//coordinats of the triangle of "corner 1, corner 2, corner 3"
	int x1 = Corner1.x;
	int y1 = Corner1.y;
	int x2 = Corner2.x;
	int y2 = Corner2.y;
	int x3 = Corner3.x;
	int y3 = Corner3.y;

	//(x,y) is the point clicked by the user we will call it point CP

	float A = Area(x1, y1, x2, y2, x3, y3);		// Calculate area of triangle we have "corner 1, corner 2, corner 3"
	float A1 = Area(x, y, x2, y2, x3, y3);		// Calculate area of triangle of "point CP, corner 2, corner 3"
	float A2 = Area(x1, y1, x, y, x3, y3);		// Calculate area of triangle of "corner 1, point CP, corner 3"
	float A3 = Area(x1, y1, x2, y2, x, y);		// Calculate area of triangle of "corner 1, corner 2, point CP"
	// if the sum A1+A2+A3 is equal to A >> the clicked point is inside the triangle region
	
	//Creates a point P(x,y)
	Point P;
	P.x = x;
	P.y = y;

	bool L1 = OnBorder(Corner1, Corner2, P);
	bool L2 = OnBorder(Corner1, Corner3, P);
	bool L3 = OnBorder(Corner2, Corner3, P);
	return (A == A1 + A2 + A3) || L1 || L2 || L3;
}

void CTriangle::Save(ofstream &OutFile)
{
	string Shape = "TRIANG";
	string Dclr = GetColorName(FigGfxInfo.DrawClr);
	OutFile << Shape << '\t' << ID << '\t' << Corner1.x << '\t' << Corner1.y << '\t' << Corner2.x << '\t' << Corner2.y << '\t' << Corner3.x << '\t' << Corner3.y << '\t' << Dclr << '\t';
	if (FigGfxInfo.isFilled == true)
	{
		string Fclr = GetColorName(FigGfxInfo.FillClr);
		OutFile << Fclr << endl;
	}
	else {
		OutFile << "NO_FILL" << endl;
	}
}

void CTriangle::Load(ifstream& InFile)
{
	string Dclr;
	string Fclr;

	//read the info of the fig from the file
	InFile >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> Corner3.x >> Corner3.y >> Dclr >> Fclr;;
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

CFigure* CTriangle::copy()
{
	return new CTriangle(*this);
}

CFigure* CTriangle::paste(int transX, int transY)
{
	Corner1.x += transX;
	Corner2.x += transX;
	Corner3.x += transX;
	Corner1.y += transY;
	Corner2.y += transY;
	Corner3.y += transY;
	return new CTriangle(*this);
}

Point CTriangle::UpperPoint()
{
	if (Corner1.y < Corner2.y && Corner1.y < Corner3.y)
		return Corner1;
	if (Corner2.y < Corner3.y)
		return Corner2;
	return Corner3;
}

void CTriangle::Resize(float scale)
{
	Point Center;
	Center.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
	Center.y = (Corner1.y + Corner2.y + Corner3.y) / 3;
	Corner1.x = Center.x + scale * (Corner1.x - Center.x);
	Corner1.y = Center.y + scale * (Corner1.y - Center.y);
	Corner2.x = Center.x + scale * (Corner2.x - Center.x);
	Corner2.y = Center.y + scale * (Corner2.y - Center.y);
	Corner3.x = Center.x + scale * (Corner3.x - Center.x);
	Corner3.y = Center.y + scale * (Corner3.y - Center.y);
}

string CTriangle::GetType()
{
	return "T";
}
float CTriangle::GetArea()
{
	int x1 = Corner1.x;
	int y1 = Corner1.y;
	int x2 = Corner2.x;
	int y2 = Corner2.y;
	int x3 = Corner3.x;
	int y3 = Corner3.y;
	return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

CTriangle::~CTriangle()
{
}
