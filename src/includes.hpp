/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** includes
*/

#ifndef INCLUDES_HPP_
#define INCLUDES_HPP_

    #include <iostream>
    #include <fstream>
    #include <string>
	#ifdef _WIN32
	    #include <io.h>
	#else
		#include <unistd.h>
	#endif
    #include <stdlib.h>
    #include <stdio.h>

    // Std
    #include <unordered_map>

    // Boost
    #include <boost/enable_shared_from_this.hpp>
    #include <boost/shared_ptr.hpp>
    #include <boost/bind.hpp>
    #include <boost/asio.hpp>
    #include <boost/array.hpp>

#endif /* !INCLUDES_HPP_ */
