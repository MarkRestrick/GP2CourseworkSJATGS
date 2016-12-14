#include "ModelLoading.h"

//http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html
GameObject * loadModelFromFile(const string & filename)
{
	LOG(INFO,"Attempting to load model %s",filename.c_str());
	GameObject *gameObject = new GameObject();
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	const aiScene* scene = aiImportFile(filename.c_str(), aiProcess_JoinIdenticalVertices|aiProcess_Triangulate | aiProcess_FlipUVs|aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

	if (scene)
	{
		Vertex ourV;

		LOG(INFO,"Parsing Model %s",filename.c_str());
		const aiMesh * mesh=scene->mMeshes[0];

		vector<int> indices;
		vector<Vertex> verts;

		float m_HX = mesh->mVertices[0].x;
		float m_LX = mesh->mVertices[0].x;
		float m_HY = mesh->mVertices[0].y;
		float m_LY = mesh->mVertices[0].y;
		float m_HZ = mesh->mVertices[0].z;
		float m_LZ = mesh->mVertices[0].z;

		for (int f = 0; f < mesh->mNumFaces; f++)
		{
			const aiFace * face = &mesh->mFaces[f];
			for (int i = 0; i < face->mNumIndices; i++)
			{
				int index = face->mIndices[i];
				indices.push_back(index);
			}
		}

		for (int v = 0; v < mesh->mNumVertices; v++)
		{
			aiVector3D position = mesh->mVertices[v];
			aiVector3D normal = mesh->mNormals[v];


			if (position.x > m_HX)
				m_HX = position.x;
			if (position.y > m_HY)
				m_HY = position.y;
			if (position.z > m_HZ)
				m_HZ = position.z;

			if (position.x < m_LX)
				m_LX = position.x;
			if (position.y < m_LY)
				m_LY = position.y;
			if (position.z < m_LZ)
				m_LZ = position.z;

			for (int i = 0; i < mesh->GetNumUVChannels(); i++)	
			{
				if (mesh->HasTextureCoords(i))
				{
					aiVector3D texCoords = mesh->mTextureCoords[i][v];
					ourV.texCoords0.x = texCoords.x;
					ourV.texCoords0.y = texCoords.y;
				}
				if (mesh->HasTangentsAndBitangents())
				{
					aiVector3D binormal = mesh->mBitangents[v];
					aiVector3D tangent = mesh->mTangents[v];
					ourV.binormal = vec3(binormal.x, binormal.y, binormal.z);
					ourV.tangent = vec3(tangent.x, tangent.y, tangent.z);
				}

			}


			ourV.position = vec3(position.x, position.y, position.z);
			ourV.normal = vec3(normal.x, normal.y, normal.z);
			

			verts.push_back(ourV);
		}

		vec3 highestCorner = vec3(m_HX, m_HY, m_HZ);
		vec3 lowestCorner = vec3(m_LX, m_LY, m_LZ);
		gameObject->getColliderSize(highestCorner, lowestCorner);

		gameObject->copyVertexData(&verts[0], verts.size(), &indices[0], indices.size());
	}
	else
	{
		LOG(ERROR,"Error Parsing Model %s",aiGetErrorString());
	}

	aiReleaseImport(scene);


	return gameObject;
}
