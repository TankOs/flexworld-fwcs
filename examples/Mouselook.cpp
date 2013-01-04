#include <FWCS/System.hpp>
#include <FWCS/Controllers/Mouselook.hpp>
#include <FWCS/Controllers/Turn.hpp>
#include <FWCS/TopDownTurnConstraint.hpp>

#include <SFML/OpenGL.hpp>
#include <FWU/Math.hpp>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <iostream>

int main() {
	// Initialize graphics.
	sf::RenderWindow render_window( sf::VideoMode( 1024, 768 ), "FWCS Mouselook Example", sf::Style::Titlebar );

	static const sf::Vector2i WINDOW_CENTER{
		static_cast<int>( render_window.getSize().x / 2 ),
		static_cast<int>( render_window.getSize().y / 2 )
	};

	// Window settings.
	render_window.setFramerateLimit( 60 );

	render_window.setMouseCursorVisible( true );

	// Setup FWCS.
	cs::System system;
	cs::TopDownTurnConstraint turn_constraint;
	auto& entity = system.create_entity();

	const auto& rotation = entity.create_property( "rotation", util::FloatQuaternion() );
	auto& mouselook_control = entity.create_property( "mouselook_control", sf::Vector2f{ 0.0f, 0.0f } );

	entity.create_property( "forward_vector", sf::Vector3f( 1.0f, 0.0f, 0.0f ) );
	entity.create_property( "angular_velocity", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	entity.create_property( "max_mouselook_angular_velocity", util::deg_to_rad( 100.0f ) );
	entity.create_property( "mouselook_angular_acceleration", util::deg_to_rad( 200.0f ) );
	entity.create_property( "mouselook_angular_deceleration", util::deg_to_rad( 250.0f ) );
	entity.create_property<cs::ctrl::Turn::Constraint*>( "turn_constraint", &turn_constraint );

	system.create_factory<cs::ctrl::Mouselook>();
	system.create_factory<cs::ctrl::Turn>();

	// Enter loop.
	sf::Event event;
	sf::Clock frametimer;

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

		// Process mouse delta.
		sf::Vector2i mouse_position{ sf::Mouse::getPosition( render_window ) };

		mouselook_control.x = static_cast<float>( mouse_position.x - WINDOW_CENTER.x ) / static_cast<float>( WINDOW_CENTER.x );
		mouselook_control.y = static_cast<float>( mouse_position.y - WINDOW_CENTER.y ) / static_cast<float>( WINDOW_CENTER.y );

		// Reset mouse.
		sf::Mouse::setPosition( WINDOW_CENTER, render_window );

		sf::Time timeslice = frametimer.restart();

		// Run the system.
		system.run( timeslice );

		render_window.clear( sf::Color( 12, 34, 56 ) );

		// Render triangle.
		render_window.pushGLStates();
		glPushMatrix();

		// Rotate.
		float angle{ 0.0f };
		sf::Vector3f axis{ 0.0f, 0.0f, 0.0f };

		rotation.to_angle_axis( angle, axis );
		glRotatef( util::rad_to_deg( angle ), axis.x, axis.y, axis.z );

		glBegin( GL_TRIANGLES );
		glColor3f( 1.0f, 1.0f, 1.0f );

		glVertex3f( 0.0f, 0.0f, 0.0f );
		glVertex3f( 1.0f, 0.0f, 0.0f );
		glVertex3f( 0.0f, 1.0f, 0.0f );

		glEnd();

		glPopMatrix();
		render_window.popGLStates();

		render_window.display();
	}

	return 0;
}
