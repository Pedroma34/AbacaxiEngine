

/*
	StateGame.cpp
	Purpose: Game machine state that will update and render game's logic.
	@author Pedro Sergio de Castro Sarmento Filho
	11/May/2022
*/


#include "pch.h"
#include "StateGame.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Window.h"
#include "EventManager.h"
#include "CommandInputs.h"


namespace abx {




	/*_________________________________________________________________________*/
	StateGame::StateGame() {}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	StateGame::~StateGame() {
		//Debugging
		LogWarn(
			"[STATE] Machine state destroyed: [" +
			std::string(typeid(*this).name()) + "]"
		);
	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::OnCreate() {

		/*Variables*/
		const auto& winSize = SharedData::Window()->GetSize();

		/*Entities*/
		auto player = SharedData::EntityMgr()->Add<EntityMinotaur>().lock();
		auto playerSpriteSys = player->GetSystem<SystemSprite>().lock();
		playerSpriteSys->SetPosition(
			winSize.x / 2,
			winSize.y / 2
		);
		auto enemy = SharedData::EntityMgr()->Add<EntityBandit>().lock();
		auto enemySpriteSys = enemy->GetSystem<SystemSprite>().lock();
		enemySpriteSys->SetPosition(
			rand() % winSize.x + 0,
			rand() % winSize.y + 0
		);

		/*Player Events*/
		SharedData::EventMgr()->Bind<CommandMoveRight>(player, sf::Keyboard::D, true);
		SharedData::EventMgr()->Bind<CommandMoveLeft>(player, sf::Keyboard::A, true);
		SharedData::EventMgr()->Bind<CommandMoveUp>(player, sf::Keyboard::W, true);
		SharedData::EventMgr()->Bind<CommandMoveDown>(player, sf::Keyboard::S, true);
		SharedData::EventMgr()->Bind<CommandAttack>(player, sf::Keyboard::Space, false);
		SharedData::EventMgr()->Bind<CommandKillEntity>(player, sf::Keyboard::Num1, false);

		/*Enemy Events*/
		SharedData::EventMgr()->Bind<CommandMoveRight>(enemy, sf::Keyboard::Right, true);
		SharedData::EventMgr()->Bind<CommandMoveLeft>(enemy, sf::Keyboard::Left, true);
		SharedData::EventMgr()->Bind<CommandMoveUp>(enemy, sf::Keyboard::Up, true);
		SharedData::EventMgr()->Bind<CommandMoveDown>(enemy, sf::Keyboard::Down, true);
		SharedData::EventMgr()->Bind<CommandAttack>(enemy, sf::Keyboard::Enter, false);
		SharedData::EventMgr()->Bind<CommandKillEntity>(enemy, sf::Keyboard::Num2, false);

		/*Data Eventss*/
		SharedData::EventMgr()->Bind<CommandDestroyApplication>(sf::Keyboard::F1, false);
		SharedData::EventMgr()->Bind<CommandDebug>(sf::Keyboard::Tab, false);
		SharedData::EventMgr()->Bind<CommandSelectEntity>(sf::Mouse::Left, false);
	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::OnDestroy() {

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::Activate() {

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::Deactivate() {

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::Update(const float& l_time) {

		SharedData::EntityMgr()->Update(l_time);

		UpdateDebugUi(l_time);

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::Render() {
		SharedData::EntityMgr()->Render();

		/*Debug*/
		if (!Debug::GetSelectedEntity().expired() &&
			SharedData::Debug()) {
			auto entity = Debug::GetSelectedEntity().lock();
			auto spriteSys = entity->GetSystem<SystemSprite>().lock();
			if (!spriteSys)
				return;
			sf::CircleShape circle;
			circle.setFillColor(sf::Color(0, 255, 255, 150));
			circle.setRadius(50.f);
			circle.setOrigin(
				circle.getGlobalBounds().width / 2,
				circle.getGlobalBounds().height / 2
			);
			circle.setPosition(
				spriteSys->GetPosition().x,
				spriteSys->GetPosition().y
			);
			SharedData::Window()->Draw(&circle);
		}
	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::UpdateDebugUi(const float& l_time) {

		if (!SharedData::Debug())
			return;

		/*Variables*/
		const auto& winSize = SharedData::Window()->GetSize();
		bool b = false;

		/*ImGui*/
		{
			/*Window*/
			ImGui::Begin("Debug", &b, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
			ImGui::SetWindowSize(ImVec2(winSize.x * 0.25, winSize.y));
			ImGui::SetWindowPos(ImVec2(0, 0));

			/*FPS*/
			{
				float fps = floor(1.f / l_time);
				ImGui::Text(std::string("FPS: " + std::to_string(fps)).c_str());
			}

			/*Adding Entities*/
			{
				ImGui::Text("Adding Entity");
				static const char* entities[]{ "Minotaur", "Bandit" };
				static int selectedEntity = 0;
				ImGui::Combo("Entity", &selectedEntity, entities, IM_ARRAYSIZE(entities), 3);

				if (ImGui::Button("Add entity")) {

					std::string entity = entities[selectedEntity];

					if (entity == "Minotaur") {
						auto ent = SharedData::EntityMgr()->Add<EntityMinotaur>().lock();
						auto spriteSys = ent->GetSystem<SystemSprite>().lock();
						spriteSys->SetPosition(
							rand() % winSize.x - spriteSys->GetSize().x + (spriteSys->GetSize().y * 2),
							rand() % winSize.y - spriteSys->GetSize().y + spriteSys->GetSize().y
						);
						Debug::SetSelectedEntity(ent);
					}
					else if (entity == "Bandit") {
						auto ent = SharedData::EntityMgr()->Add<EntityBandit>().lock();
						auto spriteSys = ent->GetSystem<SystemSprite>().lock();
						spriteSys->SetPosition(
							rand() % winSize.x - spriteSys->GetSize().x + (spriteSys->GetSize().y * 2),
							rand() % winSize.y - spriteSys->GetSize().y + spriteSys->GetSize().y
						);
						Debug::SetSelectedEntity(ent);
					}

				}
			}

			/*Viewing Entities*/
			{
				unsigned int entityCount = SharedData::EntityMgr()->GetSize();
				ImGui::Text(std::string("Entities in memory: [" + std::to_string(entityCount) + "]").c_str());
				static bool isSystemSelected = false;
				auto entitySelected = Debug::GetSelectedEntity();

				if (entityCount > 0)
					if (ImGui::Button("Remove all entitites"))
						SharedData::EntityMgr()->RemoveAll();
				if (entitySelected.expired())
					ImGui::Text("No Entity Selected");

				else {
					ImGui::Text("Entity Selected");
					if (ImGui::Button("Remove selected entity")) 
						SharedData::EntityMgr()->Remove(Debug::GetSelectedEntity().lock()->GetId());
					
					ImGui::BeginChild("Child Window", ImVec2(ImGui::GetContentRegionAvail().x * 1.f, 260),
						false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

					unsigned int systemsCount = entitySelected.lock()->GetSystemCount();					//How many systems entity has
					ImGui::Text(std::string("Systems Count: " + std::to_string(systemsCount)).c_str());

					/*Displauing Systems*/
					static std::string systemString = "";
					std::vector<std::string> systemNames;
					for (int i = 0; i < systemsCount; i++) {

						auto system = entitySelected.lock()->GetSystem(i).lock();
						systemNames.push_back(typeid(*system).name());

					}


					std::sort(												//Sorting in alphabetical order
						systemNames.begin(), 
						systemNames.end(), 
						[](std::string a, std::string b) {return a < b; }
					);
					for (int i = 0; i < systemsCount; i++) {
						if (ImGui::Button(std::string("System Name: " + systemNames.at(i)).c_str())) {
							isSystemSelected = true;
							systemString = systemNames.at(i);
						}
					}



					ImGui::EndChild();

					/*Displaying Systems Info if selected*/
					if (isSystemSelected) {

						/*Animation System*/
						if (systemString == "class abx::SystemAnimation") {

							auto sys = entitySelected.lock()->GetSystem<SystemAnimation>().lock();
							const auto& size = sys->GetAnimatorSize();
							const auto& currentAnim = sys->GetCurrentAnimation();
							ImGui::Text(std::string("[Animation System]").c_str());
							ImGui::Text(std::string("Animations [" + std::to_string(size) + "]").c_str());
							ImGui::Text(std::string("Current Animation [" + currentAnim + "]").c_str());
							ImGui::Text("List of animations: ");
							const auto& animations = sys->GetAnimationList();
							for (auto& itr : animations) {
								const auto& duration = sys->GetDuration(itr.first);
								ImGui::Text(std::string("[" + itr.second + "]" +
									" [" + std::to_string(duration) + "]seconds").c_str());
							}

						}

						else if (systemString == "class abx::SystemDirection") {

							auto sys = entitySelected.lock()->GetSystem<SystemDirection>().lock();
							const auto& currentDirection = sys->GetDirection();
							ImGui::Text(std::string("[Direction System]").c_str());
							ImGui::Text(std::string("Current Directoin: " + sys->GetDirectonString()).c_str());
							ImGui::Text(std::string("Is Inverted: " + std::to_string(sys->GetInverted())).c_str());

						}


						/*Health System*/
						else if (systemString == "class abx::SystemHealth") {

							auto sys = entitySelected.lock()->GetSystem<SystemHealth>().lock();
							const auto& maxHealth = sys->GetMaxHealth();
							const auto& health = sys->GetHealth();
							const float* healthAddress = &health;
							ImGui::Text(std::string("[SpeedSystem System]").c_str());
							ImGui::Text(std::string("Max Health[" + std::to_string(maxHealth) + "]").c_str());
							ImGui::Text(std::string("Current Health[" + std::to_string(health) + "]").c_str());
							if (ImGui::Button("Heal entity"))
								sys->SetHealth(sys->GetMaxHealth());
							if (ImGui::Button("Kill entity"))
								sys->SetHealth(0);

						}

						/*Speed System*/
						else if (systemString == "class abx::SystemSpeed") {

							auto sys = entitySelected.lock()->GetSystem<SystemSpeed>().lock();
							const auto& maxSpeed = sys->GetMaxSpeed();
							const auto& speed = sys->GetSpeed();
							ImGui::Text(std::string("[SpeedSystem System]").c_str());
							ImGui::Text(std::string("Max Speed[" + std::to_string(maxSpeed) + "] pixels per second").c_str());
							ImGui::Text(std::string("Normal Speed[" + std::to_string(speed) + "] pixels per second").c_str());

						}


						/*Sprite System*/
						else if (systemString == "class abx::SystemSprite") {

							auto sys = entitySelected.lock()->GetSystem<SystemSprite>().lock();
							const auto& size = sys->GetSize();
							const auto& pos = sys->GetPosition();
							ImGui::Text(std::string("[Sprite System]").c_str());
							ImGui::Text(std::string("Sprite Size[" + std::to_string(size.x) + "]" +
								"[" + std::to_string(size.y) + "]").c_str());
							ImGui::Text(std::string("Sprite Position[" + std::to_string(pos.x) + "]" +
								"[" + std::to_string(pos.y) + "]").c_str());

						}

						/*Texture System*/
						else if (systemString == "class abx::SystemTexture") {

							auto sys = entitySelected.lock()->GetSystem<SystemTexture>().lock();
							const auto& chunckSize = sys->GetChunckSize();
							ImGui::Text(std::string("[Texture System]").c_str());
							ImGui::Text(std::string("Chunck Size[" + std::to_string(chunckSize.x) + "]" +
								"[" + std::to_string(chunckSize.y) + "]").c_str());

						}

					}
				}
			}
			ImGui::End();
		}
		/*_________________________________________________________________________*/




	}
}