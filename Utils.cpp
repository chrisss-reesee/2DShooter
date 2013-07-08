#include "Utils.h"

void dbRectangle( int left, int top, int right, int bottom ) {
	dbLine( left, top, right, top );	// Top side
	dbLine( right, top, right, bottom );// Right side
	dbLine( left, bottom, right, bottom );	// Bottom side
	dbLine( left, top, left, bottom );	// Left side
}