#ifndef DEBUG_HPP_INCLUDED
#define DEBUG_HPP_INCLUDED

#include <iostream>

#define DEBUG 1
	// DEBUG 1 -> DEBUG activ�
	// DEBUG 0 -> DEBUG d�sactiv�

#if (DEBUG)
	#define LOG(x) std::cout << x << std::endl;
#else
	#define LOG(x)
#endif

#endif