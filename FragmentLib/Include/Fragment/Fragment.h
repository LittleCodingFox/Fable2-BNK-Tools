#ifndef FRAGMENTLIB_H
#define FRAGMENTLIB_H
/*!
	\page license License
	Copyright &copy; 2008 Nuno Silva (also known as Little Coding Fox and GhostManZero)


	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.


	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:


    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.


    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.


    3. This notice may not be removed or altered from any source
    distribution.
*/

/*!
	\mainpage FragmentLib Index


	\ref license
*/
#include "Platform.h"
#ifdef FRPLATFORM_WINDOWS
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <pthread.h>
#endif
#include "Common.h"
#include "Threads.h"
#include "Arrays.h"
#include "Strings.h"
#include "StackTracer.h"
#include "MemoryLists.h"
#include "Streams.h"
#include "Math.h"
#include "DynamicLink.h"
#include "ClassInterface.h"
#include "Translation.h"
#include "Property.h"
//Removed temporarily (hopefully)
//#include "Network.h"
#endif
