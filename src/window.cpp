#include "statemanager.h"
#include "window.h"

Window::Window() : Window{{1200u, 720u}, "Slot Machine"}
{}

Window::Window(const sf::Vector2u& size, const std::string& title) : m_size{size}, m_title{title}, m_default_size{size}
{
	m_event_manager.addDelegate(StateType::Global, "CloseWindow", this, &Window::close);

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

void Window::close([[maybe_unused]] EventDetails* details)
{
	m_closed = true;
}

bool Window::isClosed() const
{
	return m_closed;
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
	
	m_window.create({ m_default_size.x, m_default_size.y }, m_title, not_resizable);
	m_size = m_default_size;
}
