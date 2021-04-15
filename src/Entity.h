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
        bool IsActive() const {return this->isActive;};
    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component*> components;
}
