#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_LINE: return DRAW_LINE;
			case ITM_RECT: return DRAW_RECT;
			case ITM_TRI: return DRAW_TRI;
			case ITM_CIRC: return DRAW_CIRC;
			case ITM_CHNG_DRAW_CLR: return CHNG_DRAW_CLR;
			case ITM_CHNG_FILL_CLR: return CHNG_FILL_CLR;
			case ITM_CHNG_BK_CLR: return CHNG_BK_CLR;
			case ITM_SELECT:return SELECT;
			case ITM_DEL: return DEL;
			case ITM_MOVE: return MOVE;
			case ITM_COPY : return COPY;
			case ITM_CUT:return CUT;
			case ITM_PASTE:return PASTE;
			case ITM_RESIZE: return RESIZE;
			case ITM_ZOOM: return ZOOM;
			//case ITM_ROTATE: return ROTATE;
			//case ITM_SEND_BACK: return SEND_BACK;
			//case ITM_BRNG_FRNT: return BRNG_FRNT;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_PLAY_MODE: return TO_PLAY;
			case ITM_EXIT: return EXIT;
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_PickNHide: return PICK_N_HIDE;
			case ITM_DRAW_MODE: return TO_DRAW;
			case ITM_EXIT_PLAY: return EXIT;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}


		return TO_PLAY;	//just for now. This should be updated
	}	

}
/////////////////////////////////
void Input::GetDrawPoint(int& x, int& y, Output*) const
{
	GetPointClicked(x, y);
	while ((y < UI.ToolBarHeight + 4) || y > (UI.height - UI.StatusBarHeight))
	{
		GetPointClicked(x, y);
	}
}
	
Input::~Input()
{
}
