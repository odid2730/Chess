#pragma once
#include "Core/Layer.h"
#include "Renderer/Texture.h"
#include "Piece/Piece.h"

#include "Events/Event.h"
#include "Events/MouseEvent.h"

class UILayer : public Layer
{
public:
	UILayer() = default;
	virtual ~UILayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnEvent(Event & e) override;
private:
	std::shared_ptr<Texture> GetPieceTexture(Team team, PieceType type);
	std::shared_ptr<Texture> GetTextTexture(PieceType type);

	bool OnMousePressed(MousePressedEvent& e);
private:
	std::shared_ptr<Texture> m_StatusTexture;
	std::shared_ptr<Texture> m_BlackPawn, m_BlackRook, m_BlackKnight, m_BlackBishop, m_BlackQueen;
	std::shared_ptr<Texture> m_WhitePawn, m_WhiteRook, m_WhiteKnight, m_WhiteBishop, m_WhiteQueen;
	std::shared_ptr<Texture> m_Digit[9];
	std::shared_ptr<Texture> m_BlackWin, m_WhiteWin;
	std::shared_ptr<Texture> m_TurnIndicator;
	std::shared_ptr<Texture> m_MenuTexture;
	std::shared_ptr<Texture> m_PawnDestroyed, m_RookDestroyed, m_KnightDestroyed, m_BishopDestroyed, m_QueenDestroyed, m_BackgroundDestroyed;

	double m_Time = 0.0f;
	// checkmate
	double m_CheckmateAnimationTimer = 0.0f;
	double m_TransitionTime = 1.0f;
	double m_XPosition = 4.0f;
	float m_Transparency = 0.0f;
};