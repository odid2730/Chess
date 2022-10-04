#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture);
	virtual ~Queen();

	virtual bool MoveTo(int to) override;
	virtual void IsClicked() override;
	inline virtual PieceType GetType() override { return PieceType::Queen; }
	virtual void OnDestroy() override;
	virtual bool HasMovableRegion() override;
private:
};