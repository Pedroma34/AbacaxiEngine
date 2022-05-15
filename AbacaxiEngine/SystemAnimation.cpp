



/*
	SystemAnimation.cpp
	Purpose: Animation component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/




#include "pch.h"
#include "SystemAnimation.h"
#include "Entity.h"


namespace abx {




	/*___________________________________________________________________________________________________________________________________*/
	SystemAnimation::SystemAnimation() :
		m_animator(MakeRef<thor::Animator<sf::Sprite, std::string>>()),
		m_animationBackup(),
		m_animations()
	{}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	void SystemAnimation::Update(const float& l_time){
		/*Systems*/
		auto spriteSys = m_entity->GetSystem<SystemSprite>().lock();
		if (!spriteSys)
			return;
		auto textureSys = m_entity->GetSystem<SystemTexture>().lock();
		if (!textureSys)
			return;

		/*Updating animations*/
		m_animator->update(*SharedData::Time());
		m_animator->animate(*spriteSys->GetSprite());
	}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	void SystemAnimation::AddAnimation(const std::string& l_name, const int& l_row, const int& l_column, const int& l_sizeOfColumn, const float& l_duration){

		for (auto& itr : m_animations)
			if (itr.first == l_name)										//checking if animation is already in memory
				return;

		/*Systems*/
		auto spriteSys = m_entity->GetSystem<SystemSprite>().lock();
		if (!spriteSys)
			return;
		auto textureSys = m_entity->GetSystem<SystemTexture>().lock();
		if (!textureSys)
			return;

		/*Variables*/
		sf::Vector2f spriteSize(
			sf::Vector2f(
				spriteSys->GetSprite()->getGlobalBounds().width,
				spriteSys->GetSprite()->getGlobalBounds().height
			)
		);
		sf::Vector2f textureChunck = textureSys->GetChunckSize();

		/*Animation*/
		thor::FrameAnimation animation;
		for (int i = 0; i < l_sizeOfColumn; i++) {
			animation.addFrame(
				1.f,
				sf::IntRect(
					(l_row - 1) + i * textureChunck.x,
					(l_column - 1) * textureChunck.x,
					textureChunck.x,
					textureChunck.y
				)
			);
		}
		m_animations.emplace(l_name, l_name);									//adding animation handle to container
		m_animator->addAnimation(l_name, animation, sf::seconds(l_duration));	//adding animation to animator

		/*Backup*/
		auto backup = std::make_shared<AnimationData>(l_name, animation, sf::seconds(l_duration));
		m_animationBackup.emplace(l_name, std::move(backup));
	}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	void SystemAnimation::PlayAnimation(const std::string& l_name, bool l_loop){
		m_animator->playAnimation(l_name, l_loop);
	}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	void SystemAnimation::DeleteAnimation(const std::string& l_name){

		/*Checking*/
		auto stringItr = m_animations.find(l_name);				//Checking if animation is in list.
		if (stringItr == m_animations.end())	
			return;
		auto backupItr = m_animationBackup.find(l_name);		//Checking if animation is in backup.
		if (backupItr == m_animationBackup.end())
			return;
		if (!m_animator.use_count() == 1)						//Safety check. It should be unique since we're only passing weak pointers elsewhere
			return;

		m_animator.reset();										//Deleting animator;
		m_animationBackup.erase(backupItr);						//Deleting in backup
		m_animations.erase(stringItr);							//Deleting from animation list

		m_animator = std::make_shared<thor::Animator<sf::Sprite, std::string>>();
		for (auto& itr : m_animationBackup)						//Adding all animations again from backup
			m_animator->addAnimation(itr.second->m_name, itr.second->m_animationFunction, itr.second->m_time);
	}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	void SystemAnimation::ModifyDuration(const std::string& l_animation, const float& l_duration){
		if (!m_animator.use_count() == 1)								//Safety check. It should be unique since we're only passing weak pointers elsewhere
			return;
		auto stringItr = m_animations.find(l_animation);		//Checking if animation is in list and backup memory.
		if (stringItr == m_animations.end())
			return;
		auto backupItr = m_animationBackup.find(l_animation);	//Checking if animation is in backup.
		if (backupItr == m_animationBackup.end())
			return;

		auto copyBackup = std::make_shared<AnimationData>(		//Copying target animation amd passing the new duration to it
			backupItr->second->m_name,
			backupItr->second->m_animationFunction,
			sf::seconds(l_duration)
			);

		m_animator.reset();										//Deleting animator;
		m_animationBackup.erase(backupItr);						//Deleting in backup
		m_animations.erase(stringItr);							//Deleting from animation list

		m_animator = std::make_shared<thor::Animator<sf::Sprite, std::string>>();
		for (auto& itr : m_animationBackup)						//Adding backup animations with the exeption of our modified one
			m_animator->addAnimation(itr.second->m_name, itr.second->m_animationFunction, itr.second->m_time);

		m_animations.emplace(									//Adding our modified animation to list
			copyBackup->m_name, 
			copyBackup->m_name
		);
		m_animationBackup.emplace(								//Adding our modified animation to backup
			copyBackup->m_name, 
			copyBackup
		);
		m_animator->addAnimation(								//Adding our modified animation to animator
			copyBackup->m_name, 
			copyBackup->m_animationFunction, 
			copyBackup->m_time
		);
	}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	void SystemAnimation::StopAnimation(){
		m_animator->stopAnimation();
	}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	bool SystemAnimation::HasAnimation(const std::string& l_animation){
		for (auto& itr : m_animations)
			if (itr.first == l_animation)
				return true;
		return false;
	}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	bool SystemAnimation::IsPlayingAnimation() const{
		return m_animator->isPlayingAnimation();
	}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	std::string SystemAnimation::GetCurrentAnimation(){
		if (m_animator->isPlayingAnimation())
			return m_animator->getPlayingAnimation();
		return "";
	}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	const std::unordered_map<std::string, std::string>& SystemAnimation::GetAnimationList() const{
		return m_animations;
	}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	WeakRef<thor::Animator<sf::Sprite, std::string>> SystemAnimation::GetAnimator(){
		return m_animator;
	}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	float SystemAnimation::GetDuration(const std::string& l_animation){
		auto stringItr = m_animations.find(l_animation);
		if (stringItr == m_animations.end())
			return 0.0f;
		auto backupItr = m_animationBackup.find(l_animation);
		if (backupItr == m_animationBackup.end())
			return 0.0f;

		return backupItr->second->m_time.asSeconds();
	}
	/*___________________________________________________________________________________________________________________________________*/




	/*___________________________________________________________________________________________________________________________________*/
	unsigned int SystemAnimation::GetAnimatorSize(){
		return m_animations.size();
	}
	/*___________________________________________________________________________________________________________________________________*/




}
