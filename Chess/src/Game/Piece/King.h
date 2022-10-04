#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	King(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture);
	virtual ~King();

	virtual bool MoveTo(int to) override;
	virtual void IsClicked() override;
	inline virtual PieceType GetType() override { return PieceType::King; }
	virtual void OnDestroy() override;
	virtual bool HasMovableRegion() override;
private:
	bool WillBeCheckmate(int xPos, int yPos);
	bool CanBeLeftCastling();
	bool CanBeRightCastling();
private:
};