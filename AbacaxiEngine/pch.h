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

		HMODULE hModule = GetModuleHandle(nullptr);				//returns handle to this application

		if (hModule) {

			char path[256];

			
			GetModuleFileNameA(hModule, path, sizeof(path));	//Copies the path of this application to "path" buffer

			
			PathRemoveFileSpecA(path);							//Removes .exe at the end of path

	
			strcat_s(path, "\\");								//Removes '\' at the end of path

			return std::string(path);
		}
		return "";
	}


	/*
		@brief Shared data holds various pointers to application's members.
		Furthermore, it holds some booleans for general purpose. Useful for communication between classes.
		Must be initialized at some point, preferably inside application's constructor.
	*/
	struct SharedData {
		class Window*			m_window     =  nullptr;	 //Pointer to abx::Window object. Foward declaration.
		class Resources*		m_resources  =  nullptr;	 //Pointer to abx::Resources object. Foward declaration.
		class StateManager*		m_stateMgr   =  nullptr;	 //Pointer to abx::StateManager object. Foward declaration.
		class EntityManager*    m_entityMgr  =  nullptr;	 //Pointer to abx::EntityManager object. Foward declaration.	
		sf::Time*				m_time       =  nullptr;	 //Pointer to application's time.
		bool					m_debug      =  false;		 //Application's visual debug
		bool					m_log        =  true;		 //Application's logging debug
	};




	/*
		@brief Wrapper function to spdlog::info. However, it checks if log boolean is true to display message.
	*/
	template <typename T>
	inline void LogInfo(SharedData *l_sharedData, const T& l_msg) {
		if (l_sharedData->m_log)
			spdlog::info(l_msg);
	}




	/*
		@brief Wrapper function to spdlog::warn. However, it checks if log boolean is true to display message.
	*/
	template <typename T>
	inline void LogWarn(SharedData* l_sharedData, const T& l_msg) {
		if (l_sharedData->m_log)
			spdlog::warn(l_msg);
	}



	/*
		@brief Wrapper function to spdlog::warn. However, it checks if log boolean is true to display message.
	*/
	template <typename T>
	inline void LogError(SharedData* l_sharedData, const T& l_msg) {
		if (l_sharedData->m_log)
			spdlog::error(l_msg);
	}


}