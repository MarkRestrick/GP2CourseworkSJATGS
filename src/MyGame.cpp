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
		vec3(100.0f, 100.0f, 1.0f), //MR Back wall
		vec3(100.0f, 100.0f, 1.0f), //MR left wall
		vec3(100.0f, 100.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f)
	};
	vec3 position[]
	{
		vec3(25.0f, 5.0f, 5.0f),
		vec3(0.0f, 20.0f, 50.0f),
		vec3(0.0f, 0.0f, 0.0f), //MR Floor
		vec3(0.0f, 0.0f, 0.0f), //MR Back Wall
		vec3(-50.0f, 0.0f, 50.0f), //MR left wall
		vec3(50.0f, 0.0f, 50.0f),
		vec3(500.0f, 0.0f, 50.0f)


	};
	vec3 rotation[]
	{
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, 0.0f), //MR Floor
		vec3(0.0f, 0.0f, 0.0f), //MR Back Wall
		vec3(0.0f, radians(90.0f), 0.0f), //MR left wall
		vec3(0.0f, radians(-90.0f), 0.0f),
		vec3(0.0f, radians(-90.0f), 0.0f)

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




	m_CameraPosition = vec3(0.0f, 50.0f, 150.0f);

	m_Light = shared_ptr<Light>(new Light());
	m_Light->DiffuseColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->Direction = vec3(0.0f, 0.0f, -1.0f);
	m_AmbientLightColour = vec4(0.5f, 0.5f, 0.5f, 1.0f);


	m_PostBuffer = shared_ptr<PostProcessBuffer>(new PostProcessBuffer());
	m_PostBuffer->create(m_WindowWidth, m_WindowHeight);
	
	

	m_depthBuffer = shared_ptr<depthFrameBuffer>(new depthFrameBuffer());
	m_depthBuffer->create();

	m_ScreenAlignedQuad = shared_ptr<ScreenAlignedQuad>(new ScreenAlignedQuad());
	m_ScreenAlignedQuad->create();

	//string vsPostFilename = ASSET_PATH + SHADER_PATH + "/postProcessingVS.glsl";
	string ShadowVSFilename = ASSET_PATH + SHADER_PATH + "/simpleDepthShaderVS.glsl";

	
		//string fsPostFilename = ASSET_PATH + SHADER_PATH + "/colourFilterFS.glsl";
		//string fsPostFilename = ASSET_PATH + SHADER_PATH + "/sharpenFS.glsl";
		//string fsPostFilename = ASSET_PATH + SHADER_PATH + "/blurFS.glsl";
		  string ShadowFSFilename = ASSET_PATH + SHADER_PATH + "/simpleDepthShaderFS.glsl";

		  string PostVSFilename = ASSET_PATH + SHADER_PATH + "/postProcessingVS.glsl";
		  string PostFSFilename = ASSET_PATH + SHADER_PATH + "/simplePostProcessFS.glsl";

	m_PostEffect = shared_ptr<PostProcessingEffect>(new PostProcessingEffect());
	m_PostEffect->loadShader(PostVSFilename, PostFSFilename);
	



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
	if (keyCode == SDLK_a)
	{
		m_CameraPosition += vec3(-1.0f, 0.0f, 0.0f);
	}else if (keyCode == SDLK_d)
	{
		m_CameraPosition += vec3(1.0f, 0.0f, 0.0f);
	}
	if (keyCode==SDLK_w)
	{
		m_TestGO->rotate(vec3(0.1f,0.0f,0.0f));
	}
	else if (keyCode==SDLK_s)
	{
		m_TestGO->rotate(vec3(-0.1f,0.0f,0.0f));
	}
}


void MyGame::destroyScene()
{

	m_PostEffect->destroy();
	m_ScreenAlignedQuad->destroy();
	m_PostBuffer->destroy();

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
	m_ViewMatrix = lookAt(m_CameraPosition, vec3(0.0f, 0.0f, -10.0f), vec3(0.0f, 1.0f, 0.0f));

	
	//KS loop through vertor to update all ojs
	for each (shared_ptr<GameObject> temp in GOList)
	{
		temp->onUpdate();
		
	}
}

void MyGame::render()
{
	GameApplication::render();


	GLuint Sampler = 0;
	
	m_depthBuffer->bind();

	glm::mat4 lightView;
	glm::mat4 lightSpaceMatrix;

	glm::vec3 lightPos(100.0f, -150.0f, 0.0f);

	GLfloat near_plane = 1.0f, far_plane = 350.0f;
	glm::mat4 lightProjection = glm::ortho(-150.0f, 150.0f, -150.0f, 150.0f, near_plane, far_plane);
	lightView = glm::lookAt(lightPos,
		glm::vec3(0.0f, 0.0f, 0.0f),
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
	
	m_PostBuffer->bind();
	
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
		//glActiveTexture(2);

		glBindTexture(GL_TEXTURE_2D, m_ShadowTexture);

		
		glGenerateMipmap(GL_TEXTURE_2D);

		glGenSamplers(1, &Sampler);
		glSamplerParameteri(Sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glSamplerParameteri(Sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(Sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(Sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
		

		glBindSampler(0, Sampler);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_ShadowTexture);
		GLint shadowTex = glGetUniformLocation(currentShader, "shadowMap");
		glUniform1i(shadowTex, 0);

		
		temp->onRender(m_ViewMatrix, m_ProjMatrix);
		temp->draw();



		//GOList.pop_back();
	}
	
	
	m_PostBuffer->unbind();
	
		

	m_PostEffect->bind();
	GLuint currentShader = m_PostEffect->getShaderProgram();

	GLint textureLocation = glGetUniformLocation(currentShader, "texture0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_PostBuffer->GetTexture());
	glUniform1i(textureLocation, 0);
	
	

	m_ScreenAlignedQuad->render();
	m_depthBuffer->unbind();
	
	
}
