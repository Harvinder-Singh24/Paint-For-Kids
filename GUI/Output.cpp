#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1300;
	UI.height = 700;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 60;
	
	UI.DrawColor = BLACK;		//Drawing color
	UI.FillColor = BLUE;		//Filling color
	UI.MsgColor = WHITE;		//Messages color
	UI.BkGrndColor = WHITE;		//Background color
	UI.HighlightColor = PINK;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = BLUE;
	UI.PenWidth = 3;			//width of the figures frames

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	//Clear tool bar filled white rectangle
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\rectangle-icon2.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItems\\circle-icon2.jpg";
	MenuItemImages[ITM_TRI] = "images\\MenuItems\\Tri-icon2.jpg";
	MenuItemImages[ITM_LINE] = "images\\MenuItems\\Straight-line2.jpg";
	MenuItemImages[ITM_CHNG_DRAW_CLR] = "images\\MenuItems\\CH-Draw-CLR2.jpg";
	MenuItemImages[ITM_CHNG_FILL_CLR] = "images\\MenuItems\\CH-Fill-CLR2.jpg";
	MenuItemImages[ITM_CHNG_BK_CLR] = "images\\MenuItems\\CH-BGND-CLR2.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\select-icon2.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\delete-icon2.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\move-icon2.jpg";
	MenuItemImages[ITM_COPY] = "images\\MenuItems\\copy-icon2.jpg";
	MenuItemImages[ITM_CUT] = "images\\MenuItems\\cut-icon2.jpg";
	MenuItemImages[ITM_PASTE] = "images\\MenuItems\\paste-icon2.jpg";
	//MenuItemImages[ITM_ROTATE] = "images\\MenuItems\\rotate-icon.jpg";
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\resize-icon2.jpg";
	MenuItemImages[ITM_ZOOM] = "images\\MenuItems\\Zoom-in-out2.jpg";
	//MenuItemImages[ITM_BRNG_FRNT] = "images\\MenuItems\\bring-to-front.jpg";
	//MenuItemImages[ITM_SEND_BACK] = "images\\MenuItems\\send-backward-icon.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\save-icon2.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\load-icon2.jpg";
	MenuItemImages[ITM_PLAY_MODE] = "images\\MenuItems\\Play-Mode2.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Exit-icon2.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(BLUE, 4);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	//Clear tool bar filled white rectangle
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	UI.InterfaceMode = MODE_PLAY;

	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_PickNHide] = "images\\MenuItems\\pick-n-hide2.jpg";
	MenuItemImages[ITM_DRAW_MODE] = "images\\MenuItems\\Drawing-Area2.jpg";
	MenuItemImages[ITM_EXIT_PLAY] = "images\\MenuItems\\Exit-icon2.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(BLUE, 4);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}
//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	
}

void Output::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = LineGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, LineGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	style = FRAME;


	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);

}

void Output::DrawTri(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor;
	else
		DrawingClr = TriGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriGfxInfo.BorderWdth);

	drawstyle style;
	if (TriGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);

}

void Output::DrawCirc(Point P1, Point P2, GfxInfo CircGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = CircGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, CircGfxInfo.BorderWdth);
	drawstyle style;
	if (CircGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircGfxInfo.FillClr);
	}
	else
		style = FRAME;
	float radius = sqrt((P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y));

	pWind->DrawCircle(P1.x, P1.y, radius, style);

}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

