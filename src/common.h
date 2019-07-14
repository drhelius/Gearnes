/*
 * Gearnes - NES / Famicom Emulator
 * Copyright (C) 2015  Ignacio Sanchez Gines

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/
 *
 */

#ifndef COMMON_H_
#define	COMMON_H_

#define DEBUG_GEARNES 1

#ifdef DEBUG_GEARNES
    #define DISASM_GEARNES 1
#endif

#define GEARNES_TITLE "Gearnes 0.1"
#define GEARNES_VERSION 0.1f

#ifdef _WIN32
    #define BLARGG_USE_NAMESPACE 1
#endif


#define SafeDelete(pointer) if(pointer != nullptr) delete pointer; ((pointer) = nullptr)
#define SafeDeleteArray(pointer) if(pointer != nullptr) delete [] pointer; ((pointer) = nullptr)

#define InitPointer(pointer) ((pointer) = nullptr)
#define IsValidPointer(pointer) ((pointer) != nullptr)

#include "log.h"
#include "bit_ops.h"

#endif // COMMON_H_

