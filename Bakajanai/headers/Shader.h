#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "precum.h"

namespace Baka {
	class Shader {
	public:
		unsigned int ID;

		Shader(const char* vertexPath, const char* fragmentPath);

		void use();

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setFloat4(const std::string& name, std::vector<float> value);
	};
}

#endif