#include "Mesh.h"
#include <rapidjson/document.h>
#include <fstream>
#include <SDL_log.h>
#include <sstream>

#include "Renderer.h"
#include "VertexArray.h"

Mesh::Mesh():mVertexArray(nullptr),mRadius(0.0f),mSpecPower(100.0f)
{
}

bool Mesh::Load(const std::string& fileName, Renderer* renderer)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Mesh %s",fileName.c_str());
		return false;
	}
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document document;
	document.ParseStream(jsonStr);

	if (!document.IsObject())
	{
		SDL_Log("Mesh %s is not valid json",fileName.c_str());
		return false;
	}
	int version = document["version"].GetInt();

	if (version != 1)
	{
		SDL_Log("Mesh %s not version 1",fileName.c_str());
		return false;
	}
	mShaderName = document["shader"].GetString();

	size_t vertSize = 8;

	const rapidjson::Value& textures = document["textures"];
	if (!textures.IsArray() || textures.Size() < 1)
	{
		SDL_Log("Mesh %s has no textures, there shold be at least one",fileName.c_str());
		return false;
	}
	mSpecPower = static_cast<float>(document["specularPower"].GetDouble());
	for (rapidjson::SizeType i = 0; i < textures.Size(); i++)
	{
		std::string texName = textures[i].GetString();
		auto * t = renderer->GetTexture(texName);
		if (t == nullptr)
		{
			t = renderer->GetTexture(texName);
			if (t == nullptr)
			{
				t = renderer->GetTexture("Assets/Default.png");
			}
		}
		mTextures.emplace_back(t);
	}
	const rapidjson::Value& vertsJson = document["vertices"];
	if (!vertsJson.IsArray() || vertsJson.Size() < 1)
	{
		SDL_Log("Mesh %s hs no vertices",fileName.c_str());
		return false;
	}
	std::vector<float> vertices;
	vertices.reserve(vertsJson.Size() * vertSize);
	mRadius = 0.0f;
	for (rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
	{
		const rapidjson::Value& vert = vertsJson[i];
		if (!vert.IsArray() || vert.Size() != 8)
		{
			SDL_Log("Unexpected vertex format for %s",fileName.c_str());
			return false;
		}
		Vector3 pos(vert[0].GetDouble(),vert[1].GetDouble(),vert[2].GetDouble());
		mRadius = Math::Max(mRadius,pos.LengthSq());
		for (rapidjson::SizeType i = 0; i < vert.Size(); i++)
		{
			vertices.emplace_back(static_cast<float>(vert[i].GetDouble()));
		}
	}
	mRadius = Math::Sqrt(mRadius);
	const rapidjson::Value& indJson = document["indices"];
	if (!indJson.IsArray() || indJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no indices",fileName.c_str());
		return false;
	}
	std::vector<unsigned int> indices;
	indices.reserve(indJson.Size() * 3);
	for (rapidjson::SizeType i = 0; i < indJson.Size(); i++)
	{
		const rapidjson::Value& ind = indJson[i];
		if (!ind.IsArray() || ind.Size() != 3)
		{
			SDL_Log("Invalid indices for %s", fileName.c_str());
			return false;
		}
		indices.emplace_back(ind[0].GetUint());
		indices.emplace_back(ind[1].GetUint());
		indices.emplace_back(ind[2].GetUint());
	}
	mVertexArray = new VertexArray(vertices.data(),static_cast<unsigned>(vertices.size()) / vertSize,indices.data(), static_cast<unsigned>(indices.size()));
	return true;
}

void Mesh::Unload()
{
	delete mVertexArray;
	mVertexArray = nullptr;
}

Texture* Mesh::GetTexture(size_t index)
{
	if (index < mTextures.size())
	{
		return mTextures[index];
	}else
	{
		return nullptr;
	}
}




