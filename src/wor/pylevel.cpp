#include "pylevel.h"

namespace PySublimatObjects
{
SublimatObjects *u_sub_objects;
bool *PlayerStart;
bool *CalcSim;

PyObject *PySetPyNextTime(PyObject *self, PyObject *args)
	{
	int pause;
	if (!PyArg_ParseTuple (args, "i", &pause))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}

	if (pause)
		{
		u_sub_objects->SetPyNextTime(pause);
		}
	
	return Py_None;
	}

PyObject *PySetNextScript(PyObject *self, PyObject *args)
	{
	char *path;
	std::string str_path;
	if (!PyArg_ParseTuple (args, "s", &path))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	
	str_path = path;
	u_sub_objects->SetPyFile(PKGDATADIR+str_path);
	return Py_None;
	}

PyObject *PyAddGaoObject(PyObject *self, PyObject *args)
	{
	int s;
	UObject TempUObject;

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
		s=u_sub_objects->GetSectorN(((GaoObject*)addr)->GetCord());

		((GaoObject*)addr)->WriteSublimatObjects(u_sub_objects);
		((GaoObject*)addr)->WritenSector(s);

		TempUObject.in=((GaoObject*)addr);
		u_sub_objects->GetSO()->push_front(TempUObject);
		u_sub_objects->GetSeO()[s].push_front(TempUObject);
		}
	return Py_None;
	}

PyObject *PyRandom(PyObject *self, PyObject *args)
	{
	int max;
	if (!PyArg_ParseTuple (args, "i", &max))
	{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
	}
	return Py_BuildValue("i", rand()%max);
	}

PyObject *PySearchPlayer(PyObject *self, PyObject *args)
	{
	ObjectList::iterator object_iterator;
	PlayFizState *PFS;
	for(object_iterator=u_sub_objects->GetSO()->begin();
		    object_iterator!=u_sub_objects->GetSO()->end();
		    ++object_iterator)
			{
			PFS = ((AI*)object_iterator->in)->GetPFS();
			if (PFS&&PFS->player)
				#if __WORDSIZE == 64
				return Py_BuildValue("l", (long int)object_iterator->in);
				#else
				return Py_BuildValue("i", (int)object_iterator->in);
				#endif
			
			}
	#if __WORDSIZE == 64
	return Py_BuildValue("l", 0);
	#else
	return Py_BuildValue("i", 0);
	#endif
	}

PyObject *PySearchObjectByName(PyObject *self, PyObject *args)
	{
	char *name;
	std::string s_name;
	ObjectList::iterator object_iterator;
	
	if (!PyArg_ParseTuple (args, "s", &name))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	s_name = name;
	for(object_iterator=u_sub_objects->GetSO()->begin();
		    object_iterator!=u_sub_objects->GetSO()->end();
		    ++object_iterator)
			{
			if (object_iterator->in->GetName()==s_name)
				#if __WORDSIZE == 64
				return Py_BuildValue("l", (long int)object_iterator->in);
				#else
				return Py_BuildValue("i", (int)object_iterator->in);
				#endif
			}
	#if __WORDSIZE == 64
	return Py_BuildValue("l", 0);
	#else
	return Py_BuildValue("i", 0);
	#endif
	}

PyObject *PyGetPlayerStart(PyObject *self, PyObject *args)
	{
	return Py_BuildValue("i", *PlayerStart);
	}

PyObject *PySetCalcSim(PyObject *self, PyObject *args)
	{
	int temp;
	if (!PyArg_ParseTuple (args, "i", &temp))
		{
		PyErr_Print ();
		PyErr_Clear ();
		return Py_None;
		}
	*CalcSim = temp;
	return Py_None;
	}

void InitPythonSublimatObjects(bool *PlayerStart_in, bool *CalcSim_in)
	{
	PlayerStart = PlayerStart_in;
	CalcSim = CalcSim_in;

	static PyMethodDef SublimatFunctionsList[] = {
			{ "Pause", PySetPyNextTime, METH_VARARGS },
			{ "NextScript", PySetNextScript, METH_VARARGS },
			{ "AddGaoObject", PyAddGaoObject, METH_VARARGS },
			{ "Random", PyRandom, METH_VARARGS },
			{ "SearchPlayer", PySearchPlayer, METH_NOARGS },
			{ "SearchObjectByName", PySearchObjectByName, METH_VARARGS },
			{ "GetPlayerStart", PyGetPlayerStart, METH_NOARGS },
			{ "SetCalcSim", PySetCalcSim, METH_VARARGS },
			{ NULL, NULL, 0 }
			};
	Py_InitModule ("Level", SublimatFunctionsList);
	}

void SetPythonSublimatObjects(SublimatObjects *sub_objects)
	{
	u_sub_objects = sub_objects;
	}
}
