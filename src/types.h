#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#define TRUE 1
#define FALSE 0
typedef char bool;

typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;

typedef struct tagCoord {
    word x;
    word y;
} Coord;

#define DIRECTIONS_COUNT 4
typedef enum tagDirection {
    DIR_UP = 0,
    DIR_LEFT = 1,
    DIR_DOWN = 2,
    DIR_RIGHT = 3
} Direction;

// speed measured in tiles/seconds
typedef struct tagSpeed {
    word tile;
    word sec;
} Speed;

#endif // TYPES_H_INCLUDED
