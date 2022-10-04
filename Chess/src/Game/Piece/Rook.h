#pragma once

#include "Piece.h"

enum class PieceDirection
{
	None = 0, Left, Right
};

class Rook : public Piece
{
public:
	Rook(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture);
	virtual ~Rook();

	virtual bool MoveTo(int to) override;
	virtual void IsClicked() override;
	virtual void OnDestroy() override;
	virtual bool HasMovableRegion() override;

	inline virtual PieceType GetType() override { return PieceType::Rook; }
	inline PieceDirection GetDirection() { return m_Direction; }
private:
	PieceDirection m_Direction = PieceDirection::None;
};