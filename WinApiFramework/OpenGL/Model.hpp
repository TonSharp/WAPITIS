#pragma once
#include "GLLibs.hpp"
#include "Surface3.hpp"
#include "Surface4.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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

	int curSurfSize = 3;
	int curSurfInd = 0;
	vector<Surface4> surfs4;
	vector<Surface3> surfs3;

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

			if (line == "")
				continue;

			auto elems = split(line, ' ');

			if (elems[0] == "v")
			{
				vertexes.push_back({ 0 });
				elems.erase(elems.begin());

				for (auto e : elems)
				{
					float val = atof(e.c_str());

					if (curVertInd == 0)
						(vertexes.end()-1)->X = val;
					else if (curVertInd == 1)
						(vertexes.end() - 1)->Y = val;
					else
						(vertexes.end() - 1)->Z = val;

					curVertInd++;

					if (curVertInd > 2)
						curVertInd = 0;
				}

			}
			if (elems[0] == "vn")
			{
				normals.push_back({ 0 });
				elems.erase(elems.begin());

				for (auto e : elems)
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
			if (elems[0] == "f")
			{
				elems.erase(elems.begin());
				curSurfSize = elems.size();

				if (curSurfSize == 3)
					surfs3.push_back({ 0 });
				else
					surfs4.push_back({ 0 });

				for (auto e : elems)
				{
					if (e.find("//", 0) != string::npos)
					{
						auto vals = split(e, '//');

						if (curSurfSize == 3)
						{
							int ni = stoi(vals[2]);
							int vi = stoi(vals[0]);

							if (ni > 0)
								(surfs3.end() - 1)->normal = normals[ni - 1];
							else
								(surfs3.end() - 1)->normal = *(normals.end() + ni);

							if (vi > 0)
								(surfs3.end() - 1)->points[curSurfInd] = vertexes[vi - 1];
							else
								(surfs3.end() - 1)->points[curSurfInd] = *(vertexes.end() + vi);

							curSurfInd++;

							if (curSurfInd >= curSurfSize)
								curSurfInd = 0;
						}

						else
						{
							int ni = stoi(vals[2]);
							int vi = stoi(vals[0]);

							if (ni > 0)
								(surfs4.end() - 1)->normal = normals[ni - 1];
							else
								(surfs4.end() - 1)->normal = *(normals.end() + ni);

							if (vi > 0)
								(surfs4.end() - 1)->points[curSurfInd] = vertexes[vi - 1];
							else
								(surfs4.end() - 1)->points[curSurfInd] = *(vertexes.end() + vi);

							curSurfInd++;

							if (curSurfInd >= curSurfSize)
								curSurfInd = 0;
						}
					}
					else if (chCount(e, '/') == 1)
					{
						auto vals = split(e, '/');

						if (curSurfSize == 3)
						{
							int vi = stoi(vals[0]);

							if (vi > 0)
								(surfs3.end() - 1)->points[curSurfInd] = vertexes[vi - 1];
							else
								(surfs3.end() - 1)->points[curSurfInd] = *(vertexes.end() + vi);

							curSurfInd++;

							if (curSurfInd >= curSurfSize)
								curSurfInd = 0;
						}

						else
						{
							int vi = stoi(vals[0]);

							if (vi > 0)
								(surfs4.end() - 1)->points[curSurfInd] = vertexes[vi - 1];
							else
								(surfs4.end() - 1)->points[curSurfInd] = *(vertexes.end() + vi);

							curSurfInd++;

							if (curSurfInd >= curSurfSize)
								curSurfInd = 0;
						}
					}
					else
					{
						auto vals = split(e, '/');

						if (curSurfSize == 3)
						{
							int ni = stoi(vals[2]);
							int vi = stoi(vals[0]);

							if (ni > 0)
								(surfs3.end() - 1)->normal = normals[ni - 1];
							else
								(surfs3.end() - 1)->normal = *(normals.end() + ni);

							if (vi > 0)
								(surfs3.end() - 1)->points[curSurfInd] = vertexes[vi - 1];
							else
								(surfs3.end() - 1)->points[curSurfInd] = *(vertexes.end() + vi);

							curSurfInd++;

							if (curSurfInd >= curSurfSize)
								curSurfInd = 0;
						}

						else
						{
							int ni = stoi(vals[2]);
							int vi = stoi(vals[0]);

							if (ni > 0)
								(surfs4.end() - 1)->normal = normals[ni - 1];
							else
								(surfs4.end() - 1)->normal = *(normals.end() + ni);

							if (vi > 0)
								(surfs4.end() - 1)->points[curSurfInd] = vertexes[vi - 1];
							else
								(surfs4.end() - 1)->points[curSurfInd] = *(vertexes.end() + vi);

							curSurfInd++;

							if (curSurfInd >= curSurfSize)
								curSurfInd = 0;
						}
					}
				}
			}
		}
	}

	void Draw(RGBAColor color)
	{
		if (!this)
			return;

		GLColor clr = RGBToGL(color);
		glColor3f(clr.R, clr.G, clr.B);

		if (surfs3.size() > 0)
		{
			glBegin(GL_TRIANGLES);

			for (auto triangle : surfs3)
			{
				glNormal3f(triangle.normal.X, triangle.normal.Y, triangle.normal.Z);

				for (int i = 0; i < 3; i++)
					glVertex3f(triangle.points[i].X, triangle.points[i].Y, triangle.points[i].Z);
			}

			glEnd();
		}

		if (surfs4.size() > 0)
		{
			glBegin(GL_QUADS);

			for (auto quad : surfs4)
			{
				glNormal3f(quad.normal.X, quad.normal.Y, quad.normal.Z);

				for (int i = 0; i < 4; i++)
					glVertex3f(quad.points[i].X, quad.points[i].Y, quad.points[i].Z);
			}

			glEnd();
		}
	}
};