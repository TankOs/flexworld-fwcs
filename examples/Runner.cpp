#include <FWCS/System.hpp>
#include <FWCS/Controllers/Velocity.hpp>
#include <FWCS/Controllers/Position.hpp>

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

	player_entity.create_property<sf::Vector3f>( "acceleration", sf::Vector3f( 25.0f, 0.0f, 0.0f ) );
	player_entity.create_property<sf::Vector3f>( "velocity", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	player_entity.create_property<sf::Vector3f>( "position", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	player_entity.create_property<float>( "max_velocity", 70.0f );

	system.create_factory<cs::ctrl::Velocity>();
	system.create_factory<cs::ctrl::Position>();

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

		sf::Time timeslice = frametimer.restart();

		// Run the system.
		system.run( timeslice );

		// Apply FWCS entity's position to SFML sprite.
		player.setPosition(
			player_entity.find_property<sf::Vector3f>( "position" )->x,
			player_entity.find_property<sf::Vector3f>( "position" )->z
		);

		// Player animation.
		anim_timer += timeslice;

		while( anim_timer >= ANIMATION_INTERVAL ) {
			walk_frame = static_cast<uint8_t>( (walk_frame + 1) % 2 );

			anim_timer -= ANIMATION_INTERVAL;
		}

		player.setTexture( walk_textures[walk_frame] );

		render_window.clear( sf::Color( 12, 34, 56 ) );
		render_window.draw( player );
		render_window.display();
	}

	return 0;
}
