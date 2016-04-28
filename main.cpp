#include <iostream>
#include <sstream>
#include <cmath>

#include "ApplicationManager.h"
#include "Utility\Utility.h"

int main()
{

	ActionType ActType;
	//test
	//Create an object of ApplicationManager
	
	
	ApplicationManager AppManager;

	window* pWind = AppManager.GetOutput()->GetPwind();
	DrawPNG( pWind , "io.png" , 0 , 400 );
	system( "PAUSE" );
/*	do
	{
		//Read user action
		ActType = AppManager.GetUserAction();

		//Execute the action
		AppManager.ExecuteAction(ActType);
		int x, y;
		pWind->GetMouseCoord(x, y);
		cout << x << " " << y << endl;
		//Update the drawing window
		AppManager.UpdateInterface();

		//commentat kteer el fatra el gaya
		//
		// ana //mesh
		//3arfny

	}while(ActType != EXIT);   	
					 */
	return 0;
}
/*
åæ áãÇ íÏæÓ Úáì gate íÎÔ Ýì move mode
æ íÚãáåÇ highlighted æ í move ßá Çá gates Çá highlighted
áæ åæ ããÔåÇÔ ÝßÏÉ íÈÞì åæ Èí select ÝÇá gates åÊÊÑÓã ãßÇäåÇ
y3ni move w select dol action wa7da

hwa lw das 3ala 7eta fadya fa enta mt3rfsh hwa asdo ydos dosa w yskot wala asdo eno yrsm mostatel keda y3ml highlight l kaza 7aga grin emoticon

ÇÇÇå grin emoticon grin emoticon
fa e7na n3tbr eno hy3ml highlight l kaza 7aga w nla2eh m7rksh el mouse asasan yb2a n3ml unhighlight l kolo 
lw das dosa keda tbe3ya htb2a sare3a awi msh hyl72 yshof el dot grin emoticon
momken n3ml check lw ab3ad el rectangle a2l mn 10 pixels msln myrsmosh 
el connections d ha3ayat mnha grin emoticon grin emoticon grin emoticon
w el menu b2a 3ayza ttzabat nshof hyt3ml feha eh grin emoticon

Çå æ copy æ cut æ paste Ïæá grin emoticon
move asasan lessa m3mltsh 3ayz a3ml el move d w b3daha ttreme f ay 7eta ay action 
w follow led and draw w el 7agat d 3ayza tt3ml grin emoticon
w en el led mttrsmsh 3ala tool bar 
el edit menu nzbt b2a ttrsm emta w fo2 eh w t3ml eh w keda grin emoticon
w b3d keda n5aly b2a el tool bars ttl3 w tnzl 
*/

