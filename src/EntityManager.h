#pragma once
#include <vector>
#include <string>
//#include "./Entity.h"
//#include "./Component.h
#include "./Constants.h"
class Entity;
class Component;

class EntityManager{
    public:
        void ClearData();
        void Update(float deltaTime);
        void Render();
        void ListAllEntities() const;
        bool hasNoEntities();
        Entity& AddEntity(std::string entityName, LayerType layer);
        std::vector<Entity*> getEntities() const;
        std::vector<Entity*> getEntitiesByLayer(LayerType layer) const;
        unsigned int GetEntityCount();
    private:
        std::vector<Entity*> entities;
};