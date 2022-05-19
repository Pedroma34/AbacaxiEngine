#pragma once



/*
	SystemDamageBox.h
	Purpose: Damage box component for entities holds a rectangle collision box
	that will keep track of how many entities are inside of it.
	@author Pedro Sergio de Castro Sarmento Filho
	17/May/2022
*/



#include "System.h"



namespace abx {



	/*
		@brief Damage box component for entities holds a rectangle collision box
		that will keep track of how many entities are inside of it.
	*/
	class SystemDamageBox : public System {

		sf::RectangleShape			  m_shape;		//Damage box shape
		std::vector<WeakRef<Entity>>  m_colliders;  //Pointer to entities inside damage box

	public:



		/*
			@brief Constructor
		*/
		SystemDamageBox();



		/*
			@brief Updates system using app's time as seconds.
			It attaches damage box to entity according to direactoin,
			adds collision logic to collision queue in the managger,
			and removes entities pointers from damge box if they're are not inside.
			@param const float& time
		*/
		void Update(const float& l_time) override;



		/*
			@brief Renders box if visual debug is on
		*/
		void Render() override;



		/*
			@brief Solves collision logic of entities inside the box.
			Normally called on attack states.
		*/
		void SolveCollisions();



		/*
			@brief Checks if entities enter damage box. Callback called inside entity manager.
		*/
		void CheckCollision(WeakRef<Entity> l_collider);



		/*
			@brief
		*/
		void SetSize(const sf::Vector2f& l_size);



		/*
			@brief
		*/
		void SetSize(const float& l_x, const float& l_y);



		/*
			@brief
		*/
		void SetColor(const sf::Color& l_color); //Color in debug mode



		/*
			@brief
		*/
		const sf::Vector2f& GetSize() const;



		/*
			@brief
		*/
		const sf::Color& GetColor() const;



		/*
			@brief
		*/
		const sf::FloatRect& GetGlobalBounds() const;



		/*
			@brief
		*/
		const sf::Vector2f& GetPosition() const;

	private:


		/*
			@brief Adds entity pointer to container, which contains pointers to 
			all entities inside box.
		*/
		void AddToColliders(WeakRef<Entity> l_collider);



	};



}