#pragma once
#include <functional>
#include <chrono>
#include <array>
#include "sfml_event_handler.h"
#include <thread>
#include <numeric>
#include <optional>
#include <vector>

static constexpr auto nothing = [](auto&&...) {};//so i don't get std::bad_function

struct callbacks {
	//needed cuz of awkward interface if i doin't have these
	void on_key_press_callback(std::function<void(sf::RenderWindow&, const sf::Event::KeyEvent&)> f) {
		on_key_press = std::move(f);
	}

	void on_key_release_callback(std::function<void(sf::RenderWindow&, const sf::Event::KeyEvent&)> f) {
		on_key_release = std::move(f);
	}

	void on_close_callback(std::function<void(sf::RenderWindow&)> f) {
		on_close = std::move(f);
	}

	void on_focus_lost_callback(std::function<void(sf::RenderWindow&)> f) {
		on_focus_lost = std::move(f);
	}

	void on_focus_gained_callback(std::function<void(sf::RenderWindow&)> f) {
		on_focus_gained = std::move(f);
	}

	void on_joystick_button_press_callback(std::function<void(sf::RenderWindow&, const sf::Event::JoystickButtonEvent&)> f) {
		on_joystick_button_press = std::move(f);
	}

	void on_joystick_button_release_callback(std::function<void(sf::RenderWindow&, const sf::Event::JoystickButtonEvent&)> f) {
		on_joystick_button_release = std::move(f);
	}

	void on_joystick_move_callback(std::function<void(sf::RenderWindow&, const sf::Event::JoystickMoveEvent&)> f) {
		on_joystick_move = std::move(f);
	}

	void on_joystick_connect_callback(std::function<void(sf::RenderWindow&, const sf::Event::JoystickConnectEvent&)> f) {
		on_joystick_connect = std::move(f);
	}

	void on_joystick_disconnect_callback(std::function<void(sf::RenderWindow&, const sf::Event::JoystickConnectEvent&)> f) {
		on_joystick_disconnect = std::move(f);
	}

	void on_mouse_button_press_callback(std::function<void(sf::RenderWindow&, const sf::Event::MouseButtonEvent&)> f) {
		on_mouse_button_press = std::move(f);
	}

	void on_mouse_button_release_callback(std::function<void(sf::RenderWindow&, const sf::Event::MouseButtonEvent&)> f) {
		on_mouse_button_release = std::move(f);
	}

	void on_mouse_move_callback(std::function<void(sf::RenderWindow&, const sf::Event::MouseMoveEvent&)> f) {
		on_mouse_move = std::move(f);
	}

	void on_mouse_wheel_scroll_callback(std::function<void(sf::RenderWindow&, const sf::Event::MouseWheelScrollEvent&)> f) {
		on_mouse_wheel_scroll = std::move(f);
	}

	void on_resize_callback(std::function<void(sf::RenderWindow&, const sf::Event::SizeEvent&)> f) {
		on_resize = std::move(f);
	}

	void on_sensor_change_callback(std::function<void(sf::RenderWindow&, const sf::Event::SensorEvent&)> f) {
		on_sensor_change = std::move(f);
	}

	void on_text_callback(std::function<void(sf::RenderWindow&, const sf::Event::TextEvent&)> f) {
		on_text = std::move(f);
	}

	void on_touch_begin_callback(std::function<void(sf::RenderWindow&, const sf::Event::TouchEvent&)> f) {
		on_touch_begin = std::move(f);
	}

	void on_touch_move_callback(std::function<void(sf::RenderWindow&, const sf::Event::TouchEvent&)> f) {
		on_touch_move = std::move(f);
	}

	void on_touch_end_callback(std::function<void(sf::RenderWindow&, const sf::Event::TouchEvent&)> f) {
		on_touch_end = std::move(f);
	}
	//get
	const auto& on_key_press_callback()const noexcept{
		return on_key_press;
	}

	const auto& on_key_release_callback()const noexcept {
		return on_key_release;
	}

	const auto& on_close_callback()const noexcept {
		return on_close;
	}

	const auto& on_focus_lost_callback() const noexcept {
		return on_focus_lost;
	}

	const auto& on_focus_gained_callback()const noexcept {
		return on_focus_gained;
	}

	const auto& on_joystick_button_press_callback()const noexcept {
		return on_joystick_button_press;
	}

	const auto& on_joystick_button_release_callback()const noexcept {
		return on_joystick_button_release;
	}

	const auto& on_joystick_move_callback() const noexcept {
		return on_joystick_move;
	}

	const auto& on_joystick_connect_callback()const noexcept {
		return on_joystick_connect;
	}

	const auto& on_joystick_disconnect_callback() const noexcept {
		return on_joystick_disconnect;
	}

	const auto& on_mouse_button_press_callback()const noexcept {
		return on_mouse_button_press;
	}

	const auto& on_mouse_button_release_callback()const noexcept {
		return on_mouse_button_release;
	}

	const auto& on_mouse_move_callback() const noexcept {
		return on_mouse_move;
	}

	const auto& on_mouse_wheel_scroll_callback() const noexcept {
		return on_mouse_wheel_scroll;
	}

	const auto& on_resize_callback() const noexcept {
		return on_resize;
	}

	const auto& on_sensor_change_callback() const noexcept {
		return on_sensor_change;
	}

	const auto& on_text_callback() const noexcept {
		return on_text;
	}

	const auto& on_touch_begin_callback() const noexcept {
		return on_touch_begin;
	}

	const auto& on_touch_move_callback() const noexcept {
		return on_touch_move;
	}

	const auto& on_touch_end_callback() const noexcept {
		return on_touch_end;
	}

	//need to be public so it doesn't get sfinae'd ;-;

	std::function<void(sf::RenderWindow&, const sf::Event::KeyEvent&)> on_key_press = nothing;//so i don't get std::bad_function
	std::function<void(sf::RenderWindow&, const sf::Event::KeyEvent&)> on_key_release = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::TextEvent&)> on_text = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::MouseButtonEvent&)> on_mouse_button_press = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::MouseButtonEvent&)> on_mouse_button_release = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::MouseWheelScrollEvent&)> on_mouse_wheel_scroll = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::MouseMoveEvent&)> on_mouse_move = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::TouchEvent&)> on_touch_begin = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::TouchEvent&)> on_touch_move = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::TouchEvent&)> on_touch_end = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::SizeEvent&)> on_resize = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::JoystickButtonEvent&)> on_joystick_button_press = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::JoystickButtonEvent&)> on_joystick_button_release = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::JoystickConnectEvent&)> on_joystick_connect = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::JoystickConnectEvent&)> on_joystick_disconnect = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::JoystickMoveEvent&)> on_joystick_move = nothing;
	std::function<void(sf::RenderWindow&, const sf::Event::SensorEvent&)> on_sensor_change = nothing;

	std::function<void(sf::RenderWindow&)> on_mouse_enter = nothing;
	std::function<void(sf::RenderWindow&)> on_mouse_leave = nothing;
	std::function<void(sf::RenderWindow&)> on_focus_lost = nothing;
	std::function<void(sf::RenderWindow&)> on_focus_gained = nothing;
	std::function<void(sf::RenderWindow&)> on_close = nothing;
};

struct track_mouse_pos {
	void on_mouse_move(sf::RenderWindow&, sf::Event::MouseMoveEvent e) {
		m_pos.x = e.x;
		m_pos.y = e.y;
	}
	sf::Vector2i mouse_pos()const noexcept {
		return m_pos;
	}
private:
	sf::Vector2i m_pos;
};

template<typename clock = std::chrono::steady_clock>
struct track_poll_times{	
	using time_point = typename clock::time_point;

	void on_poll_start() noexcept {
		m_times.front() = m_times.back();
		m_times.back() = clock::now();
	}

	template<typename duration = std::chrono::milliseconds>
	duration time_since_last_poll() const noexcept {
		return std::chrono::duration_cast<duration>(m_times.back() - m_times.front());
	}

	const time_point& time_of_last_poll()const noexcept {
		return m_times.back();
	}

	const time_point& prev_time_of_last_poll()const noexcept {
		return m_times.front();
	}
private:
	std::array<time_point, 2> m_times = { clock::now() };
};

template<typename clock = std::chrono::steady_clock>
struct track_hold_times:track_poll_times<clock> {	
	using time_point = typename clock::time_point;
		
	void on_key_press(sf::RenderWindow&, const sf::Event::KeyEvent& e) noexcept{
		m_keyboard_counts[e.code] = this->time_of_last_poll();
	}

	void on_key_release(sf::RenderWindow&,const sf::Event::KeyEvent& e) noexcept{
		m_keyboard_counts[e.code] = std::nullopt;
	}

	//may be inaccurate due to rounding, use is_held to see if it's held
	template<typename duration = std::chrono::milliseconds>
	duration held_for(const sf::Keyboard::Key key) const noexcept{
		if (m_keyboard_counts[key])
			return std::chrono::duration_cast<duration>(this->time_of_last_poll() - *m_keyboard_counts[(size_t)key]);
		return duration{0};
	}

	std::optional<time_point> held_since(sf::Keyboard::Key key) const noexcept {
		return m_keyboard_counts[key];
	}

	void on_mouse_button_press(sf::RenderWindow&, const sf::Event::MouseButtonEvent& e) noexcept {
		m_mouse_button_counts[e.button] = this->time_of_last_poll();
	}
	void on_mouse_button_release(sf::RenderWindow&, const sf::Event::MouseButtonEvent& e) noexcept {
		m_mouse_button_counts[e.button] = std::nullopt;
	}
	//may be 0 even when button is held, use is_held to see if it's held
	template<typename duration = std::chrono::milliseconds>
	duration held_for(const sf::Mouse::Button button) const noexcept {
		if (m_mouse_button_counts[button])
			return std::chrono::duration_cast<duration>(this->time_of_last_poll() - *m_mouse_button_counts[(size_t)button]);
		return duration{0};
	}

	std::optional<time_point> held_since(const sf::Mouse::Button button) const noexcept {
		return m_keyboard_counts[button];
	}

	bool is_held(const sf::Keyboard::Key key)const noexcept {
		return m_keyboard_counts[key].has_value();
	}

	bool is_held(const sf::Mouse::Button button) const noexcept {
		return m_mouse_button_counts[button].has_value();
	}

private:
	std::array<std::optional<time_point>, (size_t)sf::Keyboard::Key::KeyCount> m_keyboard_counts = {};
	std::array<std::optional<time_point>, (size_t)sf::Mouse::Button::ButtonCount> m_mouse_button_counts = {};
};

struct extension_obj{
	template<typename T>
	extension_obj(T thing):m_self(std::make_unique<model<T>>(std::move(thing))){}
		
	template<typename T>
	extension_obj& operator=(T thing) {
		m_self = std::make_unique<model<T>>(std::move(thing)); 
		return *this;
	}

	void on_close(sf::RenderWindow& a) const{ m_self->on_close(a); }
	void on_focus_gained(sf::RenderWindow& a) const { m_self->on_focus_gained(a); }
	void on_focus_lost(sf::RenderWindow& a) const { m_self->on_focus_lost(a); }
	void on_joystick_button_press(sf::RenderWindow& a, const sf::Event::JoystickButtonEvent& b)const { m_self->on_joystick_button_press(a, b); }
	void on_joystick_button_release(sf::RenderWindow& a, const sf::Event::JoystickButtonEvent& b) const { m_self->on_joystick_button_release(a, b); }
	void on_joystick_move(sf::RenderWindow& a, const sf::Event::JoystickMoveEvent& b)const { m_self->on_joystick_move(a, b); }
	void on_joystick_connect(sf::RenderWindow& a, const sf::Event::JoystickConnectEvent& b) const { m_self->on_joystick_connect(a, b); }
	void on_joystick_disconnect(sf::RenderWindow& a, const sf::Event::JoystickConnectEvent& b)const { m_self->on_joystick_disconnect(a, b); }
	void on_key_press(sf::RenderWindow& a, const sf::Event::KeyEvent& b) const { m_self->on_key_press(a, b); }
	void on_key_release(sf::RenderWindow& a, const sf::Event::KeyEvent& b) const { m_self->on_key_release(a, b); }
	void on_mouse_button_press(sf::RenderWindow& a, const sf::Event::MouseButtonEvent& b)const { m_self->on_mouse_button_press(a, b); }
	void on_mouse_button_release(sf::RenderWindow& a, const sf::Event::MouseButtonEvent& b)const { m_self->on_mouse_button_release(a, b); }
	void on_mouse_enter(sf::RenderWindow& a)const { m_self->on_mouse_enter(a); }
	void on_mouse_leave(sf::RenderWindow& a)const { m_self->on_mouse_leave(a); }
	void on_mouse_move(sf::RenderWindow& a, const sf::Event::MouseMoveEvent& b)const { m_self->on_mouse_move(a, b); }
	void on_mouse_wheel_scroll(sf::RenderWindow& a, const sf::Event::MouseWheelScrollEvent& b) const { m_self->on_mouse_wheel_scroll(a, b); }
	void on_poll_start() const { m_self->on_poll_start(); }
	void on_poll_stop()const { m_self->on_poll_stop(); }
	void on_resize(sf::RenderWindow& a, const sf::Event::SizeEvent& b)const { m_self->on_resize(a, b); }
	void on_sensor_change(sf::RenderWindow& a, const sf::Event::SensorEvent& b)const { m_self->on_sensor_change(a, b); }
	void on_text(sf::RenderWindow& a, const sf::Event::TextEvent& b)const { m_self->on_text(a, b); }
	void on_touch_begin(sf::RenderWindow& a, const sf::Event::TouchEvent& b)const { m_self->on_touch_begin(a, b); }
	void on_touch_move(sf::RenderWindow& a, const sf::Event::TouchEvent& b)const { m_self->on_touch_move(a, b); }
	void on_touch_end(sf::RenderWindow& a, const sf::Event::TouchEvent& b)const { m_self->on_touch_end(a,b); }

	template<typename U>
	auto get_as() {
		return static_cast<U*>(m_self->me());
	}

	template<typename U>
	auto get_as() const{
		return static_cast<const U*>(m_self->me());
	}

private:
	struct concept_{
		concept_() = default;
		concept_(concept_&&) = default;
		concept_(const concept_&) = default;
		concept_& operator=(concept_&&) = default;
		concept_& operator=(const concept_&) = default;
		virtual ~concept_() = default;

		virtual void on_close(sf::RenderWindow&) = 0;
		virtual void on_focus_gained(sf::RenderWindow&) = 0;
		virtual void on_focus_lost(sf::RenderWindow&) = 0;
		virtual void on_joystick_button_press(sf::RenderWindow&, const sf::Event::JoystickButtonEvent&) = 0;
		virtual void on_joystick_button_release(sf::RenderWindow&, const sf::Event::JoystickButtonEvent&) = 0;
		virtual void on_joystick_move(sf::RenderWindow&, const sf::Event::JoystickMoveEvent&) = 0;
		virtual void on_joystick_connect(sf::RenderWindow&,const sf::Event::JoystickConnectEvent&) = 0;
		virtual void on_joystick_disconnect(sf::RenderWindow&, const sf::Event::JoystickConnectEvent&) = 0;
		virtual void on_key_press(sf::RenderWindow&,const sf::Event::KeyEvent&) = 0;
		virtual void on_key_release(sf::RenderWindow&, const sf::Event::KeyEvent&) = 0;
		virtual void on_mouse_button_press(sf::RenderWindow&,const sf::Event::MouseButtonEvent&) = 0;
		virtual void on_mouse_button_release(sf::RenderWindow&, const sf::Event::MouseButtonEvent&) = 0;
		virtual void on_mouse_enter(sf::RenderWindow&) = 0;
		virtual void on_mouse_leave(sf::RenderWindow&) = 0;
		virtual void on_mouse_move(sf::RenderWindow&,const sf::Event::MouseMoveEvent&) = 0;
		virtual void on_mouse_wheel_scroll(sf::RenderWindow&,const sf::Event::MouseWheelScrollEvent&) = 0;
		virtual void on_poll_start() = 0;
		virtual void on_resize(sf::RenderWindow&,const sf::Event::SizeEvent&) = 0;
		virtual void on_sensor_change(sf::RenderWindow&,const sf::Event::SensorEvent&) = 0;
		virtual void on_text(sf::RenderWindow&,const sf::Event::TextEvent&) = 0;
		virtual void on_touch_begin(sf::RenderWindow&,const sf::Event::TouchEvent&) = 0;
		virtual void on_touch_move(sf::RenderWindow&, const sf::Event::TouchEvent&) = 0;
		virtual void on_touch_end(sf::RenderWindow&, const sf::Event::TouchEvent&) = 0;
		virtual void on_poll_stop() = 0;
		virtual void* me() = 0;
	};
	template<typename T>
	struct model final:concept_{
		model(T s):self(std::move(s)){}
		void on_close(sf::RenderWindow& a)override final { call_close(self, a); }
		void on_focus_gained(sf::RenderWindow& a)override final { call_focus_gained(self, a); }
		void on_focus_lost(sf::RenderWindow& a)override final { call_focus_lost(self, a); }
		void on_joystick_button_press(sf::RenderWindow& a, const sf::Event::JoystickButtonEvent& b) override final { call_joystick_button_press(self, a, b); }
		void on_joystick_button_release(sf::RenderWindow& a, const sf::Event::JoystickButtonEvent& b)override final { call_joystick_button_release(self, a, b); }
		void on_joystick_move(sf::RenderWindow& a, const sf::Event::JoystickMoveEvent& b)override final { call_joystick_move(self, a, b); }
		void on_joystick_connect(sf::RenderWindow& a, const sf::Event::JoystickConnectEvent& b)override final { call_joystick_connect(self, a, b); }
		void on_joystick_disconnect(sf::RenderWindow& a, const sf::Event::JoystickConnectEvent& b) override final { call_joystick_disconnect(self, a, b); }
		void on_key_press(sf::RenderWindow& a, const sf::Event::KeyEvent& b)override final { call_key_press(self, a, b); }
		void on_key_release(sf::RenderWindow& a, const sf::Event::KeyEvent& b) override final { call_key_release(self, a, b); }
		void on_mouse_button_press(sf::RenderWindow& a, const sf::Event::MouseButtonEvent& b) override final { call_mouse_button_press(self, a, b); }
		void on_mouse_button_release(sf::RenderWindow& a, const sf::Event::MouseButtonEvent& b)override final { call_mouse_button_release(self, a, b); }
		void on_mouse_enter(sf::RenderWindow& a) override final { call_mouse_enter(self, a); }
		void on_mouse_leave(sf::RenderWindow& a)override final { call_mouse_leave(self, a); }
		void on_mouse_move(sf::RenderWindow& a, const sf::Event::MouseMoveEvent& b) override final { call_mouse_move(self, a, b); }
		void on_mouse_wheel_scroll(sf::RenderWindow& a, const sf::Event::MouseWheelScrollEvent& b)override final { call_mouse_wheel_scroll(self, a, b); }
		void on_poll_start() override final { call_poll_start(self); }
		void on_poll_stop() override final { call_poll_stop(self); }
		void on_resize(sf::RenderWindow& a, const sf::Event::SizeEvent& b) override final { call_resize(self, a, b); }
		void on_sensor_change(sf::RenderWindow& a, const sf::Event::SensorEvent& b) override final { call_sensor_change(self, a, b); }
		void on_text(sf::RenderWindow& a, const sf::Event::TextEvent& b) override final { call_text(self, a, b); }
		void on_touch_begin(sf::RenderWindow& a, const sf::Event::TouchEvent& b)override final { call_touch_begin(self, a, b); }
		void on_touch_move(sf::RenderWindow& a, const sf::Event::TouchEvent& b)override final { call_touch_move(self, a, b); }
		void on_touch_end(sf::RenderWindow& a, const sf::Event::TouchEvent& b)override final { call_touch_end(self, a, b);}
		void* me()final {
			return &self;
		};
		T self;
	};

	std::unique_ptr<concept_> m_self = nullptr;//no sbo
};

struct dynamic_extensions{
	void on_poll_start() { for (auto& i : m_extensions)i.on_poll_start(); }
	void on_poll_stop() { for (auto& i : m_extensions)i.on_poll_stop(); }
	void on_close(sf::RenderWindow& a){ for (auto& i : m_extensions)i.on_close(a); }
	void on_focus_gained(sf::RenderWindow& a) const { for (auto& i : m_extensions)i.on_focus_gained(a); }
	void on_focus_lost(sf::RenderWindow& a) const { for (auto& i : m_extensions)i.on_focus_lost(a); }
	void on_joystick_button_press(sf::RenderWindow& a, const sf::Event::JoystickButtonEvent& b) { for (auto& i : m_extensions)i.on_joystick_button_press(a, b); }
	void on_joystick_button_release(sf::RenderWindow& a, const sf::Event::JoystickButtonEvent& b)  { for (auto& i : m_extensions)i.on_joystick_button_release(a, b); }
	void on_joystick_move(sf::RenderWindow& a, const sf::Event::JoystickMoveEvent& b) { for (auto& i : m_extensions)i.on_joystick_move(a, b); }
	void on_joystick_connect(sf::RenderWindow& a, const sf::Event::JoystickConnectEvent& b)  { for (auto& i : m_extensions)i.on_joystick_connect(a, b); }
	void on_joystick_disconnect(sf::RenderWindow& a, const sf::Event::JoystickConnectEvent& b) { for (auto& i : m_extensions)i.on_joystick_disconnect(a, b); }
	void on_key_press(sf::RenderWindow& a, const sf::Event::KeyEvent& b) { for (auto& i : m_extensions)i.on_key_press(a, b); }
	void on_key_release(sf::RenderWindow& a, const sf::Event::KeyEvent& b)  { for (auto& i : m_extensions)i.on_key_release(a, b);; }
	void on_mouse_button_press(sf::RenderWindow& a, const sf::Event::MouseButtonEvent& b) { for (auto& i : m_extensions)i.on_mouse_button_press(a, b); }
	void on_mouse_button_release(sf::RenderWindow& a, const sf::Event::MouseButtonEvent& b) { for (auto& i : m_extensions)i.on_mouse_button_release(a,b); }
	void on_mouse_enter(sf::RenderWindow& a) { for (auto& i : m_extensions)i.on_mouse_enter(a); }
	void on_mouse_leave(sf::RenderWindow& a) { for (auto& i : m_extensions)i.on_mouse_leave(a); }
	void on_mouse_move(sf::RenderWindow& a, const sf::Event::MouseMoveEvent& b) { for (auto& i : m_extensions)i.on_mouse_move(a, b); }
	void on_mouse_wheel_scroll(sf::RenderWindow& a, const sf::Event::MouseWheelScrollEvent& b)  { for (auto& i : m_extensions)i.on_mouse_wheel_scroll(a, b); }
	void on_resize(sf::RenderWindow& a, const sf::Event::SizeEvent& b) { for (auto& i : m_extensions)i.on_resize(a, b); }
	void on_sensor_change(sf::RenderWindow& a, const sf::Event::SensorEvent& b) { for (auto& i : m_extensions)i.on_sensor_change(a, b); }
	void on_text(sf::RenderWindow& a, const sf::Event::TextEvent& b) { for (auto& i : m_extensions)i.on_text(a, b); }
	void on_touch_begin(sf::RenderWindow& a, const sf::Event::TouchEvent& b) { for (auto& i : m_extensions)i.on_touch_begin(a, b); }
	void on_touch_move(sf::RenderWindow& a, const sf::Event::TouchEvent& b) { for (auto& i : m_extensions)i.on_touch_move(a, b); }
	void on_touch_end(sf::RenderWindow& a, const sf::Event::TouchEvent& b) { for (auto& i : m_extensions)i.on_touch_end(a, b); }
	
	template<typename T>
	[[maybe_unused]]
	T* push(T&& thing) {
		m_extensions.emplace_back(std::forward<T>(thing));
		return m_extensions.back().get_as<T>();
	}

	[[maybe_unused]]
	bool erase(void* thing) {
		const auto it = std::find_if(m_extensions.begin(), m_extensions.end(), [&](const extension_obj& i) {return i.get_as<void>() == thing; });
		if (it == m_extensions.end())
			return false;
		std::swap(*it,m_extensions.back());
		m_extensions.pop_back();
		return true;
	}

	template<typename T>
	[[maybe_unused]]
	bool erase(const T& thing) {
		return erase((void*)&thing);
	}
private:
	std::vector<extension_obj> m_extensions;
};

template<typename duration>
struct time_point_difference_t{
	template<typename time_point>
	constexpr duration operator()(const time_point& a,const time_point& b)const noexcept{
		return std::chrono::duration_cast<duration>(b - a);
	}
};

template<typename D>
static constexpr time_point_difference_t<D> time_point_difference = {};

template<int frame_cache_size = 5> 
struct fps_tracker{
	fps_tracker() {
		std::fill(m_frames_starts.begin(), m_frames_starts.end(), std::chrono::steady_clock::now());
	}
	void on_poll_stop() {
		std::rotate(m_frames_starts.begin(), m_frames_starts.begin() + 1, m_frames_starts.end());//shift left
		m_frames_starts.back() = std::chrono::steady_clock::now();
	}
	
	double avg_fps()const noexcept{
		using namespace std::literals;
		return (frame_cache_size-1) *std::nano::den/static_cast<double>(std::inner_product(m_frames_starts.begin(), m_frames_starts.end() - 1, m_frames_starts.begin() + 1, 0us,
			std::plus<>{},
			time_point_difference<std::chrono::nanoseconds>).count());
		//m_frames[i + 1] - m_frames[i]for all i in [0,frame_cache_size) doesn't include the last element since m_frames[last+1] is an error
		//frame_cache_size since frame_cache_size-0 = frame_cache_size
		//inner_product returns nanoseconds
		//we want 1/seconds
		//equivalent to adjacent_difference then divide
		/*
		std::array<std::chrono::nanoseconds, frame_cache_size - 1> diffs;
		std::adjacent_difference(m_frames_starts.begin(), m_frames_starts.end(), diffs, time_point_difference<std::chrono::nanoseconds>);
		const double d = std::accumulate(diffs.begin(), diffs.end(), 0.0, [](const auto& t) {return t.count(); })/diffs.size();
		return d * std::nano::den;
		*/
	}

private:
	std::array<std::chrono::steady_clock::time_point, frame_cache_size> m_frames_starts = {};
};

static_assert(has_on_poll_stop<fps_tracker<>>::value);

/*
inline void asduohgasdjkA() {
	sf::RenderWindow win;
	sfml_event_handler<callbacks, track_hold_times<std::chrono::steady_clock>, track_mouse_pos> event_handler(win);

	event_handler.on_key_press_callback([&](sf::RenderWindow& window,sf::Event::KeyEvent k){
		//do something
	});

	while (win.isOpen()) {
		event_handler.poll_stuff();

		auto held_for = event_handler.held_for<std::chrono::milliseconds>(sf::Keyboard::Key::A);
		auto uio = event_handler.held_since(sf::Keyboard::Key::T);
		if(held_for>2ms) {
			
		}
		auto u = event_handler.mouse_pos();
		win.clear();
		//draw
		win.display();
	}
}
*/