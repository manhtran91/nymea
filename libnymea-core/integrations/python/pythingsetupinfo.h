#ifndef PYTHINGSETUPINFO_H
#define PYTHINGSETUPINFO_H

#include <Python.h>
#include "structmember.h"

#include "pything.h"

#include "integrations/thingsetupinfo.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#pragma GCC diagnostic ignored "-Wwrite-strings"

typedef struct {
    PyObject_HEAD
    ThingSetupInfo* info;
    PyThing *pyThing;
} PyThingSetupInfo;


static int PyThingSetupInfo_init(PyThingSetupInfo */*self*/, PyObject */*args*/, PyObject */*kwds*/) {
    return 0;
}


static void PyThingSetupInfo_dealloc(PyThingSetupInfo * self) {
    Py_TYPE(self)->tp_free(self);
}

static PyObject * PyThingSetupInfo_finish(PyThingSetupInfo* self, PyObject* args) {
    int status;
    char *message = nullptr;

    if (!PyArg_ParseTuple(args, "i|s", &status, &message)) {
        PyErr_SetString(PyExc_TypeError, "Invalid arguments in finish call. Expected: finish(ThingError, message = \"\"");
        return nullptr;
    }

    Thing::ThingError thingError = static_cast<Thing::ThingError>(status);
    QString displayMessage = message != nullptr ? QString(message) : QString();

    if (self->info) {
        QMetaObject::invokeMethod(self->info, "finish", Qt::QueuedConnection, Q_ARG(Thing::ThingError, thingError), Q_ARG(QString, displayMessage));
    }

    Py_RETURN_NONE;
}

static PyMemberDef PyThingSetupInfo_members[] = {
    {"thing", T_OBJECT_EX, offsetof(PyThingSetupInfo, pyThing), 0, "Thing being setup in this setup transaction"},
    {nullptr, 0, 0, 0, nullptr}  /* Sentinel */
};

static PyMethodDef PyThingSetupInfo_methods[] = {
    { "finish", (PyCFunction)PyThingSetupInfo_finish,    METH_VARARGS,       "finish a setup" },
    {nullptr, nullptr, 0, nullptr} // sentinel
};

static PyTypeObject PyThingSetupInfoType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "nymea.ThingSetupInfo",   /* tp_name */
    sizeof(PyThingSetupInfo), /* tp_basicsize */
    0,                         /* tp_itemsize */
    0,                         /* tp_dealloc */
    0,                         /* tp_vectorcall_offset */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_as_async */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "Noddy objects",           /* tp_doc */ 
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static void registerThingSetupInfoType(PyObject *module) {
    PyThingSetupInfoType.tp_new = PyType_GenericNew;
    PyThingSetupInfoType.tp_dealloc=(destructor) PyThingSetupInfo_dealloc;
    PyThingSetupInfoType.tp_basicsize = sizeof(PyThingSetupInfo);
    PyThingSetupInfoType.tp_flags = Py_TPFLAGS_DEFAULT;
    PyThingSetupInfoType.tp_doc = "ThingSetupInfo class";
    PyThingSetupInfoType.tp_methods = PyThingSetupInfo_methods;
    PyThingSetupInfoType.tp_members = PyThingSetupInfo_members;
    PyThingSetupInfoType.tp_init = (initproc)PyThingSetupInfo_init;

    if (PyType_Ready(&PyThingSetupInfoType) < 0) {
        return;
    }
    PyModule_AddObject(module, "ThingSetupInfo", (PyObject *)&PyThingSetupInfoType);
}




#pragma GCC diagnostic pop

#endif // PYTHINGSETUPINFO_H
