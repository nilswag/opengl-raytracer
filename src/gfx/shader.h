#pragma once
#include <string>
#include <map>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& tag);
	~Shader();

	inline unsigned int getId() const { return m_id; }

	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;

	void setMat2(const std::string& name, const glm::mat2& value) const;
	void setMat3(const std::string& name, const glm::mat3& value) const;
	void setMat4(const std::string& name, const glm::mat4& value) const;

private:
	std::map<std::string, GLint> m_uniforms;
	std::string m_tag;
	unsigned int m_id;

	unsigned int compileShader(const std::string& src, GLenum type);

	inline bool hasUniform(const std::string& name) const
	{
		if (m_uniforms.contains(name)) return true;
		spdlog::error("Uniform does not exist: {}", name);
		return false;
	}
};