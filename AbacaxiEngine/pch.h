#pragma once


/*
	pch.h
	Purpose: Precompile headers to enhance compile time and hold some helper functions and data.
	@author Pedro Sergio de Castro Sarmento Filho
	10/May/2022
*/


//SFML
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"


//Thor
#include "Thor/Input.hpp"
#include "Thor/Resources.hpp"
#include "Thor/Animations.hpp"


//IMGUI
#include "imgui.h"
#include "imgui-SFML.h"


//Log
#include "spdlog/spdlog.h"


//String
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ostream>
#include <typeindex>


//Memory
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <array>
#include <stack>


//Math
#include <algorithm>


//Windows
#include <Windows.h>
#include <Shlwapi.h>   //needs to add in dependencies


namespace abx {
	/*
		Utilities
		Purpose: Provide helper functions and shortcuts for various methods.
		@author Pedro Sergio de Castro Sarmento Filho
		10/May/2022
	*/


	/*Shared Pointer*/
	template <typename T>
	using Ref = std::shared_ptr<T>;
	template <typename T, typename... Args>
	auto MakeRef(Args&&... args) { return std::make_shared<T>(std::forward<Args>(args)...); }


	/*Unique Pointer*/
	template <typename T>
	using Scope = std::unique_ptr<T>;
	template <typename T, typename... Args>
	auto MakeScope(Args&&... args) { return std::make_unique<T>(std::forward<Args>(args)...); }


	/*Weak Pointer*/
	template <typename T>
	using WeakRef = std::weak_ptr<T>;


	/*
	@brief Returns the current path to the executable file.
	@return Path to the current application.
	*/
	inline std::string GetDirectory() {


		char path[MAX_PATH];

		
		GetModuleFileNameA(NULL, path, sizeof(path));						 //Copies the path of this application to "path" buffer

		
		std::string::size_type pos = std::string(path).find_last_of("\\/");

	
		std::string result = std::string(path).substr(0, pos);

		result.append("\\");

		return result;

	}




	/*
		@brief Singleton shared data holds various pointers to application's members.
		Furthermore, it holds some booleans for general purpose. Useful for communication between classes.
		Each pointer should be bound in the crostuctor of the respective object.
	*/
	class SharedData {

		SharedData() {}
		class Window*		   m_window     =  nullptr;	   //Pointer to abx::Window object. Foward declaration.
		class Resources*       m_resources  =  nullptr;	   //Pointer to abx::Resources object. Foward declaration.
		class StateManager*    m_stateMgr   =  nullptr;	   //Pointer to abx::StateManager object. Foward declaration.
		class EntityManager*   m_entityMgr  =  nullptr;	   //Pointer to abx::EntityManager object. Foward declaration.
		class EventManager*    m_eventMgr   =  nullptr;	   //Pointer to abx::EventManager object. Foward declaration.
		sf::Time*              m_time       =  nullptr;	   //Pointer to application's time.
		sf::View*			   m_currentView = nullptr;	   //Pointer to window's current view
		bool				   m_debug      =  false;	   //Application's visual debug
		bool				   m_log        =  true;	   //Application's logging debug

	public:
		SharedData(const SharedData&) = delete;

		static SharedData& Get() {
			static SharedData instance;
			return instance;
		}

		//Setters
		static void SetWindow    (Window* l_window)           { Get().m_window     =  l_window;    }
		static void SetResource  (Resources* l_resource)      { Get().m_resources  =  l_resource;  }
		static void SetStateMgr  (StateManager* l_stateMgr)   { Get().m_stateMgr   =  l_stateMgr;  }
		static void SetEntityMgr (EntityManager* l_entityMgr) { Get().m_entityMgr  =  l_entityMgr; }
		static void SetEventMgr  (EventManager* l_eventMgr)   { Get().m_eventMgr   =  l_eventMgr;  }
		static void SetTime	     (sf::Time* l_time)           { Get().m_time       =  l_time;      }
		static void SetView		 (sf::View* l_view)			  { Get().m_currentView = l_view;      }
		static void SetDebug	 (bool l_debug)				  { Get().m_debug      =  l_debug;     }
		static void SetLog       (bool l_log)				  { Get().m_log        =  l_log;       }

		//Getters
		static Window*        Window()	   { return Get().m_window;       }
		static Resources*     Resource()   { return Get().m_resources;    }
		static StateManager*  StateMgr()   { return Get().m_stateMgr;     }
		static EntityManager* EntityMgr()  { return Get().m_entityMgr;    }
		static EventManager*  EventMgr()   { return Get().m_eventMgr;     }
		static sf::Time*	  Time()       { return Get().m_time;         }
		static sf::View&      View()	   { return *Get().m_currentView; }
		static const bool&    Debug()	   { return Get().m_debug;        }
		static const bool&    Log()		   { return Get().m_log;          }
	};

	

	/*
		@brief Debug static class wil hold some debug helper methods.
	*/
	class Debug {

		Debug() {}
		WeakRef<class Entity> m_selectedEntity  =  WeakRef<class Entity>();		//Keep track of last clicked entity
		WeakRef<class Entity> m_player			=  WeakRef<class Entity>();		//Pointer to player if any
		sf::Vector2f		  m_lastMousePos    =  sf::Vector2f(0, 0);			//Keep track of the last mouse position.

	public:

		Debug(const Debug&) = delete;

		static Debug& Get() {
			static Debug instance;
			return instance;
		}

		//Setters
		static void SetSelectedEntity (WeakRef<class Entity> l_selectedEntity) { Get().m_selectedEntity  =  l_selectedEntity; }
		static void SetPlayer         (WeakRef<class Entity> l_player)		   { Get().m_player = l_player;                   }
		static void SetLastMousePos   (const sf::Vector2f& l_mousePos)         { Get().m_lastMousePos = l_mousePos;           }

		//Getters
		static WeakRef<Entity> GetSelectedEntity()   { return Get().m_selectedEntity; }
		static WeakRef<Entity> GetPlayer()			 { return Get().m_player;         }
		static const sf::Vector2f& GetLastMousePos() { return Get().m_lastMousePos;   }
	};




	/*
		@brief Wrapper function to spdlog::info. However, it checks if log boolean is true to display message.
	*/
	template <typename T>
	inline void LogInfo(const T& l_msg) {
		if (SharedData::Log())
			spdlog::info(l_msg);
	}




	/*
		@brief Wrapper function to spdlog::warn. However, it checks if log boolean is true to display message.
	*/
	template <typename T>
	inline void LogWarn(const T& l_msg) {
		if (SharedData::Log())
			spdlog::warn(l_msg);
	}



	/*
		@brief Wrapper function to spdlog::warn. However, it checks if log boolean is true to display message.
	*/
	template <typename T>
	inline void LogError(const T& l_msg) {
		if (SharedData::Log())
			spdlog::error(l_msg);
	}


}