#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "Common.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "Transform.h"
#include <iostream>
#include "Renderer.h"
#include "Mesh.h"
#include "BoxCollider.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void onUpdate();
	void onRender(mat4& view, mat4& projection);
	void onInit();
	void onDestroy();
	void draw();

	void addChild(shared_ptr<GameObject> gameobject);

	//Transform stuff
	void setTransform(vec3 scale, vec3 pos, vec3 rot);

	//RendererStuff
	//const string& vsFilename, const string& fsFilename, 
	void loadShadersAndTextures(const string& diffFilename, const string& spFilename, const string& norFilename, const string& heigFilename);


	mat4& getModelMatrix()
	{
		return m_ModelMatrix;
	};
	void rotate(const vec3& delta);
	void copyVertexData(Vertex *pVertex, int numberOfVertices, int *pIndices, int numberOfIndices);
	GLuint getShaderProgram();

	bool checkCollision(vec3 position);

	void getColliderSize(vec3 high, vec3 low);
private:
	GameObject * m_pParent;
	vector<shared_ptr<GameObject> > m_ChildrenGameObjects;

	mat4 m_ModelMatrix;
	//Shader Program
	GLuint m_Sampler;
	Transform m_GameObjectTransform;
	Renderer m_GameObjectRenderer;
	Mesh m_GameObjectMesh;
	BoxCollider m_GameObjectCollider;

	string parallaxFS = "assets/shaders/parallaxMappingFS2.glsl";
	string parallaxVS = "assets/shaders/parallaxMappingVS2.glsl";

	string normalFS = "assets/shaders/lightTextureFS2.glsl";
	string normalVS = "assets/shaders/lightTextureVS2.glsl";

	string specFS = "assets/shaders/lightFS2.glsl";
	string specVS = "assets/shaders/lightVS2.glsl";
};

#endif