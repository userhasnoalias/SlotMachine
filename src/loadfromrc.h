#pragma once

#include "commontypes.h"

#include <cstdlib>
#include <iostream>
#include <string>

using ResInfo = std::pair<void*, std::size_t>;

#ifdef _WIN32
#include <Windows.h>

namespace rsc
{
	inline ResInfo loadFromRc(int32 id, const char* type)
	{
		HRSRC rc_handle = FindResourceA(NULL, MAKEINTRESOURCEA(id), type);
		if (!rc_handle)
		{
			std::cerr << "Failed finding resource handle! ID: " << id << '\n';
			return { nullptr, 0u };
		}

		HGLOBAL g_rc_handle = LoadResource(NULL, rc_handle);
		if (!g_rc_handle)
		{
			std::cerr << "Failed loading resource! ID: " << id << '\n';
			return { nullptr, 0u };
		}

		LPVOID rc_p = LockResource(g_rc_handle);
		if (!rc_p)
		{
			std::cerr << "Failed resource lock! ID: " << id << '\n';
			return { nullptr, 0u };
		}

		DWORD rc_size = SizeofResource(NULL, rc_handle);
		if (rc_size <= 0)
		{
			std::cerr << "Failed determining resourse size! ID: " << id << '\n';
			return { nullptr, 0u };
		}

		return { rc_p, rc_size };
	}
} // rsc namespace
#elif defined __linux__
namespace rsc
{
	inline ResInfo loadFromRc(int id, const std::string& type)
	{
		std::cerr << "Unix platforms are not yet supported.\n";
		std::exit(1);
	}
}// rsc namespace
#endif