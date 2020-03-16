/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "includes.hpp"

namespace rtype {
    namespace engine {
        class Parser {
            public:
                Parser() = default;
                virtual ~Parser() = default;

                static std::map<std::string, std::string> getConfigFile(std::string fileName);
        };
        
    }
}

#endif /* !PARSER_HPP_ */