#pragma once
#include "stdafx.h"
#include "ShaderProgram.h"
#include "Geometry.h"
#include "SphereGeom.h"
#include "Transforms.h"
#include "Drawable.h"
#include "PointLight.h"
#include <time.h> 
class Ripple : public Drawable
{
	SOF::ShaderProgram* shader;
	SOF::Geometry* geom;
	glm::vec4 color;
	SOF::Texture* texture;
	void CreateGeometry(const GeometryHelper& geometry)
	{
		shader = new SOF::ShaderProgram("shaders/v_ripple.glsl", "shaders/f_ripple.glsl");
		geom = new SOF::Geometry(geometry.GetNumVertices());
		geom->AddAttribute(geometry.GetPositionVector(), "vertexPos");
		geom->Finalize(shader);
	}
public:
	Ripple(const GeometryHelper& geometry, const glm::vec4& color, const std::string& textureName = "default") : color(color) {

		CreateGeometry(geometry);
		if (textureName == "default")
			texture = new SOF::Texture("textures/default_diffuse.png");
		else
			texture = new SOF::Texture(textureName);

	}
	virtual void Draw(const Transforms& trans, const PointLight& light) override
	{

		//Static time variable,to increment value to act as timer
		static float time;
		//Speed of the simulation
		float speed = 2.;
		//Frequency of sin wave which is used to make ripples
		float frequency = 40;
		//Height or radius of wave,radius for ripple
		float amplitude = 2.;
		//increment the timer
		time += 0.0001 * speed; // make this take deltaT so not to be reliant on frame rate
		glm::mat4 mvp;
		mvp = trans.GetProj() * trans.GetView() * trans.GetModel();
		shader->Use();
		shader->SetUniformMat4("mvp", mvp);
		shader->SetUniformVec4("color", color);
		shader->SetUniformFloat("timer", time);
		shader->SetUniformFloat("frequency", frequency);
		shader->SetUniformFloat("amplitude", amplitude);
		shader->AssignTextureSampler("textureSampler", texture);
		geom->DrawPrimitives();
	}
};