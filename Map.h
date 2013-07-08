#pragma once

#include <stdio.h>
#include <assert.h>

#define MAP_MAX_HEIGHT 39
#define MAP_MAX_WIDTH 58
#define TILE_WIDTH 128
#define TILE_HEIGHT 128

typedef enum {
	EMPTY,
	DIFFICULT_TERRAIN,
	COVER,
	WALL
} tileType_t;


class Map
{
public:
	Map(void);
	~Map(void);
	bool loadFromFile(char *filename);
	tileType_t getTileType(int x, int y);
	void setTileType(int x, int y, tileType_t type);

	// Setters and getters
	int getHeight() { return m_height; }
	int getWidth() { return m_width; }
	

private:
	int m_width, m_height;
	tileType_t m_map[MAP_MAX_HEIGHT][MAP_MAX_WIDTH];
};
