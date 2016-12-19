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
	string diffTextureFileName[]{"/bricks_diff.jpg","/TBall_Diff.jpg", "/floor.jpg", "/bricks_diff.jpg", "/bricks_diff.jpg", "/bricks_diff.jpg" , "/bricks_diff.jpg" };
	string specTextureFilename[]{"/bricks_spec.png","/TBall_Spec.png", "/Floor_Spec.png", "/bricks_spec.png", "/bricks_spec.png", "/bricks_spec.png", "/bricks_spec.png" };
	string normTextureFilename[]{"/bricks_norm.png","none", "none", "/bricks_norm.png", "/bricks_norm.png", "/bricks_norm.png", "/bricks_norm.png" };
	string heightTextureFilename[]{"/bricks_height.png","none", "none", "/bricks_height.png", "none", "/bricks_height.png", "/bricks_height.png" };

	//string vsFilenameContainter[] { light, lightex, normal, parallax} MRKS Later optimisation, save objects and call via define

	vec3 scale[]
	{
		vec3(5.0f, 5.0f, 5.0f),
		vec3(5.0f, 5.0f, 5.0f),
		vec3(1000.0f, 10.0f, 1000.0f), //MR Floor
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
		if (normTextureFilename[i] != "none")
		{
			normTextureFilename[i] = textureFP + normTextureFilename[i];
		}
		else
		{
			normTextureFilename[i] = textureFP + "/White.png";
		}

		if (heightTextureFilename[i] != "none")
		{
			heightTextureFilename[i] = textureFP + heightTextureFilename[i];
		}
		else
		{
			heightTextureFilename[i] = textureFP + "/White.png";
		}


		m_TestGO = shared_ptr<GameObject>(loadModelFromFile(modelFP+modelPath[i]));
		//shaderFP+vsFilename[i], shaderFP+fsFilename[i], 
		m_TestGO->loadShadersAndTextures(textureFP+diffTextureFileName[i], textureFP+specTextureFilename[i], normTextureFilename[i], heightTextureFilename[i]);
		//m_TestGO->setTransform(vec3(5.0f, 5.0f, 5.0f), vec3(i*25.0f, i*10.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f));
		//m_TestGO->addChild(m_TestGO);
		m_TestGO->setTransform(scale[i],position[i],rotation[i]);
		GOList.push_back(m_TestGO);
	}

	m_CameraRotation = vec3(0.0f, radians(180.0f), 0.0f);
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
	
	string PostVSFilename = ASSET_PATH + SHADER_PATH + "/postProcessingVS.glsl";
	string PostFSFilename = ASSET_PATH + SHADER_PATH + "/simplePostProcessFS.glsl";



	/*
	m_PassThroughPostProcess2 = unique_ptr<PostProcess>(new PostProcess());
	m_PassThroughPostProcess2->create(m_WindowWidth, m_WindowHeight, ASSET_PATH + SHADER_PATH + "/sharpenFS.glsl");
	*/

	/*
	
	shared_ptr<PostProcess> post = shared_ptr<PostProcess>(new PostProcess());
	string fsPostColourCorrectionFilename = ASSET_PATH + SHADER_PATH + "/SharpenFS.glsl";
	post->create(m_WindowWidth, m_WindowHeight, PostVSFilename, fsPostColourCorrectionFilename);
	addPostProcessingEffect(post);

	

	post = shared_ptr<PostProcess>(new PostProcess());
	string fsPostColourFilterFS = ASSET_PATH + SHADER_PATH + "/colourFilterFS.glsl";
	post->create(m_WindowWidth, m_WindowHeight, PostVSFilename, fsPostColourFilterFS);
	addPostProcessingEffect(post);
	

	post = shared_ptr<PostProcess>(new PostProcess());
	string fsPostColourInvertFS = ASSET_PATH + SHADER_PATH + "/colourInvertFS.glsl";
	post->create(m_WindowWidth, m_WindowHeight, PostVSFilename, fsPostColourInvertFS);
	addPostProcessingEffect(post);
	*/




	m_depthBuffer = shared_ptr<depthFrameBuffer>(new depthFrameBuffer());
	m_depthBuffer->create();


	//string vsPostFilename = ASSET_PATH + SHADER_PATH + "/postProcessingVS.glsl";
	string ShadowVSFilename = ASSET_PATH + SHADER_PATH + "/simpleDepthShaderVS.glsl";


	//string fsPostFilename = ASSET_PATH + SHADER_PATH + "/colourFilterFS.glsl";
	//string fsPostFilename = ASSET_PATH + SHADER_PATH + "/sharpenFS.glsl";
	//string fsPostFilename = ASSET_PATH + SHADER_PATH + "/blurFS.glsl";
	string ShadowFSFilename = ASSET_PATH + SHADER_PATH + "/simpleDepthShaderFS.glsl";



	m_PassThroughPostProcess = unique_ptr<PostProcess>(new PostProcess());
	m_PassThroughPostProcess->create(m_WindowWidth, m_WindowHeight, PostVSFilename, PostFSFilename);

	//m_PostEffect = shared_ptr<PostProcessingEffect>(new PostProcessingEffect());
	//m_PostEffect->loadShader(PostVSFilename, PostFSFilename);




	GLuint vertexShaderProgram = loadShaderFromFile(ShadowVSFilename, VERTEX_SHADER);

	GLuint fragmentShaderProgram = loadShaderFromFile(ShadowFSFilename, FRAGMENT_SHADER);

	m_shadowProgram = glCreateProgram();
	glAttachShader(m_shadowProgram, vertexShaderProgram);
	glAttachShader(m_shadowProgram, fragmentShaderProgram);
	glLinkProgram(m_shadowProgram);
	checkForLinkErrors(m_shadowProgram);

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

	logShaderInfo(m_shadowProgram);

	
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
				if (gameObject->checkCollision(m_Camera->collisionCheck("Forward")))
				{
					temp = true;
				}
			}
			if (!temp)
			{
				m_Camera->move("Forward");
			}
		}
		else
		{
			m_Camera->move("Forward");
		}
	}
	else if (keyCode == SDLK_s)
	{
		if (!m_DebugMode)
		{
			bool temp = false;
			for each (shared_ptr<GameObject> gameObject in GOList)
			{
				if (gameObject->checkCollision(m_Camera->collisionCheck("Backward")))
				{
					temp = true;
				}

			}
			if (!temp)
			{
				m_Camera->move("Backward");
			}

		}
		else
		{
			m_Camera->move("Backward");
		}
	}

		if (keyCode == SDLK_a)
		{
			if (!m_DebugMode)
			{
				bool temp = false;
				for each (shared_ptr<GameObject> gameObject in GOList)
				{
					if (gameObject->checkCollision(m_Camera->collisionCheck("Left")))
					{
						temp = true;
					}

				}
				if (!temp)
				{
					m_Camera->move("Left");
				}

			}
			else
			{
				m_Camera->move("Right");
			}
		}
		else if (keyCode == SDLK_d)
		{
			if (!m_DebugMode)
			{
				bool temp = false;
				for each (shared_ptr<GameObject> gameObject in GOList)
				{
					if (gameObject->checkCollision(m_Camera->collisionCheck("Right")))
					{
						temp = true;
					}

				}
				if (!temp)
				{
					m_Camera->move("Right");
				}

			}
			else
			{
				m_Camera->move("Right");
			}
		}

		if (keyCode == SDLK_SPACE)
		{
			m_Camera->jump(m_DebugMode);
		}

		if (keyCode == SDLK_LSHIFT)
		{
			if (m_DebugMode)
			{
				m_Camera->down();
			}

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

void MyGame::onMouseMove(float x, float y)
{
	m_Camera->mouseRotation(x, y);
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

	vec3 position = m_Camera->getCameraPosition();
	bool tempBool = false;

	//KS loop through vertor to update all ojs
	for each (shared_ptr<GameObject> temp in GOList)
	{
		temp->onUpdate();
		
		if (temp->checkCollision(position - vec3(0.0f, 25.0f, 0.0f)))
		{
			tempBool = true;
		}

	}

	m_Camera->setGrounded(tempBool);

	if (!m_DebugMode)
	{
		m_Camera->onUpdate();
	}
}

void MyGame::render()
{

	m_ViewMatrix = lookAt(m_Camera->getCameraPosition(), m_Camera->getLookAtPosition(), vec3(0.0f, 1.0f, 0.0f));

	GameApplication::render();

	GLuint Sampler = 0;

	m_depthBuffer->bind();

	glm::mat4 lightView;
	glm::mat4 lightSpaceMatrix;

	glm::vec3 lightPos(100.0f, 150.0f, 0.0f);

	GLfloat near_plane = 1.0f, far_plane = 1000.0f;
	glm::mat4 lightProjection = glm::ortho(-1000.0f, 1000.0f, -1000.0f, 1000.0f, near_plane, far_plane);
	lightView = glm::lookAt(lightPos,
		glm::vec3(0.0f, 20.0f, 50.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	lightSpaceMatrix = lightProjection * lightView;


	for each (shared_ptr<GameObject> temp in GOList)
	{
		//GLuint currentShader = m_PostEffect->getShaderProgram();
		glUseProgram(m_shadowProgram);
		glUniformMatrix4fv(glGetUniformLocation(m_shadowProgram, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
		glUniformMatrix4fv(glGetUniformLocation(m_shadowProgram, "model"), 1, GL_FALSE, glm::value_ptr(temp->getModelMatrix()));
		temp->draw();
	}
	//get model uniform here

	m_depthBuffer->unbind();



	

	glViewport(0, 0, m_WindowWidth, m_WindowHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);






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

		glUniformMatrix4fv(glGetUniformLocation(currentShader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
		//glUniform3fv(glGetUniformLocation(currentShader, "lightPos"), 1, GL_FALSE, glm::value_ptr(vec2( 100.0f, 150.0f)));
		GLint lightPositionLocation = glGetUniformLocation(currentShader, "lightPos");
		glUniform3fv(lightPositionLocation, 1, value_ptr(lightPos));



		GLuint m_ShadowTexture = m_depthBuffer->GetTexture();
		glActiveTexture(8);


		glBindTexture(GL_TEXTURE_2D, m_ShadowTexture);


		glGenerateMipmap(GL_TEXTURE_2D);

		glGenSamplers(1, &Sampler);
		glSamplerParameteri(Sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glSamplerParameteri(Sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(Sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(Sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glBindSampler(8, Sampler);
		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, m_ShadowTexture);
		GLint shadowTex = glGetUniformLocation(currentShader, "shadowMap");
		glUniform1i(shadowTex, 8);

		
		

		temp->onRender(m_ViewMatrix, m_ProjMatrix);
		temp->draw();
		//GOList.pop_back();
	}


	
	m_PassThroughPostProcess->getBuffer()->unbind();

	

	m_PassThroughPostProcess->getEffect()->bind();
	GLuint currentShader = m_PassThroughPostProcess->getEffect()->getShaderProgram();
	GLint textureLocation = glGetUniformLocation(currentShader, "texture0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_PassThroughPostProcess->getBuffer()->GetTexture());
	glUniform1i(textureLocation, 0);


	

	//m_PassThroughPostProcess2->getBuffer()->bind();

	if (m_PostProcessChain.size() > 0)
	{
		m_PostProcessChain[0]->getBuffer()->bind();
	}
	

	m_PassThroughPostProcess->getQuad()->render();
	m_PassThroughPostProcess->getBuffer()->unbind();


	
	//m_PassThroughPostProcess2->getEffect()->bind(); //PP2


	/*
	GLuint currentShader2 = m_PassThroughPostProcess2->getEffect()->getShaderProgram();
	GLint textureLocation2 = glGetUniformLocation(currentShader2, "texture0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_PassThroughPostProcess2->getBuffer()->GetTexture());
	glUniform1i(textureLocation2, 0);

	m_PassThroughPostProcess2->getQuad()->render();
	m_PassThroughPostProcess2->getBuffer()->unbind();
	*/

	
	for (int i = 0; i < m_PostProcessChain.size(); i++)
	{

		//post->getBuffer()->bind();
		m_PostProcessChain[i]->getEffect()->bind();
		GLuint currentShader = m_PostProcessChain[i]->getEffect()->getShaderProgram();

		GLint textureLocation = glGetUniformLocation(currentShader, "texture0");
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_PostProcessChain[i]->getBuffer()->GetTexture());
		glUniform1i(textureLocation, 0);

		if (i + 1 < m_PostProcessChain.size())
		{
			m_PostProcessChain[i + 1]->getBuffer()->bind();
		}
		m_PostProcessChain[i]->getQuad()->render();
		m_PostProcessChain[i]->getBuffer()->unbind();
	}
	
	

	//m_PostBuffer->unbind();



	

	//Do above again but with out the object for loop
}
