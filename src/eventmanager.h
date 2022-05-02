#pragma once

#include "commontypes.h"

#include <SFML/Graphics.hpp>

#include <functional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

enum class EventType;
enum class StateType;
struct EventCode;
struct EventDetails;
struct Binding;

// Type that represtents all keys we need press (or do other stuff) to fire an event
using Events = std::vector<std::pair<EventType, EventCode>>;

using Bindings = std::unordered_map<std::string, Binding*>;

// Container of delegates which we call if all input from binding matches the specific delegate
using Delegates = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

// Each StateType has its own Delegates
using DelegateContainer = std::unordered_map<StateType, Delegates>;

enum class EventType
{
	KeyPressed = sf::Event::KeyPressed,
	KeyReleased = sf::Event::KeyReleased,
	MousePressed = sf::Event::MouseButtonPressed,
	MouseReleased = sf::Event::MouseButtonReleased,
	WindowClosed = sf::Event::Closed,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	Keyboard = sf::Event::Count + 1,
	Mouse,
	MaxEventType,
};

// Structure holding code of the event (e.g. code of some keyboard button)
struct EventCode
{
	int32 m_code = 0;

	EventCode() {}

	EventCode(int32 code) : m_code{ code }
	{}

	friend bool operator==(EventCode code, int32 other)
	{
		return code.m_code == other;
	}

	friend bool operator==(int32 other, EventCode code)
	{
		return code == other;
	}
};

struct EventDetails
{
	std::string m_name;
	
	sf::Vector2i m_mouse_pos;

	sf::Vector2i m_new_window_size;

	EventDetails(const std::string& name) : m_name{ name }
	{
		clear();
	}

	void clear()
	{
		m_mouse_pos = { 0, 0 };
		m_new_window_size = { 0,0 };
	}
};

struct Binding
{
	Events m_events;

	std::string m_name;

	int32 m_hit_counter;

	EventDetails m_details;

	Binding(const std::string& name, EventType type, EventCode code = EventCode())
		: m_name{ name }, m_details{ name }, m_hit_counter{ 0 }
	{
		bindEvent(type, code);
	}

	/* Helper method to add multiple keys to a binding*/
	void bindEvent(EventType type, EventCode code = EventCode())
	{
		m_events.emplace_back(type, code);
	}
};

class EventManager final
{
public:

	EventManager();

	~EventManager();

	bool addBinding(Binding* bind);

	bool removeBinding(const std::string& name);

	void processEvent(sf::Event& event);

	void update();

	void setCurrentState(StateType state);

	void setFocus(bool focus);

	template<class T>
	bool addDelegate(StateType type, const std::string& name, T* object, void(T::* func)(EventDetails*))
	{
		auto it = m_delegates.emplace(type, Delegates{}).first;
		auto fun = std::bind(func, object, std::placeholders::_1);
		return it->second.emplace(name, fun).second;
	}

	bool removeDelegate(StateType type, const std::string& name)
	{
		auto it = m_delegates.find(type);
		if (it == m_delegates.end()) { return false; }

		auto delegate_it = it->second.find(name);
		if (delegate_it == it->second.end()) { return false; }

		it->second.erase(delegate_it);
		return true;
	}
private:
	
	StateType m_current_state;

	Bindings m_bindings;

	DelegateContainer m_delegates;

	bool m_has_focus = true;
};