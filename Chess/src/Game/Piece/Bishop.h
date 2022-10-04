#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture);
	virtual ~Bishop();

	virtual bool MoveTo(int to) override;
	virtual void IsClicked() override;
	inline virtual PieceType GetType() override { return PieceType::Bishop; }
	virtual void OnDestroy() override;
	virtual bool HasMovableRegion() override;
private:
};