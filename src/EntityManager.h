#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include "Entity.h"
#include "Component.h"

class EntityManager {
	private:
		std::vector<Entity*> entities;
	public:
		void ClearData();
		void Update(float deltaTime);
		void Render();
		bool HasNoEntities();
		void ListAllEntities() const;
		Entity& AddEntity(std::string entityName, LayerType layer);
		std::vector<Entity*> GetEntities() const;
		std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
		unsigned int GetEntityCount();
		CollisionType CheckCollisions() const;
};

#endif
