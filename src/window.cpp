#include "statemanager.h"
#include "window.h"

Window::Window() : Window{{1024u, 1024u}, "Slot Machine"}
{}

Window::Window(const sf::Vector2u& size, const std::string& title) : m_size{size}, m_title{title}, m_default_size{size}
{
	m_event_manager.addDelegate(StateType::Global, "CloseWindow", this, &Window::close);
	m_event_manager.addDelegate(StateType::Global, "ToggleFullScreen", this, &Window::toggleFullScreen);

	create();
}

Window::~Window()
{
	m_window.close();
}

void Window::startDraw()
{
	m_window.clear();
}

void Window::endDraw()
{
	m_window.display();
}

void Window::update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::GainedFocus)
		{
			m_event_manager.setFocus(true);
		}
		else if (event.type == sf::Event::LostFocus)
		{
			m_event_manager.setFocus(false);
		}

		m_event_manager.processEvent(event);
	}

	m_event_manager.update();
}

void Window::draw(sf::Drawable& drawable)
{
	m_window.draw(drawable);
}

void Window::toggleFullScreen([[maybe_unused]] EventDetails* details)
{
	m_fullscreen = !m_fullscreen;
	m_window.close();
	create();
}

void Window::close([[maybe_unused]] EventDetails* details)
{
	m_closed = true;
}

bool Window::isClosed() const
{
	return m_closed;
}

bool Window::isFullSreen() const
{
	return m_fullscreen;
}

sf::Vector2u Window::size() const
{
	return m_size;
}

sf::RenderWindow* Window::getRenderWindow()
{
	return &m_window;
}

EventManager* Window::getEventManager()
{
	return &m_event_manager;
}

void Window::create()
{
	int32 not_resizable = sf::Style::Titlebar | sf::Style::Close;
	int32 style = m_fullscreen ? sf::Style::Fullscreen : not_resizable;

	if (style == not_resizable)
	{
		m_window.create({ m_default_size.x, m_default_size.y }, m_title, style);
		m_size = m_default_size;
	}
	else if (style == sf::Style::Fullscreen)
	{
		sf::VideoMode mode = sf::VideoMode::getFullscreenModes().front();
		m_window.create(mode, m_title, style);
		m_size.x = mode.width;
		m_size.y = mode.height;
	}
}
