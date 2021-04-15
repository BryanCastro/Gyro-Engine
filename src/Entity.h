#pragma once
#include <vector>
#include <string>
#include <map>

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
        4-add component to componentTypeMap with its type as the key
        4-then initializes the component
        5-returns a reference to component*/
        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args){
            T* newComponent(new T(std::forward<TArgs>(args)...));
            newComponent->owner = this;
            components.emplace_back(newComponent);
            componentTypeMap[&typeid(*newComponent)] = newComponent;
            newComponent->Initialize();
            return *newComponent;
        }

        /*get the component by using its type as key to access it
        if we used the vector to access this component directly, we would have to iterate
        through the whole vector completely which is not ideal
        */
        template <typename T>
        T* GetComponent(){
            return static_cast<T*>(componentTypeMap[&typeid(T)]);
        }
    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component*> components;
        std::map<const std::type_info*, Component*> componentTypeMap;
};
