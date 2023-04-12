#include "GUI/EditorGUI/SceneGUI.hpp"
#include "Engine/Transform.hpp"
#include "Engine/Input.hpp"
#include "Resource/ResourceManager.hpp"
#include "LowRenderer/Renderer.hpp"

using namespace Maths; 
using namespace Wrapper;
using namespace EditorGUI;
using namespace Engine;

SceneGUI::SceneGUI() : IGUI("Scene",true), speedModifier(1.000f)
{

}
void SceneGUI::UpdateCamera()
{
	Vec3 direction = Vec3(Vec2(0, 1).GetRotated(Vec2(), -m_sceneCamera.transform->rotation.y * DEG2RAD), 0);
	Vec3 forward = Vec3(direction.x, 0, direction.y);
	Vec3 left = Vec3(forward.z, 0, -forward.x);


	float speed = 0.4f;

	Input& input = Input::GetInstance();
	int scroDel = input.GetScrollDelta();

	if (!input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
	{
		return;
	}
	m_sceneCamera.transform->rotation += Vec3(input.GetMouseDelta().y, input.GetMouseDelta().x, 0) * 0.4f;

	if (input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
		speed *= 2;

	if (scroDel != 0)
	{
		if (speedModifier + scroDel/10.f <= 0.0001f)
			speedModifier /= 10;
		else if (speedModifier < 0.1f)
			speedModifier *= 10;
		else
			speedModifier += ((float)scroDel / 10.f);

		if (speedModifier > 2)
			speedModifier = 2;
		if (speedModifier < 0.001)
			speedModifier = 0.001;
	}
	speed *= speedModifier;

	//std::cout << speedModifier << std::endl;

	m_sceneCamera.transform->position += forward * input.GetVerticalAxis() * speed;
	m_sceneCamera.transform->position += left * input.GetHorizontalAxis() * speed;

	if (input.IsKeyPressed(GLFW_KEY_E))
		m_sceneCamera.transform->position.y += 1 * speed;
	if (input.IsKeyPressed(GLFW_KEY_Q))
		m_sceneCamera.transform->position.y += -1 * speed;
}
void SceneGUI::DoUpdate()
{

	/*printf("ZA CHE AN ZONG WO");
	printf("XIN ZAI WO YOU BING CHILLING");
	printf("WO RHEN SHI RHUEN BING CHILLING");
	printf("DE CHU SUDU YU QIJIN JO BI BING CHILLING !");*/

	// TEMP Camera Input 
	if (isOnFocus)
	{
		UpdateCamera();
	}

	if (m_currentScene)
		m_currentScene->GetRenderer()->RenderAll(&m_sceneCamera, size - Vec2(10, 35), false);
		//m_sceneCamera.Render(m_currentScene->GetRenderer()->GetMeshRenderers(), size - Vec2(10, 35));

	Wrapper::GUI::Image(m_sceneCamera.GetRenderTexture(), Maths::Vec2(size.x - 10, size.y - 35));
	m_sceneCamera.OnGUI();

}
