#pragma once

#include "commontypes.h"
#include "loadfromrc.h"

#include <SFML/Graphics.hpp>

#include <array>
#include <cassert>
#include <cstdint>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using LocationContainer = std::unordered_map<int32, ResInfo>;

using IDs = std::vector<int32>;

template<class Derived, class T>
class ResourceManager
{
protected:

	// Pair containts resource pointer in heap and a counter of object requiring this resource
	using ResourceContainer = std::unordered_map<int32, std::pair<T*, std::size_t>>;

	ResourceManager(const IDs& id_vec, const char* type)
	{
		for (int32 id : id_vec)
		{
			ResInfo res_info = rsc::loadFromRc(id, type);
			if (res_info.first)
			{
				m_locations.emplace(id, res_info);
			}
		}
	}

	~ResourceManager() { releaseAll(); }

	T* load(ResInfo resource)
	{
		// https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
		return static_cast<Derived*>(this)->load(resource);
	}
public:

	bool requireResource(int32 id)
	{
		auto res = find(id);
		if (res)
		{
			++res->second;
			return true;
		}

		auto loc = m_locations.find(id);
		if (loc == m_locations.end()) { return false; }

		T* resource = load(loc->second);
		if (!resource) { return false; }
		
		m_resources.emplace(id, std::make_pair(resource, 1u));
		return true;
	}

	bool releaseResource(int id)
	{
		auto res = find(id);
		if (!res) { return false; }
		--res->second;
		if (res->second == 0u) { unload(id); }
		return true;
	}

	T* getResource(int id)
	{
		auto res = find(id);
		assert(res);
		return res ? res->first : nullptr;
	}

	void releaseAll()
	{
		while (m_resources.begin() != m_resources.end())
		{
			auto it = m_resources.begin();
			delete it->second.first;
			m_resources.erase(it);
		}
	}
private:

	std::pair<T*, std::size_t>* find(int32 id)
	{
		if (m_resources.empty())
		{
			std::cout << "empty!";
		}
		auto it = m_resources.find(id);
		return it != m_resources.end() ? &it->second : nullptr;
	}

	bool unload(int32 id)
	{
		auto it = m_resources.find(id);
		if (it == m_resources.end()) { return false; }

		delete it->second.first;
		m_resources.erase(it);
		return true;
	}

	LocationContainer m_locations;

	ResourceContainer m_resources;
};