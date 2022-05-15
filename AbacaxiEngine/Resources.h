#pragma once


/*
	Resources.h
	Purpose: Manage application's various resource type, like textures, fonts, etc. Works using reference count and
	thor's resource manager.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/


#include "pch.h"


namespace abx {


	/*
		@brief Class that manages application's various resources, like textures, fonts, etc. Works using reference count.
		Uses thor's resource manager.
		To aquire a resource, call aquire method. Resource is destroyed if there are not shared pointers pointing to that
		resource.
	*/
	class Resources {

		thor::ResourceHolder <sf::Font, std::string, thor::Resources::RefCounted>		 m_fonts;		 //Thor's resource manager for fonts. Based on ref count.
		thor::ResourceHolder <sf::Texture, std::string, thor::Resources::RefCounted>	 m_textures;	 //Thor's resource manager for textures. Based on ref count.
		std::unordered_map   <std::string, std::string>									 m_textureKey;	 //name and location
		std::unordered_map   <std::string, std::string>									 m_fontKey;		 //name and location

	public:



		/*
			@brief Constructor. Binds keys and locations.
		*/
		Resources() {

			Utils::SharedData::SetResource(this);

			//Textures//
			m_textureKey [ "Minotaur" ]  =  GetDirectory() + "Data/Textures/minotaur.png";
			m_textureKey [ "Bandit"   ]  =  GetDirectory() + "Data/Textures/bandit.png";

			//Fonts//
			m_fontKey    [ "Arial" ]  =  GetDirectory() + "Data/Fonts/arial.ttf";

		}



		/*
			@brief Destructor.
		*/
		~Resources() {}



		/*
			@brief	Returns a shared pointer to a texture. If texture is not
			already in memory, it loads in. Else, it returns a reference, 
			increasing ref count. Returns nullptr if resource id is not in container.
			@param const std::string& textureName
			@returns std::shared_ptr<sf::Texture> texture
		*/
		Ref<sf::Texture>AcquireTexture(const std::string& l_resourceId) {
			auto itr = m_textureKey.find(l_resourceId);
			if (itr == m_textureKey.end()) {
				//Debug//
				spdlog::error("Texture not found: [" + l_resourceId + "]");

				return nullptr;
			}
			//Debug//
			spdlog::info("Texture acquired: [" + itr->first + "]");
			return m_textures.acquire(itr->first, thor::Resources::fromFile<sf::Texture>(itr->second), thor::Resources::Reuse);
		}


		/*
			@brief	Returns a shared pointer to a font. If font is not
			already in memory, it loads in. Else, it returns a reference,
			increasing ref count. Returns nullptr if resource id is not in container.
			@param const std::string& fontName
			@returns std::shared_ptr<sf::Font> font
		*/
		Ref<sf::Font> AcquireFont(const std::string& l_resourceId) {
			auto itr = m_fontKey.find(l_resourceId);
			if (itr == m_fontKey.end()) {
				//Debug//
				spdlog::error("Font not found: [" + l_resourceId + "]");
				return nullptr;
			}
			//Debug//
			spdlog::info("Font acquired: [" + itr->first + "]");
			return m_fonts.acquire(itr->first, thor::Resources::fromFile<sf::Font>(itr->second), thor::Resources::Reuse);
		}
	};

}