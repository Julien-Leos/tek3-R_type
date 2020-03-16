/*
** EPITECH PROJECT, 2019
** tek3
** File description:
** Parser
*/

#include "Parser.hpp"

namespace rtype {
    namespace engine {
        std::map<std::string, std::string> Parser::getConfigFile(std::string fileName)
        {
            std::map<std::string, std::string> map;
            std::ifstream file(std::string("config/" + fileName + ".conf").c_str());
            std::string line;

            while(getline(file, line)) {
                size_t pos = line.find("=");
                std::string key = line.substr(0, pos);
                line.erase(0, pos + 1);
                map.insert(std::make_pair(key, line));
            }
            return map;
        }
    }
}