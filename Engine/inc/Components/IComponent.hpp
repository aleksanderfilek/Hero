#pragma once 

#include<vector>
#include<cstdint>
#include<utility>

namespace Hero
{
    class Actor;
    
    class IComponent
    {
        private:
            void* system = nullptr;
            uint32_t index = 0;

        protected:
            Actor* actor = nullptr;
    };

    template<typename T>
    class IComponentSystem
    {
        private:
            int startSize;
            int chunkSize;
            virtual void dataInit(T* data){}
            virtual void dataUpdate(T* data){}
            virtual void dataDestroy(T* data){}
        protected:
            std::vector<std::pair<bool, T>> data;
            uint32_t usedNumber = 0;
            uint32_t firstEmpty = 0;

        public:
            IComponentSystem(uint32_t _startSize, uint32_t _chunkSize)
            {
                data.reserve(_startSize);
                chunkSize = _chunkSize;
            }
            ~IComponentSystem()
            {
                for(auto component: data)
                {
                    dataDestroy(&component.second);
                }

                data.clear();
            }

            virtual void update()
            {
                for(auto component: data)
                {
                    if(!component.first)
                        continue;

                    dataUpdate(&component.second);
                }
            } 
            IComponent* add(const T& component)
            {
                uint32_t index = firstEmpty;
                std::pair<bool, T> element(true, component);
                
                element.second.index = this;
                element.second.index = index;
                data[firstEmpty] = element;
                usedNumber++;
                dataInit(&data.at(index).second);

                if(data.size() <= usedNumber)
                {
                    data.resize(usedNumber + chunkSize);
                }

                for(int i = firstEmpty; i < data.size(); i++)
                {
                    if(data.at(i).first == false)
                    {
                        firstEmpty = i;
                        break;
                    }
                }

                return &data.at(index).second;
            }
            void remove(IComponent* component)
            {
                data.at(component->index).first = false;
                usedNumber--;
                
                if(component->index < firstEmpty)
                {
                    firstEmpty = component->index;
                }
            }
    };

}