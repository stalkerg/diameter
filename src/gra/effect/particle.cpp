#include "./particle.h"

void Particle::Initn(int in, bool lf)
{
nPart[in].color=nColor;
nPart[in].cor=cor;
//nPart[in].cor.z=0;//-in/100.0+0.01;
nPart[in].nap=nDirection;
nPart[in].nap.x+=((rand()%fSpeed_x)-(fSpeed_x/2))/1000.0f;
nPart[in].nap.y+=((rand()%fSpeed_y)-(fSpeed_y/2))/1000.0f;
//nPart[in].nap.z+=((rand()%fSpeed2)-(fSpeed2/2))/1000.0f;
nPart[in].speed=nSpeed;
nPart[in].t=0;
nPart[in].life=lf;
}

void Particle::Init()
{
int i;
for(i=0; i<n; i++)
	Initn(i,false);
//nFade=1/life;
cFade[0]=(kColor[0]-nColor[0])/life;
cFade[1]=(kColor[1]-nColor[1])/life;
cFade[2]=(kColor[2]-nColor[2])/life;
cFade[3]=(kColor[3]-nColor[3])/life;
}

void Particle::Calc()
{
int i, temp=(int)(*tnow);
if(temp-t2>(life/n)*1000)
	up=true;

for(i=0;i<n;i++)
	{
	if(nPart[i].life)
		{
		if(temp-nPart[i].t>life*1000)
			{
			Initn(i,false);
			}
		else
			{			
			nPart[i].cor.x+=(((*t)*nPart[i].speed)*nPart[i].nap.x);
			nPart[i].cor.y+=(((*t)*nPart[i].speed)*nPart[i].nap.y);
			nPart[i].cor.z+=(((*t)*nPart[i].speed)*nPart[i].nap.z);
			nPart[i].color[0]+=cFade[0]*(*t);
			nPart[i].color[1]+=cFade[1]*(*t);
			nPart[i].color[2]+=cFade[2]*(*t);
			nPart[i].color[3]+=cFade[3]*(*t);
			}
		}
		else
			if(up&&nSpeed!=0)
				{
				Initn(i,true);
				nPart[i].t=temp;
				up=false;
				t2=nPart[i].t;
				}
		
	}
}

void Particle::Draw()
{
glDisable (GL_LIGHTING);
glEnable (GL_BLEND);
glBlendFunc (GL_SRC_ALPHA, GL_ONE);
glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
glDepthMask (GL_FALSE);

int i;
for(i=0;i<n;i++)
	{
	if(nPart[i].life)
		{
		glColor4f(nPart[i].color[0],nPart[i].color[1],nPart[i].color[2],nPart[i].color[3]);
		inSprite->Draw(nPart[i].cor);
		}
	}
glDepthMask (GL_TRUE);
glDisable (GL_BLEND);
}


namespace PyParticle
{
SpriteList *slist;
float *n_time, *e_time;

PyObject *PyNewParticle(PyObject *self, PyObject *args)
	{
	Particle *PyPart = NULL;
	int num;
	if (!PyArg_ParseTuple (args, "i", &num))
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	if (num)
		PyPart = new Particle(num);
	
	#if __WORDSIZE == 64
	return Py_BuildValue("l", (long int)PyPart);
	#else
	return Py_BuildValue("i", (int)PyPart);
	#endif
	}

PyObject *PySetSprite(PyObject *self, PyObject *args)
	{
	char *name_sprite = NULL;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "ls" ,&addr, &name_sprite))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "is", &addr, &name_sprite))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	if (name_sprite&&addr)
		((Particle*)addr)->inSprite = GetSFName(name_sprite, slist);
	
	return Py_None;
	}

PyObject *PySetnDirection(PyObject *self, PyObject *args)
	{
	float x, y, z;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "lfff", &addr, &x, &y, &z))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "ifff", &addr, &x, &y, &z))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	
	if (addr)
		{
		((Particle*)addr)->nDirection.x = x;
		((Particle*)addr)->nDirection.y = y;
		((Particle*)addr)->nDirection.z = z;
		}
	return Py_None;
	}

PyObject *PySetCor(PyObject *self, PyObject *args)
	{
	float x, y, z;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "lfff", &addr, &x, &y, &z))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "ifff", &addr, &x, &y, &z))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	if (addr)
		{
		((Particle*)addr)->cor.x = x;
		((Particle*)addr)->cor.y = y;
		((Particle*)addr)->cor.z = z;
		}

	return Py_None;
	}

PyObject *PySetnColor(PyObject *self, PyObject *args)
	{
	float r, g, b, a;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "lffff", &addr, &r, &g, &b, &a))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "iffff", &addr, &r, &g, &b, &a))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	if (addr)
		{
		((Particle*)addr)->nColor.r = r;
		((Particle*)addr)->nColor.g = g;
		((Particle*)addr)->nColor.b = b;
		((Particle*)addr)->nColor.a = a;
		}

	return Py_None;
	}

PyObject *PySetkColor(PyObject *self, PyObject *args)
	{
	float r, g, b, a;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "lffff", &addr, &r, &g, &b, &a))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "iffff", &addr, &r, &g, &b, &a))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	
	if (addr)
		{
		((Particle*)addr)->kColor.r = r;
		((Particle*)addr)->kColor.g = g;
		((Particle*)addr)->kColor.b = b;
		((Particle*)addr)->kColor.a = a;
		}
	
	return Py_None;
	}

PyObject *PySetSpeed(PyObject *self, PyObject *args)
	{
	int nSpeed, fSpeed_x, fSpeed_y;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "liii", &addr, &nSpeed, &fSpeed_x, &fSpeed_y))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "iiii", &addr, &nSpeed, &fSpeed_x, &fSpeed_y))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	
	if (addr)
		{
		((Particle*)addr)->nSpeed = nSpeed;
		((Particle*)addr)->fSpeed_x = fSpeed_x;
		((Particle*)addr)->fSpeed_y = fSpeed_y;
		}

	return Py_None;
	}

PyObject *PySetLife(PyObject *self, PyObject *args)
	{
	float num;
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "lf", &addr, &num))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "if", &addr, &num))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	if (num&&addr)
		((Particle*)addr)->life = num;
	
	return Py_None;
	}

PyObject *PyInit(PyObject *self, PyObject *args)
	{
	#if __WORDSIZE == 64
	long int addr;
	if (!PyArg_ParseTuple (args, "l", &addr))
	#else
	int addr;
	if (!PyArg_ParseTuple (args, "i", &addr))
	#endif
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}

	if (addr)
		{
		((Particle*)addr)->tnow = n_time;
		((Particle*)addr)->t = e_time;
		((Particle*)addr)->Init();
		}

	return Py_None;
	}

void InitPythonParticle(SpriteList *gslist, float *time_n, float *time_e)
	{
	n_time = time_n;
	e_time = time_e;
	slist = gslist;
	static PyMethodDef ParticleFunctionsList[] = {
			{ "NewParticle", PyNewParticle, METH_VARARGS },
			{ "SetSprite", PySetSprite, METH_VARARGS },
			{ "SetnDirection", PySetnDirection, METH_VARARGS },
			{ "SetCor", PySetCor, METH_VARARGS },
			{ "SetnColor", PySetnColor, METH_VARARGS },
			{ "SetkColor", PySetkColor, METH_VARARGS },
			{ "SetSpeed", PySetSpeed, METH_VARARGS },
			{ "SetLife", PySetLife, METH_VARARGS },
			{ "Init", PyInit, METH_VARARGS },
			{ NULL, NULL, 0 }
			};
	Py_InitModule ("Particle", ParticleFunctionsList);
	}
}

