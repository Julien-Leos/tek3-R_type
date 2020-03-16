//
// Created by simon on 01/12/19.
//

#ifndef RTYPE_SOUNDMANAGER_HPP
#define RTYPE_SOUNDMANAGER_HPP

#include <unordered_map>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include "Throw.hpp"

namespace rtype {
    namespace engine {
        /**
     * @brief djControl which control all song of our game.
     */
    class SoundManager {
    public:
        virtual ~SoundManager();

        SoundManager();

        /**
         * @brief add song to the map.
         * @param path path to the file song.
         * @param name name of the song.
         */
        void addSong(const std::string &path, const std::string &name);

        /**
         * @brief play a song by this name.
         * @param name name of the song in the map.
         */
        void playSong(const std::string &name);

        /**
         * @brief control the volume of a song by this name in the name.
         * @param name name in the map.
         * @param volume volume of this menu (between 0 and 100).
         */
        void controlVolumeSong(const std::string &name, unsigned int volume);

        /**
         * @brief stop the song by this name in the map.
         * @param name name of the song in the map.
         */
        void stopSong(const std::string &name);

        /**
         * @brief pause the song by this name.
         * @param name name of the song in the map.
         */
        void pauseSong(const std::string &name);

        /**
         * @brief remove song of the map by this name.
         * @param name name of the song in the map.
         */
        void removeSong(const std::string &name);

        /**
         * @brief set to true a song in the name by this name.
         * @param name name of the song in the map.
         */
        void setLoopToASong(const std::string &name);

        /**
         * @brief get the volume of a song by this name.
         * @param name name of the song in the map.
         * @return return the volume of the song in float
         */
        float getVolumeOfASong(const std::string &name);

    private:
        std::unordered_map<std::string, sf::Music *> _songMap;

    protected:
    };
    }
}


#endif //RTYPE_SOUNDMANAGER_HPP
