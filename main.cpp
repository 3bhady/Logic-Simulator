#include <iostream>
#include "ApplicationManager.h"

int main()
{

	ActionType ActType;
	//Create an object of ApplicationManager

	
	ApplicationManager AppManager;
	

	do
	{
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


elmfrod n3ml undo w redo
w n3ml detect hwa das 3ala pin wala das 3ala eh blzbt
w save w load 3ayzen ytzbto
w n3ml block kaml keda
el toolbars elmfrod tb2a bttl3 w tnzl w te5tefe y3ni
w lable bta3 kol gate w component w keda w yt3ml label l kaza 7aga lw selected
w ngeb getstring mn el project el tany
n3ml e3lan t7t f el status bar by2oul el hot keys
w n3ml menu keda bt2oulk eh hya el hot keys


dlw2ty 3ndy shwyt gates m3mol 3lehom highlight
lw dost 3ala C hy2om msh hy7sl 7aga lw geet b3daha dost 3ala V t2om el gates zahra 3al mouse w yt3ml move components keda
lw dost escape ytl3'e el copy lw dost V yrg3 tany l7d ma ados 3lshan yt7ato 3al grid
lw dost 3ala X ytshalo mn mkanhom w y7sl nfs elklam bta3 C b2a y3ni X d 3obara 3n delete w Copy m3 b3d
w nfs elklam byt3ml b el menu
w delete tt3ml b D

lazm nfr2 been el highlighted w been el forbidden fe 7agat kter awi m7taga tt3adl f el mwdo3 dh w functions kter

DsgnMenuItm el enum dh bnst3mlo kter w el mfrod n3ml enum tany esmo componenttype w yb2a feh kol el types fa m7tag dh yt3'yr
w yt7at f class component bdl designmenu item dh w kol 7aga feh tb2a m7tot b nfs el trteb bta dsgn menu itm
3lshan lama n7b n7wl mn enum l el tany el mwdo3 yb2a baset


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

