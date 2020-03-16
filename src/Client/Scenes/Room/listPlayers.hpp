//
// Created by simon on 30/11/19.
//

#ifndef RTYPE_LISTPLAYERS_HPP
#define RTYPE_LISTPLAYERS_HPP

#include "listMatch.hpp"
#include "ISceneManager.hpp"
#include "Scene.hpp"
#include "Button.hpp"
#include "Text.hpp"

namespace rtype
{
    namespace client
    {
        class Player : public rtype::engine::Object
        {
        public:
            Player(const std::string &name,
                 const unsigned &spriteId,
                 std::function<void(engine::Button &)> callbackPressed,
                 std::function<void(engine::Button &)> callbackHover,
                 std::function<void(engine::Button &)> callbackUnHover,
                 rtype::engine::IScene &scene,
                 const pos_t &position, const std::string &username, const unsigned int &id);
            void display(sf::RenderWindow &window) override;
            void manageEvents(const engine::event_t &event) override;
            std::shared_ptr<engine::Button> getButton();
            std::shared_ptr<engine::Text> getText();
            unsigned int getIdPlayer() const;
            void setId(unsigned int id);


        private:
            const std::string _name;
            bool _isHover;
            unsigned int _id;
            std::shared_ptr<engine::Button> _button;
            std::shared_ptr<engine::Text> _text;
        };

        class ListPlayers : public rtype::engine::Scene
        {
        public:
            ListPlayers(const std::string &name, rtype::engine::ISceneManager &sceneManager, std::vector<std::string> &listPlayers, std::pair<int, int> interval = {0, 0});
            void display(sf::RenderWindow &window) override;
            void manageEvents(const engine::event_t &event) override ;

            void setInterval(const std::pair<int, int> &interval);
            const std::pair<int, int> &getInterval() const;
            void addPlayer(std::string &name, const unsigned int &id);
			void addPlayerReady(const unsigned int &id);
            void removePlayer(const unsigned int &id);
            std::vector<std::shared_ptr<Player>> &getElements();

        private:
            std::vector<std::shared_ptr<rtype::client::Player>> _elements;
            std::pair<int, int> _interval;
        };
    }
}


#endif //RTYPE_LISTPLAYERS_HPP