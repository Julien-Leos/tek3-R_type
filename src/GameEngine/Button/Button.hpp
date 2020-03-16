//
// Created by simon on 20/11/19.
//

#ifndef RTYPE_BUTTON_HPP
#define RTYPE_BUTTON_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "Communication.hpp"
#include "Object.hpp"

namespace rtype {
    namespace engine {

        class Button : public Object {
        public:
            Button(const std::string &name,
                   const unsigned &spriteId,
                   std::function<void(Button &)> callbackPressed,
                   std::function<void(Button &)> callbackHover,
                   std::function<void(Button &)> callbackUnHover,
                   IScene &scene,
                   const pos_t &position = {0, 0});
            ~Button();
            void manageEvents(const event_t &event) override;
            const unsigned &getSpriteId();
            virtual void setCallBackButton(std::function<void(Button &)> &callback);
            virtual void setCallbackHover(std::function<void(Button &)> &callback);
            virtual void setCallbackUnHover(std::function<void(Button &)> &callback);
            const pos_t &getButtonPos() const;
            void callPressed();
            void callHover();
            void callUnHover();


        protected:
            pos_t _buttonPos;
            const unsigned _spriteId;
            bool _isHover;
            std::function<void(Button &)> _mPressedCallback;
            std::function<void(Button &)> _mHoverCallback;
            std::function<void(Button &)> _mUnHoverCallback;

        };
    }
}


#endif //RTYPE_BUTTON_HPP
