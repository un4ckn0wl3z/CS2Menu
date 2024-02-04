#pragma once
#include <Windows.h>

class Config 
{
public:
	bool boxes = 0;
	bool healthBar = 0;
	bool healthStatus = 0;
	bool lines = 0;
	bool team = 0;
	bool distance = 0;
	bool triggerBot = 0;
	bool aimbot = 0;
	bool crosshair = 0;
	bool foundGameProcess = 0;
	bool runFeatures = 1;
};

extern Config config;

struct Vec2
{
	float x;
	float y;
};

struct Vec3 
{
	float x;
	float y;
	float z;
};

struct Vec4
{
	float x;
	float y;
	float z;
	float w;
};

#define CONFIG_FOV 20