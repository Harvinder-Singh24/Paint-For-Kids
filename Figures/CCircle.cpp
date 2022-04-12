#include "CCircle.h"

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo, int id) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Border = P2;
	Radius = CalcDist(Center, Border);
	ID = id;
}


void CCircle::Draw(Output* pOut) const
{
	if (isZoomed == true)
	{
		int r = Radius * ZoomScale;
		Point Temp;
		Temp.x = Center.x + r;
		Temp.y = Border.y;
		pOut->DrawCirc(Center, Temp, FigGfxInfo, Selected);
	}
	else   //Call Output::DrawCirc to draw a Circle on the screen	
		pOut->DrawCirc(Center, Border, FigGfxInfo, Selected);
}

void CCircle::PrintInfo(Output* pOut)
{
	string message = "Circle, ID: " + to_string(ID) + ", Center (" + to_string(Center.x) + "," + to_string(Center.y)
		+ "), Radius: " + to_string(int(Radius));
	pOut->PrintMessage(message);
}

bool CCircle::OnFig(int x, int y)
{
	//Creates a point P(x,y) to use to calculate the distance between the center of the circle and this point
	Point C;
	C.x = x;
	C.y = y;
	//Check the distance between center and the point if it is within the range the return will be true
	return (Radius >= CalcDist(Center, C));
}

void CCircle::Save(ofstream &OutFile)
{
	string Shape = "CIRCLE";
	string Dclr = GetColorName(FigGfxInfo.DrawClr);
	OutFile << Shape << '\t' << ID << '\t' << Center.x << '\t' << Center.y << '\t' << Radius << '\t' << Dclr << '\t';
	if (FigGfxInfo.isFilled == true)
	{
		string Fclr = GetColorName(FigGfxInfo.FillClr);
		OutFile << Fclr << endl;
	}
	else {
		OutFile << "NO_FILL" << endl;
	}
}

/*void CCircle::Save(ofstream& OutFile)
{
	string Shape = "CIRCLE";
	string Dclr = GetColorName(FigGfxInfo.DrawClr);
	OutFile << Shape << '\t' << ID << '\t' << Center.x << '\t' << Center.y << '\t' << Border.x << '\t' << Border.y << '\t' << Radius << '\t' << Dclr << '\t';
	if (FigGfxInfo.isFilled == true)
	{
		string Fclr = GetColorName(FigGfxInfo.FillClr);
		OutFile << Fclr << endl;
	}
	else {
		OutFile << "NO_FILL" << endl;
	}
}*/

void CCircle::Load(ifstream &InFile)
{
	string Dclr;
	string Fclr;

	//read info of the fig from the file
	InFile >> ID >> Center.x >> Center.y >> Radius >> Dclr >> Fclr;
	Border.x = Center.x + Radius;
	Border.y = Center.y;
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

CFigure* CCircle::copy()
{
	return new CCircle(*this);
}

CFigure* CCircle::paste(int transX, int transY)
{
	Center.x += transX;
	Center.y += transY;
	Border.x += transX;
	Border.y += transY;
	return new CCircle(*this);
}

Point CCircle::UpperPoint()
{
	Point HP;
	HP.x = Center.x;
	HP.y = Center.y - Radius;
	return HP;
}

void CCircle::Resize(float scale)
{
	Radius *= scale;
	Border.x = Center.x + Radius;
	//Border.y = Center.y + Radius;
}

string CCircle::GetType()
{
	return "C";
}
float CCircle::GetArea()
{
	return 3.14 * Radius * Radius;
}

CCircle::~CCircle()
{
}
