#include <FWCS/Controllers/Gravity.hpp>
#include <FWCS/Controllers/ForceReset.hpp>
#include <FWCS/Controllers/MovementForceTransform.hpp>
#include <FWCS/Controllers/Acceleration.hpp>
#include <FWCS/Controllers/Movement.hpp>
#include <FWCS/Controllers/PositionLimit.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Properties/Object.hpp>
#include <FWCS/Properties/PositionLimit.hpp>
#include <FWCS/System.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream> // XXX 

int main() {
	// Initialize graphics.
	sf::RenderWindow render_window( sf::VideoMode( 1024, 768 ), "FWCS Runner Example" );

	// Visible object.
	sf::RectangleShape shape( sf::Vector2f( 50, 50 ) );
	shape.setFillColor( sf::Color::White );

	// Custom view.
	sf::View view = render_window.getDefaultView();

	view.setSize( view.getSize().x, -view.getSize().y );
	render_window.setView( view );

	// Framerate limit.
	render_window.setFramerateLimit( 60 );

	// HUD.
	sf::Text hud_text;

	hud_text.setCharacterSize( 16 );

	// Setup FWCS.
	cs::System system;

	system.create_controller<cs::ctrl::ForceReset>();
	system.create_controller<cs::ctrl::Gravity>();
	system.create_controller<cs::ctrl::MovementForceTransform>();
	system.create_controller<cs::ctrl::Acceleration>();
	system.create_controller<cs::ctrl::Movement>();
	system.create_controller<cs::ctrl::PositionLimit>();

	cs::Entity &entity = system.create_entity( 0 );

	entity.create_property<cs::prop::Object>();
	entity.create_property<cs::prop::Moveable>();

	{
		cs::prop::PositionLimit& limit_property = entity.create_property<cs::prop::PositionLimit>();

		limit_property.set_lower_limit( sf::Vector3f( 0, 0, 0 ) );
		limit_property.set_upper_limit(
			sf::Vector3f(
				static_cast<float>( render_window.getSize().x ),
				static_cast<float>( render_window.getSize().y ),
				0
			)
		);
	}

	entity.find_property<cs::prop::Moveable>()->set_mass( 20.0f );
	entity.find_property<cs::prop::Object>()->set_position( sf::Vector3f( 50.0f, 500.0f, 0.0f ) );

	// Enter loop.
	sf::Event event;
	sf::Clock frametimer;
	sf::Time sim_time;

	while( render_window.isOpen() ) {
		// Read events.
		while( render_window.pollEvent( event ) ) {
			if( event.type == sf::Event::Closed ) {
				render_window.close();
			}
			else if( event.type == sf::Event::KeyPressed ) {
				if( event.key.code == sf::Keyboard::Escape ) {
					render_window.close();
				}
			}
		}

		sf::Time timeslice = frametimer.restart();

		sim_time += timeslice;
		system.run( timeslice );

		// Apply FWCS's entity position to SFML shape.
		shape.setPosition(
			entity.find_property<cs::prop::Object>()->get_position().x,
			entity.find_property<cs::prop::Object>()->get_position().y
		);

		// Rebuild HUD text.
		{
			std::stringstream sstr;

			sstr
				<< "Acceleration:"
				<< " " << entity.find_property<cs::prop::Moveable>()->get_acceleration().x
				<< ", " << entity.find_property<cs::prop::Moveable>()->get_acceleration().y
				<< " m/s^2\n"
				<< "Velocity:"
				<< " " << entity.find_property<cs::prop::Moveable>()->get_velocity().x
				<< ", " << entity.find_property<cs::prop::Moveable>()->get_velocity().y
				<< " m/s\n"
				<< "Simulation time:"
				<< " " << sim_time.asSeconds()
				<< " s\n"
			;

			hud_text.setString( sstr.str() );
		}

		render_window.clear();
		render_window.draw( shape );

		render_window.setView( render_window.getDefaultView() );
		render_window.draw( hud_text );
		render_window.setView( view );

		render_window.display();
	}

	return 0;
}
