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

lazm nfr2 been el highlighted w been el forbidden fe 7agat kter awi m7taga tt3adl f el mwdo3 dh w functions kter

DsgnMenuItm el enum dh bnst3mlo kter w el mfrod n3ml enum tany esmo componenttype w yb2a feh kol el types fa m7tag dh yt3'yr
w yt7at f class component bdl designmenu item dh w kol 7aga feh tb2a m7tot b nfs el trteb bta dsgn menu itm
3lshan lama n7b n7wl mn enum l el tany el mwdo3 yb2a baset


�� ��� ���� ��� gate ��� �� move mode
� ������ highlighted � � move �� �� gates �� highlighted
�� �� ������ ���� ���� �� �� select ��� gates ������ ������
y3ni move w select dol action wa7da

hwa lw das 3ala 7eta fadya fa enta mt3rfsh hwa asdo ydos dosa w yskot wala asdo eno yrsm mostatel keda y3ml highlight l kaza 7aga grin emoticon

���� grin emoticon grin emoticon
fa e7na n3tbr eno hy3ml highlight l kaza 7aga w nla2eh m7rksh el mouse asasan yb2a n3ml unhighlight l kolo 
lw das dosa keda tbe3ya htb2a sare3a awi msh hyl72 yshof el dot grin emoticon
momken n3ml check lw ab3ad el rectangle a2l mn 10 pixels msln myrsmosh 
el connections d ha3ayat mnha grin emoticon grin emoticon grin emoticon
w el menu b2a 3ayza ttzabat nshof hyt3ml feha eh grin emoticon

�� � copy � cut � paste ��� grin emoticon
move asasan lessa m3mltsh 3ayz a3ml el move d w b3daha ttreme f ay 7eta ay action 
w follow led and draw w el 7agat d 3ayza tt3ml grin emoticon
w en el led mttrsmsh 3ala tool bar 
el edit menu nzbt b2a ttrsm emta w fo2 eh w t3ml eh w keda grin emoticon
w b3d keda n5aly b2a el tool bars ttl3 w tnzl 
*/

