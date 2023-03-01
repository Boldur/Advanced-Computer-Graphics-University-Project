#pragma once
#include "stdafx.h"
#include "GeometryHelper.h"

class TrackGeometry : public GeometryHelper
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec2> uvs;

	void CreateGeometry(float height, int nDivisions)
	{
		glm::vec3* circle = new glm::vec3[nDivisions];
		glm::vec2* circleUV = new glm::vec2[nDivisions];
		for (int i = 0; i < nDivisions; i++)
		{
			float theta = glm::radians(360.0) * (float)i / (nDivisions - 1);
			circle[i] = glm::vec3(cos(-theta), sin(-theta), 0.0f);
			circleUV[i] = (glm::vec2(circle[i].y, circle[i].z) + glm::vec2(1.0f, 1.0f)) * 0.5f;
		}

		for (int i = 0; i < nDivisions/2; i++) // divide by two to get half the can
		{
			glm::vec3 pos[4]; glm::vec3 norm[4]; glm::vec3 tang[4]; glm::vec2 uv[4];
			// positions
			pos[0] = circle[i] + glm::vec3(0, 0 , -height );
			pos[1] = circle[i] + glm::vec3(0, 0, height );
			pos[2] = circle[(i + 1) % nDivisions] + glm::vec3(0,0, height);
			pos[3] = circle[(i + 1) % nDivisions] + glm::vec3(0, 0, -height);
			
			// normals
			norm[0] = -circle[i];
			norm[1] = -circle[i];
			norm[2] = -circle[(i + 1) % nDivisions];
			norm[3] = -circle[(i + 1) % nDivisions];
			// tangents
			tang[0] = glm::cross(norm[0], glm::vec3(0, 1, 0));
			tang[1] = glm::cross(norm[1], glm::vec3(0, 1, 0));
			tang[2] = glm::cross(norm[2], glm::vec3(0, 1, 0));
			tang[3] = glm::cross(norm[3], glm::vec3(0, 1, 0));
			// uv
			uv[0] = glm::vec2((float)i / nDivisions, 0);
			uv[1] = glm::vec2((float)i / nDivisions, 1);
			uv[2] = glm::vec2((float)(i + 1) / nDivisions, 1);
			uv[3] = glm::vec2((float)(i + 1) / nDivisions, 0);

			int triangles[] = { 0, 1, 2, 0, 2, 3 };

			for (int i = 0; i < 6; i++)
			{
				positions.push_back(pos[triangles[i]]);
				normals.push_back(norm[triangles[i]]);
				tangents.push_back(tang[triangles[i]]);
				uvs.push_back(uv[triangles[i]]);
			}
		}
	}
public:
	TrackGeometry(float height = 1.0f, int nDivisions = 30) { CreateGeometry(height, nDivisions); }
	const std::vector<glm::vec3>& GetPositionVector() const { return positions; }
	const std::vector<glm::vec3>& GetNormalVector() const { return normals; }
	const std::vector<glm::vec2>& GetUVVector() const { return uvs; }
	const std::vector<glm::vec3>& GetTangentVector() const { return tangents; }
	int GetNumVertices() const { return positions.size(); }

};