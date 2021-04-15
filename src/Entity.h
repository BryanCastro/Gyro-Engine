#pragma once
#include <vector>
#include <string>

class EntityManager;
class Component;

class Entity{
    public:
        std::string name;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;

        /*
        1-template that creates a new component of type T
        2-sets owner to this entity
        3-adds it to component vector
        4-then initializes the component
        5-returns a reference to component*/
        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args){
            T* newComponent(new T(std::forward<TArgs>(args)...));
            newComponent->owner = this;
            components.emplace_back(newComponent);
            newComponent->Initialize();
            return *newComponent;
        }
    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component*> components;
};
