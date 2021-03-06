#include "GameObject.h"

GameObject::GameObject()
{
	m_ModelMatrix = mat4(1.0f);

	m_Sampler=0;
	m_pParent = nullptr;
}

GameObject::~GameObject()
{
}
void GameObject::onUpdate()
{

	m_GameObjectTransform.TransformUpdate(); 

	m_ModelMatrix = m_GameObjectTransform.getModelMatrix();
	if (m_pParent)
	{
		m_ModelMatrix *= m_pParent->getModelMatrix();
	}
	

	m_GameObjectCollider.setTransform(m_GameObjectTransform.getPosition(), m_GameObjectTransform.getScale());
}

void GameObject::onRender(mat4& view, mat4& projection)
{
	GLuint VAO = m_GameObjectMesh.getVAO ();
	GLuint VBO = m_GameObjectMesh.getVBO();
	GLuint EBO = m_GameObjectMesh.getEBO();
	GLuint numberOfVertices = m_GameObjectMesh.getNumberOfIndices();
	m_GameObjectRenderer.onRender(view, projection, VAO, m_ModelMatrix, numberOfVertices, VBO, EBO);
}

void GameObject::onInit()
{
}

void GameObject::onDestroy()
{
	m_GameObjectMesh.onDestroy();
	glDeleteSamplers(1, &m_Sampler);
	m_GameObjectRenderer.onDestroy();
}

void GameObject::addChild(shared_ptr<GameObject> gameobject)
{
	//gameobject->m_pParent = this;
	m_ChildrenGameObjects.push_back(gameobject);
}



void GameObject::rotate(const vec3 & delta)
{
	//m_Rotation += delta;
}

//function to set transform
void GameObject::setTransform(vec3 scale, vec3 pos, vec3 rot)
{
	m_GameObjectTransform.setScale(scale);
	m_GameObjectTransform.setPosition(pos);
	m_GameObjectTransform.setRotation(rot);
}

//function to set sharders and textures

void GameObject::loadShadersAndTextures(const string & diffFilename, const string & spFilename, const string & norFilename, const string & heigFilename)
{


		m_GameObjectRenderer.loadShaders(parallaxVS, parallaxFS);
		m_GameObjectRenderer.loadDiffuseTexture(diffFilename);
		m_GameObjectRenderer.loadSpecularTexture(spFilename);
		m_GameObjectRenderer.loadNormalTexture(norFilename);
		m_GameObjectRenderer.loadHeightTexture(heigFilename);

}

void GameObject::copyVertexData(Vertex * pVertex, int numberOfVertices, int * pIndices, int numberOfIndices)
{
	m_GameObjectMesh.copyVertexData(pVertex, numberOfVertices, pIndices, numberOfIndices);
}

GLuint GameObject::getShaderProgram()
{
	return m_GameObjectRenderer.getShaderProgram();
}

bool GameObject::checkCollision(vec3 position)
{
	return m_GameObjectCollider.checkCollision(position);
}

void GameObject::getColliderSize(vec3 high, vec3 low)
{
	m_GameObjectCollider.setTransform(m_GameObjectTransform.getPosition(), m_GameObjectTransform.getScale());
	m_GameObjectCollider.setCollider(high, low);
}
void GameObject::draw()
{
	GLuint VAO = m_GameObjectMesh.getVAO();
	GLuint VBO = m_GameObjectMesh.getVBO();
	GLuint EBO = m_GameObjectMesh.getEBO();
	GLuint numberOfVertices = m_GameObjectMesh.getNumberOfIndices();
	m_GameObjectRenderer.draw(VAO, VBO, EBO, numberOfVertices);
}
