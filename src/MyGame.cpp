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


	//Set up the camera
	m_Camera = shared_ptr<CameraController>(new CameraController);
	

	//KS Changed to Array and vector that can be iterated through
	string modelPath [] {"/Earth.fbx", "/Earth.fbx", "/unitCube.fbx", "/unitCube.fbx", "/unitCube.fbx", "/unitCube.fbx", "/unitCube.fbx" };
	string diffTextureFileName[]{"/bricks_diff.jpg","/TBall_Diff.jpg", "/floor.jpg", "/bricks_diff.jpg", "/bricks_diff.jpg", "/bricks_diff.jpg" , "/bricks_diff.jpg" };
	string specTextureFilename[]{"/bricks_spec.png","/TBall_Spec.png", "/Floor_Spec.png", "/bricks_spec.png", "/bricks_spec.png", "/bricks_spec.png", "/bricks_spec.png" };
	string normTextureFilename[]{"/bricks_norm.png","none", "none", "/bricks_norm.png", "/bricks_norm.png", "/bricks_norm.png", "/bricks_norm.png" };
	string heightTextureFilename[]{"/bricks_height.png","none", "none", "/bricks_height.png", "none", "/bricks_height.png", "/bricks_height.png" };

	vec3 scale[]
	{
		vec3(5.0f, 5.0f, 5.0f),
		vec3(5.0f, 5.0f, 5.0f),
		vec3(200.0f, 10.0f, 200.0f),
		vec3(100.0f, 50.0f, 1.0f),
		vec3(1.0f, 50.0f, 100.0f), 
		vec3(1.0f, 50.0f, 100.0f) 
	};
	vec3 position[]
	{
		vec3(25.0f, 5.0f, 5.0f),
		vec3(0.0f, 20.0f, 50.0f),
		vec3(0.0f, 0.0f, -50.0f), 
		vec3(0.0f, 25.0f, 0.0f), 
		vec3(-50.0f, 25.0f, 0.0f), 
		vec3(50.0f, 25.0f, 0.0f) 
	};
	vec3 rotation[]
	{
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, 0.0f), 
		vec3(0.0f, 0.0f, 0.0f), 
		vec3(0.0f, 0.0f, 0.0f), 
		vec3(0.0f, 0.0f, 0.0f)
	};

	
	int arrayLength = sizeof(modelPath) / sizeof(modelPath[0]); //Get the length of the array

	//Iterate through the array
	for (int i = 0; i < arrayLength; i++)
	{
		//If it has a normal texture, use it, otherwise replace with whitespace
		if (normTextureFilename[i] != "none")
		{
			normTextureFilename[i] = textureFP + normTextureFilename[i];
		}
		else
		{
			normTextureFilename[i] = textureFP + "/White.png";
		}

		//If it has a normal texture, use it, otherwise replace with whitespace
		if (heightTextureFilename[i] != "none")
		{
			heightTextureFilename[i] = textureFP + heightTextureFilename[i];
		}
		else
		{
			heightTextureFilename[i] = textureFP + "/White.png";
		}

		//Load the model, shaders and set the transform before adding it to the list of gameobjects
		m_TestGO = shared_ptr<GameObject>(loadModelFromFile(modelFP+modelPath[i]));
		m_TestGO->loadShadersAndTextures(textureFP+diffTextureFileName[i], textureFP+specTextureFilename[i], normTextureFilename[i], heightTextureFilename[i]);
		m_TestGO->setTransform(scale[i],position[i],rotation[i]);
		GOList.push_back(m_TestGO);
	}

	//Set the camera starting values
	m_CameraRotation = vec3(0.0f, radians(180.0f), 0.0f);
	m_CameraPosition = vec3(0.0f, 25.0f, 150.0f);
	m_CameraLookAtPosition = vec3(cos(m_CameraRotation.y), 0, sin(m_CameraRotation.y));

	//Set up the light for the scene
	m_Light = shared_ptr<Light>(new Light());
	m_Light->DiffuseColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->Direction = vec3(0.0f, 0.0f, -1.0f);
	m_AmbientLightColour = vec4(0.5f, 0.5f, 0.5f, 1.0f);

	//Create the depth buffer object to be used for shadow mapping
	m_depthBuffer = shared_ptr<depthFrameBuffer>(new depthFrameBuffer());
	m_depthBuffer->create();

	string ShadowVSFilename = ASSET_PATH + SHADER_PATH + "/simpleDepthShaderVS.glsl";
	string ShadowFSFilename = ASSET_PATH + SHADER_PATH + "/simpleDepthShaderFS.glsl";

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

	//Set up the first post processing object, which will return a screen aligned quad with the scene drawn onto it
	m_PassThroughPostProcess = unique_ptr<PostProcess>(new PostProcess());
	m_PassThroughPostProcess->create(m_WindowWidth, m_WindowHeight, PostVSFilename, PostFSFilename);




	

	
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

		if (keyCode == SDLK_1)
		{
			//If sharpen isn't active, activate it, if it is, remove it from the post process list
			if (!m_Sharpen)
			{
				shared_ptr<PostProcess> postsharpen = shared_ptr<PostProcess>(new PostProcess());
				string fsSharpenFilename = ASSET_PATH + SHADER_PATH + "/SharpenFS.glsl";
				postsharpen->create(m_WindowWidth, m_WindowHeight, PostVSFilename, fsSharpenFilename);
				addPostProcessingEffect(postsharpen);
				m_Sharpen = true;
			}
			else
			{
				for (int i = 0; i < m_PostProcessChain.size(); i++)
				{
					if (m_PostProcessChain[i]->getFS() == ASSET_PATH + SHADER_PATH + "/SharpenFS.glsl")
					{
						m_PostProcessChain.erase(m_PostProcessChain.begin()+i);
					}
					
					
				}
				m_Sharpen = false;
			}
		}

		if (keyCode == SDLK_2)
		{
			if (!m_Blur)
			{
				shared_ptr<PostProcess> postBlur = shared_ptr<PostProcess>(new PostProcess());
				string fsPostBlurFilename = ASSET_PATH + SHADER_PATH + "/blurFS.glsl";
				postBlur->create(m_WindowWidth, m_WindowHeight, PostVSFilename, fsPostBlurFilename);
				addPostProcessingEffect(postBlur);
				m_Blur = true;
			}
			else
			{
				for (int i = 0; i < m_PostProcessChain.size(); i++)
				{
					if (m_PostProcessChain[i]->getFS() == ASSET_PATH + SHADER_PATH + "/blurFS.glsl")
					{
						m_PostProcessChain.erase(m_PostProcessChain.begin() + i);
					}


				}
				m_Blur = false;
			}
		}

		if (keyCode == SDLK_3)
		{
			if (!m_Invert)
			{
				shared_ptr<PostProcess> postColourInvert = shared_ptr<PostProcess>(new PostProcess());
				string fsPostColourInvertFilename = ASSET_PATH + SHADER_PATH + "/colourInvertFS.glsl";
				postColourInvert->create(m_WindowWidth, m_WindowHeight, PostVSFilename, fsPostColourInvertFilename);
				addPostProcessingEffect(postColourInvert);
				m_Invert = true;
			}
			else
			{
				for (int i = 0; i < m_PostProcessChain.size(); i++)
				{
					if (m_PostProcessChain[i]->getFS() == ASSET_PATH + SHADER_PATH + "/colourInvertFS.glsl")
					{
						m_PostProcessChain.erase(m_PostProcessChain.begin() + i);
					}


				}
				m_Invert = false;
			}
		}

		if (keyCode == SDLK_4)
		{
			if (!m_ColourCorrect)
			{
				shared_ptr<PostProcess> postFilter = shared_ptr<PostProcess>(new PostProcess());
				string fsPostColourFilterFilename = ASSET_PATH + SHADER_PATH + "/ColourFilterFS.glsl";
				postFilter->create(m_WindowWidth, m_WindowHeight, PostVSFilename, fsPostColourFilterFilename);
				addPostProcessingEffect(postFilter);
				m_ColourCorrect = true;
			}
			else
			{
				for (int i = 0; i < m_PostProcessChain.size(); i++)
				{
					if (m_PostProcessChain[i]->getFS() == ASSET_PATH + SHADER_PATH + "/ColourFilterFS.glsl")
					{
						m_PostProcessChain.erase(m_PostProcessChain.begin() + i);
					}


				}
				m_ColourCorrect = false;
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

	//Set up values for our shadow projection matrix
	GLuint Sampler = 0;

	glm::mat4 lightView;
	glm::mat4 lightSpaceMatrix;
	glm::vec3 lightPos(100.0f, 150.0f, 0.0f);

	GLfloat near_plane = 1.0f, far_plane = 1000.0f;
	glm::mat4 lightProjection = glm::ortho(-1000.0f, 1000.0f, -1000.0f, 1000.0f, near_plane, far_plane);
	lightView = glm::lookAt(lightPos,
		glm::vec3(0.0f, 20.0f, 50.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	lightSpaceMatrix = lightProjection * lightView;

	//Set opengl to render to the shadow fbo, to make the shadow map
	m_depthBuffer->bind();
	for each (shared_ptr<GameObject> temp in GOList)
	{
		glUseProgram(m_shadowProgram);
		glUniformMatrix4fv(glGetUniformLocation(m_shadowProgram, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
		glUniformMatrix4fv(glGetUniformLocation(m_shadowProgram, "model"), 1, GL_FALSE, glm::value_ptr(temp->getModelMatrix()));
		temp->draw();
	}
	m_depthBuffer->unbind();
	//Bring it to the front



	
	//Reset the viewport/buffers
	glViewport(0, 0, m_WindowWidth, m_WindowHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	


	//Get ready for the actual render pass
	m_PassThroughPostProcess->getBuffer()->bind();

	//KS loop through vector to render all ojs
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


		//Grab the shadowmap and set opengl to be working with texture 8
		GLuint m_ShadowTexture = m_depthBuffer->GetTexture();
		glActiveTexture(8);


		glBindTexture(GL_TEXTURE_2D, m_ShadowTexture);


		glGenerateMipmap(GL_TEXTURE_2D);

		glGenSamplers(1, &Sampler);
		glSamplerParameteri(Sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glSamplerParameteri(Sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(Sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(Sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Pass in the shadowmap to be used in the fragment shader
		glBindSampler(8, Sampler);
		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, m_ShadowTexture);
		GLint shadowTex = glGetUniformLocation(currentShader, "shadowMap");
		glUniform1i(shadowTex, 8);

		
		

		temp->onRender(m_ViewMatrix, m_ProjMatrix);
		temp->draw();
	}

	m_PassThroughPostProcess->getBuffer()->unbind();
	//Bring everything to the front

	
	//Set up the first post process effect (Draw everything to a screen aligned quad)
	m_PassThroughPostProcess->getEffect()->bind();
	GLuint currentShader = m_PassThroughPostProcess->getEffect()->getShaderProgram();
	GLint textureLocation = glGetUniformLocation(currentShader, "texture0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_PassThroughPostProcess->getBuffer()->GetTexture());
	glUniform1i(textureLocation, 0);


	//If there are more effects to come, prep the first one
	if (m_PostProcessChain.size() > 0)
	{
		m_PostProcessChain[0]->getBuffer()->bind();
	}
	
	//Draw the screen aligned quad, will be captured by the next effect
	m_PassThroughPostProcess->getQuad()->render();
	m_PassThroughPostProcess->getBuffer()->unbind();

	//Loop through all post processing effects, one at a time, always checking if there is another one to come after
	for (int i = 0; i < m_PostProcessChain.size(); i++)
	{

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
	

}
