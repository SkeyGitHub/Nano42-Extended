// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Library Files:
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Winmm.lib")

// Windows Header Files:
#include <windows.h>
#include <Mmsystem.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <Psapi.h>
#include <MinHook.h>
#include <timeapi.h>
#include <time.h>

// Additional Header Files:
#include "Log.h"
#include "Memory.h"
#include "types.h"
#include "enums.h"
#include "InputHook.h"
#include "keyboard.h"
#include "CrossMapping.h"
#include "NativeInvoker.h"
#include "nativeCaller.h"
#include "natives.h"
#include "Hooking.h"



// Menu Files:
#include "GUI.h"
#include "menu.h"
#include "types.h"
#include "Functions.h"


#include <locale>
#include <codecvt>
#include <stdio.h>
#include "Auth/Networking/sha512.hh"
#include "Auth/Networking/Web2.0.h"


class globalHandle
{
private:
	void* _handle;

public:
	globalHandle(int index)
		: _handle(&Hooking::getGlobalPtr()[index >> 18 & 0x3F][index & 0x3FFFF])
	{ }

	globalHandle(void* p)
		: _handle(p)
	{ }

	globalHandle(const globalHandle& copy)
		: _handle(copy._handle)
	{ }

	globalHandle At(int index)
	{
		return globalHandle(reinterpret_cast<void**>(this->_handle) + (index));
	}

	globalHandle At(int index, int size)
	{
		// Position 0 = Array Size
		return this->At(1 + (index * size));
	}

	template <typename T>
	T* Get()
	{
		return reinterpret_cast<T*>(this->_handle);
	}

	template <typename T>
	T& As()
	{
		return *this->Get<T>();
	}
};

