#pragma once

namespace Core
{
	class ProjectManager
	{
	public:
		ProjectManager();
		~ProjectManager();

		bool Init();
		void Run();
		void Destroy();
	private:
	};
}