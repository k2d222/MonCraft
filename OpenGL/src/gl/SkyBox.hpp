#pragma once

#include <GL/glew.h>

class Camera;
class Shader;

class SkyBox
{
public:
	SkyBox();

	Shader* skyBoxShader;
	void render(Camera& camera, float time);

private:
	GLuint buffer;
	GLuint skyDayTxr;
	GLuint skyNightTxr;
	GLuint initSky();
	void calcBlendFactor(float skytime);
};
