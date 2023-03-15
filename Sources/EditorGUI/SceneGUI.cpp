#include "EditorGUI/SceneGUI.hpp"
#include "Engine/Transform.hpp"
#include "Engine/Input.hpp"

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

			m_sceneCamera.transform->position += forward * Input::GetInstance().GetVerticalAxis() * speed;
			m_sceneCamera.transform->position += left * Input::GetInstance().GetHorizontalAxis() * speed;
			if (Input::GetInstance().IsKeyPressed(GLFW_KEY_SPACE))
				m_sceneCamera.transform->position.y += 1 * speed;
			if (Input::GetInstance().IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
				m_sceneCamera.transform->position.y += -1 * speed;

			if (Input::GetInstance().IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
			{
				m_sceneCamera.transform->rotation += Vec3(Input::GetInstance().GetMouseDelta().y, Input::GetInstance().GetMouseDelta().x, 0) * 0.4f;
			}

		}

		if(m_currentScene)
			m_sceneCamera.Render(m_currentScene->GetModelList(), size - Vec2(10, 35));

		ImGui::Image((ImTextureID)m_sceneCamera.GetRenderTextureKey(), ImVec2(size.x - 10, size.y - 35), ImVec2(0, 1), ImVec2(1, 0));


}
