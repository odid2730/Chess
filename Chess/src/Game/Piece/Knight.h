#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture);
	virtual ~Knight();

	virtual bool MoveTo(int to) override;
	virtual void IsClicked() override;
	inline virtual PieceType GetType() override { return PieceType::Knight; }
	virtual void OnDestroy() override;
	virtual bool HasMovableRegion() override;
private:
};