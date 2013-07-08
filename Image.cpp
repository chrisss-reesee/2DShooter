#include "Image.h"

Image::Image(void)
{
	m_instanceNum = g_dbImageNextInstanceNum;
	g_dbImageNextInstanceNum++;
}

Image::Image(char *filename)
{
	m_instanceNum = g_dbImageNextInstanceNum;
	g_dbImageNextInstanceNum++;

	load( filename );
}

Image::~Image(void)
{
	dbDeleteImage( m_instanceNum );
}

void Image::load( char *filename ) {
	dbLoadImage( filename, m_instanceNum );
}

void Image::save( char *filename ) {
	dbSaveImage( filename, m_instanceNum );
}

void Image::paste( int x, int y ) {
	dbPasteImage( m_instanceNum, x, y );
}

bool Image::exists() {
	if( dbImageExist(m_instanceNum) == 1 )
		return true;
	else
		return false;
}

