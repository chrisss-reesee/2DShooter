#pragma once

#include "DarkGDK.h"

static int g_dbBitmapNextInstanceNum = 1;

class Bitmap
{
public:
	Bitmap(int width, int height);
	~Bitmap(void);
	void setAsActiveTarget( bool x = true );
	void draw( int x, int y );
	void resize( int width, int height );

	int getInstanceNum() { return m_instanceNum; }

private:
	int m_width;
	int m_height;
	int m_instanceNum;
};
