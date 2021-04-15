#include "Entity.h"
#include "Component.h"

Entity::Entity(EntityManager& manager): manager(manager){
    this->isActive=true;
}
Entity::Entity(EntityManager& manager, std::string name): manager(manager), name(name){
    this->isActive=true;
}

//loops through all the entities components and calls their update function
void Entity::Update(float deltaTime){
    for(auto& component: components){
        component->Update(deltaTime);
    }
}

//loops through all the entities components and calls their render function
void Entity::Render(){
    for(auto& component: components){
        component->Render();
    }
}
void Entity::Destroy(){
    this->isActive = false;
}

bool Entity::IsActive() const{
    return this->isActive;
}