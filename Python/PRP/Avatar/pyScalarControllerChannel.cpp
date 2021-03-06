/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pyAGChannel.h"

#include <PRP/Avatar/plScalarChannel.h>
#include "PRP/pyCreatable.h"
#include "PRP/Animation/pyController.h"

PY_PLASMA_NEW(ScalarControllerChannel, plScalarControllerChannel)

PY_PROPERTY_CREATABLE(plController, Controller, ScalarControllerChannel,
                      controller, getController, setController)

static PyGetSetDef pyScalarControllerChannel_GetSet[] = {
    pyScalarControllerChannel_controller_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ScalarControllerChannel, plScalarControllerChannel,
               "plScalarControllerChannel wrapper")

PY_PLASMA_TYPE_INIT(ScalarControllerChannel) {
    pyScalarControllerChannel_Type.tp_new = pyScalarControllerChannel_new;
    pyScalarControllerChannel_Type.tp_getset = pyScalarControllerChannel_GetSet;
    pyScalarControllerChannel_Type.tp_base = &pyScalarChannel_Type;
    if (PyType_CheckAndReady(&pyScalarControllerChannel_Type) < 0)
        return NULL;

    Py_INCREF(&pyScalarControllerChannel_Type);
    return (PyObject*)&pyScalarControllerChannel_Type;
}

PY_PLASMA_IFC_METHODS(ScalarControllerChannel, plScalarControllerChannel)
