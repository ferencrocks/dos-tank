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

typedef struct tagGranularCoord {
    double x;
    double y;
} GranularCoord;

#define DIRECTIONS_COUNT 4
typedef enum tagDirection {
    DIR_UP = 0,
    DIR_LEFT = 1,
    DIR_DOWN = 2,
    DIR_RIGHT = 3
} Direction;

typedef struct tagDirectionVector {
    signed char x;
    signed char y;
} DirectionVector;

// speed measured in tiles/seconds
typedef struct tagSpeed {
    double sprite;
    word sec;
} Speed;


DirectionVector Type_DirToVect(Direction dir);

#endif // TYPES_H_INCLUDED
