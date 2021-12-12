#include "Input.h"

#include "Output.h"

//======================================================================================//
//								General Functions									    //
//======================================================================================//

Input::Input(window* pW) 
{
	pWind = pW; // point to the passed window
}

////////////////////////////////////////////////////////////////////////////////////////// 

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y); // Note: x and y of WaitMouseClick are sent by reference
}

////////////////////////////////////////////////////////////////////////////////////////// 

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if(Key == 13 )	// ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

////////////////////////////////////////////////////////////////////////////////////////// 

int Input::GetInteger(Output *pO) const 
{

	//(done)/TODO: implement the GetInteger function as described in Input.h file 
	//       using function GetString() defined above and function stoi()
	
	string num = Input::GetSrting(pO); // getting the integer as a string.

	// Note: stoi(s) converts string s into its equivalent integer (for example, "55" is converted to 55)

	return stoi(num); // this line should be changed with your implementation
}

//======================================================================================//
//								Game  Functions									        //
//======================================================================================//

ActionType Input::GetUserAction() const
{	
	int x = -1, y = -1;
	GetPointClicked(x, y); 

	//  ============ GUI in the Design mode ============
	if ( UI.InterfaceMode == MODE_DESIGN )	
	{
		// [1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_ADD_LADDER: return ADD_LADDER;
			case ITM_ADD_SNAKE: return ADD_SNAKE;
			case ITM_ADD_CARD: return ADD_CARD;
			case ITM_DEXIT: return EXIT;
			case ITM_SWITCH_TO_PLAY_MODE: return TO_PLAY_MODE;			

			///(Done)TODO: Add cases for the other items of Design Mode
			case ITM_COPY_CARD: return COPY_CARD;
			case ITM_CUT_CARD: return CUT_CARD;
			case ITM_PASTE_CARD: return PASTE_CARD;
			case ITM_DELETE_OBJECT: return DELETE_OBJECT;
			case ITM_SAVE_GRID: return SAVE_GRID;
			case ITM_OPEN_GRID: return OPEN_GRID;


			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ( (y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;	
		}

		// [3] User clicks on the status bar
		return STATUS;
	}

	// ============ GUI in the Play mode ============
	else	
	{
		///(Done)TODO:
		// perform checks similar to Design mode checks above for the Play Mode
		// and return the corresponding ActionType

		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_ROLL_DICE: return ROLL_DICE;
			case ITM_SWITCH_TO_DESIGN_MODE: return TO_DESIGN_MODE;
			
			//Added By Hamdy
			case ITM_INPUT_DICE_VALUE: return INPUT_DICE_VALUE;
			case ITM_NEW_GAME: return NEW_GAME;
			case ITM_PEXIT: return EXIT;

			default: return EMPTY;	// A click on an empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;

	}	

}

////////////////////////////////////////////////////////////////////////////////////////// 

CellPosition Input::GetCellClicked() const
{
	int x,y;
	pWind->WaitMouseClick(x, y);	// Get the coordinates of the user click

	CellPosition cellPos;

	if ( UI.InterfaceMode == MODE_DESIGN )	
	{
		if ( y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight))
		{
			//(done)/TODO: SetHCell and SetVCell of the object cellPost appropriately
			//       using the coordinates x, y and the appropriate variables of the UI_Info Object (UI)
			
			y -= UI.ToolBarHeight; // getting the active value of y according to the grid.

			cellPos.SetHCell(x/UI.CellWidth); cellPos.SetVCell(y/UI.CellHeight); // getting the coordinates of the cell.

		}
	}

	return cellPos;
}

////////////////////////////////////////////////////////////////////////////////////////// 
