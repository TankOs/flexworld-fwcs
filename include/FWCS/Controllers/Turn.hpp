#pragma once

#include <FWCS/Controller.hpp>

#include <FWU/Quaternion.hpp>

namespace cs {
class ControllerRequirements;
}

namespace cs {
namespace ctrl {

/** Turn controller.
 *
 * The turn controller changes an entity's rotation by an angular velocity.
 *
 * Because rotations can't be changed like velocities, for example, one must
 * specify the turn constraint, which in turn specifies how the angular
 * velocity is added to the rotation.
 *
 * After the rotation is updated, the quaternion is automatically normalized.
 *
 * The controller accepts all constraints that are derived from
 * Turn::Constraint.
 *
 * If the entity has the optional property "forward_vector", this controller
 * will update it accordingly to the rotation.
 *
 * Properties:
 *   * rotation (util::FloatQuaternion, in/out): Rotation.
 *   * angular_velocity (sf::Vector3f, in): Angular velocity, in radians.
 *   * turn_constraint (Turn::Constraint*, in): Turn constraint.
 *   * forward_vector (sf::Vector3f, out, optional): Forward vector in direction of rotation.
 */
class Turn : public Controller {
	public:
		/** Turn constraint.
		 */
		class Constraint {
			public:
				/** Dtor.
				 */
				virtual ~Constraint();

				/** Update rotation.
				 * @param rotation Rotation to be updated.
				 * @param angular_velocity Angular velocity.
				 * @param sim_time Simulation time.
				 */
				virtual void update_rotation( util::FloatQuaternion& rotation, const sf::Vector3f& angular_velocity, const sf::Time& sim_time ) = 0;

			private:
		};

		/** Get requirements.
		 * @return Requirements.
		 */
		static const ControllerRequirements& get_requirements();

		/** Ctor.
		 * @param entity Entity.
		 */
		Turn( Entity& entity );

		void execute( const sf::Time& sim_time );

	private:
		util::FloatQuaternion* m_rotation;
		const sf::Vector3f* m_angular_velocity;
		Constraint** m_turn_constraint;
		sf::Vector3f* m_forward_vector;
};

}
}
