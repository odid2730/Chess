#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture);
	virtual ~Pawn();

	virtual bool MoveTo(int to) override;
	virtual void IsClicked() override;
	inline virtual PieceType GetType() override { return PieceType::Pawn; }
	virtual void OnDestroy() override;
	virtual bool HasMovableRegion() override;
	void SetCanBeKilledByEnPassant(bool enabled) { m_CanBeKilledByEnPassant = enabled; }
	bool GetCanBeKilledByEnPassant() { return m_CanBeKilledByEnPassant; }
private:
	void Promotion();
private:
	float m_Time = 0.0f;
	bool m_FirstMove = true;
	bool m_CanBeKilledByEnPassant = false;
};