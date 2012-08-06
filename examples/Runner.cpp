#include <FWCS/Controllers/Gravity.hpp>
#include <FWCS/Controllers/ForceReset.hpp>
#include <FWCS/Controllers/MovementForceTransform.hpp>
#include <FWCS/Controllers/Acceleration.hpp>
#include <FWCS/Controllers/Movement.hpp>
#include <FWCS/Controllers/PositionLimit.hpp>
#include <FWCS/Controllers/Drag.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Properties/Object.hpp>
#include <FWCS/Properties/PositionLimit.hpp>
#include <FWCS/Properties/Environment.hpp>
#include <FWCS/Properties/Drag.hpp>
#include <FWCS/System.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream> // XXX 

static const float SCALE_FACTOR = 50.0f; // X pixels = 1 meter.

int main() {
	// Initialize graphics.
	sf::RenderWindow render_window( sf::VideoMode( 1024, 768 ), "FWCS Runner Example" );

	// Visible object.
	sf::RectangleShape shape( sf::Vector2f( 0.5f * SCALE_FACTOR, 1.75f * SCALE_FACTOR ) );
	shape.setFillColor( sf::Color::White );

	// Framerate limit.
	render_window.setFramerateLimit( 60 );

	// HUD.
	sf::Text hud_text;

	hud_text.setCharacterSize( 16 );

	// Setup FWCS.
	cs::System system;

	system.create_controller<cs::ctrl::ForceReset>();
	system.create_controller<cs::ctrl::Gravity>();
	system.create_controller<cs::ctrl::Drag>();
	system.create_controller<cs::ctrl::MovementForceTransform>();
	system.create_controller<cs::ctrl::Acceleration>();
	system.create_controller<cs::ctrl::Movement>();
	system.create_controller<cs::ctrl::PositionLimit>();

	cs::Entity &entity = system.create_entity( 0 );

	entity.create_property<cs::prop::Object>();
	entity.create_property<cs::prop::Moveable>();
	entity.create_property<cs::prop::Environment>();

	{
		cs::prop::PositionLimit& limit_property = entity.create_property<cs::prop::PositionLimit>();

		limit_property.set_lower_limit( sf::Vector3f( 0, 0, 0 ) );
		limit_property.set_upper_limit(
			sf::Vector3f(
				static_cast<float>( render_window.getSize().x ),
				999999.0f,
				0
			)
		);
	}
	{
		cs::prop::Drag& drag_property = entity.create_property<cs::prop::Drag>();

		drag_property.set_area( 0.5f * 0.2f );
		drag_property.set_resistance_coeff( 0.78f );
	}

	entity.find_property<cs::prop::Moveable>()->set_mass( 50.0f );
	entity.find_property<cs::prop::Object>()->set_position( sf::Vector3f( 1.0f, 10.0f, 0.0f ) );

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

		// Apply FWCS's entity position to SFML shape. Apply a factor for scaling.
		shape.setPosition(
			entity.find_property<cs::prop::Object>()->get_position().x * SCALE_FACTOR,
			(
				static_cast<float>( render_window.getSize().y ) -
				(
				 entity.find_property<cs::prop::Object>()->get_position().y * SCALE_FACTOR
				) -
				shape.getGlobalBounds().height
			)
		);

		// Rebuild HUD text.
		{
			std::stringstream sstr;

			sstr
				<< std::fixed
				<< "Acceleration:"
				<< " " << entity.find_property<cs::prop::Moveable>()->get_acceleration().x
				<< ", " << entity.find_property<cs::prop::Moveable>()->get_acceleration().y
				<< " m/s^2\n"
				<< "Velocity:"
				<< " " << entity.find_property<cs::prop::Moveable>()->get_velocity().x
				<< ", " << entity.find_property<cs::prop::Moveable>()->get_velocity().y
				<< " m/s"
				<< " (" << entity.find_property<cs::prop::Moveable>()->get_velocity().x / 1000.0f * 60.0f * 60.0f
				<< ", " << entity.find_property<cs::prop::Moveable>()->get_velocity().y / 1000.0f * 60.0f * 60.0f
				<< " km/h)\n"
				<< "Position:"
				<< " " << entity.find_property<cs::prop::Object>()->get_position().x
				<< ", " << entity.find_property<cs::prop::Object>()->get_position().y
				<< " m\n"
				<< "Simulation time:"
				<< " " << sim_time.asSeconds()
				<< " s\n"
			;

			hud_text.setString( sstr.str() );
		}

		render_window.clear();
		render_window.draw( shape );
		render_window.draw( hud_text );

		render_window.display();
	}

	return 0;
}
