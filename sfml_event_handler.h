#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

template<typename T, typename = void>
struct has_on_poll_start :std::false_type {};

template<typename T>
struct has_on_poll_start<T, std::void_t<decltype(std::declval<T>().on_poll_start())>> :std::true_type {};

template<typename T, typename = void>
struct has_on_poll_stop :std::false_type {};

template<typename T>
struct has_on_poll_stop<T, std::void_t<decltype(std::declval<T>().on_poll_stop())>> :std::true_type {};

template<typename T, typename = void>
struct has_on_close :std::false_type {};

template<typename T>
struct has_on_close<T, std::void_t<decltype(std::declval<T>().on_close(std::declval<sf::RenderWindow&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_resize :std::false_type {};

template<typename T>
struct has_on_resize<T, std::void_t<decltype(std::declval<T>().on_resize(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::SizeEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_key_press :std::false_type {};

template<typename T>
struct has_on_key_press<T, std::void_t<decltype(std::declval<T>().on_key_press(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::KeyEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_key_release :std::false_type {};

template<typename T>
struct has_on_key_release<T, std::void_t<decltype(std::declval<T>().on_key_release(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::KeyEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_focus_lost :std::false_type {};

template<typename T>
struct has_on_focus_lost<T, std::void_t<decltype(std::declval<T>().on_focus_lost(std::declval<sf::RenderWindow&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_focus_gained :std::false_type {};

template<typename T>
struct has_on_focus_gained<T, std::void_t<decltype(std::declval<T>().on_focus_gained(std::declval<sf::RenderWindow&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_text :std::false_type {};

template<typename T>
struct has_on_text<T, std::void_t<decltype(std::declval<T>().on_text(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::TextEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_mouse_wheel_scroll :std::false_type {};

template<typename T>
struct has_on_mouse_wheel_scroll<T, std::void_t<decltype(std::declval<T>().on_mouse_wheel_scroll(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::MouseWheelScrollEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_mouse_button_press :std::false_type {};

template<typename T>
struct has_on_mouse_button_press<T, std::void_t<decltype(std::declval<T>().on_mouse_button_press(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::MouseButtonEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_mouse_button_release :std::false_type {};

template<typename T>
struct has_on_mouse_button_release<T, std::void_t<decltype(std::declval<T>().on_mouse_button_release(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::MouseButtonEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_mouse_move :std::false_type {};

template<typename T>
struct has_on_mouse_move<T, std::void_t<decltype(std::declval<T>().on_mouse_move(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::MouseMoveEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_mouse_enter :std::false_type {};

template<typename T>
struct has_on_mouse_enter<T, std::void_t<decltype(std::declval<T>().on_mouse_enter(std::declval<sf::RenderWindow&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_mouse_leave :std::false_type {};

template<typename T>
struct has_on_mouse_leave<T, std::void_t<decltype(std::declval<T>().on_mouse_leave(std::declval<sf::RenderWindow&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_joystick_button_press :std::false_type {};

template<typename T>
struct has_on_joystick_button_press<T, std::void_t<decltype(std::declval<T>().on_joystick_button_press(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::JoystickButtonEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_joystick_button_release :std::false_type {};

template<typename T>
struct has_on_joystick_button_release<T, std::void_t<decltype(std::declval<T>().on_joystick_button_release(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::JoystickButtonEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_joystick_move :std::false_type {};

template<typename T>
struct has_on_joystick_move<T, std::void_t<decltype(std::declval<T>().on_joystick_move(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::JoystickMoveEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_joystick_connect :std::false_type {};

template<typename T>
struct has_on_joystick_connect<T, std::void_t<decltype(std::declval<T>().on_joystick_connect(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::JoystickConnectEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_joystick_disconnect :std::false_type {};

template<typename T>
struct has_on_joystick_disconnect<T, std::void_t<decltype(std::declval<T>().on_joystick_disconnect(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::JoystickConnectEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_touch_begin :std::false_type {};

template<typename T>
struct has_on_touch_begin<T, std::void_t<decltype(std::declval<T>().on_touch_begin(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::TouchEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_touch_move :std::false_type {};

template<typename T>
struct has_on_touch_move<T, std::void_t<decltype(std::declval<T>().on_touch_move(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::TouchEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_touch_end :std::false_type {};

template<typename T>
struct has_on_touch_end<T, std::void_t<decltype(std::declval<T>().on_touch_end(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::TouchEvent&>()))>> :std::true_type {};

template<typename T, typename = void>
struct has_on_sensor_change :std::false_type {};

template<typename T>
struct has_on_sensor_change<T, std::void_t<decltype(std::declval<T>().on_sensor_change(std::declval<sf::RenderWindow&>(), std::declval<const sf::Event::SensorEvent&>()))>> :std::true_type {};

template<typename T>
struct typeu{};

template<typename T>
void call_poll_start(T& thing) {
	if constexpr(has_on_poll_start<T>::value)
		thing.on_poll_start();
}

template<typename T>
void call_poll_stop(T& thing) {
	if constexpr(has_on_poll_stop<T>::value)
		thing.on_poll_stop();
}

template<typename T>
void call_resize(T& thing, sf::RenderWindow& a, const sf::Event::SizeEvent& b) {
	if constexpr(has_on_resize<T>::value)
		thing.on_resize(a, b);
}

template<typename T>
void call_close(T& thing, sf::RenderWindow& a) {
	if constexpr(has_on_close<T>::value)
		thing.on_close(a);
}

template<typename T>
void call_mouse_button_press(T& thing, sf::RenderWindow& a, const sf::Event::MouseButtonEvent& b) {
	if constexpr(has_on_mouse_button_press<T>::value)
		thing.on_mouse_button_press(a, b);
}

template<typename T>
void call_mouse_button_release(T& thing, sf::RenderWindow& a, const sf::Event::MouseButtonEvent& b) {
	if constexpr(has_on_mouse_button_release<T>::value)
		thing.on_mouse_button_release(a, b);
}

template<typename T>
void call_focus_lost(T& thing, sf::RenderWindow& a) {
	if constexpr(has_on_focus_lost<T>::value)
		thing.on_focus_lost(a);
}

template<typename T>
void call_focus_gained(T& thing, sf::RenderWindow& a) {
	if constexpr(has_on_focus_gained<T>::value)
		thing.on_focus_gained(a);
}

template<typename T>
void call_mouse_move(T& thing, sf::RenderWindow& a, const sf::Event::MouseMoveEvent& b) {
	if constexpr(has_on_mouse_move<T>::value)
		thing.on_mouse_move(a, b);
}

template<typename T>
void call_mouse_wheel_scroll(T& thing, sf::RenderWindow& a, const sf::Event::MouseWheelScrollEvent& b) {
	if constexpr(has_on_mouse_wheel_scroll<T>::value)
		thing.on_mouse_wheel_scroll(a, b);
}

template<typename T>
void call_mouse_enter(T& thing, sf::RenderWindow& a) {
	if constexpr(has_on_mouse_enter<T>::value)
		thing.on_mouse_enter(a);
}

template<typename T>
void call_mouse_leave(T& thing, sf::RenderWindow& a) {
	if constexpr(has_on_mouse_leave<T>::value)
		thing.on_mouse_leave(a);
}

template<typename T>
void call_joystick_button_press(T& thing, sf::RenderWindow& a, const sf::Event::JoystickButtonEvent& b) {
	if constexpr(has_on_joystick_button_press<T>::value)
		thing.on_joystick_button_press(a, b);
}

template<typename T>
void call_joystick_button_release(T& thing, sf::RenderWindow& a, const sf::Event::JoystickButtonEvent& b) {
	if constexpr(has_on_joystick_button_release<T>::value)
		thing.on_joystick_button_release(a, b);
}

template<typename T>
void call_joystick_move(T& thing, sf::RenderWindow& a, const sf::Event::JoystickMoveEvent& b) {
	if constexpr(has_on_joystick_move<T>::value)
		thing.on_joystick_move(a, b);
}

template<typename T>
void call_joystick_connect(T& thing, sf::RenderWindow& a, const sf::Event::JoystickConnectEvent& b) {
	if constexpr(has_on_joystick_connect<T>::value)
		thing.on_joystick_connect(a, b);
}

template<typename T>
void call_joystick_disconnect(T& thing, sf::RenderWindow& a, const sf::Event::JoystickConnectEvent& b) {
	if constexpr(has_on_joystick_disconnect<T>::value)
		thing.on_joystick_disconnect(a, b);
}

template<typename T>
void call_sensor_change(T& thing, sf::RenderWindow& a, const sf::Event::SensorEvent& b) {
	if constexpr(has_on_sensor_change<T>::value)
		thing.on_sensor_change(a, b);
}

template<typename T>
void call_touch_begin(T& thing, sf::RenderWindow& a, const sf::Event::TouchEvent& b) {
	if constexpr(has_on_touch_begin<T>::value)
		thing.on_touch_begin(a, b);
}

template<typename T>
void call_touch_end(T& thing, sf::RenderWindow& a, const sf::Event::TouchEvent& b) {
	if constexpr(has_on_touch_end<T>::value)
		thing.on_touch_end(a, b);
}

template<typename T>
void call_touch_move(T& thing, sf::RenderWindow& a, const sf::Event::TouchEvent& b) {
	if constexpr(has_on_touch_move<T>::value)
		thing.on_touch_move(a, b);
}

template<typename T>
void call_key_press(T& thing, sf::RenderWindow& a, const sf::Event::KeyEvent& b) {
	if constexpr(has_on_key_press<T>::value)
		thing.on_key_press(a, b);
}

template<typename T>
void call_key_release(T& thing, sf::RenderWindow& a, const sf::Event::KeyEvent& b) {
	if constexpr(has_on_key_release<T>::value)
		thing.on_key_release(a, b);
}

template<typename T>
void call_text(T& thing, sf::RenderWindow& a, const sf::Event::TextEvent& b) {
	if constexpr(has_on_text<T>::value)
		thing.on_text(a, b);
}

template<typename ...extensions>
struct sfml_event_handler_extender :extensions... {
protected:
	//try to call on_{event_name} on all the extensions
	//
	void call_on_poll_start() {
		(call_poll_start(static_cast<extensions&>(*this)), ...);
	}
	void call_on_poll_stop() {
		(call_poll_stop(static_cast<extensions&>(*this)), ...);
	}
	
	void call_on_close(sf::RenderWindow& win) {
		(call_close(static_cast<extensions&>(*this), win), ...);
	}

	void call_on_resize(sf::RenderWindow& win, sf::Event::SizeEvent& e) {
		(call_resize(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_focus_gained(sf::RenderWindow& win) {
		(call_focus_gained(static_cast<extensions&>(*this), win), ...);
	}

	void call_on_focus_lost(sf::RenderWindow& win) {
		(call_focus_lost(static_cast<extensions&>(*this), win), ...);
	}

	void call_on_joystick_button_press(sf::RenderWindow& win, sf::Event::JoystickButtonEvent& e) {
		(call_joystick_button_press(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_joystick_button_release(sf::RenderWindow& win, sf::Event::JoystickButtonEvent& e) {
		(call_joystick_button_release(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_joystick_connect(sf::RenderWindow& win, sf::Event::JoystickConnectEvent& e) {
		(call_joystick_connect(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_joystick_disconnect(sf::RenderWindow& win, sf::Event::JoystickConnectEvent& e) {
		(call_joystick_disconnect(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_joystick_move(sf::RenderWindow& win, sf::Event::JoystickMoveEvent& e) {
		(call_joystick_move(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_key_press(sf::RenderWindow& win, sf::Event::KeyEvent& e) {
		(call_key_press(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_key_release(sf::RenderWindow& win, sf::Event::KeyEvent& e) {
		(call_key_release(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_mouse_button_press(sf::RenderWindow& win, sf::Event::MouseButtonEvent& e) {
		(call_mouse_button_press(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_mouse_button_release(sf::RenderWindow& win, sf::Event::MouseButtonEvent& e) {
		(call_mouse_button_release(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_mouse_enter(sf::RenderWindow& win) {
		(call_mouse_enter(static_cast<extensions&>(*this), win), ...);
	}

	void call_on_mouse_leave(sf::RenderWindow& win) {
		(call_mouse_leave(static_cast<extensions&>(*this), win), ...);
	}

	void call_on_mouse_move(sf::RenderWindow& win, sf::Event::MouseMoveEvent& e) {
		(call_mouse_move(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_mouse_wheel_scroll(sf::RenderWindow& win, sf::Event::MouseWheelScrollEvent& e) {
		(call_mouse_wheel_scroll(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_sensor_change(sf::RenderWindow& win, sf::Event::SensorEvent& e) {
		(call_sensor_change(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_text(sf::RenderWindow& win, sf::Event::TextEvent& e) {
		(call_text(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_touch_begin(sf::RenderWindow& win, sf::Event::TouchEvent& e) {
		(call_touch_begin(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_touch_move(sf::RenderWindow& win, sf::Event::TouchEvent& e) {
		(call_touch_move(static_cast<extensions&>(*this), win, e), ...);
	}

	void call_on_touch_end(sf::RenderWindow& win, sf::Event::TouchEvent& e) {
		(call_touch_end(static_cast<extensions&>(*this), win, e), ...);
	}
};


template<typename...extensions>
struct sfml_event_handler :sfml_event_handler_extender<extensions...> {
	sfml_event_handler(sf::RenderWindow& w) :m_window(w) {}

	void poll_stuff() {
		sf::Event e = {};
		this->call_on_poll_start();
		while (m_window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				m_window.close();
				this->call_on_close(window());
				break;
			case sf::Event::Resized:
				this->call_on_resize(window(), e.size);
				break;
			case sf::Event::LostFocus:
				this->call_on_focus_lost(window());
				break;
			case sf::Event::GainedFocus:
				this->call_on_focus_gained(window());
				break;
			case sf::Event::TextEntered:
				this->call_on_text(window(), e.text);
				break;
			case sf::Event::KeyPressed:
				this->call_on_key_press(window(), e.key);
				break;
			case sf::Event::KeyReleased:
				this->call_on_key_release(window(), e.key);
				break;
			case sf::Event::MouseWheelMoved:

				break;
			case sf::Event::MouseWheelScrolled:
				this->call_on_mouse_wheel_scroll(window(), e.mouseWheelScroll);
				break;
			case sf::Event::MouseButtonPressed:
				this->call_on_mouse_button_press(window(), e.mouseButton);
				break;
			case sf::Event::MouseButtonReleased:
				this->call_on_mouse_button_release(window(), e.mouseButton);
				break;
			case sf::Event::MouseMoved:
				this->call_on_mouse_move(window(), e.mouseMove);
				break;
			case sf::Event::MouseEntered:
				this->call_on_mouse_enter(window());
				break;
			case sf::Event::MouseLeft:
				this->call_on_mouse_leave(window());
				break;
			case sf::Event::JoystickButtonPressed:
				this->call_on_joystick_button_press(window(), e.joystickButton);
				break;
			case sf::Event::JoystickButtonReleased:
				this->call_on_joystick_button_release(window(), e.joystickButton);
				break;
			case sf::Event::JoystickMoved:
				this->call_on_joystick_move(window(), e.joystickMove);
				break;
			case sf::Event::JoystickConnected:
				this->call_on_joystick_connect(window(), e.joystickConnect);
				break;
			case sf::Event::JoystickDisconnected:
				this->call_on_joystick_disconnect(window(), e.joystickConnect);
				break;
			case sf::Event::TouchBegan:
				this->call_on_touch_begin(window(), e.touch);
				break;
			case sf::Event::TouchMoved:
				this->call_on_touch_move(window(), e.touch);
				break;
			case sf::Event::TouchEnded:
				this->call_on_touch_end(window(), e.touch);
				break;
			case sf::Event::SensorChanged:
				this->call_on_sensor_change(window(), e.sensor);
				break;
			case sf::Event::Count: break;
			default:;
			}
		}
		this->call_on_poll_stop();
	}
	sf::RenderWindow& window()noexcept { return m_window; }
	const sf::RenderWindow& window()const noexcept { return m_window; }
private:
	sf::RenderWindow& m_window;
};

