/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "pickable_object.h"

#ifdef WIN32
#include "windows.h"
#endif

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace cg3 {

unsigned int PickableObject::objectBits = 8;

PickableObject::PickableObject() : DrawableObject()
{
}

void PickableObject::setMeshBits(unsigned int nBits)
{
    if (nBits < 32) {
		objectBits = nBits;
    }
}

void PickableObject::glPushName(unsigned int idElement) const
{
	::glPushName((id << (32 - objectBits)) + idElement);
}

void PickableObject::getIdsFromIdName(unsigned int idName, unsigned int &idObject, unsigned int& idElement)
{
	idObject = idName >> (32 - objectBits);
	idElement = idName - (idObject << (32 - objectBits));
}

}
