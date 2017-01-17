/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 *  Author: Damiano Vitulli <info@spacesimulator.net>
 *
 * ALL RIGHTS RESERVED
 *
 *
 * Tutorial 4: 3d engine - 3ds models loader
 * 
 * File header: 3dsloader.h
 *  
 */

/*
Linux port by Panteleakis Ioannis
mail: pioann@csd.auth.gr

just run: make and you are done.
of course you may need to change the makefile
*/



/**********************************************************
 *
 * FUNCTION Load3DS (obj_type_ptr, char *)
 *
 * This function loads a mesh from a 3ds file.
 * Please note that we are loading only the vertices, polygons and mapping lists.
 * If you need to load meshes with advanced features as for example: 
 * multi objects, materials, lights and so on, you must insert other chunk parsers.
 *
 *********************************************************/
#ifndef __3DSLOADH__
#define __3DSLOADH__
 
#define MAX_VERTICES 8000 // Max number of vertices (for each object)
#define MAX_POLYGONS 8000 // Max number of polygons (for each object)

#include "../gra/mathlib.h"

// Our vertex type
typedef struct
{
float x,y,z;
} vertex_type;

// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct
{
int a,b,c;
} polygon_type;

// The mapcoord type, 2 texture coordinates for each vertex
typedef struct
{
float u,v;
} mapcoord_type;

// The object type
typedef struct 
{
char name[20]; // Name of the object
int vertices_qty; // Number of vertices
int polygons_qty; // Number of polygons

vertex_type vertex[MAX_VERTICES]; // Array of vertices
vertex_type normal[MAX_VERTICES]; // Array of the vertices' normals
polygon_type polygon[MAX_POLYGONS]; // Array of polygons (numbers that point to the vertices' list)
mapcoord_type mapcoord[MAX_VERTICES]; // Array of U,V coordinates for texture mapping
int id_texture; // Number of the texture 
} obj_type, *obj_type_ptr;


extern char Load3DS (obj_type_ptr ogg, char *filename);
void ObjCalcNormals(obj_type_ptr p_object);

#endif

