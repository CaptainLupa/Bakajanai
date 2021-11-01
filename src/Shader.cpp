#include "Shader.h"

namespace Baka {
	Shader::Shader(const char* vertexPath, const char* fragmentPath) {
		std::string vCode, fCode;
		std::ifstream vFile, fFile;

		vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vFile.open(vertexPath);
			fFile.open(fragmentPath);

			std::stringstream vStream, fStream;

			vStream << vFile.rdbuf();
			fStream << fFile.rdbuf();

			vFile.close();
			fFile.close();

			vCode = vStream.str();
			fCode = fStream.str();
		} catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::NOT_SUCCESSFULLY_READ\n" << e.what() << std::endl;
		}

		const char* vCode_cStr = vCode.c_str();
		const char* fCode_cStr = fCode.c_str();

		unsigned int vertex, fragment;

		int succ;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vCode_cStr, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &succ);

		if (!succ) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::VERTEX_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fCode_cStr, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &succ);

		if (!succ) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &succ);

		if (!succ) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	/// <summary>
	/// creates a texture and adds it to the texture vector.
	/// </summary>
	/// <param name="imagePath">Path to texture image</param>
	/// <param name="extension">Defaults to ".png", set to ".jpg" etc</param>
	void Shader::createTexture(const std::string& imagePath, const std::string& extension, bool flip) {
		stbi_set_flip_vertically_on_load(flip);

		GLint colorType = (extension == ".png" ? GL_RGBA : GL_RGB);
		std::string wtf = "images/";
		wtf.append(imagePath);

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, channels;
		unsigned char* data = stbi_load(wtf.c_str(), &width, &height, &channels, 0);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, colorType, width, height, 0, colorType, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			std::cout << Baka::BakaText("Failed to load image " + imagePath + ".", BakaColors::RED);
		}
		stbi_image_free(data);

		textures.push_back(texture);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Shader::setActiveTextureUnit(short pos = 0) {
		glActiveTexture(GL_TEXTURE0 + pos);
	}

	void Shader::useTexture(short pos = 0) {
		glBindTexture(GL_TEXTURE_2D, textures[pos]);
	}

	void Shader::use() {
		glUseProgram(ID);
	}

	void Shader::suspend() {
		glUseProgram(0);
	}

	void Shader::setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void Shader::setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void Shader::setFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void Shader::setFloat4(const std::string& name, std::vector<float> value) {
		if (value.size() > 4) {
			std::cout << "ERROR::FLOAT_VECTOR_VALUE_TOO_HIGH\nsetFloat4(" << name << ", vector of size " << value.size() << ")\nProgram ID: " << ID << std::endl;
		} else {
			glUniform4f(glGetUniformLocation(ID, name.c_str()), value[0], value[1], value[2], value[3]);
		}
	}

	void Shader::setFloat3(const std::string& name, std::vector<float> value) {
		if (value.size() > 3) {
			std::cout << "ERROR::FLOAT_VECTOR_VALUE_TOO_HIGH\nsetFloat3(" << name << ", vector of size " << value.size() << ")\nProgram ID: " << ID << std::endl;
		} else {
			glUniform3f(glGetUniformLocation(ID, name.c_str()), value[0], value[1], value[2]);
		}
	}
}