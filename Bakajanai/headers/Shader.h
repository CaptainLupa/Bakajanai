#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "precomp.h"
#include "Text.h"

namespace Baka {
	class Shader {
	public:
		unsigned int ID;
		std::vector<unsigned int> textures = {};

		Shader(const char* vertexPath, const char* fragmentPath);

		void createTexture(const std::string& imagePath, const std::string& extension = ".png", bool flip = true);
		void setActiveTextureUnit(short pos);
		void useTexture(short pos);

		void use();
		void suspend();

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setFloat4(const std::string& name, std::vector<float> value);
		void setFloat3(const std::string& name, std::vector<float> value);
	};
}

#endif