#pragma once

#include "GLLibs.hpp"

using namespace std;

class GameObject
{
private:
	Mesh* mesh;

	bool Existing()
	{
		return this;
	}

public:

	Vec3 Transform = *(new Vec3());
	Vec3 Rotation = *(new Vec3());
	Vec3 Scale = *(new Vec3());

	GameObject()
	{
		Scale.X = 1;
		Scale.Y = 1;
		Scale.Z = 1;
	}

	void LoadMesh(string path)
	{
		mesh = new Mesh();
		mesh->Load(path);
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

		mesh->Draw({255, 255, 255, 255});

		glPopMatrix();
	}
};