#pragma once
#include "stdafx.h"
#include "Drawable.h"
#include <string>
class Terrain : public Drawable
{
	float xzScale;
	float yScale;
	float deltaU;
	float deltaV;
	SOF::Texture* heightMap;
	SOF::Texture* splatMap;
	SOF::Texture* tex0;
	SOF::Texture* tex1;
	SOF::Texture* tex2;
	SOF::Geometry* geom;
	SOF::ShaderProgram* shader;
public:
	Terrain(
		const std::string& heightMapFile, 
		const std::string& splatMapFile,
		const std::string& tex0File, 
		const std::string& tex1File,
		const std::string& tex2File, 
		float xzScale, float yScale);

	virtual void Draw(const Transforms& renderTransform, const PointLight& light) override;
	virtual ~Terrain() {};
};
