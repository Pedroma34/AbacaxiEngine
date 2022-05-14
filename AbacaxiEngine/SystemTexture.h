#pragma once



/*
	SystemTexture.h
	Purpose: Texture component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/




#include "System.h"



namespace abx {



	/*
		@brief Comoponent holds a texture and texture's chunck size (in case of sprite sheet)
		A wrapper for sf::Texture
	*/
	class SystemTexture : public System {


		Ref<sf::Texture>  m_texture;		//Texture holder that counts to resource ref count. If this class is destroyed, texture will be destroyed too.
		sf::Vector2f	  m_chuckSize;		//Chunck size of texture, like if it's being used as a sprite sheet.


	public:



		/*
			@brief Set chunck size. It's the chunck of the texture used for sprite sheets.
			@param const sf::Vector2f& size
		*/
		void SetChunckSize(const sf::Vector2f& l_size);



		/*
			@brief Applies texture. Idealy acquired from resource manager for ref count.
			@param std::shared_ptr<sf::Texture>& texture.
		*/
		void SetTexture(Ref<sf::Texture> l_texture);



		/*
			@brief Gets a weak pointer to texture.
			@retrurns std::weak_ptr<sf::Texture> texture
		*/
		WeakRef<sf::Texture> GetTexture();



		/*
			@brief Gets a chunck size. It's the chunck of the texture used for sprite sheets.
			@retrurns const sf::Vector2f& chunckSize.
		*/
		const sf::Vector2f& GetChunckSize() const;
	};


}