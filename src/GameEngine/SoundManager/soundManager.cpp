//
// Created by simon on 01/12/19.
//

#include "soundManager.hpp"

namespace rtype {
    namespace engine {
        SoundManager::SoundManager() = default;

        SoundManager::~SoundManager()
        {
            for (const auto& obj : _songMap)
                obj.second->stop();
            this->_songMap.clear();
        }

        void SoundManager::playSong(const std::string& name)
        {
            if (_songMap.empty())
                EXCEPTION(std::runtime_error, "Sound can't be found");

            if (_songMap.find(name) == _songMap.end())
                EXCEPTION(std::runtime_error, name + " key can't be found");

            auto song = _songMap.find(name)->second;

            if (!song)
                EXCEPTION(std::runtime_error, name + " second pattern was null");
            song->play();

            if (name == "buttonClicked") {
                _songMap.erase(name);
                this->addSong("assets/Sounds/buttonClicked.wav", "buttonClicked");
            }
        }

        void SoundManager::addSong(const std::string& path, const std::string& name)
        {
            if (_songMap.find(name) != _songMap.end())
                EXCEPTION(std::runtime_error, name + " key can't be found");

            auto *song = new sf::Music();

            if (!song->openFromFile(path))
                EXCEPTION(std::runtime_error, path + " can't be open.");

            _songMap.insert(std::make_pair(name, song));
        }

        void SoundManager::controlVolumeSong(const std::string& name, unsigned int volume)
        {
            if (_songMap.find(name) == _songMap.end())
                EXCEPTION(std::runtime_error, name + " key can't be found");

            auto song = _songMap.find(name)->second;

            if (!song)
                EXCEPTION(std::runtime_error, name + " second pattern was null.");

            if (volume > 100)
                EXCEPTION(std::runtime_error, "You can't set up the volume more than 100 and no less than 0");

            song->setVolume(volume);
        }

        void SoundManager::stopSong(const std::string& name)
        {
            if (_songMap.find(name) == _songMap.end())
                EXCEPTION(std::runtime_error, name + " key can't be found");

            auto song = _songMap.find(name)->second;

            if (!song)
                EXCEPTION(std::runtime_error, name + " second pattern can't be found");

            if (song->getStatus() != sf::Sound::Status::Stopped)
                song->stop();
        }

        void SoundManager::removeSong(const std::string& name)
        {
            if (_songMap.find(name) == _songMap.end())
                EXCEPTION(std::runtime_error, name + " key can't be found");

            _songMap.erase(name);
        }

        void SoundManager::pauseSong(const std::string& name)
        {
            if (_songMap.find(name) == _songMap.end())
                EXCEPTION(std::runtime_error, name + " key can't be found");

            auto song = _songMap.find(name)->second;

            if (!song)
                EXCEPTION(std::runtime_error, name + " second pattern was null.");

            if (song->getStatus() == sf::Sound::Status::Playing)
                song->pause();
        }

        void SoundManager::setLoopToASong(const std::string& name)
        {
            if (_songMap.find(name) == _songMap.end())
                EXCEPTION(std::runtime_error, name + " key can't be found");

            auto song = _songMap.find(name)->second;

            if (!song)
                EXCEPTION(std::runtime_error, name + " second pattern was null.");

            song->setLoop(true);
        }

        float SoundManager::getVolumeOfASong(const std::string& name)
        {
            if (_songMap.find(name) == _songMap.end())
                EXCEPTION(std::runtime_error, name + " key can't be found");

            auto song = _songMap.find(name)->second;

            if (!song)
                EXCEPTION(std::runtime_error, name + " second pattern was null.");

            return (song->getVolume());
        }
    }
}