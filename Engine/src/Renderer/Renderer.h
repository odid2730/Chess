#pragma once

#include "Camera.h"
#include "Texture.h"

#include <glm/glm.hpp>

class Renderer
{
public:
	static void Init();

	static void BeginScene(const Camera& camera);
	static void EndScene();

	static void DrawQuad(const glm::vec3& position, const glm::vec4& color, const glm::vec2& size, int index = 0, float rotation = 0.0f);
	static void DrawQuad(const glm::vec3& position, const std::shared_ptr<Texture>& texture, const glm::vec2& size, int index = 0, float rotation = 0.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	
	static void DrawFixedQuad(const glm::vec3& position, const glm::vec4& color, const glm::vec2& size, int index = 0, float rotation = 0.0f);
	static void DrawFixedQuad(const glm::vec3& position, const std::shared_ptr<Texture>& texture, const glm::vec2& size, int index = 0, float rotation = 0.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

	static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
	static void DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, const glm::vec4& tintColor = glm::vec4(1.0f));

	static void DrawFixedQuad(const glm::mat4& transform, const glm::vec4& color);
	static void DrawFixedQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, const glm::vec4& tintColor = glm::vec4(1.0f));
};