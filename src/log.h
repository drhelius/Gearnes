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

#ifndef LOG_H_
#define	LOG_H_

#include <cstdio>
#include <cstdarg>

namespace Gearnes
{

#ifdef DEBUG_GEARNES
    #define Log(msg, ...) (Gearnes::LogImpl(msg, ##__VA_ARGS__))
#else
    #define Log(msg, ...)
#endif

__attribute__((__format__ (__printf__, 1, 0)))
inline void LogImpl(const char* const msg, ...)
{
    static int count = 1;
    char szBuf[512];
    va_list args;
    va_start(args, msg);
    vsprintf(szBuf, msg, args);
    va_end(args);
    printf("%d: %s\n", count, szBuf);
    count++;
}

} // namespace Gearnes

#endif // LOG_H_
