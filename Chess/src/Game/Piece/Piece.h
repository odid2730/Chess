#pragma once

#include "Renderer/Texture.h"

#include <glm/glm.hpp>
#include <stdint.h>
#include <memory>

enum class Team
{
	None = 0, Black = 1, White = 2
};

enum class PieceType
{
	None = 0, Pawn, Rook, Knight, Bishop, Queen, King
};

class Piece
{
public:
	Piece(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture);
	virtual ~Piece() = default;

	virtual bool MoveTo(int to) = 0;
	virtual void IsClicked() = 0;
	virtual PieceType GetType() = 0;
	virtual void OnDestroy() = 0;

	inline void SetPosition(int x, int y) { m_Position.x = x; m_Position.y = y; }
	inline glm::vec3 GetPosition() const { return m_Position; }
	inline std::shared_ptr<Texture>& GetTexture() { return m_Texture; }
	inline uint32_t GetPieceID() { return m_PieceID; }
	inline Team GetTeam() { return m_Team; }

	virtual bool HasMovableRegion() = 0;
protected:
	// Utility
	bool InBound(float xPos, float yPos);
	bool IsAlly(int row, int col);
	bool IsEnemy(int row, int col);
	bool IsBlank(int row, int col);
	bool WillBeCheckmate(int xPos, int yPos);
protected:

	Team m_Team = Team::None;
	glm::vec3 m_Position;
	std::shared_ptr<Texture> m_Texture = nullptr;
	bool m_IsClicked = false;
	int m_MovableRegion = 0;
	uint32_t m_PieceID = 0;
};