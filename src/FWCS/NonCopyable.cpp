#include <FWCS/NonCopyable.hpp>

namespace cs {

NonCopyable::NonCopyable() {
}

NonCopyable::NonCopyable( const NonCopyable& ) {
}

const NonCopyable& NonCopyable::operator=( const NonCopyable& ) {
	return *this;
}

}
