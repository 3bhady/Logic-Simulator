#include "Utility.h"

void ReadPNG( vector<unsigned char>& Image,unsigned int &width ,unsigned int& height , const char * filename )
{
	//vector<unsigned char> Image;
	unsigned error = lodepng::decode(Image , width , height , filename );
}
void WritePNG( window * pWind , image &screen , int x , int y , vector<unsigned char>& Image , unsigned int width , unsigned int height )
{
	//if ( x + width+15 >= UI.width )
		//width = UI.width - x -15;
	//if ( y + height + 15 >= UI.height )
		//height = UI.height - y - 15;
	pWind->StoreImage( screen , x , y , width , height );
	unsigned char * Arr = screen.GetArr( );
	unsigned int Size = Image.size();
	//int Size = (sizeof( Arr ) / sizeof( *Arr ));
	unsigned int i;
	for ( i = 0; i < Size; i+=4 )
	{
		if (Image[i + 3])

		{
			Arr[i] = Image[i + 2];
			Arr[i + 1] = Image[i + 1];
			Arr[i + 2] = Image[i];
		}
		/*if ( i % 4 == 3 )
		{
			if (Image[i] == 0)
			{
				Arr[i - 1] = r;
				Arr[i - 2] = g;
				Arr[i - 3] = b;
				//Arr[i] = 0;
			}
		}
		else if (i % 4 == 0)
			b = Arr[i], Arr[i] = Image[i + 2];
		else if (i % 4 == 2)
			r = Arr[i], Arr[i] = Image[i - 2];
		else
			g = Arr[i], Arr[i] = Image[i];
			*/

	}
	screen.SetArr( Arr );
}

void DrawPNG( window * pWind , string r_filename , GraphicsInfo GfxInfo )
{
	int x = GfxInfo.x1;
	int y = GfxInfo.y1;
	int x2 =GfxInfo.x2, y2=GfxInfo.y2;
	if ( x < 0 || y < 0 || x2+15 >= UI.width || y2+15 >= UI.height )
		return;
	const char * filename = r_filename.c_str( );
	vector<unsigned char> Image;
	unsigned int width , height;
	image screen;
	ReadPNG( Image , width , height , filename );
	WritePNG( pWind , screen , x , y , Image , width , height );
	pWind->DrawImage( screen , x , y );
}
