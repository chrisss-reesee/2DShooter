#include "Map.h"

Map::Map(void)
{
	m_height = 0;
	m_width = 0;
}

Map::~Map(void)
{
}

// Load a map from a file
// TODO needs more error checking

// Map file structure
// [Width] [Height] [NumberOfTileTypes]
// [TileTypeXImageName]
// ...
// [MapData]

bool Map::loadFromFile(char *filename) {
	FILE *file = NULL;
	if( !( file = fopen(filename, "r") ) ) {
		return false;
	}
	
	int width, height;

	fscanf(file, "%d %d", &width, &height);
	m_height = height;
	m_width = width;

	for( int i=0; i<height; i++ ) {
		for( int j=0; j<width; j++ ) {
			fscanf( file, "%d", &m_map[i][j] );
		}
	}
	

	fclose( file );
	return true;
}


tileType_t Map::getTileType(int x, int y) {
	assert( (x<m_width) && (y<m_height) && "Attempt to retrieve tile outside map" );

	return m_map[y][x];
}


void Map::setTileType(int x, int y, tileType_t type) {
	assert( (x<m_width) && (y<m_height) && "Attempt to retrieve tile outside map" );

	m_map[y][x] = type;
}