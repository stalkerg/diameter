#ifndef PYLEVEL
#define PYLEVEL

#include "./object.h"
#include "./objects/gao.h"

namespace PySublimatObjects
{
PyObject *PySetPyNextTime(PyObject *self, PyObject *args);

void InitPythonSublimatObjects(bool *PlayerStart_in, bool *CalcSim_in);
void SetPythonSublimatObjects(SublimatObjects *sub_objects);
}

#endif

