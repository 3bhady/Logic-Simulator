#pragma once
#include "..\lodepng.h"
#include "..\ApplicationManager.h"
#include <queue>
using namespace std;
  /*
int arr1[100][100];
pair<int , int> arr[100][100];
bool vis[100][100];
int n;
bool isvalid( int x , int y )
{
	if ( x<n&&y<n )
		if ( x >= 0 && y >= 0 )
		{
			if ( vis[x][y] == 0 )
			{
				if ( arr1[x][y] == 0 )
					return true;
				else
				{

					return true;
				}
			}


		}
	return false;
}
void bfs( int x1 , int y1 , int x2 , int y2 )
{
	queue< pair<int , int> > qu;

	qu.push( make_pair( x1 , y1 ) );
	while ( !qu.empty( ) )
	{
		pair<int , int> pr = qu.front( );
		vis[pr.first][pr.second] = 1;
		qu.pop( );
		if ( isvalid( pr.first + 1 , pr.second ) )
		{
			qu.push( make_pair( pr.first + 1 , pr.second ) );
			arr[pr.first + 1][pr.second] = make_pair( pr.first , pr.second );
			vis[pr.first + 1][pr.second] = 1;
			if ( qu.back( ).first == x2 && qu.back( ).second == y2 )
				break;
		}

		if ( isvalid( pr.first , pr.second + 1 ) )
		{
			qu.push( make_pair( pr.first , pr.second + 1 ) );
			arr[pr.first][pr.second + 1] = make_pair( pr.first , pr.second );
			vis[pr.first][pr.second + 1] = 1;	   if ( qu.back( ).first == x2 && qu.back( ).second == y2 )
				break;
		}

		if ( isvalid( pr.first - 1 , pr.second ) )
		{
			qu.push( make_pair( pr.first - 1 , pr.second ) );
			arr[pr.first - 1][pr.second] = make_pair( pr.first , pr.second );
			vis[pr.first - 1][pr.second] = 1;	if ( qu.back( ).first == x2 && qu.back( ).second == y2 )
				break;
		}

		if ( isvalid( pr.first , pr.second - 1 ) )
		{
			qu.push( make_pair( pr.first , pr.second - 1 ) );
			arr[pr.first][pr.second - 1] = make_pair( pr.first , pr.second );
			vis[pr.first][pr.second - 1] = 1;	   if ( qu.back( ).first == x2 && qu.back( ).second == y2 )
				break;
		}


	}

}	  */
void ReadPNG( vector<unsigned char> &Image,unsigned int &width,unsigned int& height , const char * filename );
void WritePNG( window * pWind , image &screen , int x , int y , vector<unsigned char>& Image , unsigned int width , unsigned int height );
void DrawPNG( window * pWind , string r_filename , int x , int y );
