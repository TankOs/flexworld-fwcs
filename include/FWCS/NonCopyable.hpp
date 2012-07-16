#pragma once

namespace cs {

/** Non-copyable base class.
 */
class NonCopyable {
	public:
		NonCopyable();

	private:
		NonCopyable( const NonCopyable& );
		const NonCopyable& operator=( const NonCopyable& );
};

}
