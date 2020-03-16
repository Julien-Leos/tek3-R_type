//
// Created by simon on 22/11/19.
//

#ifndef RTYPE_THROW_HPP
#define RTYPE_THROW_HPP

/* EXCEPTION FOR SMART THROWING  */

#define COLOR(number) "\033[1;" #number "m"
#define CLEAR std::string("\033[0m")

/**
 * @brief func which smart throw with line, func, file of the crash.
 * @tparam E type of the throw.
 * @param msg message of the throw
 * @param file filepath of the throw.
 * @param function name of the function which contains the crash.
 * @param line line number of the crash.
 */
template<class E>
void throw_func(std::string msg,
                char const* file, char const* function,
                std::size_t line) {
    throw E( std::string{} +
             std::string(std::string(COLOR(33)) + file + CLEAR) +
             std::string(std::string(COLOR(31)) + "(" + std::to_string(line) + "):" + CLEAR) +
             std::string(std::string(COLOR(34)) + " [" + std::string(function) + "] " + CLEAR + std::string("--> ")) +
             std::string(std::string(COLOR(31)) + std::string("\x1B[1m") + msg + CLEAR));
}
#define EXCEPTION( TYPE, MESSAGE ) \
    throw_func<TYPE>( MESSAGE, __FILE__, __func__, __LINE__ )


#endif //RTYPE_THROW_HPP
