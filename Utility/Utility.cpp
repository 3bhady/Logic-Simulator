#include "Utility.h"
void ReadPNG( vector<unsigned char>& Image,unsigned int &width ,unsigned int& height , const char * filename )
{
	//vector<unsigned char> Image;
	unsigned error = lodepng::decode(Image , width , height , filename );
	
}
void WritePNG(window * pWind, image &screen ,int x,int y,vector<unsigned char>& Image ,unsigned int width,unsigned int height)
{		

	pWind->StoreImage( screen , x , y , width , height );
	unsigned char * Arr = screen.GetArr( );

	int r , g , b;
	for ( long long i = 0; i < Image.size( ); i++ )
	{

		if ( i % 4 == 3 )
		{
			if ( Image[i] == 0 )
			{
				Arr[i - 1] =r;
				Arr[i - 2] = g;
				Arr[i - 3] = b;
			/*	Arr[i - 1] = 255;
				Arr[i - 2] =255;
				Arr[i - 3] = 255; */
				Arr[i] = 0;
			}

		}	  
		if ( i % 4 == 0 )
			b=Arr[i],Arr[i] = Image[i + 2];
		else if ( i % 4 == 2 )
			r=Arr[i],Arr[i] = Image[i - 2];
		else
			g=Arr[i],Arr[i] = Image[i];
	}
	screen.SetArr( Arr );
}

void DrawPNG( window * pWind , string r_filename , int x , int y )
{
	const char * filename = r_filename.c_str( );
	vector<unsigned char> Image;
	unsigned int width , height;
	image screen;
	ReadPNG( Image , width , height , filename );
	WritePNG( pWind , screen , x , y , Image , width , height );
	pWind->DrawImage( screen , x , y );
}
