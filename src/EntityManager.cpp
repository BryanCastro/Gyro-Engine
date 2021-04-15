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
    for(auto& entity: entities){
        entity->Render();
    }
}

//return bool if entities exist or not
bool EntityManager::hasNoEntities(){
    return entities.size() == 0;
}

//create a new entity, push into entity vector and return a reference back to user
Entity& EntityManager::AddEntity(std::string entityName){
    Entity *entity = new Entity(*this, entityName);
    entities.emplace_back(entity);
    return *entity;
}

//returns all entitites
std::vector<Entity*> EntityManager::getEntities() const{
    return entities;
}
//return entity count
unsigned int EntityManager::GetEntityCount(){
    return entities.size();
}
