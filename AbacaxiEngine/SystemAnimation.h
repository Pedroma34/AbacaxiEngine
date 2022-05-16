#pragma once



/*
	SystemAnimation.h
	Purpose: Animation component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "System.h"



namespace abx {

	/*
		@brief A struct wrapper for thor animation's data.
		Useful to manipulate animation since thor doesn't provide more control over it.
	*/
	struct AnimationData {



		std::string									m_name;					//key of the animation
		std::function<void(sf::Sprite&, float)>		m_animationFunction;	//thor's animation parameter
		sf::Time									m_time;					//duration of the animation



		/*
			@brief Constructor
		*/
		AnimationData(
			const std::string& l_name, 
			std::function<void(sf::Sprite&, float)> l_animation, 
			const sf::Time& l_time
		) :
			m_name(l_name), 
			m_animationFunction(l_animation), 
			m_time(l_time) 
		{}



	};



	/*
		@brief Component holds a thor animation feature. Improved wrapper for it.
	*/
	class SystemAnimation : public System {



		Ref<thor::Animator<sf::Sprite, std::string>>		  m_animator;		   //thor's animator. Hearth of system
		std::unordered_map<std::string, Ref<AnimationData>>	  m_animationBackup;   //backup of all animations. Allows us to modify animations on the fly
		std::unordered_map<std::string, std::string>		  m_animations;		   //list of animations. Allows us to keep records of all animations



	public:



		/*
			@brief Constructor. Initialize members.
		*/
		SystemAnimation();



		/*
			@brief Updates component using app's time as seconds.
			@param cosnt float& time
		*/
		void Update(const float& l_time) override;



		/*	
			@brief Adds an animation to the animator. Takes a name (serves as handle), the row number 
			(where it starts horizontally,) the column number (vertical), the size of the column, 
			and the total duration of the animation. The texture chunck size is derived from the sprite system.
			@param const std::string& name  (handle)
			@param const int& row			(horizontal)
			@param const int& column		(vertical)
			@param const int& sizeOfColumn  (horizontal size)
			@param const float& l_duration  (seconds)
		*/
		void AddAnimation(const std::string& l_name, const int& l_row, const int& l_column, const int& l_sizeOfColumn, const float& l_duration);



		/*
			@brief Plays an animation.
			@param const std::string name (handle to animation)
			@param bool loop (false default)
		*/
		void PlayAnimation(const std::string& l_name, bool l_loop = false);



		/*
			@brief. Deletes an animation from animator. Since Thor doesn't offer a delete feature, 
			this function will delete "m_animator" and copy all animations from backup to its new pointer
			with the exception of the animation that we want to delete, of course.
			@param const std::string& name
		*/
		void DeleteAnimation(const std::string& l_name);



		/*
			@brief Modifies duration of a certain animation. Much like the delete function, it deletes the 
			"m_animator" and copies all the backup animations to the new animator with the new modified duration.
			@param const std::string& animationKey
			@param const float& duration (seconds)
		*/
		void ModifyDuration(const std::string& l_animation, const float& l_duration);



		/*
			@brief Stops current animation
		*/
		void StopAnimation();



		/*
			@brief Checks if said animation is in the animator. Returns false if it is not.
			@param const std::stringn& animationKey
			@returns true if it's in memory
		*/
		bool HasAnimation(const std::string& l_animation);



		/*
			@brief Checks if any animation is currently playing.
			@returns true if an animation is playing
		*/
		bool IsPlayingAnimation() const;



		/*
			@brief Returns the handle of the current playing animation
			@returns std::string currentAnimation
		*/
		std::string GetCurrentAnimation();



		/*
			@brief Returns an unoredered map of a list of all animations
			@returns unordred_map animations
		*/
		const std::unordered_map<std::string, std::string>& GetAnimationList() const;



		/*
			@brief Gets a pointer to thor's animator.
			@returns std::weak_ptr<thor::Animator> animator
		*/
		WeakRef<thor::Animator<sf::Sprite, std::string>> GetAnimator();

		/*
			@brief Gets the duration of said animation
			@param const std::string& animationKey
			@returns float duration (seconds)
		*/
		float GetDuration(const std::string& l_animation);

		/*
			@brief Returns how many animations are bound.
			@return unsigned int size
		*/
		unsigned int GetAnimatorSize();



	};



}