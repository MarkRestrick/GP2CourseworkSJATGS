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


	//m_PostBuffer = shared_ptr<PostProcessBuffer>(new PostProcessBuffer());
	//m_PostBuffer->create(m_WindowWidth, m_WindowHeight);
	
	

	m_depthBuffer = shared_ptr<depthFrameBuffer>(new depthFrameBuffer());
	m_depthBuffer->create();

	m_ScreenAlignedQuad = shared_ptr<ScreenAlignedQuad>(new ScreenAlignedQuad());
	m_ScreenAlignedQuad->create();

	//string vsPostFilename = ASSET_PATH + SHADER_PATH + "/postProcessingVS.glsl";
	string vsPostFilename = ASSET_PATH + SHADER_PATH + "/simpleDepthShaderVS.glsl";

	
		//string fsPostFilename = ASSET_PATH + SHADER_PATH + "/colourFilterFS.glsl";
		//string fsPostFilename = ASSET_PATH + SHADER_PATH + "/sharpenFS.glsl";
		//string fsPostFilename = ASSET_PATH + SHADER_PATH + "/blurFS.glsl";
		  string fsPostFilename = ASSET_PATH + SHADER_PATH + "/simpleDepthShaderFS.glsl";

	m_PostEffect = shared_ptr<PostProcessingEffect>(new PostProcessingEffect());
	m_PostEffect->loadShader(vsPostFilename,fsPostFilename);
	
	

	


}


void MyGame::onKeyDown(SDL_Keycode keyCode)
{
	if (keyCode == SDLK_a)
	{
		m_TestGO->rotate(vec3(0.0f, 0.1f, 0.0f));
	}else if (keyCode == SDLK_d)
	{
		m_TestGO->rotate(vec3(0.0f, -0.1f, 0.0f));
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
	//m_PostBuffer->destroy();

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
	m_ViewMatrix = lookAt(m_CameraPosition, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	
	//KS loop through vertor to update all ojs
	for each (shared_ptr<GameObject> temp in GOList)
	{
		temp->onUpdate();
		
	}
}

void MyGame::render()
{

	m_depthBuffer->bind();

	GameApplication::render();
	
	


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

	
	glm::mat4 lightView;
	glm::mat4 lightSpaceMatrix;

	GLfloat near_plane = 1.0f, far_plane = 7.5f;
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
							glm::vec3(0.0f, 0.0f, 0.0f), 
							glm::vec3(0.0f, 1.0f, 0.0f));
	lightSpaceMatrix = lightProjection * lightView;

	GLuint currentShader = m_PostEffect->getShaderProgram();
	glUniformMatrix4fv(glGetUniformLocation(currentShader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	

	m_depthBuffer->unbind();

	m_PostEffect->bind();
	//GLuint currentShader = m_PostEffect->getShaderProgram();

	//GLint textureLocation = glGetUniformLocation(currentShader, "depthMap");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_depthBuffer->GetTexture());
	//glUniform1i(textureLocation, 0);

	m_ScreenAlignedQuad->render();
	m_depthBuffer->unbind();
	//Do above again but with out the object for loop
	
}
