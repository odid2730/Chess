#pragma once

#include "Engine.h"

#include "Renderer/Texture.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Piece/Piece.h"

#include "Renderer/Camera.h"

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnEvent(Event& e) override;
private:
	bool OnKeyPressed(KeyPressedEvent& e);
	bool OnMousePressed(MousePressedEvent& e);
private:
	std::shared_ptr<Texture> m_GrayTile, m_BrownTile;
	std::shared_ptr<Texture> m_StatusTexture;
	std::shared_ptr<Texture> m_Digit[9];
	std::shared_ptr<Texture> m_BlackWin, m_WhiteWin;
	std::shared_ptr<Texture> m_TurnIndicator;

	int m_ClickedPieceID = 0;
	Piece* m_ClickedPiece = nullptr;

	double m_CheckmateAnimationTimer = 0.0f;
	double m_TransitionTime = 1.0f;
	double m_XPosition = 4.0f;
	float m_Transparency = 0.0f;

	Camera m_Camera;

	bool m_MovableTest = false;
};