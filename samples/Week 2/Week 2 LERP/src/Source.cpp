/*
Week 2 tutorial sample - LERP
Quinn Daggett 2021
*/

#include "NOU/App.h"
#include "NOU/Input.h"
#include "NOU/Entity.h"
#include "NOU/CCamera.h"
#include "NOU/CMeshRenderer.h"
#include "NOU/Shader.h"
#include "NOU/GLTFLoader.h"

#include "Logging.h"

#include <memory>

using namespace nou;

// TODO: create a templated LERP function

void testfunction(Entity e) {
	if (KEYEVENTF_KEYUP) {
		e.transform.m_pos = glm::vec3(0.0f, 0.0f + 0.1f, 4.0f);
		e.transform.RecomputeGlobal();
	}
}

int main()
{
	// Create window and set clear color
	App::Init("Week 2 tutorial - LERP", 800, 600);
	App::SetClearColor(glm::vec4(0.0f, 0.27f, 0.4f, 1.0f));

	App::Tick();

	// Load vertex and fragment shaders
	std::unique_ptr vs_litShader = std::make_unique<Shader>("shaders/texturedlit.vert", GL_VERTEX_SHADER);
	std::unique_ptr fs_litShader = std::make_unique<Shader>("shaders/texturedlit.frag", GL_FRAGMENT_SHADER);

	// Activate shader program
	ShaderProgram shaderProgram = ShaderProgram({ vs_litShader.get(), fs_litShader.get() });

	// Create and load mesh for duck
	Mesh mesh_ducky;
	GLTF::LoadMesh("duck/Duck.gltf", mesh_ducky);

	// Create material and load textures for duck
	Texture2D tex2D_ducky = Texture2D("duck/DuckCM.png");
	Material mat_ducky(shaderProgram);
	mat_ducky.AddTexture("albedo", tex2D_ducky);

	// Create and set up camera
	Entity ent_camera = Entity::Create();
	CCamera& cam = ent_camera.Add<CCamera>(ent_camera);
	cam.Perspective(60.0f, 1.0f, 0.1f, 100.0f);
	ent_camera.transform.m_pos = glm::vec3(0.0f, 0.0f, 4.0f);

	// Creating duck entity
	Entity ent_ducky = Entity::Create();
	ent_ducky.Add<CMeshRenderer>(ent_ducky, mesh_ducky, mat_ducky);
	ent_ducky.transform.m_scale = glm::vec3(0.005f, 0.005f, 0.005f);
	ent_ducky.transform.m_pos = glm::vec3(0.0f, -1.0f, 0.0f);
	ent_ducky.transform.m_rotation = glm::angleAxis(glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// TODO: define necessary variables for LERPing

	// Main loop
	while (!App::IsClosing() && !Input::GetKeyDown(GLFW_KEY_ESCAPE))
	{
		App::FrameStart();
		float deltaTime = App::GetDeltaTime();
		// TODO: LERP duck properties


		// Update camera and duck, draw duck
		ent_camera.Get<CCamera>().Update();

		ent_ducky.transform.RecomputeGlobal();

		ent_ducky.Get<CMeshRenderer>().Draw();

		//testfunction(ent_ducky);
		ent_ducky.transform.m_scale.x += 0.00001 * deltaTime;
		ent_ducky.transform.m_scale.y += 0.00001 * deltaTime;
		ent_ducky.transform.m_scale.z += 0.00001 * deltaTime;

			//ent_ducky.transform.m_pos.x += 1 * deltaTime;
			ent_ducky.transform.m_pos.y += 1 * deltaTime;
			ent_ducky.transform.m_pos.z += 1 * deltaTime;

			ent_ducky.transform.m_rotation.x += 0.5 * deltaTime;
			ent_ducky.transform.m_rotation.y += 0.5 * deltaTime;
			ent_ducky.transform.m_rotation.z += 0.5 * deltaTime;
			float t = 0;
			t += 0.5 * deltaTime;
			ent_ducky.transform.m_pos.x += 0.1 * deltaTime;
			//Material::m_color(mat_ducky);
		//	mat_ducky.m_color(1.f, 1.f, 1.f);
			mat_ducky.m_color.x += 100 * deltaTime;
			mat_ducky.m_color.y += 2 * deltaTime;
			mat_ducky.m_color.z += 0.200 * deltaTime;

			ent_ducky.transform.RecomputeGlobal();
			ent_ducky.Get<CMeshRenderer>().Draw();
		//ent_ducky.Get

		// Draw everything we just did to the screen
		App::SwapBuffers();
	}

	// Destroy window
	App::Cleanup();

	return 0;
}