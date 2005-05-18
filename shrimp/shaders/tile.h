/*
    tile.h
    Simple tiling routine
    Author: A.Gill, August 2000
*/

#ifndef TILE_H
#define TILE_H

#include "shrimp_util.h"


// this function is likely to be replaced by a better one.
// ( as soon as I can think what a better one would look like )
/* 
    Takes the point (x,y) and returns the coords inside the tile (xt,yt)
    and the tile column and row. xfreq, yfreq affect the quantity ( and
    consequently the shape ) of the tiles in the x and y directions.
*/
void
shTile( float x, y;
      uniform float xfreq, yfreq;
      output float xt, yt;
      output float column, row; )
{
    xt = repeat( x, xfreq );
    yt = repeat( y, yfreq );
    
    column = whichtile( x, xfreq );
    row = whichtile( y, yfreq );
}


#endif
