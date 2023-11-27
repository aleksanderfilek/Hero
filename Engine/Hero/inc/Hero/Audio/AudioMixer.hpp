#pragma once

#include"Sid.hpp"

namespace Hero
{
    class AudioMixer
    {
        private:
            uint8_t volume;
            
        public:
            Sid sid;
    };
} // namespace Hero