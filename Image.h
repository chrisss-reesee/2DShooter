#pragma once

#include "DarkGDK.h"

static int g_dbImageNextInstanceNum = 1;

class Image
{
public:
	Image(void);
	Image( char *filename );
	~Image(void);
	void load( char *filename );
	void save( char *filename );		// Supports BMP,DDS,JPG,DIB
	void paste( int x, int y );
	bool exists();
	int getInstanceNum() { return m_instanceNum; }

	//TODO add ability to change global color key

private:
	int m_instanceNum;
};
