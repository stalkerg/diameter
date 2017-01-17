/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli <info@spacesimulator.net>
 *
 * ALL RIGHTS RESERVED
 *
 *
 * 3ds models loader
 *  
 */

#ifdef __WIN32__
#include <windows.h>
#include <conio.h>
#include <io.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#endif

#include <stdio.h>
#include <stdlib.h>
//#include "object.h"
#include "3dsloader.h"



/**********************************************************
 *
 * FUNCTION Load3DS(obj_type_ptr p_object, char *p_filename)
 *
 * This function loads a mesh from a 3ds file.
 * Please note that we are loading only the vertices, polygons and mapping lists.
 * If you need to load meshes with advanced features as for example: 
 * multi objects, materials, lights and so on, you must insert other chunk parsers.
 *
 * Input parameters: p_object = Pointer to the Object
 *					 p_filename = Filename of the object to load
 *
 * Return value: (char) 1 if the object was loaded correctly, 0 otherwise
 *
 *********************************************************/

char Load3DS(obj_type_ptr p_object, char *p_filename)
{
int i; //Index variable	
FILE *l_file; //File pointer	
unsigned short l_chunk_id; //Chunk identifier
unsigned int l_chunk_lenght; //Chunk lenght
unsigned char l_char; //Char variable
unsigned short l_qty; //Number of elements in each chunk
unsigned short l_face_flags; //Flag that stores some face information

//Init arrays
for (i=0; i<MAX_VERTICES; i++)
	{
	p_object->vertex[i].x = 0;
	p_object->vertex[i].y = 0;
	p_object->vertex[i].z = 0;
	}

for (i=0; i<MAX_POLYGONS; i++)
	{
	p_object->polygon[i].a = 0;
	p_object->polygon[i].b = 0;
	p_object->polygon[i].c = 0;
	}

#ifndef __WIN32__
struct stat file_status;
#endif

if (p_filename=='\0')
	return(0);

if ((l_file=fopen (p_filename, "rb"))== NULL)
	{
#ifdef __WIN32__
	MessageBox(NULL,"3DS file not found","Spacesim",MB_OK | MB_ICONERROR);
#else
	printf ("3DS file {%s} not found\n",p_filename);
#endif
	return (0);
	}

#ifdef __WIN32__
while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file 
#else
fstat(fileno (l_file), &file_status);
while (ftell (l_file) < file_status.st_size)
#endif
	{
	fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
	fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
	switch (l_chunk_id)
        	{
		//----------------- MAIN3DS -----------------
		// Description: Main chunk, contains all the other chunks
		// Chunk ID: 4d4d 
		// Chunk Lenght: 0 + sub chunks
		//-------------------------------------------
		case 0x4d4d:
			break;

		//----------------- EDIT3DS -----------------
		// Description: 3D Editor chunk, objects layout info 
		// Chunk ID: 3d3d (hex)
		// Chunk Lenght: 0 + sub chunks
		//-------------------------------------------
		case 0x3d3d:
			break;
			
		//--------------- EDIT_OBJECT ---------------
		// Description: Object block, info for each object
		// Chunk ID: 4000 (hex)
		// Chunk Lenght: len(object name) + sub chunks
		//-------------------------------------------
		case 0x4000:
			i=0;
			do
				{
				fread (&l_char, 1, 1, l_file);
				p_object->name[i]=l_char;
				i++;
                		}
			while(l_char != '\0' && i<20);
			break;

		//--------------- OBJ_TRIMESH ---------------
		// Description: Triangular mesh, contains chunks for 3d mesh info
		// Chunk ID: 4100 (hex)
		// Chunk Lenght: 0 + sub chunks
		//-------------------------------------------
		case 0x4100:
			break;
		//--------------- TRI_VERTEXL ---------------
		// Description: Vertices list
		// Chunk ID: 4110 (hex)
		// Chunk Lenght: 1 x unsigned short (number of vertices) 
		//             + 3 x float (vertex coordinates) x (number of vertices)
		//             + sub chunks
		//-------------------------------------------
		case 0x4110:
			fread (&l_qty, sizeof (unsigned short), 1, l_file);
                	p_object->vertices_qty = l_qty;
			if (l_qty>MAX_VERTICES) 
				{
#ifdef __WIN32__
			        MessageBox(NULL,"Number of vertices too high","Spacesim",MB_OK | MB_ICONERROR);
#else
				printf ("Number of vertices too high.\n");
#endif
				return (0);
				}
			for (i=0; i<l_qty; i++)
				{
				fread (&p_object->vertex[i].x, sizeof(float), 1, l_file);
				fread (&p_object->vertex[i].y, sizeof(float), 1, l_file);
				fread (&p_object->vertex[i].z, sizeof(float), 1, l_file);
				}
			break;

		//--------------- TRI_FACEL1 ----------------
		// Description: Polygons (faces) list
		// Chunk ID: 4120 (hex)
		// Chunk Lenght: 1 x unsigned short (number of polygons) 
		//             + 3 x unsigned short (polygon points) x (number of polygons)
		//             + sub chunks
		//-------------------------------------------
		case 0x4120:
			fread (&l_qty, sizeof (unsigned short), 1, l_file);
			p_object->polygons_qty = l_qty;
			if (l_qty>MAX_POLYGONS) 
				{
#ifdef __WIN32__
			        MessageBox(NULL,"Number of polygons too high","Spacesim",MB_OK | MB_ICONERROR);
#else
				printf ("Number of polygons too high\n");
#endif
				return (0);
				}
			for (i=0; i<l_qty; i++)
				{
				fread (&p_object->polygon[i].a, sizeof (unsigned short), 1, l_file);
				fread (&p_object->polygon[i].b, sizeof (unsigned short), 1, l_file);
				fread (&p_object->polygon[i].c, sizeof (unsigned short), 1, l_file);
				fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
				}
			break;

		//------------- TRI_MAPPINGCOORS ------------
		// Description: Vertices list
		// Chunk ID: 4140 (hex)
		// Chunk Lenght: 1 x unsigned short (number of mapping points) 
		//             + 2 x float (mapping coordinates) x (number of mapping points)
		//             + sub chunks
		//-------------------------------------------
		case 0x4140:
			fread (&l_qty, sizeof (unsigned short), 1, l_file);
			for (i=0; i<l_qty; i++)
				{
				fread (&p_object->mapcoord[i].u, sizeof (float), 1, l_file);
				fread (&p_object->mapcoord[i].v, sizeof (float), 1, l_file);
				}
			break;

		//----------- Skip unknow chunks ------------
		//We need to skip all the chunks that currently we don't use
		//We use the chunk lenght information to set the file pointer
		//to the same level next chunk
		//-------------------------------------------
		default:
			 fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
		}
	}
fclose (l_file); // Closes the file stream
return (1); // Returns ok
}


void ObjCalcNormals(obj_type_ptr p_object)
{
int i;
vec3 l_vect1, l_vect2, l_vect3, l_vect_b1, l_vect_b2, l_normal;  //Some local vectors
int l_connections_qty[MAX_VERTICES]; //Number of poligons around each vertex

   // Resetting vertices' normals...
for (i=0; i<p_object->vertices_qty; i++)
	{
		p_object->normal[i].x = 0.0;
		p_object->normal[i].y = 0.0;
		p_object->normal[i].z = 0.0;
		l_connections_qty[i]=0;
	}

for (i=0; i<p_object->polygons_qty; i++)
	{
	l_vect1.x = p_object->vertex[p_object->polygon[i].a].x;
	l_vect1.y = p_object->vertex[p_object->polygon[i].a].y;
	l_vect1.z = p_object->vertex[p_object->polygon[i].a].z;
	l_vect2.x = p_object->vertex[p_object->polygon[i].b].x;
	l_vect2.y = p_object->vertex[p_object->polygon[i].b].y;
	l_vect2.z = p_object->vertex[p_object->polygon[i].b].z;
	l_vect3.x = p_object->vertex[p_object->polygon[i].c].x;
	l_vect3.y = p_object->vertex[p_object->polygon[i].c].y;
	l_vect3.z = p_object->vertex[p_object->polygon[i].c].z;

        // Polygon normal calculation
	// Vector from the first vertex to the second one
	l_vect_b1=l_vect2-l_vect1;
	l_vect_b1.normalize();
	// Vector from the first vertex to the third one
	l_vect_b2=l_vect3-l_vect1;
	l_vect_b2.normalize();
	 // Dot product between the two vectors
	l_normal.cross(l_vect_b1,l_vect_b2);
	 //Normalizing the resultant we obtain the polygon normal
	l_normal.normalize();

	// For each vertex shared by this polygon we increase the number of connections
	l_connections_qty[p_object->polygon[i].a]+=1; 
	l_connections_qty[p_object->polygon[i].b]+=1;
	l_connections_qty[p_object->polygon[i].c]+=1;

	// For each vertex shared by this polygon we add the polygon normal
	p_object->normal[p_object->polygon[i].a].x+=l_normal.x; 
	p_object->normal[p_object->polygon[i].a].y+=l_normal.y;
	p_object->normal[p_object->polygon[i].a].z+=l_normal.z;
	p_object->normal[p_object->polygon[i].b].x+=l_normal.x;
	p_object->normal[p_object->polygon[i].b].y+=l_normal.y;
	p_object->normal[p_object->polygon[i].b].z+=l_normal.z;
	p_object->normal[p_object->polygon[i].c].x+=l_normal.x;
	p_object->normal[p_object->polygon[i].c].y+=l_normal.y;
	p_object->normal[p_object->polygon[i].c].z+=l_normal.z;
	}
	
for (i=0; i<p_object->vertices_qty; i++)
	{
	if (l_connections_qty[i]>0)
		{
		// Let's now average the polygons' normals to obtain the vertex normal!
		p_object->normal[i].x /= l_connections_qty[i]; 
		p_object->normal[i].y /= l_connections_qty[i];
		p_object->normal[i].z /= l_connections_qty[i];
		}
	}
}

