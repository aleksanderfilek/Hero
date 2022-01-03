#pragma once

#include<vector>
#include<typeinfo>
#include<iostream>

namespace Hero
{
    class IComponent;

    class Actor
    {
        private:
            std::vector<IComponent*> components;

        public:
            Actor();
            ~Actor();

            template<typename T>
            T* getComponent()
            {
                for(auto component: components)
                {
                    if(typeid(T) == typeid(*component))
                    {
                        return component;
                    }
                }

                #ifdef HERO_DEBUG
                std::cout<<"Could not get component of type: "<<typename(T).name()<<std::endl;
                #endif

                return nullptr;
            }
    };
} 
