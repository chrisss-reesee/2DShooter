#include "Bitmap.h"

Bitmap::Bitmap(int width, int height)
{
	m_width = width;
	m_height = height;

	m_instanceNum = g_dbBitmapNextInstanceNum;
	g_dbBitmapNextInstanceNum++;

	dbCreateBitmap( m_instanceNum, width, height );
	dbSetCurrentBitmap( 0 );
}

Bitmap::~Bitmap(void)
{
	dbDeleteBitmap( m_instanceNum );
}


void Bitmap::setAsActiveTarget( bool x ) {
	if( x ) {
		dbSetCurrentBitmap( m_instanceNum );
	}
	else {
		dbSetCurrentBitmap( 0 );
	}
}

void Bitmap::draw( int x, int y ) {
	dbCopyBitmap( m_instanceNum, 0, 0, m_width, m_height, 0, x, y, x+m_width, y+m_height );
}

void Bitmap::resize( int width, int height ) {
	dbDeleteBitmap( m_instanceNum );
	dbCreateBitmap( m_instanceNum, width, height );
	dbSetCurrentBitmap( 0 );
	m_width = width;
	m_height = height;
}
