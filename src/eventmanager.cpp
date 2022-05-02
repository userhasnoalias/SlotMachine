#include "eventmanager.h"
#include "statemanager.h"

EventManager::EventManager() : m_current_state{ StateType::Global }
{
	std::vector<Binding*> bindings;
	// Add all bindings here
	bindings.emplace_back(new Binding("ToggleFullScreen", EventType::KeyPressed, sf::Keyboard::F5));
	bindings.emplace_back(new Binding("CloseWindow", EventType::WindowClosed));


	for (Binding* bind : bindings)
	{
		if (!addBinding(bind)) { delete bind; }
	}
}

EventManager::~EventManager()
{
	for (auto& bind : m_bindings)
	{
		delete bind.second;
	}
}

bool EventManager::addBinding(Binding* bind)
{
	return m_bindings.emplace(bind->m_name, bind).second;
}

bool EventManager::removeBinding(const std::string& name)
{
	auto it = m_bindings.find(name);
	if (it == m_bindings.end()) { return false; }

	delete it->second;
	m_bindings.erase(it);
	return true;
}

void EventManager::processEvent(sf::Event& event)
{
	if (!m_has_focus) { return; }

	for (auto& bind : m_bindings)
	{
		Binding* cur_bind = bind.second;
		for (auto& ev : cur_bind->m_events)
		{
			EventType current_event_type = static_cast<EventType>(event.type);
			EventType bind_event_type = ev.first;
			EventCode bind_event_code = ev.second;
			if (current_event_type != bind_event_type) { continue; }

			if (current_event_type == EventType::KeyPressed || current_event_type == EventType::KeyReleased)
			{
				if (bind_event_code == event.key.code)
				{
					cur_bind->m_hit_counter += 1;

					// If we found a match we can skip checking other events for this bind
					// as each bind should contain only 1 event of type KeyPressed or KeyReleased by design
					break;
				}
			}
			else if (current_event_type == EventType::MousePressed || current_event_type == EventType::MouseReleased)
			{
				if (bind_event_code == event.mouseButton.button)
				{
					cur_bind->m_details.m_mouse_pos.x = event.mouseButton.x;
					cur_bind->m_details.m_mouse_pos.y = event.mouseButton.y;

					cur_bind->m_hit_counter += 1;

					// Same as with Keyboard
					break;
				}
			}
			else
			{
				if (current_event_type == EventType::WindowResized)
				{
					cur_bind->m_details.m_new_window_size.x = event.size.width;
					cur_bind->m_details.m_new_window_size.y = event.size.height;
				}

				cur_bind->m_hit_counter += 1;
			}
		}
	}
}

void EventManager::update()
{
	if (!m_has_focus) { return; }

	for (auto& bind : m_bindings)
	{
		Binding* cur_bind = bind.second;
		for (auto& event : cur_bind->m_events)
		{
			EventType type = event.first;
			EventCode code = event.second;
			
			switch (type)
			{
			case EventType::Keyboard:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(code.m_code)))
				{
					cur_bind->m_hit_counter += 1;
				}
			case EventType::Mouse:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(code.m_code)))
				{
					cur_bind->m_hit_counter += 1;
				}
			default:
				break;
			}
		}

		// If every button for this bind is pressed atm
		if (cur_bind->m_hit_counter == cur_bind->m_events.size())
		{
			auto delegates_it = m_delegates.find(m_current_state);
			if (delegates_it != m_delegates.end())
			{
				auto it = delegates_it->second.find(cur_bind->m_name);
				if (it != delegates_it->second.end())
				{
					it->second(&cur_bind->m_details);
				}
			}

			/* Anything with the state type Global will be invoked regardless of which state we're in.*/
			auto global_delegates_it = m_delegates.find(StateType::Global);
			if (global_delegates_it != m_delegates.end())
			{
				auto it = global_delegates_it->second.find(cur_bind->m_name);
				if (it != global_delegates_it->second.end())
				{
					it->second(&cur_bind->m_details);
				}
			}
		}

		cur_bind->m_hit_counter = 0;
		cur_bind->m_details.clear();
	}
}

void EventManager::setCurrentState(StateType state)
{
	m_current_state = state;
}

void EventManager::setFocus(bool focus)
{
	m_has_focus = focus;
}
