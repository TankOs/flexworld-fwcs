#include <FWCS/Controllers/Gravity.hpp>
#include <FWCS/Controllers/ForceReset.hpp>
#include <FWCS/Controllers/MovementForceTransform.hpp>
#include <FWCS/Controllers/Acceleration.hpp>
#include <FWCS/Controllers/Movement.hpp>
#include <FWCS/Controllers/PositionLimit.hpp>
#include <FWCS/Controllers/Drag.hpp>
#include <FWCS/Controllers/Jump.hpp>
#include <FWCS/System.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/Graphics.hpp>
#include <sstream>

static const float SCALE_FACTOR = 50.0f; // X pixels = 1 meter.

int main() {
	// Initialize graphics.
	sf::RenderWindow render_window( sf::VideoMode( 1024, 768 ), "FWCS Runner Example" );

	// Visible object.
	sf::RectangleShape earth_shape( sf::Vector2f( 0.5f * SCALE_FACTOR, 1.75f * SCALE_FACTOR ) );
	sf::RectangleShape mars_shape( sf::Vector2f( 0.5f * SCALE_FACTOR, 1.75f * SCALE_FACTOR ) );

	earth_shape.setFillColor( sf::Color::White );
	mars_shape.setFillColor( sf::Color::Yellow );

	// Framerate limit.
	render_window.setFramerateLimit( 60 );

	// HUD.
	sf::Font font;
	font.loadFromFile( "data/DejaVuSans.ttf" );

	sf::Text hud_text( "", font, 18 );

	// Setup FWCS.
	cs::System system;

	system.create_controller<cs::ctrl::ForceReset>();
	system.create_controller<cs::ctrl::Gravity>();
	system.create_controller<cs::ctrl::Jump>();
	system.create_controller<cs::ctrl::Drag>();
	system.create_controller<cs::ctrl::MovementForceTransform>();
	system.create_controller<cs::ctrl::Acceleration>();
	system.create_controller<cs::ctrl::Movement>();
	system.create_controller<cs::ctrl::PositionLimit>();

	cs::Entity& earth_entity = system.create_entity();

	earth_entity.create_property<sf::Vector3f>( "position", sf::Vector3f( 1.0f, 10.0f, 0.0f ) );
	earth_entity.create_property<sf::Vector3f>( "velocity" );
	earth_entity.create_property<sf::Vector3f>( "acceleration" );
	earth_entity.create_property<sf::Vector3f>( "force" );
	earth_entity.create_property<sf::Vector3f>( "lower_position_limit", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	earth_entity.create_property<sf::Vector3f>( "upper_position_limit", sf::Vector3f( static_cast<float>( render_window.getSize().x ), 999999.0f, 0.0f ) );
	earth_entity.create_property<sf::Vector3f>( "jump_vector", sf::Vector3f( 0.0f, 1.0f, 0.0f ) );
	earth_entity.create_property<float>( "jump_force", 3200.0f );
	earth_entity.create_property<float>( "drag_area", 0.5f * 0.2f );
	earth_entity.create_property<float>( "air_density", 1.275f );
	earth_entity.create_property<float>( "resistance_coeff", 0.78f );
	earth_entity.create_property<float>( "mass", 50.0f );
	earth_entity.create_property<float>( "gravity", -9.80665f );
	earth_entity.create_property<bool>( "jump_active", false );

	cs::Entity& mars_entity = system.create_entity();

	mars_entity.create_property<sf::Vector3f>( "position", sf::Vector3f( 10.0f, 10.0f, 0.0f ) );
	mars_entity.create_property<sf::Vector3f>( "velocity" );
	mars_entity.create_property<sf::Vector3f>( "acceleration" );
	mars_entity.create_property<sf::Vector3f>( "force" );
	mars_entity.create_property<sf::Vector3f>( "lower_position_limit", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	mars_entity.create_property<sf::Vector3f>( "upper_position_limit", sf::Vector3f( static_cast<float>( render_window.getSize().x ), 999999.0f, 0.0f ) );
	mars_entity.create_property<sf::Vector3f>( "jump_vector", sf::Vector3f( 0.0f, 1.0f, 0.0f ) );
	mars_entity.create_property<float>( "jump_force", 3200.0f );
	mars_entity.create_property<float>( "mass", 50.0f );
	mars_entity.create_property<float>( "gravity", -3.71f );
	mars_entity.create_property<bool>( "jump_active", false );

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
				else if( event.key.code == sf::Keyboard::Space ) {
					// Jump only when standing.
					if( earth_entity.find_property<sf::Vector3f>( "velocity" )->get_value().y == 0.0f ) {
						earth_entity.find_property<bool>( "jump_active" )->set_value( true );
					}

					if( mars_entity.find_property<sf::Vector3f>( "velocity" )->get_value().y == 0.0f ) {
						mars_entity.find_property<bool>( "jump_active" )->set_value( true );
					}
				}
			}
		}

		sf::Time timeslice = frametimer.restart();

		sim_time += timeslice;
		system.run( timeslice );

		// Apply FWCS's entity positions to SFML shapes. Apply a factor for scaling.
		earth_shape.setPosition(
			earth_entity.find_property<sf::Vector3f>( "position" )->get_value().x * SCALE_FACTOR,
			(
				static_cast<float>( render_window.getSize().y ) -
				(
				 earth_entity.find_property<sf::Vector3f>( "position" )->get_value().y * SCALE_FACTOR
				) -
				earth_shape.getGlobalBounds().height
			)
		);

		mars_shape.setPosition(
			mars_entity.find_property<sf::Vector3f>( "position" )->get_value().x * SCALE_FACTOR,
			(
				static_cast<float>( render_window.getSize().y ) -
				(
				 mars_entity.find_property<sf::Vector3f>( "position" )->get_value().y * SCALE_FACTOR
				) -
				mars_shape.getGlobalBounds().height
			)
		);

		// Rebuild HUD text.
		{
			std::stringstream sstr;

			sstr
				<< "Left: Earth | Right: Mars\n"
				<< "Press <Space> to jump.\n\n"
				<< std::fixed
				<< "Acceleration:"
				<< " " << earth_entity.find_property<sf::Vector3f>( "acceleration" )->get_value().x
				<< ", " << earth_entity.find_property<sf::Vector3f>( "acceleration" )->get_value().y
				<< " m/s^2\n"
				<< "Velocity:"
				<< " " << earth_entity.find_property<sf::Vector3f>( "velocity" )->get_value().x
				<< ", " << earth_entity.find_property<sf::Vector3f>( "velocity" )->get_value().y
				<< " m/s"
				<< " (" << earth_entity.find_property<sf::Vector3f>( "velocity" )->get_value().x / 1000.0f * 60.0f * 60.0f
				<< ", " << earth_entity.find_property<sf::Vector3f>( "velocity" )->get_value().y / 1000.0f * 60.0f * 60.0f
				<< " km/h)\n"
				<< "Position:"
				<< " " << earth_entity.find_property<sf::Vector3f>( "position" )->get_value().x
				<< ", " << earth_entity.find_property<sf::Vector3f>( "position" )->get_value().y
				<< " m\n"
				<< "Simulation time:"
				<< " " << sim_time.asSeconds()
				<< " s\n"
			;

			hud_text.setString( sstr.str() );
		}

		render_window.clear( sf::Color( 12, 34, 56 ) );
		render_window.draw( earth_shape );
		render_window.draw( mars_shape );
		render_window.draw( hud_text );

		render_window.display();
	}

	return 0;
}
