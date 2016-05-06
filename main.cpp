#include <iostream>
#include "ApplicationManager.h"

int main()
{

	ActionType ActType;
	//Create an object of ApplicationManager

	
	ApplicationManager AppManager;
	

	do
	{
		/*
		AppManager.GetOutput()->DrawwPNG("Images\\test\\0.png", 150, 150);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\0H.png", 150, 230);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\0F.png", 150, 310);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\1.png", 150, 390);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\1H.png", 150, 470);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\1F.png", 150, 550);

		AppManager.GetOutput()->DrawwPNG("Images\\test\\2.png", 250, 150);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\9H.png", 250, 230);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\2F.png", 250, 310);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\8.png", 250, 390);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\3H.png", 250, 470);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\3F.png", 250, 550);

		AppManager.GetOutput()->DrawwPNG("Images\\test\\4.png", 350, 150);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\4H.png", 350, 230);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\6F.png", 350, 310);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\5.png", 350, 390);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\7H.png", 350, 470);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\5F.png", 350, 550);

		AppManager.GetOutput()->DrawwPNG("Images\\test\\10.png", 450, 150);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\10H.png", 450, 230);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\10F.png", 450, 310);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\11.png", 450, 390);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\12H.png", 450, 470);
		AppManager.GetOutput()->DrawwPNG("Images\\test\\13F.png", 450, 550);
		*/
		//Read user action
		ActType = AppManager.GetUserAction();

		//Execute the action
		AppManager.ExecuteAction(ActType);

	//	int x, y;
		//pWind->GetMouseCoord(x, y);
		//cout << x << " " << y << endl;

		//Update the drawing window
		AppManager.UpdateInterface();

	}while(ActType != EXIT);   	
					 
	return 0;
}
/*
ns2l mo3ed :
(move component w follow mouse and draw need to be one function! )

dlw2ty fe mashakl f edit menu
msh 3arf a5leha t5tfe emta dlw2ty hwa lama ydos f 7eta bara el edit menu y3ni elmfrod en get user action trg3 7aga trg3 action msln
fa e7na lw hn3ml action btshel bs el edit menu mashy
bs lw hwa das b2a 3ala el edit menu w das copy
elmfrod nshelha ezay? kan fe mashakl lama 3mlna en update interface bt3ml el grid w el toolbars el denya kant 5rbana 5als btbarbsh
w lama 3mlna set buffering true w keda mb2tsh tbarbsh bs b2a el area select msh bytrsm w 7agat kter b2t 5arbana fa d m7taga tfker shwya


3ayzen nshof mwdo3 el delete dh w n3ml function f application manager bt3ml delete l el component
dh 3'er el function ele btms7 el component bs 3lshan nrsmo y3ni n3ml function delete w function erase
3lshan hn7tag enena mara nshelo mn el component list asasan w mara nshelo bs mn 3al grid w nshelo mn el 2D array
w m7taga ttzabat f classes ktera


m7tag yt3ml delete
delete tt3ml b D aw edit menu

elmfrod n3ml undo w redo
w n3ml detect hwa das 3ala pin wala das 3ala eh blzbt
w save w load 3ayzen ytzbto
w n3ml block kaml keda
el toolbars elmfrod tb2a bttl3 w tnzl w te5tefe y3ni
w lable bta3 kol gate w component w keda w yt3ml label l kaza 7aga lw selected
w ngeb getstring mn el project el tany
n3ml e3lan t7t f el status bar by2oul el hot keys
w n3ml menu keda bt2oulk eh hya el hot keys




lazm nfr2 been el highlighted w been el forbidden fe move components
w lama yo2f b gate t7t toolbar nrsmha a7mr


w follow led and draw w el 7agat d 3ayza tt3ml grin emoticon
w en el led mttrsmsh 3ala tool bar 
 
*/

