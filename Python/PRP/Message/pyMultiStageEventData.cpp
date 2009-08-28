#include <PyPlasma.h>
#include <PRP/Message/proEventData.h>
#include "pyEventData.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyMultiStageEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMultiStageEventData* self = (pyMultiStageEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proMultiStageEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyMultiStageEventData_Convert(PyObject*, PyObject* args) {
    pyEventData* evt;
    if (!PyArg_ParseTuple(args, "O", &evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    if (!pyEventData_Check((PyObject*)evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    return pyMultiStageEventData_FromMultiStageEventData(proMultiStageEventData::Convert(evt->fThis));
}

static PyObject* pyMultiStageEventData_getStage(pyMultiStageEventData* self, void*) {
    return PyInt_FromLong(self->fThis->getStage());
}

static PyObject* pyMultiStageEventData_getEvent(pyMultiStageEventData* self, void*) {
    return PyInt_FromLong(self->fThis->getEvent());
}

static PyObject* pyMultiStageEventData_getAvatar(pyMultiStageEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getAvatar());
}

static int pyMultiStageEventData_setStage(pyMultiStageEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "stage should be an int");
        return -1;
    }
    self->fThis->setStage(PyInt_AsLong(value));
    return 0;
}

static int pyMultiStageEventData_setEvent(pyMultiStageEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "event should be an int");
        return -1;
    }
    self->fThis->setEvent(PyInt_AsLong(value));
    return 0;
}

static int pyMultiStageEventData_setAvatar(pyMultiStageEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setAvatar(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setAvatar(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "avatar should be a plKey");
        return -1;
    }
}
static PyMethodDef pyMultiStageEventData_Methods[] = {
    { "Convert", (PyCFunction)pyMultiStageEventData_Convert, METH_VARARGS | METH_STATIC,
      "Convert a proEventData to a proMultiStageEventData" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyMultiStageEventData_GetSet[] = {
    { "stage", (getter)pyMultiStageEventData_getStage, (setter)pyMultiStageEventData_setStage, NULL, NULL },
    { "event", (getter)pyMultiStageEventData_getEvent, (setter)pyMultiStageEventData_setEvent, NULL, NULL },
    { "avatar", (getter)pyMultiStageEventData_getAvatar, (setter)pyMultiStageEventData_setAvatar, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyMultiStageEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.proMultiStageEventData",  /* tp_name */
    sizeof(pyMultiStageEventData),      /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "proMultiStageEventData wrapper",   /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMultiStageEventData_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pyMultiStageEventData_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyMultiStageEventData_new,          /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyMultiStageEventData_Type() {
    pyMultiStageEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyMultiStageEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyMultiStageEventData_Type);
    return (PyObject*)&pyMultiStageEventData_Type;
}

int pyMultiStageEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyMultiStageEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyMultiStageEventData_Type))
        return 1;
    return 0;
}

PyObject* pyMultiStageEventData_FromMultiStageEventData(proMultiStageEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyMultiStageEventData* pyobj = PyObject_New(pyMultiStageEventData, &pyMultiStageEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}