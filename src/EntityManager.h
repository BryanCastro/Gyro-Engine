#pragma once
#include "./Entity.h"
#include "./Component.h"
#include <vector>

class EntityManager{
    public:
        void Update(float deltaTime);
        void Render();
        bool hasNoEntities();
        Entity& AddEntity(std::string entityName);
        std::vector<Entity*> getEntities() const;
        unsigned int GetEntityCount();
    private:
        std::vector<Entity*> entities;
}