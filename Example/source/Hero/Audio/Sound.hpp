#pragma once

#include"ThirdParty.hpp"

namespace Hero
{
    class Sound
    {
        private:
            Mix_Chunk chunk;

        public:
            Sound();
            ~Sound();
    };
} // namespace Hero
