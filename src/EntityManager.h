#pragma once
#include <vector>
#include <string>

class Entity;
class Component;

class EntityManager{
    public:
        void ClearData();
        void Update(float deltaTime);
        void Render();
        bool hasNoEntities();
        Entity& AddEntity(std::string entityName);
        std::vector<Entity*> getEntities() const;
        unsigned int GetEntityCount();
    private:
        std::vector<Entity*> entities;
};