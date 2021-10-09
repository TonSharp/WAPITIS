#pragma once

#include <utility>

#include "GLLibs.hpp"

using namespace std;

class GameObject
{
private:
	Mesh* mesh;
	Texture* texture;

	bool Existing()
	{
		return this;
	}

public:

	Vec3 Transform = *(new Vec3(0, 0, 0));
	Vec3 Rotation = *(new Vec3(0, 0, 0));
	Vec3 Scale = *(new Vec3(1, 1, 1));

	GameObject()
	{
		Scale.X = 1;
		Scale.Y = 1;
		Scale.Z = 1;

		mesh = nullptr;
	}

	void LoadMesh(string path)
	{
		mesh = new Mesh();
		mesh->Load(path);
	}
	void LoadTexture(string path)
	{
		texture = new Texture();
		texture->Load(path);

		glGenTextures(1, &texture->ID);
		glBindTexture(GL_TEXTURE_2D, texture->ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		GLenum format = texture->GetBitsPerPixel() == 24 ? GL_RGB : GL_RGBA;

		glEnable(GL_TEXTURE_2D);
		glTexImage2D(GL_TEXTURE_2D, 0, texture->GetBitsPerPixel() / 8, texture->GetWidth(), texture->GetHeight(), 0, format,
		             GL_UNSIGNED_BYTE, texture->GetData());
	}

	void AssignMesh(Mesh* mesh)
	{
		this->mesh = mesh;
	}

	void ScaleObject(float val)
	{
		if (!Existing())
			return;

		Scale.X = val;
		Scale.Y = val;
		Scale.Z = val;
	}

	void Draw()
	{
		if (!Existing())
			return;

		glPushMatrix();

		glTranslatef(Transform.X, Transform.Y, Transform.Z);
		glRotatef(Rotation.X, 1, 0, 0);
		glRotatef(Rotation.Y, 0, 1, 0);
		glRotatef(Rotation.Z, 0, 0, 1);
		glScalef(Scale.X, Scale.Y, Scale.Z);

		mesh->Draw(texture);

		glPopMatrix();
	}
};