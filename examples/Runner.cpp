#include <FWCS/System.hpp>
#include <FWCS/Controllers/Move.hpp>
#include <FWCS/Controllers/Walk.hpp>

#include <FWU/Math.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdint>

static const sf::Time ANIMATION_INTERVAL = sf::milliseconds( 200 );

int main() {
	// Initialize graphics.
	sf::RenderWindow render_window( sf::VideoMode( 1024, 768 ), "FWCS Runner Example", sf::Style::Titlebar );

	// Window settings.
	render_window.setFramerateLimit( 60 );

	render_window.setMouseCursorVisible( false );

	// Resources.
	sf::Texture walk_textures[2];
	sf::Texture crosshair_texture;

	walk_textures[0].loadFromFile( "data/avt3_fr1.png" );
	walk_textures[1].loadFromFile( "data/avt3_fr2.png" );
	crosshair_texture.loadFromFile( "data/crosshair.png" );

	// Character.
	sf::Sprite player{ walk_textures[0] };
	uint8_t walk_frame = 0;

	player.setOrigin(
		player.getGlobalBounds().width / 2.0f,
		player.getGlobalBounds().height / 2.0f
	);

	// HUD.
	sf::Font font;
	sf::Text hud_text( "", font, 18 );
	sf::Sprite crosshair_sprite{ crosshair_texture };

	font.loadFromFile( "data/DejaVuSansMono.ttf" );
	crosshair_sprite.setOrigin( 15.0f, 15.0f );

	// Setup FWCS.
	cs::System system;
	cs::Entity& player_entity = system.create_entity();

	const auto& velocity = player_entity.create_property<sf::Vector3f>( "velocity", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	auto& player_position = player_entity.create_property<sf::Vector3f>( "position", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	const auto& forward = player_entity.create_property<sf::Vector3f>( "forward", sf::Vector3f( 1.0f, 0.0f, 0.0f ) );
	player_entity.create_property<float>( "max_velocity", 70.0f );
	player_entity.create_property<float>( "walk_max_velocity", 80.0f );
	player_entity.create_property<float>( "walk_acceleration", 200.0f );
	auto& forward_control = player_entity.create_property<float>( "walk_forward_control", 0.0f );
	auto& strafe_control = player_entity.create_property<float>( "walk_strafe_control", 0.0f );

	player_position.x = static_cast<float>( render_window.getSize().x ) / 2.0f;
	player_position.z = static_cast<float>( render_window.getSize().y ) / 2.0f;

	system.create_factory<cs::ctrl::Walk>();
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

		sf::Time timeslice = frametimer.restart();

		// Run the system.
		system.run( timeslice );

		// Apply FWCS entity's position to SFML sprite.
		player.setPosition(
			player_position.x,
			player_position.z
		);

		// Apply rotation.
		float angle = util::rad_to_deg( std::atan2( forward.z, forward.x ) - std::atan2( 0.0f, 1.0f ) );
		player.setRotation( angle + 90.0f );

		// Player animation (only if walking).
		anim_timer += timeslice;

		while( anim_timer >= ANIMATION_INTERVAL ) {
			if( util::calc_length( velocity ) > 0 ) {
				walk_frame = static_cast<uint8_t>( (walk_frame + 1) % 2 );
			}

			anim_timer -= ANIMATION_INTERVAL;
		}

		player.setTexture( walk_textures[walk_frame] );

		// Update HUD.
		crosshair_sprite.setPosition(
			static_cast<float>( sf::Mouse::getPosition( render_window ).x ),
			static_cast<float>( sf::Mouse::getPosition( render_window ).y )
		);

		render_window.clear( sf::Color( 12, 34, 56 ) );
		render_window.draw( player );
		render_window.draw( crosshair_sprite );
		render_window.display();
	}

	return 0;
}
