#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(uint32_t width, uint32_t height, const glm::vec3& position);
	~Camera();

	void OnUpdate();
	void TurnChange(double time);

	const glm::mat4& GetProjection() const { return m_Projection; }
	const glm::mat4& GetViewProjection() const { return m_ViewProjection; }
private:
	void RecalculateViewProjection();
private:
	float m_AspectRatio;
	glm::mat4 m_Projection, m_ViewProjection = glm::mat4(1.0f);
	glm::vec3 m_Position;
	float m_Angle = 0.0f;
	double m_Time = 0.0f;
	double m_TransitionTime = 0.0f;
};