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

#include "pySimulationMsg.h"

#include "PRP/KeyedObject/pyKey.h"
#include <PRP/Message/plSimulationMsg.h>

PY_PLASMA_NEW(SubWorldMsg, plSubWorldMsg)

PY_PROPERTY(plKey, SubWorldMsg, worldKey, getWorldKey, setWorldKey);

static PyGetSetDef pySubworldMsg_GetSet[] = {
    pySubWorldMsg_worldKey_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SubWorldMsg, plSubWorldMsg, "plSubWorldMsg wrapper")

PY_PLASMA_TYPE_INIT(SubWorldMsg) {
    pySubWorldMsg_Type.tp_new = pySubWorldMsg_new;
    pySubWorldMsg_Type.tp_getset = pySubworldMsg_GetSet;
    pySubWorldMsg_Type.tp_base = &pySimulationMsg_Type;
    if (PyType_CheckAndReady(&pySubWorldMsg_Type) < 0)
        return NULL;

    Py_INCREF(&pySubWorldMsg_Type);
    return (PyObject*)&pySubWorldMsg_Type;
}

PY_PLASMA_IFC_METHODS(SubWorldMsg, plSubWorldMsg)
