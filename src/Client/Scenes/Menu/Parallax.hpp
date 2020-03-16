//
// Created by simon on 26/11/19.
//

#ifndef RTYPE_PARALLAX_HPP
#define RTYPE_PARALLAX_HPP

#include "ISceneManager.hpp"
#include "Scene.hpp"

namespace rtype {
    namespace client {
        class ParallaxObject : public rtype::engine::Object {
            public:
                ParallaxObject(const std::string &name, const unsigned int &spriteId,
                            engine::IScene &scene, const pos_t &position,
                            const pos_t &restartPos,
                            const pos_t &reachedDestination,
                            const unsigned &speed
                );

                ~ParallaxObject() = default;
                void setDestination(const pos_t &reachedDestination, const unsigned &speed);
                void eventReachedDestination() override;
            private:
                pos_t _restartDestination;
                pos_t _reachedDestination;
                unsigned int _speed;

        };
        class Parallax : public rtype::engine::Scene {
            public:
                Parallax(const std::string &name, rtype::engine::ISceneManager &sceneManager);

                virtual ~Parallax();

        };
    }
}


#endif //RTYPE_PARALLAX_HPP
