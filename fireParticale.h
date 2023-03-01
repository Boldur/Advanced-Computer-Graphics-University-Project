#pragma once
#include "stdafx.h"
#include "ShaderProgram.h"
#include "Geometry.h"
#include "SphereGeom.h"
#include "Transforms.h"
#include "Drawable.h"
#include "PointLight.h"

class fireParticale : Drawable
{
private:
	glm::vec3 postion;
	glm::vec3 velocity;
	float gravity;
	float lifeLength;
	float rotation;
	float scale;

	float elapsedTime = 0.0f;

public:
	fireParticale(const GeometryHelper& geometry, glm::vec3 postion, glm::vec3 velocity, float gravity,	float lifeLength, float rotation, 	float scale)
	
};
