//
// Created by simon on 27/11/19.
//

#ifndef RTYPE_LISTMATCH_HPP
#define RTYPE_LISTMATCH_HPP

#include "ISceneManager.hpp"
#include "Scene.hpp"
#include "Button.hpp"
#include "Text.hpp"

namespace rtype
{
    namespace client
    {
        class Room : public rtype::engine::Object
        {
        public:
            Room(const std::string &name,
                 const unsigned &spriteId,
                 std::function<void(engine::Button &)> callbackPressed,
                 std::function<void(engine::Button &)> callbackHover,
                 std::function<void(engine::Button &)> callbackUnHover,
                 rtype::engine::IScene &scene,
                 const pos_t &position, const std::string &roomName, unsigned int id);
            void display(sf::RenderWindow &window) override;
            void manageEvents(const engine::event_t &event) override;
            std::shared_ptr<engine::Button> getButton();
            std::shared_ptr<engine::Text> getText();
            unsigned int getIdRoom() const;
            void setId(unsigned int id);

        private:
            const std::string _name;
            std::shared_ptr<engine::Button> _button;
            std::shared_ptr<engine::Text> _text;
            bool _isHover;
            unsigned int _id;
        };

        class ListRoom : public rtype::engine::Scene
        {
        public:
            ListRoom(const std::string &name, rtype::engine::ISceneManager &sceneManager, std::vector<std::string> &listRooms, std::pair<int, int> interval = {0, 0});
            void display(sf::RenderWindow &window) override;
            void manageEvents(const engine::event_t &event) override ;

            void setInterval(const std::pair<int, int> &interval);
            const std::pair<int, int> &getInterval() const;
            void addRoom(std::string &name, unsigned id);
            void removeRoom(unsigned int id);
            std::vector<std::shared_ptr<Room>> &getElements();

        private:
            std::vector<std::shared_ptr<rtype::client::Room>> _elements;
            std::pair<int, int> _interval;
        };
    }
}


#endif //RTYPE_LISTMATCH_HPP
