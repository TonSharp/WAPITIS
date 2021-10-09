#pragma once
#include "GLLibs.hpp"
#include "Surface3.hpp"
#include "Surface4.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Texture.hpp"

class Texture;
using namespace std;

vector<string> split(const string& s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> elems;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

int chCount(string str, char ch)
{
	int count = 0;

	for (auto c : str)
		if (c == ch)
			count++;

	return count;
}

class Mesh
{
private:

	int curVertInd = 0;
	vector<Vertex> vertexes;

	int curNormInd = 0;
	vector<Vertex> normals;

	int curTexInd = 0;
	vector<TextureCoord> texCoords;

	int curSurfSize = 3;
	int curSurfInd = 0;

	vector<Surface4> surfs4;
	vector<Surface3> surfs3;

	void ParseVertex(vector<string>* vertexData)
	{
		for (auto e : *vertexData)
		{
			float val = atof(e.c_str());

			if (curVertInd == 0)
				(vertexes.end() - 1)->X = val;
			else if (curVertInd == 1)
				(vertexes.end() - 1)->Y = val;
			else
				(vertexes.end() - 1)->Z = val;

			curVertInd++;

			if (curVertInd > 2)
				curVertInd = 0;
		}
	}

	void ParseNormal(vector<string>* normalData)
	{
		for (auto e : *normalData)
		{
			float val = atof(e.c_str());

			if (curNormInd == 0)
				(normals.end() - 1)->X = val;
			else if (curNormInd == 1)
				(normals.end() - 1)->Y = val;
			else
				(normals.end() - 1)->Z = val;

			curNormInd++;

			if (curNormInd > 2)
				curNormInd = 0;
		}
	}

	void ParseTexture(vector<string>* textureData)
	{
		for (auto e : *textureData)
		{
			float val = atof(e.c_str());

			if (curTexInd == 0)
				(texCoords.end() - 1)->X = val;
			else
				(texCoords.end() - 1)->Y = val;

			curTexInd++;

			if (curTexInd > 1)
				curTexInd = 0;
		}
	}

	void ParseSurface(vector<string>* surfaceData)
	{
		if (curSurfSize == 3)
			surfs3.push_back({ 0 });
		else
			surfs4.push_back({ 0 });

		for (auto e : *surfaceData)
		{
			if (e.find("//", 0) != string::npos)
			{
				auto vals = split(e, '//');
				ParseSurfVertexAndNormal(&vals);
			}
			else if (chCount(e, '/') == 1)
			{
				auto vals = split(e, '/');
				ParseSurfVertexAndTexture(&vals);
			}
			else
			{
				auto vals = split(e, '/');
				ParseSurfFull(&vals);
			}
		}
	}

	void ParseSurfVertexAndNormal(vector<string>* data)
	{
		int ni = stoi(data->at(2));
		int vi = stoi(data->at(0));

		if (curSurfSize == 3)
		{
			if (ni > 0)
				(surfs3.end() - 1)->normal = normals[ni - 1];
			else
				(surfs3.end() - 1)->normal = *(normals.end() + ni);

			if (vi > 0)
				(surfs3.end() - 1)->points[curSurfInd] = vertexes[vi - 1];
			else
				(surfs3.end() - 1)->points[curSurfInd] = *(vertexes.end() + vi);
		}

		else
		{
			if (ni > 0)
				(surfs4.end() - 1)->normal = normals[ni - 1];
			else
				(surfs4.end() - 1)->normal = *(normals.end() + ni);

			if (vi > 0)
				(surfs4.end() - 1)->points[curSurfInd] = vertexes[vi - 1];
			else
				(surfs4.end() - 1)->points[curSurfInd] = *(vertexes.end() + vi);
		}

		curSurfInd++;

		if (curSurfInd >= curSurfSize)
			curSurfInd = 0;
	}
	void ParseSurfVertexAndTexture(vector<string>* data)
	{
		int vi = stoi(data->at(0));
		int ti = stoi(data->at(1));

		if (curSurfSize == 3)
		{
			if (vi > 0)
				(surfs3.end() - 1)->points[curSurfInd] = vertexes[vi - 1];
			else
				(surfs3.end() - 1)->points[curSurfInd] = *(vertexes.end() + vi);

			if(ti > 0)
				(surfs3.end() - 1)->texCoords[curSurfInd] = texCoords[ti - 1];
			else
				(surfs3.end() - 1)->texCoords[curSurfInd] = *(texCoords.end() + ti);
		}

		else
		{
			if (vi > 0)
				(surfs4.end() - 1)->points[curSurfInd] = vertexes[vi - 1];
			else
				(surfs4.end() - 1)->points[curSurfInd] = *(vertexes.end() + vi);

			if (ti > 0)
				(surfs4.end() - 1)->texCoords[curSurfInd] = texCoords[ti - 1];
			else
				(surfs4.end() - 1)->texCoords[curSurfInd] = *(texCoords.end() + ti);
		}

		curSurfInd++;

		if (curSurfInd >= curSurfSize)
			curSurfInd = 0;
	}
	void ParseSurfFull(vector<string>* data)
	{
		int ni = stoi(data->at(2));
		int ti = stoi(data->at(1));
		int vi = stoi(data->at(0));

		if (curSurfSize == 3)
		{
			if (ni > 0)
				(surfs3.end() - 1)->normal = normals[ni - 1];
			else
				(surfs3.end() - 1)->normal = *(normals.end() + ni);

			if (ti > 0)
				(surfs3.end() - 1)->texCoords[curSurfInd] = texCoords[ti - 1];
			else
				(surfs3.end() - 1)->texCoords[curSurfInd] = *(texCoords.end() + ti);

			if (vi > 0)
				(surfs3.end() - 1)->points[curSurfInd] = vertexes[vi - 1];
			else
				(surfs3.end() - 1)->points[curSurfInd] = *(vertexes.end() + vi);
		}
		else
		{
			if (ni > 0)
				(surfs4.end() - 1)->normal = normals[ni - 1];
			else
				(surfs4.end() - 1)->normal = *(normals.end() + ni);

			if (ti > 0)
				(surfs4.end() - 1)->texCoords[curSurfInd] = texCoords[ti - 1];
			else
				(surfs4.end() - 1)->texCoords[curSurfInd] = *(texCoords.end() + ti);

			if (vi > 0)
				(surfs4.end() - 1)->points[curSurfInd] = vertexes[vi - 1];
			else
				(surfs4.end() - 1)->points[curSurfInd] = *(vertexes.end() + vi);
		}

		curSurfInd++;

		if (curSurfInd >= curSurfSize)
			curSurfInd = 0;
	}

public:

	void Scale(Vertex scale)
	{
		glScalef(scale.X, scale.Y, scale.Z);
	}
	void Translate(Vertex pos)
	{
		glTranslatef(pos.X, pos.Y, pos.Z);
	}
	void Rotate(float angle, Vertex vert)
	{
		glRotatef(angle, vert.X, vert.Y, vert.Z);
	}

	void Load(string fname)
	{
		ifstream stream(fname);

		if (!stream.is_open())
			return;

		while(!stream.eof())
		{
			char buff[256];
			stream.getline(buff, 256);

			string line(buff);

			if (line.empty())
				continue;

			auto elems = split(line, ' ');

			auto dataType = elems[0];
			elems.erase(elems.begin());

			if (dataType == "v")
			{
				vertexes.push_back({ 0, 0, 0 });
				ParseVertex(&elems);
			}
			if(dataType == "vt")
			{
				texCoords.push_back({ 0, 0 });
				ParseTexture(&elems);
			}
			if (dataType == "vn")
			{
				normals.push_back({ 0, 0, 0 });
				ParseNormal(&elems);
			}
			if (dataType == "f")
			{
				curSurfSize = elems.size();
				ParseSurface(&elems);
			}
		}
	}

	void Draw(Texture* texture)
	{
		if (!this)
			return;

		if (texture != nullptr)
			glBindTexture(GL_TEXTURE_2D, texture->ID);

		if (!surfs3.empty())
		{
			glBegin(GL_TRIANGLES);

			for (auto triangle : surfs3)
			{

				glNormal3f(triangle.normal.X, triangle.normal.Y, triangle.normal.Z);

				for (int i = 0; i < 3; i++)
				{
					glTexCoord2f(triangle.texCoords[i].X, triangle.texCoords[i].Y);
					glVertex3f(triangle.points[i].X, triangle.points[i].Y, triangle.points[i].Z);
				}
					
			}

			glEnd();
		}

		if (!surfs4.empty())
		{
			glBegin(GL_QUADS);

			for (auto quad : surfs4)
			{
				glNormal3f(quad.normal.X, quad.normal.Y, quad.normal.Z);

				for (int i = 0; i < 4; i++)
				{
					glTexCoord2f(quad.texCoords[i].X, quad.texCoords[i].Y);
					glVertex3f(quad.points[i].X, quad.points[i].Y, quad.points[i].Z);
				}
			}

			glEnd();
		}
	}
};