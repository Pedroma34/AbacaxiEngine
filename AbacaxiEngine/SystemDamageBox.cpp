



/*
	SystemDamageBox.cpp
	Purpose: Damage box component for entities holds a rectangle collision box
	that will keep track of how many entities are inside of it.
	@author Pedro Sergio de Castro Sarmento Filho
	17/May/2022
*/




#include "pch.h"
#include "SystemDamageBox.h"
#include "EntityManager.h"
#include "Window.h"



namespace abx {




	/*____________________________________________________*/
	SystemDamageBox::SystemDamageBox() : 
		m_shape(),
		m_colliders()
	{
		m_shape.setFillColor(sf::Color(255, 0, 0, 30));  //red transparent
	}
	/*____________________________________________________*/



	/*____________________________________________________*/
	void SystemDamageBox::Update(const float& l_time){

		/*Systems*/
		auto spriteSys = m_entity->GetSystem<SystemSprite>().lock();
		if (!spriteSys)
			return;
		auto directionSys = m_entity->GetSystem<SystemDirection>().lock();
		if (!directionSys)
			return;


		/*Variables*/
		const auto& entityPos		 =  spriteSys->GetPosition						();
		const auto& entitySize		 =  spriteSys->GetSize							();
		const auto& thisPos			 =  m_shape.getPosition							();
		const auto& thisSize		 =  m_shape.getSize								();
		const auto& entityDirection  =  directionSys->GetDirection					();
																						 
		/*Logic*/																		 
		switch (entityDirection) {														 //Attach box to entity according to direction
		case Direction::Right:
			m_shape.setPosition(entityPos.x + thisSize.x, entityPos.y);
			break;
		case Direction::Left:
			m_shape.setPosition(entityPos.x - thisSize.x, entityPos.y);
			break;
		}

		SharedData::EntityMgr()->AddCollisionQueue(										 //Add collision logic to queue
			m_entity,																     //This entity
			&SystemDamageBox::CheckCollision,											 //Callback function
			this
		);	

		unsigned int count = 0;
		for (auto& itr : m_colliders) {													//Check if entities aren't colliding with box anymore.
			
			count++;

			auto entity = itr.lock();
			if (!entity)
				continue;

			auto hitBoxSys = entity->GetSystem<SystemHitBox>().lock();
			if (!hitBoxSys)
				continue;

			if (!m_shape.getGlobalBounds().intersects(
				hitBoxSys->GetShape()->getGlobalBounds()
			)) {
				m_colliders.erase(m_colliders.begin() + count - 1);                    //Remove entity pointer from container
				continue;
			}

		}
	}
	/*____________________________________________________*/



	/*____________________________________________________*/
	void SystemDamageBox::Render(){
		if (SharedData::Debug())
			SharedData::Window()->Draw(&m_shape);
	}
	/*____________________________________________________*/



	/*____________________________________________________*/
	void SystemDamageBox::SolveCollisions(){

		for (auto& itr : m_colliders) {

			/*System*/
			auto collider = itr.lock();
			if (!collider)
				continue;
			auto colliderHealthSy= collider->GetSystem<SystemHealth>().lock();
			if (!colliderHealthSy)
				return;
			auto thisDamageSys = m_entity->GetSystem<SystemDamage>().lock();
			if (!thisDamageSys)
				return;

			/*Variables*/
			const auto& thisDamage      =  thisDamageSys->GetDamage();
			const auto& colliderHealth  =  colliderHealthSy->GetHealth();
			float result			    =  colliderHealth - thisDamage;

			/*Logic*/
			if (result <= 0)													//Applying damage
				colliderHealthSy->SetHealth(0);
			else
				colliderHealthSy->SetHealth(
					colliderHealth - thisDamage
				);

			collider->SetState<StateEntityHurt>();
		}

	}
	/*____________________________________________________*/



	/*____________________________________________________*/
	void SystemDamageBox::CheckCollision(WeakRef<Entity> l_collider){

		auto collider = l_collider.lock();
		if (!collider)
			return;
		if (collider->GetId() == m_entity->GetId())
			return;

		/*Systems*/
		auto colliderSpriteSys = collider->GetSystem<SystemSprite>().lock();
		if (!colliderSpriteSys)
			return;
		auto colliderHitBoxSys = collider->GetSystem<SystemHitBox>().lock();
		if (!colliderHitBoxSys)
			return;

		/*Logic*/
		if (colliderHitBoxSys->GetShape()->getGlobalBounds().intersects(		//If collider's hitbox is inside this damage box
			m_shape.getGlobalBounds())) 
			AddToColliders(collider);
		
	}
	/*____________________________________________________*/



	/*____________________________________________________*/
	void SystemDamageBox::SetSize(const sf::Vector2f& l_size){
		m_shape.setSize(l_size);
		m_shape.setOrigin(
			m_shape.getGlobalBounds().width / 2,
			m_shape.getGlobalBounds().height / 2
		);

	}
	/*____________________________________________________*/



	/*____________________________________________________*/
	void SystemDamageBox::SetSize(const float& l_x, const float& l_y){
		m_shape.setSize(sf::Vector2f(l_x, l_y));
		m_shape.setOrigin(
			m_shape.getGlobalBounds().width / 2,
			m_shape.getGlobalBounds().height / 2
		);

	}
	/*____________________________________________________*/



	/*____________________________________________________*/
	void SystemDamageBox::SetColor(const sf::Color& l_color){
		m_shape.setFillColor(l_color);
	}
	/*____________________________________________________*/



	/*____________________________________________________*/
	const sf::Vector2f& SystemDamageBox::GetSize() const{
		return m_shape.getSize();
	}
	/*____________________________________________________*/



	/*____________________________________________________*/
	const sf::Color& SystemDamageBox::GetColor() const{
		return m_shape.getFillColor();
	}
	/*____________________________________________________*/



	/*____________________________________________________*/
	const sf::FloatRect& SystemDamageBox::GetGlobalBounds() const{
		return m_shape.getGlobalBounds();
	}
	/*____________________________________________________*/



	/*____________________________________________________*/
	void SystemDamageBox::AddToColliders(WeakRef<Entity> l_collider){

		auto collider = l_collider.lock();
		if (!collider)
			return;

		for (auto& itr : m_colliders) {							//Checkign if collider is already in container
			auto entity = itr.lock();
			if (entity)
				if (entity->GetId() == collider->GetId())
					return; 
		}

		m_colliders.push_back(l_collider);						//Adding to container

	}
	/*____________________________________________________*/




}