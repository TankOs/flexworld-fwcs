#include <FWCS/System.hpp>
#include <FWCS/Controllers/Accelerate.hpp>
#include <FWCS/Controllers/Move.hpp>
#include <FWCS/Controllers/Walk.hpp>
#include <FWCS/Math.hpp>

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdint>

static const sf::Time ANIMATION_INTERVAL = sf::milliseconds( 200 );

int main() {
	// Initialize graphics.
	sf::RenderWindow render_window( sf::VideoMode( 1024, 768 ), "FWCS Runner Example", sf::Style::Titlebar );

	// Framerate limit.
	render_window.setFramerateLimit( 60 );

	// Resources.
	sf::Texture walk_textures[2];

	walk_textures[0].loadFromFile( "data/avt3_fr1.png" );
	walk_textures[1].loadFromFile( "data/avt3_fr2.png" );

	// Character.
	sf::Sprite player{ walk_textures[0] };
	uint8_t walk_frame = 0;

	// HUD.
	sf::Font font;
	font.loadFromFile( "data/DejaVuSansMono.ttf" );

	sf::Text hud_text( "", font, 18 );

	// Setup FWCS.
	cs::System system;
	cs::Entity& player_entity = system.create_entity();

	auto& acceleration = player_entity.create_property<sf::Vector3f>( "acceleration", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	const auto& velocity = player_entity.create_property<sf::Vector3f>( "velocity", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	const auto& player_position = player_entity.create_property<sf::Vector3f>( "position", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	player_entity.create_property<sf::Vector3f>( "forward", sf::Vector3f( 0.0f, 0.0f, -1.0f ) );
	player_entity.create_property<float>( "max_velocity", 70.0f );
	player_entity.create_property<float>( "walk_max_velocity", 80.0f );
	player_entity.create_property<float>( "walk_acceleration", 200.0f );
	auto& forward_control = player_entity.create_property<float>( "walk_forward_control", 0.0f );
	auto& strafe_control = player_entity.create_property<float>( "walk_strafe_control", 0.0f );

	system.create_factory<cs::ctrl::Walk>();
	system.create_factory<cs::ctrl::Accelerate>();
	system.create_factory<cs::ctrl::Move>();

	// Enter loop.
	sf::Event event;
	sf::Clock frametimer;
	sf::Time anim_timer;

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

		// Update walk control values.
		float multiplier = (sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) ? 1.0f : 0.4f);
		forward_control = (sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ? multiplier : 0.0f) + (sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ? -multiplier : 0.0f);
		strafe_control = (sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ? -multiplier * 0.6f : 0.0f) + (sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ? multiplier * 0.6f : 0.0f);

		// FIXME
		acceleration = sf::Vector3f( 0.0f, 0.0f, 0.0f );

		sf::Time timeslice = frametimer.restart();

		// Run the system.
		system.run( timeslice );

		// Apply FWCS entity's position to SFML sprite.
		player.setPosition(
			player_position.x,
			player_position.z
		);

		// Player animation (only if walking).
		anim_timer += timeslice;

		while( anim_timer >= ANIMATION_INTERVAL ) {
			if( cs::calc_length( velocity ) > 0 ) {
				walk_frame = static_cast<uint8_t>( (walk_frame + 1) % 2 );
			}

			anim_timer -= ANIMATION_INTERVAL;
		}

		player.setTexture( walk_textures[walk_frame] );

		render_window.clear( sf::Color( 12, 34, 56 ) );
		render_window.draw( player );
		render_window.display();
	}

	return 0;
}
