#include <iostream>
#include "EntityManager.h"
#include "Entity.h"

//Call all entities Destructors
void EntityManager::ClearData(){
    for (auto& entity: entities){
        entity->Destroy();
    }
}

//Call all entities Update component
void EntityManager::Update(float deltaTime){
    for(auto& entity : entities){
        entity->Update(deltaTime);
    }
}

//Call all entities Render Component
void EntityManager::Render(){
    for(int layerNumber=0;layerNumber<NUM_LAYERS; layerNumber++){
        for(auto& entity: getEntitiesByLayer(static_cast<LayerType>(layerNumber))){
            entity->Render();
        }

    }
    
}

//Lists all Entities in Manager
void EntityManager::ListAllEntities() const{
    unsigned int i=0;
    for(auto& entity: entities){
        std::cout<<"Entity ["<<i<<"] Name: "<<entity->name<<std::endl;
        entity->ListAllComponents();
        i++;
    }
}

//return bool if entities exist or not
bool EntityManager::hasNoEntities(){
    return entities.size() == 0;
}

//create a new entity, push into entity vector and return a reference back to user
Entity& EntityManager::AddEntity(std::string entityName, LayerType layer){
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}

//returns all entitites
std::vector<Entity*> EntityManager::getEntities() const{
    return entities;
}

std::vector<Entity*> EntityManager::getEntitiesByLayer(LayerType layer) const{
    std::vector<Entity*> selectedEntities;
    for(auto& entity: entities){
        if(entity->layer==layer){
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

//return entity count
unsigned int EntityManager::GetEntityCount(){
    return entities.size();
}
