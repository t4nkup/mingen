#include "mingen.h"

#ifndef _ENUM
#define _ENUM

// 
//  ENUM:  holds all of our enum declarations
//

typedef enum type
{
    A = 0, B = 10, C = 20, D = 30, E = 40, F = 50, G = 60, H = 70, I = 80, J = 90, K = 100,
    L = 110, M = 120, N = 130, O = 140, P = 150, Q = 160, R = 170, S = 180, T = 190, U = 200,
    V = 210, W = 220, X = 230, Y = 240, Z = 250,

    ARRAY = A + 1,
    BUTTON = B + 1,
    CHUNK = C + 1,
    ENTRY = E + 1,
    FLOAT3 = F + 1,
    GAME = G + 1,
    GRID = G + 2,
    INT3 = I + 1,
    MAP = M + 1,
    MESH = M + 2,
    SHAPE = S + 1,
    TABLE = T + 1,
    TRANSFORM = T + 2,
    UID = U + 1,
}
type;

typedef enum array_type { INT = 0, FLOAT = 1, CHAR = 2, COMPONENT = 33 } array_type;

// typedef enum SHAPE
// {
//     CUBE = 0,
//     RAMP = 1,
// }
// SHAPE;

#endif