#pragma once 

#include<vector>
#include<cstdint>
#include<utility>

namespace Hero
{
    class Actor;
    class IComponent;

    template<typename T>
    class IComponentSystem
    {
        protected:
            std::vector<std::pair<bool, T> data;
            uint32_t usedNumber = 0;
            uint32_t firstEmpty = 0;

        public:
            IComponentSystem(uint32_t _startSize, uint32_t _chunkSize);
            ~IComponentSystem();

            virtual void update();
            IComponent* add(const T& data);
            void remove(IComponent* data);

        private:

            int startSize;
            int chunkSize;
            virtual void dataInit(T* data) = 0;
            virtual void dataUpdate(T* data) = 0;
            virtual void dataDestroy(T* data) = 0;
    };

    class IComponent
    {
        private:
            void* system = nullptr;
            uint32_t index = 0;

        protected:
            Actor* actor = nullptr;
    };
}