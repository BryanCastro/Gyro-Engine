#include <iostream>
#include "EntityManager.h"
#include "Entity.h"
#include "./Collision.h";
#include "./Components/ColliderComponent.h"


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
    DestroyInactiveEntities();
}

void EntityManager::DestroyInactiveEntities(){
    for(int i=0;i<entities.size();i++){
        if(!entities[i]->IsActive()){
            entities.erase(entities.begin()+i);
        }
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

Entity* EntityManager::GetEntityByName(std::string entityName) const {
    for (auto* entity: entities) {
        if (entity->name.compare(entityName) == 0) {
            return entity;
        }
    }
    return NULL;
}

//return entity count
unsigned int EntityManager::GetEntityCount(){
    return entities.size();
}

CollisionType EntityManager::CheckCollisions() const{
    for(int i=0;i<entities.size()-1;i++){
        auto& thisEntity = entities[i];
        if(thisEntity->HasComponent<ColliderComponent>()){
            ColliderComponent *thisCollider = thisEntity->GetComponent<ColliderComponent>();
            for(int j=i+1;j<entities.size();j++){
                auto& thatEntity = entities[j];
                if(thisEntity->name.compare(thatEntity->name)!=0 && thatEntity->HasComponent<ColliderComponent>()){
                    ColliderComponent *thatCollider = thatEntity->GetComponent<ColliderComponent>();
                    if(Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider)){
                        if(thisCollider->colliderTag.compare("PLAYER")==0 &&
                            thatCollider->colliderTag.compare("ENEMY")==0
                        ){
                            return PLAYER_ENEMY_COLLISION;
                        }
                        if(thisCollider->colliderTag.compare("PLAYER")==0 &&
                           thatCollider->colliderTag.compare("PROJECTILE")==0
                           ){
                               return PLAYER_PROJECTILE_COLLISION;
                           }
                        if(thisCollider->colliderTag.compare("ENEMY")==0 &&
                           thatCollider->colliderTag.compare("FRIENDLY_PROJECTILE")==0
                           ){
                               return ENEMY_PROJECTILE_COLLISION;
                           }
                        if(thisCollider->colliderTag.compare("PLAYER")==0 &&
                           thatCollider->colliderTag.compare("LEVEL_COMPLETE")==0
                           ){
                               return PLAYER_LEVEL_COMPLETE_COLLISION;
                           }
                    }    
                }
            }
        }
    }
    return NO_COLLISION;
}
