#include <SFML/Graphics.hpp>
#include <iostream>
#include "sfml_event_handler_extensions.h"
#include <boost/geometry.hpp>
#include <random>
#include <mutex>
#include <atomic>

using point2d = boost::geometry::model::d2::point_xy<double>;
using polygon2d = boost::geometry::model::polygon<point2d>;
using box2d = boost::geometry::model::box<point2d>;

struct ship{
	ship() {
		shape.outer() = { {100,400},{130,415},{100,430} };
	}
	polygon2d shape;
};

struct astroid{
	polygon2d shape;
	double vel = 0;
};

box2d bounding_box(const polygon2d& poly) {
	double min_x = poly.outer()[0].x();
	double max_x = poly.outer()[0].x();
	double min_y = poly.outer()[0].y();
	double max_y = poly.outer()[0].y();

	for(const auto& point:poly.outer()) {
		max_x = std::max(point.x(), max_x);
		min_x = std::min(point.x(), min_x);
		max_y = std::max(point.y(), max_y);
		min_y = std::min(point.y(), min_y);
	}
	return box2d({ min_x,min_y }, { max_x,max_y });
}

void draw_fill(sf::RenderWindow& window,const polygon2d& poly, const sf::Color fill,const sf::Color outline = sf::Color::Black) {	
	sf::ConvexShape shapey;
	shapey.setPointCount(poly.outer().size());
	for(int i = 0;i<(int)poly.outer().size();++i){
		shapey.setPoint(i, sf::Vector2f((float)poly.outer()[i].x(), (float)poly.outer()[i].y()));
	}
	shapey.setFillColor(fill);
	shapey.setOutlineColor(outline);
	
	window.draw(shapey);
}

void move_shape(polygon2d& poly, const double dx,const double dy) {
	if (dx == 0 && dy == 0)	return;
	for(auto& point:poly.outer()) 
		point = point2d(point.x() + dx, point.y() + dy);
	
	for (auto& ring : poly.inners())
		for(auto& point:ring)
			point = point2d(point.x() + dx, point.y() + dy);	
}

struct astroid_spawner {
	int min_x = 0;
	int max_x = 0;

	int min_y = 0;
	int max_y = 0;

	double min_radius = 0;
	double max_radius = 0;

	int num_points_min = 0;
	int num_points_max = 0;

	double min_vel = 0;
	double max_vel = 0;
	template<typename engine_t>
	astroid get(engine_t&& engine){
		std::uniform_int_distribution<int> x_distribution(min_x, max_x);
		std::uniform_int_distribution<int> y_distribution(min_y, max_y);
		std::uniform_int_distribution<int> num_points_distribution(15,20);
		std::uniform_real_distribution<double> vel_dist(min_vel, max_vel);
		const int x = x_distribution(engine);
		const int y = y_distribution(engine);
		
		std::uniform_real_distribution<double> r_distribution(min_radius, max_radius);
		std::normal_distribution<> dist2(r_distribution(engine));
		polygon2d poly;
		const auto num_points = num_points_distribution(engine);
		poly.outer().reserve(num_points);

		const double d_theta = 2 * 3.1415926535 / (num_points + 1);
		for(int i = 0;i<num_points;++i) {
			const double r = dist2(engine);
			poly.outer().emplace_back(x + r * cos(d_theta*i), y + r * sin(d_theta*i));
		}
		return astroid{ std::move(poly), vel_dist(engine) };
	}
};
using namespace std::literals;
int main() {
	sf::RenderWindow win(sf::VideoMode(800, 800), "");
	win.setFramerateLimit(60);
	sfml_event_handler<track_hold_times<>> event_thing(win);
	
	ship shipy;

	const double vel = 0.125;
	auto spawner = astroid_spawner();

	spawner.min_radius = 5;
	spawner.max_radius = 15;
	spawner.min_x = 800;
	spawner.max_x = 900;
	spawner.min_y = 0;
	spawner.max_y = 800;
	spawner.min_vel = 0.05;
	spawner.max_vel = 0.2;

	std::vector<astroid> roids;	
	std::mutex roids_mut;
	std::atomic<bool> is_done = false;

	std::thread th = std::thread([&](){
		std::mt19937 engine(std::random_device{}());
		while (!is_done.load(std::memory_order_relaxed)) {
			std::this_thread::sleep_for(500ms);
			auto t = spawner.get(engine);			
			std::lock_guard lock{ roids_mut };
			roids.push_back(std::move(t));
		}
	});
	box2d game_screen_bounds ({ {0,0},{1000,1000} });

	std::function<void()> update = [&](){
		const double real_vel = vel + vel * (event_thing.is_held(sf::Keyboard::LShift) || event_thing.is_held(sf::Keyboard::RShift));
		double dx = 0;
		double dy = 0;
		const auto update_difference = event_thing.time_since_last_poll().count();
		if (event_thing.is_held(sf::Keyboard::A)) 
			dx += -real_vel * update_difference;
		if (event_thing.is_held(sf::Keyboard::W)) 
			dy += -real_vel * update_difference;		
		if (event_thing.is_held(sf::Keyboard::S)) 
			dy += real_vel * update_difference;		
		if (event_thing.is_held(sf::Keyboard::D)) 
			dx += real_vel * update_difference;		

		boost::geometry::strategy::transform::translate_transformer<double, 2, 2> trasformer(dx, dy);
		polygon2d res;
		res.outer().reserve(shipy.shape.outer().size());
		boost::geometry::transform(shipy.shape, res, trasformer);

		if (boost::geometry::intersects(res, game_screen_bounds))
			std::swap(res, shipy.shape);

		win.clear(sf::Color::White);
		draw_fill(win, shipy.shape, sf::Color::Green, sf::Color::Black);

		const auto ship_bounds = bounding_box(shipy.shape);
		std::lock_guard lock{ roids_mut };//this can block the spawner thread for a while, but it doesn't matter
		for (int i = (int)roids.size() - 1; i >=0; --i) {//i can do swap-pop_back trick when iterating in reverse
			auto& roid = roids[i];
			move_shape(roid.shape, -roid.vel * update_difference, 0);
			const auto roid_bounds = bounding_box(roid.shape);
			if(!boost::geometry::intersects(roid_bounds, game_screen_bounds)) {
				std::swap(roid, roids.back());
				roids.pop_back();
			}else if(boost::geometry::intersects(roid_bounds, ship_bounds) && //box-box intersects is much faster than polygon-polygon
					 boost::geometry::intersects(roid.shape, shipy.shape)) {
				is_done.store(true, std::memory_order_relaxed);
				win.clear(sf::Color::White);
				update = []() {};
			}else draw_fill(win, roid.shape, sf::Color::Blue);
		}
	};

	while(win.isOpen()) {
		event_thing.poll_stuff();

		update();

		win.display();
	}

	is_done.store(true, std::memory_order_relaxed);
	th.join();
	//*/
}

