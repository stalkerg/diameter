#include "3ds.h"
#include <cmath>
#include <iostream>

glm3ds::~glm3ds() {
	#ifdef DEBUG
		std::cout<<"Delete ModelList "<<file_name<<"  id:"<<nList<<std::endl;
	#endif
	glDeleteBuffers(1, &vbo_buffer);
}

void glm3ds::Unable() {
	std::cout<<"Unable 3ds modele: "<<file_name<<std::endl;
	glDeleteBuffers(1, &vbo_buffer);
}

void glm3ds::LoadModel(std::string chin, float rtmin) {
	int l_index, vertex_index;
	in_scale = rtmin;
	file_name = chin;
	object = new obj_type;
	if(!Load3DS (object,(char *)chin.c_str()))
		exit(0);

	vertex_count = object->polygons_qty * 3;
	ObjCalcNormals(object);

	float *buffer = new float[vertex_count*8];

	for (l_index = 0, vertex_index = 0; l_index < object->polygons_qty; l_index++, vertex_index += 3) {
		// A
		buffer[vertex_index * 8] = object->vertex[object->polygon[l_index].a].x * rtmin;
		buffer[vertex_index * 8 + 1] = object->vertex[object->polygon[l_index].a].y * rtmin;
		buffer[vertex_index * 8 + 2] = object->vertex[object->polygon[l_index].a].z * rtmin;

		buffer[vertex_index * 8 + 3] = object->normal[object->polygon[l_index].a].x;
		buffer[vertex_index * 8 + 4] = object->normal[object->polygon[l_index].a].y;
		buffer[vertex_index * 8 + 5] = object->normal[object->polygon[l_index].a].z;

		buffer[vertex_index * 8 + 6] = object->mapcoord[object->polygon[l_index].a].u;
		buffer[vertex_index * 8 + 7] = object->mapcoord[object->polygon[l_index].a].v;

		// B
		buffer[(vertex_index + 1) * 8] = object->vertex[object->polygon[l_index].b].x * rtmin;
		buffer[(vertex_index + 1) * 8 + 1] = object->vertex[object->polygon[l_index].b].y * rtmin;
		buffer[(vertex_index + 1) * 8 + 2] = object->vertex[object->polygon[l_index].b].z * rtmin;

		buffer[(vertex_index + 1)*8+3] = object->normal[object->polygon[l_index].b].x;
		buffer[(vertex_index + 1)*8+4] = object->normal[object->polygon[l_index].b].y;
		buffer[(vertex_index + 1)*8+5] = object->normal[object->polygon[l_index].b].z;

		buffer[(vertex_index + 1)*8+6] = object->mapcoord[object->polygon[l_index].b].u;
		buffer[(vertex_index + 1)*8+7] = object->mapcoord[object->polygon[l_index].b].v;

		// B
		buffer[(vertex_index + 2) * 8] = object->vertex[object->polygon[l_index].c].x * rtmin;
		buffer[(vertex_index + 2) * 8 + 1] = object->vertex[object->polygon[l_index].c].y * rtmin;
		buffer[(vertex_index + 2) * 8 + 2] = object->vertex[object->polygon[l_index].c].z * rtmin;

		buffer[(vertex_index + 2)*8+3] = object->normal[object->polygon[l_index].c].x;
		buffer[(vertex_index + 2)*8+4] = object->normal[object->polygon[l_index].c].y;
		buffer[(vertex_index + 2)*8+5] = object->normal[object->polygon[l_index].c].z;

		buffer[(vertex_index + 2)*8+6] = object->mapcoord[object->polygon[l_index].c].u;
		buffer[(vertex_index + 2)*8+7] = object->mapcoord[object->polygon[l_index].c].v;
	}

	glGenBuffers(1, &vbo_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_count*8*sizeof(float), buffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
	delete[] buffer;

	time_last_draw = SDL_GetTicks();
	enable = true;
}

void glm3ds::Draw() {
	time_last_draw=SDL_GetTicks();
	if(!enable) {
		std::cout<<"ReLoad model: "<<file_name<<std::endl;
		LoadModel(file_name, in_scale);
		delete object;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer);
	glDisableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(float)*8, NULL);  //Vertex start position address
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(float)*8, (GLvoid *)(sizeof(float)*3)); //Normal start position address
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float)*8, (GLvoid *)(sizeof(float)*6));  //Texcoord start position address

	glDrawArrays(GL_TRIANGLES, 0, vertex_count);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

float glm3ds::GetRadius(float rtmin) {
	int l_index;
	float R=0, tr=0, R2;
	for (l_index=0;l_index<object->polygons_qty;l_index++) {
		// Coordinates of the first vertex
		if((tr=sqrt(object->vertex[ object->polygon[l_index].a ].x*object->vertex[ object->polygon[l_index].a ].x
		+object->vertex[ object->polygon[l_index].a ].y*object->vertex[ object->polygon[l_index].a ].y))>R) R=tr;
		// Coordinates of the second vertex
		if((tr=sqrt(object->vertex[ object->polygon[l_index].b ].x*object->vertex[ object->polygon[l_index].b ].x
		+object->vertex[ object->polygon[l_index].b ].y*object->vertex[ object->polygon[l_index].b ].y))>R) R=tr;
		// Coordinates of the Third vertex
		if((tr=sqrt(object->vertex[ object->polygon[l_index].c ].x*object->vertex[ object->polygon[l_index].c ].x
		+object->vertex[ object->polygon[l_index].c ].y*object->vertex[ object->polygon[l_index].c ].y))>R) R=tr;
	}

	R2=sqrt(object->vertex[ object->polygon[0].a ].x*object->vertex[ object->polygon[0].a ].x
		+object->vertex[ object->polygon[0].a ].y*object->vertex[ object->polygon[0].a ].y);
	for (l_index=0;l_index<object->polygons_qty;l_index++) {
		// Coordinates of the first vertex
		if((tr=sqrt(object->vertex[ object->polygon[l_index].a ].x*object->vertex[ object->polygon[l_index].a ].x
		+object->vertex[ object->polygon[l_index].a ].y*object->vertex[ object->polygon[l_index].a ].y))<R2) R2=tr;
		// Coordinates of the second vertex
		if((tr=sqrt(object->vertex[ object->polygon[l_index].b ].x*object->vertex[ object->polygon[l_index].b ].x
		+object->vertex[ object->polygon[l_index].b ].y*object->vertex[ object->polygon[l_index].b ].y))<R2) R2=tr;
		// Coordinates of the Third vertex
		if((tr=sqrt(object->vertex[ object->polygon[l_index].c ].x*object->vertex[ object->polygon[l_index].c ].x
		+object->vertex[ object->polygon[l_index].c ].y*object->vertex[ object->polygon[l_index].c ].y))<R2) R2=tr;
	}
	if(R2<0)
		R2*=-1;
	if(R2>R)
		return R2*rtmin;
	else
		return R*rtmin;
}

