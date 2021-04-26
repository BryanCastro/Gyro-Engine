#include <iostream>
#include "Entity.h"
#include "Component.h"

Entity::Entity(EntityManager& manager): manager(manager){
    this->isActive=true;
}
Entity::Entity(EntityManager& manager, std::string name, LayerType layer): manager(manager), name(name), layer(layer){
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

void Entity::ListAllComponents() const{
    std::cout<<"\tComponents:"<<std::endl;
    for(auto& component: componentTypeMap){
        std::cout<<"\t\t"<<component.first->name()<<std::endl;
    }
    std::cout<<std::endl;
}