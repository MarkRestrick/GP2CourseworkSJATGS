#include "MyGame.h"
#define modelFP ASSET_PATH+MODEL_PATH
#define shaderFP ASSET_PATH + SHADER_PATH
#define textureFP ASSET_PATH + TEXTURE_PATH

const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string MODEL_PATH = "/models";

MyGame::MyGame()
{
	//m_TestGO = nullptr;
}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{	
	//shared_ptr<GameObject> OjArray[]{m_TestGO};

	m_Camera = shared_ptr<CameraController>(new CameraController);
	//Camera

	//KS Changed to Array and vector that can be iterated through
	string modelPath [] {"/Earth.fbx", "/Earth.fbx", "/unitCube.fbx", "/unitCube.fbx", "/unitCube.fbx", "/unitCube.fbx", "/unitCube.fbx" };
	string vsFilename[] {"/parallaxMappingVS2.glsl" ,"/parallaxMappingVS2.glsl", "/parallaxMappingVS2.glsl", "/parallaxMappingVS2.glsl", "/parallaxMappingVS2.glsl", "/parallaxMappingVS2.glsl", "/parallaxMappingVS2.glsl" };
	string fsFilename[] {"/parallaxMappingFS2.glsl" ,"/parallaxMappingFS2.glsl", "/parallaxMappingFS2.glsl", "/parallaxMappingFS2.glsl", "/parallaxMappingFS2.glsl", "/parallaxMappingFS2.glsl" , "/parallaxMappingFS2.glsl" };
	string diffTextureFileName[]{"/bricks_diff.jpg","/TBall_Diff.jpg", "/floor.jpg", "/bricks_diff.jpg", "/bricks_diff.jpg", "/bricks_diff.jpg" , "/bricks_diff.jpg" };
	string specTextureFilename[]{"/bricks_spec.png","/TBall_Spec.png", "/Floor_Spec.png", "/bricks_spec.png", "/bricks_spec.png", "/bricks_spec.png", "/bricks_spec.png" };
	string normTextureFilename[]{"/bricks_norm.png","/TBall_Norm.png", "/Floor_N.png", "/bricks_norm.png", "/bricks_norm.png", "/bricks_norm.png", "/bricks_norm.png" };
	string heightTextureFilename[]{"/bricks_height.png","/TBall_Height.png", "/Floor_H.png", "/bricks_height.png", "/bricks_height.png", "/bricks_height.png", "/bricks_height.png" };

	//string vsFilenameContainter[] { light, lightex, normal, parallax} MRKS Later optimisation, save objects and call via define

	

	vec3 scale[]
	{
		vec3(5.0f, 5.0f, 5.0f),
		vec3(5.0f, 5.0f, 5.0f),
		vec3(100.0f, 1.0f, 100.0f), //MR Floor
		vec3(100.0f, 50.0f, 1.0f), //MR Back wall
		vec3(1.0f, 50.0f, 100.0f), //MR left wall
		vec3(1.0f, 50.0f, 100.0f) //MR Right wall
	};
	vec3 position[]
	{
		vec3(25.0f, 5.0f, 5.0f),
		vec3(0.0f, 20.0f, 50.0f),
		vec3(0.0f, 0.0f, 0.0f), //MR Floor
		vec3(0.0f, 25.0f, 0.0f), //MR Back Wall
		vec3(-50.0f, 25.0f, 0.0f), //MR left wall
		vec3(50.0f, 25.0f, 0.0f) //MR right wall


	};
	vec3 rotation[]
	{
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, 0.0f), //MR Floor
		vec3(0.0f, 0.0f, 0.0f), //MR Back Wall
		vec3(0.0f, 0.0f, 0.0f), //MR left wall
		vec3(0.0f, 0.0f, 0.0f)

	};

	

	

	int arrayLength = sizeof(modelPath) / sizeof(modelPath[0]);

	for (int i = 0; i < arrayLength; i++)
	{
		m_TestGO = shared_ptr<GameObject>(loadModelFromFile(modelFP+modelPath[i]));

		m_TestGO->loadShadersAndTextures(shaderFP+vsFilename[i], shaderFP+fsFilename[i], textureFP+diffTextureFileName[i], textureFP+specTextureFilename[i], textureFP+normTextureFilename[i], textureFP+heightTextureFilename[i]);
		//m_TestGO->setTransform(vec3(5.0f, 5.0f, 5.0f), vec3(i*25.0f, i*10.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f));
		//m_TestGO->addChild(m_TestGO);
		m_TestGO->setTransform(scale[i],position[i],rotation[i]);
		GOList.push_back(m_TestGO);
	}

	m_CameraRotation = vec3(0.0f, 0.0f, 0.0f);
	m_CameraPosition = vec3(0.0f, 25.0f, 150.0f);
	m_CameraLookAtPosition = vec3(cos(m_CameraRotation.y), 0, sin(m_CameraRotation.y));

	m_Light = shared_ptr<Light>(new Light());
	m_Light->DiffuseColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->Direction = vec3(0.0f, 0.0f, -1.0f);
	m_AmbientLightColour = vec4(0.5f, 0.5f, 0.5f, 1.0f);

	/*
	m_PostBuffer = shared_ptr<PostProcessBuffer>(new PostProcessBuffer());
	m_PostBuffer->create(m_WindowWidth, m_WindowHeight);

	m_ScreenAlignedQuad = shared_ptr<ScreenAlignedQuad>(new ScreenAlignedQuad());
	m_ScreenAlignedQuad->create();
	*/


	/*
	const std::string ASSET_PATH = "assets";
	const std::string SHADER_PATH = "/shaders";
	string fsPostFilename = ASSET_PATH + SHADER_PATH + "/colourFilterFS.glsl";
	

	m_PostEffect = shared_ptr<PostProcessingEffect>(new PostProcessingEffect());
	m_PostEffect->loadShader(fsPostFilename);
	*/
	


	m_PassThroughPostProcess = unique_ptr<PostProcess>(new PostProcess());
	m_PassThroughPostProcess->create(m_WindowWidth, m_WindowHeight, ASSET_PATH + SHADER_PATH + "/colourFilterFS.glsl");


	m_PassThroughPostProcess2 = unique_ptr<PostProcess>(new PostProcess());
	m_PassThroughPostProcess2->create(m_WindowWidth, m_WindowHeight, ASSET_PATH + SHADER_PATH + "/sharpenFS.glsl");



	/*
	shared_ptr<PostProcess> post = shared_ptr<PostProcess>(new PostProcess());
	string fsPostColourCorrectionFilename = ASSET_PATH + SHADER_PATH + "/colourFilterFS.glsl";
	post->create(m_WindowWidth, m_WindowHeight, fsPostColourCorrectionFilename);
	addPostProcessingEffect(post);

	*/

	
}


void MyGame::onKeyDown(SDL_Keycode keyCode)
{
	if (keyCode == SDLK_w)
	{
		if (!m_DebugMode)
		{
			bool temp = false;
			for each (shared_ptr<GameObject> gameObject in GOList)
			{
				if (gameObject->checkCollision(m_Camera->collisionCheck(true)))
				{
					temp = true;
				}
			}
			if (!temp)
			{
				m_Camera->moveForward();
			}
		}
		else
		{
			m_Camera->moveForward();
		}
	}
	else if (keyCode == SDLK_s)
	{
		if (!m_DebugMode)
		{
			bool temp = false;
			for each (shared_ptr<GameObject> gameObject in GOList)
			{
				if (gameObject->checkCollision(m_Camera->collisionCheck(false)))
				{
					temp = true;
				}
				if (!temp)
				{
					m_Camera->moveBackward();
				}

			}

		}
		else
		{
			m_Camera->moveBackward();
		}
	}

		if (keyCode == SDLK_e)
		{
			m_Camera->rotateCamera(3.0f);
		}
		else if (keyCode == SDLK_q)
		{
			m_Camera->rotateCamera(-3.0f);
		}


		if (keyCode == SDLK_p)
		{
			if (!m_DebugMode)
			{
				m_DebugMode = true;
			}
			else
			{
				m_DebugMode = false;
			}

		}
}


void MyGame::destroyScene()
{
	m_PassThroughPostProcess->destroy();
	

	//KS loop through vertor to delect all ojs
	for each (shared_ptr<GameObject> temp in GOList)
	{
		temp->onDestroy();
	}

	/*
	for(int i=0;i<&GOList.capacity;i++)
	{
		m_TestGO->onDestroy();
		GOList.pop_back();
	}
	*/
	
}

void MyGame::update()
{
	GameApplication::update();

	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 1000.0f);
	m_ViewMatrix = lookAt(m_CameraPosition, m_CameraPosition + m_CameraLookAtPosition, vec3(0.0f, 1.0f, 0.0f));
	
	//KS loop through vertor to update all ojs
	for each (shared_ptr<GameObject> temp in GOList)
	{
		temp->onUpdate();
		
	}
}

void MyGame::render()
{

	m_ViewMatrix = lookAt(m_Camera->getCameraPosition(), m_Camera->getLookAtPosition(), vec3(0.0f, 1.0f, 0.0f));

	GameApplication::render();

	m_PassThroughPostProcess->getBuffer()->bind();

	

	//KS loop through vertor to render all ojs
	for each (shared_ptr<GameObject> temp in GOList)
	{
		GLuint currentShader = temp->getShaderProgram();

		GLint ambientLightColourLocation = glGetUniformLocation(currentShader, "directionLight.ambientColour");
		glUniform4fv(ambientLightColourLocation, 1, value_ptr(m_AmbientLightColour));

		GLint diffuseLightColourLocation = glGetUniformLocation(currentShader, "directionLight.diffuseColour");
		glUniform4fv(diffuseLightColourLocation, 1, value_ptr(m_Light->DiffuseColour));

		GLint specularLightColourLocation = glGetUniformLocation(currentShader, "directionLight.specularColour");
		glUniform4fv(specularLightColourLocation, 1, value_ptr(m_Light->SpecularColour));

		GLint lightDirectionLocation = glGetUniformLocation(currentShader, "directionLight.direction");
		glUniform3fv(lightDirectionLocation, 1, value_ptr(m_Light->Direction));

		GLint cameraPositionLocation = glGetUniformLocation(currentShader, "cameraPos");
		glUniform3fv(cameraPositionLocation, 1, value_ptr(m_CameraPosition));

		temp->onRender(m_ViewMatrix, m_ProjMatrix);

		//GOList.pop_back();
	}


	
	m_PassThroughPostProcess->getBuffer()->unbind();

	

	m_PassThroughPostProcess->getEffect()->bind();
	GLuint currentShader = m_PassThroughPostProcess->getEffect()->getShaderProgram();
	GLint textureLocation = glGetUniformLocation(currentShader, "texture0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_PassThroughPostProcess->getBuffer()->GetTexture());
	glUniform1i(textureLocation, 0);


	

	m_PassThroughPostProcess2->getBuffer()->bind();

	m_PassThroughPostProcess->getQuad()->render();
	m_PassThroughPostProcess->getBuffer()->unbind();


	
	m_PassThroughPostProcess2->getEffect()->bind(); //PP2


	
	GLuint currentShader2 = m_PassThroughPostProcess2->getEffect()->getShaderProgram();
	GLint textureLocation2 = glGetUniformLocation(currentShader2, "texture0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_PassThroughPostProcess2->getBuffer()->GetTexture());
	glUniform1i(textureLocation2, 0);

	m_PassThroughPostProcess2->getQuad()->render();
	m_PassThroughPostProcess2->getBuffer()->unbind();
	/*
	for (auto& post : m_PostProcessChain)
	{
		post->getBuffer()->bind();
		post->getEffect()->bind();
		GLuint currentShader = post->getEffect()->getShaderProgram();

		GLint textureLocation = glGetUniformLocation(currentShader, "texture0");
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, post->getBuffer()->GetTexture());
		glUniform1i(textureLocation, 0);

		post->getQuad()->render();
		post->getBuffer()->unbind();
	}
	*/
	

	//m_PostBuffer->unbind();





	//Do above again but with out the object for loop
}
