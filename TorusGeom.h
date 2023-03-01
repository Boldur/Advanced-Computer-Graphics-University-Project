#pragma once
#include "stdafx.h"
#include "GeometryHelper.h"

class TorusGeometry : public GeometryHelper
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
			circle[i] = glm::vec3(cos(theta), 0.0f, sin(theta));
			circleUV[i] = (glm::vec2(circle[i].x, circle[i].z) + glm::vec2(1.0f, 1.0f)) * 0.5f;
		}
		
		// sides

		// the outer for loop generates pairs of cross-sections
		for (int theta = 0; theta < 360; theta += 30) {

			// the inner loop generates two sets of vertices for those sections
			for (int i = 0; i < nDivisions; i++)
			{
				glm::vec3 pos[4]; glm::vec3 norm[4]; glm::vec3 tang[4]; glm::vec2 uv[4];
				// positions
				// rotate around the torus center, first offseting them by (2,0,0);
				{
					float angleRad = glm::radians(static_cast<float>(theta));
					// generate a 4x4 rotation matrix around Z
					auto rot = glm::rotate(glm::mat4(), angleRad, glm::vec3(0, 0, 1));

					// generate cross-section points on segment n 
					glm::vec4 pos0 = glm::vec4(circle[i], 1.0) + glm::vec4(2, 0, 0, 0);
					glm::vec4 pos3 = glm::vec4(circle[(i + 1) % nDivisions], 1.0) + glm::vec4(2, 0, 0, 0);

					// rotate the cross sections in global space so that they follow the torus space
					
					pos[0] = rot * pos0;
					pos[3] = rot * pos3;

					glm::vec4 norm0 = glm::vec4(circle[i], 1.0);
					glm::vec4 norm3 = glm::vec4(circle[(i + 1) % nDivisions], 1.0);

					norm[0] = rot * norm0;
					norm[3] = rot * norm3;
				}

				// segment n+1
				{
					float angleRad = glm::radians(static_cast<float>(theta + 30));
					auto rot = glm::rotate(glm::mat4(), angleRad, glm::vec3(0, 0, 1));
					glm::vec4 pos1 = glm::vec4(circle[i], 1.0) + glm::vec4(2, 0, 0, 0);
					glm::vec4 pos2 = glm::vec4(circle[(i + 1) % nDivisions], 1.0) + glm::vec4(2, 0, 0, 0);

					pos[1] = rot * pos1;
					pos[2] = rot * pos2;

					glm::vec4 norm1 = glm::vec4(circle[i], 1.0);
					glm::vec4 norm2 = glm::vec4(circle[(i + 1) % nDivisions], 1.0);

					norm[1] = rot * norm1;
					norm[2] = rot * norm2;
				}
				
				// tangents
				tang[0] = glm::cross(norm[0], glm::vec3(0, 1, 0));
				tang[1] = glm::cross(norm[1], glm::vec3(0, 1, 0));
				tang[2] = glm::cross(norm[2], glm::vec3(0, 1, 0));
				tang[3] = glm::cross(norm[3], glm::vec3(0, 1, 0));

				// uv
				uv[0] = glm::vec2((float)i / nDivisions, 0);
				uv[1] = glm::vec2((float)i / nDivisions, 1);
				//uv[1] = glm::vec2((float)i / nDivisions, theta / 360.0); // follow cross section
				//uv[2] = glm::vec2((float)(i + 1) / nDivisions, theta / 360.0); // follow cross section
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
	}
public:
	TorusGeometry(float height = 1.0f, int nDivisions = 16) { CreateGeometry(height, nDivisions); }
	const std::vector<glm::vec3>& GetPositionVector() const { return positions; }
	const std::vector<glm::vec3>& GetNormalVector() const { return normals; }
	const std::vector<glm::vec2>& GetUVVector() const { return uvs; }
	const std::vector<glm::vec3>& GetTangentVector() const { return tangents; }
	int GetNumVertices() const { return positions.size(); }

};
