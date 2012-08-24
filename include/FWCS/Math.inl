namespace cs {

template <class T>
int calc_signum( T value ) {
	return (T( 0 ) < value) - (value < T( 0 ));
}

}
