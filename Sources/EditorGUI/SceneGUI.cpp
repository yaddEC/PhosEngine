#include "EditorGUI/SceneGUI.hpp"
#include "Engine/Transform.hpp"
#include "Engine/Input.hpp"
#include "Resource/ResourceManager.hpp"
#include "GUI/GUI.hpp"

using namespace Maths;
using namespace EditorGUI;
using namespace Engine;

void SceneGUI::DoUpdate()
{

		/*printf("ZA CHE AN ZONG WO");
		printf("XIN ZAI WO YOU BING CHILLING");
		printf("WO RHEN SHI RHUEN BING CHILLING");
		printf("DE CHU SUDU YU QIJIN JO BI BING CHILLING !");*/

		// TEMP Camera Input 
		if (isOnFocus)
		{
			Vec3 direction = Vec3(Vec2(0, 1).GetRotated(Vec2(), -m_sceneCamera.transform->rotation.y * (M_PI / 180)), 0);
			Vec3 forward = Vec3(direction.x, 0, direction.y);
			Vec3 left = Vec3(forward.z, 0, -forward.x);
			

			float speed = 0.4f;
			Input& input = Input::GetInstance();
			if (input.IsAnyKeyDown())
			{
				std::cout << "Key down" << std::endl;
			}

			m_sceneCamera.transform->position += forward * input.GetVerticalAxis() * speed;
			m_sceneCamera.transform->position += left * input.GetHorizontalAxis() * speed;
			if (input.IsKeyPressed(GLFW_KEY_SPACE))
				m_sceneCamera.transform->position.y += 1 * speed;
			if (input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
				m_sceneCamera.transform->position.y += -1 * speed;

			if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
			{
				m_sceneCamera.transform->rotation += Vec3(input.GetMouseDelta().y, input.GetMouseDelta().x, 0) * 0.4f;
			}
			/*ImGui::Text(std::to_string(Input::GetInstance().GetVerticalAxis()).c_str()); ImGui::SameLine();
			ImGui::Text(std::to_string(Input::GetInstance().GetHorizontalAxis()).c_str());
			ImGui::Text("%.2f, %.2f", input.GetMouseDelta().x, input.GetMouseDelta().y);*/
			
		}

		if(m_currentScene)
			m_sceneCamera.Render(m_currentScene->GetModelList(), size - Vec2(10, 35));

		GUI::DisplayVec2("Axis Input", Maths::Vec2(Input::GetInstance().GetVerticalAxis(), Input::GetInstance().GetHorizontalAxis()));
		GUI::DisplayVec2("Mouse Delta", Input::GetInstance().GetMouseDelta());
		/*ImGui::DragFloat3("Camera Position", &m_sceneCamera.transform->position.x, 0.05f);
		ImGui::DragFloat3("Camera Rotation", &m_sceneCamera.transform->rotation.x, 0.05f);*/
		GUI::EditVec3("Camera Position", m_sceneCamera.transform->position, 0.1f);
		GUI::EditVec3("Camera Rotation", m_sceneCamera.transform->rotation, 0.1f);

		//ImGui::Image((ImTextureID)m_sceneCamera.GetRenderTextureKey(), ImVec2(size.x - 10, size.y - 35), ImVec2(0, 1), ImVec2(1, 0));
		GUI::Image(m_sceneCamera.GetRenderTexture(), Maths::Vec2(size.x - 10, size.y - 35));

}
