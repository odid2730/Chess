#include "pch.h"
#include "UILayer.h"

#include "Core/Application.h"
#include "Renderer/Renderer.h"

#include "Utils/MousePicking.h"
#include "GameData.h"

void UILayer::OnAttach()
{
	m_StatusTexture = Texture::Create("assets/textures/status.png");

	m_BlackPawn = Texture::Create("assets/textures/b_pawn_2x_ns.png");
	m_BlackRook =  Texture::Create("assets/textures/b_rook_2x_ns.png");
	m_BlackKnight = Texture::Create("assets/textures/b_knight_2x_ns.png");
	m_BlackBishop = Texture::Create("assets/textures/b_bishop_2x_ns.png");
	m_BlackQueen = Texture::Create("assets/textures/b_queen_2x_ns.png");
	
	m_WhitePawn = Texture::Create("assets/textures/w_pawn_2x_ns.png");
	m_WhiteRook = Texture::Create("assets/textures/w_rook_2x_ns.png");
	m_WhiteKnight = Texture::Create("assets/textures/w_knight_2x_ns.png");
	m_WhiteBishop = Texture::Create("assets/textures/w_bishop_2x_ns.png");
	m_WhiteQueen = Texture::Create("assets/textures/w_queen_2x_ns.png");

	m_Digit[0] = nullptr;
	m_Digit[1] = Texture::Create("assets/textures/one.png");
	m_Digit[2] = Texture::Create("assets/textures/two.png");
	m_Digit[3] = Texture::Create("assets/textures/three.png");
	m_Digit[4] = Texture::Create("assets/textures/four.png");
	m_Digit[5] = Texture::Create("assets/textures/five.png");
	m_Digit[6] = Texture::Create("assets/textures/six.png");
	m_Digit[7] = Texture::Create("assets/textures/seven.png");
	m_Digit[8] = Texture::Create("assets/textures/eight.png");

	m_TurnIndicator = Texture::Create("assets/textures/turnindicator.png");

	m_BlackWin = Texture::Create("assets/textures/blackwin.png");
	m_WhiteWin = Texture::Create("assets/textures/whitewin.png");

	m_MenuTexture = Texture::Create("assets/textures/menu.png");

	m_PawnDestroyed = Texture::Create("assets/textures/pawndestroyed.png");
	m_RookDestroyed = Texture::Create("assets/textures/rookdestroyed.png");
	m_KnightDestroyed = Texture::Create("assets/textures/knightdestroyed.png");
	m_BishopDestroyed = Texture::Create("assets/textures/bishopdestroyed.png");
	m_QueenDestroyed = Texture::Create("assets/textures/queendestroyed.png");
	m_BackgroundDestroyed = Texture::Create("assets/textures/backgrounddestroyed.png");
}

void UILayer::OnDetach()
{
}

void UILayer::OnUpdate()
{
	auto& gameInfo = GameData::GetGameInfo();
	auto& whosTurn = gameInfo.WhosTurn;

	bool isPromotion = gameInfo.StartPromotionAnimation;

	// UI
	const std::vector<std::pair<Piece*, int>>& blackDestroyed = gameInfo.BlackDeadPieces;
	const std::vector<std::pair<Piece*, int>>& whiteDestroyed = gameInfo.WhiteDeadPieces;
	Renderer::DrawFixedQuad({ -6.2f, 3.8f, 0.6f }, m_StatusTexture, { 4.0f, 2.0f });
	int i = 0;
	for (const auto& black : blackDestroyed)
	{
		Piece* blackDead = black.first;
		int count = black.second;
		Renderer::DrawFixedQuad({ -7.665f + 0.73f * i, 4.28f, 0.65f }, blackDead->GetTexture(), { 0.55f, 0.55f });
		Renderer::DrawFixedQuad({ -7.48f + 0.73f * i, 4.45f, 0.66f }, m_Digit[count], { 0.3f, 0.3f });
		i++;
	}
	i = 0;
	for (const auto& white : whiteDestroyed)
	{
		Piece* whiteDead = white.first;
		int count = white.second;
		Renderer::DrawFixedQuad({ -7.665f + 0.73f * i, 3.53f, 0.65f }, whiteDead->GetTexture(), { 0.55f, 0.55f });
		Renderer::DrawFixedQuad({ -7.48f + 0.73f * i, 3.70f, 0.66f }, m_Digit[count], { 0.3f, 0.3f });
		i++;
	}
	
	if (GameData::CheckmateCheck())
	{
		double ts = 1.0f / 60.0f;
		m_CheckmateAnimationTimer += 1.0f / 60.0f;
		m_XPosition -= 5.0f * (m_CheckmateAnimationTimer * m_CheckmateAnimationTimer) * ts / m_TransitionTime;
		m_Transparency += (m_CheckmateAnimationTimer * m_CheckmateAnimationTimer) * ts / m_TransitionTime;
		if (m_XPosition <= 0.0f)
			m_XPosition = 0.0f;
		if (m_Transparency >= 1.0f)
			m_Transparency = 1.0f;
		Renderer::DrawFixedQuad({ 0.0f,0.0f,0.99f }, { 0.3f,0.3f,0.3f, 0.6f }, { 20,20 });
		if (whosTurn == GameData::GameState::Black)
		{
			Renderer::DrawFixedQuad({ m_XPosition, 2.5f, 1.0f }, m_WhiteWin, { 4.0f, 2.0f }, 0, 0, { 1.0f, 1.0f, 1.0f, m_Transparency });
		}
		else
		{
			Renderer::DrawFixedQuad({ m_XPosition, 2.5f, 1.0f }, m_BlackWin, { 4.0f, 2.0f }, 0, 0, { 1.0f, 1.0f, 1.0f, m_Transparency });
		}
		Renderer::DrawFixedQuad({ 0.0f, -2.0f, 1.0f }, m_MenuTexture, { 2.0f, 1.0f }, 1);
	}
	
	// Turn indicator
	if (whosTurn == GameData::GameState::Black)
	{
		Renderer::DrawQuad({ 3.5f, 0.5f, -0.6f }, m_TurnIndicator, { 8.4f, 2.4f });
	}
	else if (whosTurn == GameData::GameState::White)
	{
		Renderer::DrawQuad({ 3.5f, 6.5f, -0.6f }, m_TurnIndicator, { 8.4f, 2.4f }, 0, 180.0f);
	}

	// Promotion
	if (isPromotion)
	{
		Renderer::DrawFixedQuad({ 0.0f, 0.0f, 0.7f }, { 0.3f, 0.3f, 0.3f, 0.5f }, { 1200.0f / 720.0f * 10.0f, 10.0f });
		if (whosTurn == GameData::GameState::White)
		{
			Renderer::DrawFixedQuad({ -2.25f, 3.0f, 0.71f }, m_BlackRook, { 1.0f, 1.0f }, 10);
			Renderer::DrawFixedQuad({ -0.75f, 3.0f, 0.71f }, m_BlackKnight, { 1.0f, 1.0f }, 11);
			Renderer::DrawFixedQuad({  0.75f, 3.0f, 0.71f }, m_BlackBishop, { 1.0f, 1.0f }, 12);
			Renderer::DrawFixedQuad({  2.25f, 3.0f, 0.71f }, m_BlackQueen, { 1.0f, 1.0f }, 13);
		}
		else if (whosTurn == GameData::GameState::Black)
		{
			Renderer::DrawFixedQuad({ -2.25f, 3.0f, 0.71f }, m_BlackRook, { 1.0f, 1.0f }, 10);
			Renderer::DrawFixedQuad({ -0.75f, 3.0f, 0.71f }, m_BlackKnight, { 1.0f, 1.0f }, 11);
			Renderer::DrawFixedQuad({ 0.75f, 3.0f, 0.71f }, m_BlackBishop, { 1.0f, 1.0f }, 12);
			Renderer::DrawFixedQuad({ 2.25f, 3.0f, 0.71f }, m_BlackQueen, { 1.0f, 1.0f }, 13);
		}
	}

	// Piece destroy
	bool isDestroyed = gameInfo.JustDestroyedPiece;
	if (isDestroyed)
	{
		double ts = 1.0f / 60.0f;
		double transitionTime = 1.0f;
		double deltaX = 4 - 4 * (m_Time * m_Time) / transitionTime;
		if (deltaX <= 0)
			deltaX = 0.0f;
		m_Time += ts;

		Team team = gameInfo.JustDestroyedPieceTeam;
		PieceType type = gameInfo.JustDestroyedPieceType;

		std::shared_ptr<Texture> deadPieceTexture = GetPieceTexture(team, type);
		std::shared_ptr<Texture> deadPieceTextTexture = GetTextTexture(type);
	
		Renderer::DrawFixedQuad({ 0.75f + deltaX, 3.0f, 0.69f }, m_BackgroundDestroyed, { 8.0f, 1.5f }, 0, 0.0f, { 1.0f, 1.0f, 1.0f, 0.8f });
		Renderer::DrawFixedQuad({ -2.0f + deltaX, 3.0f, 0.7f }, deadPieceTexture, { 1.0f, 1.0f });
		Renderer::DrawFixedQuad({  1.5f + deltaX, 3.0f, 0.7f }, deadPieceTextTexture, { 6.0f, 1.5f });
		if (m_Time >= 2.0f)
		{
			GameData::ResetJustDestroyedPieceData();
			m_Time = 0.0f;
		}
	}
}

void UILayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MousePressedEvent>(std::bind(&UILayer::OnMousePressed, this, std::placeholders::_1));
}

std::shared_ptr<Texture> UILayer::GetPieceTexture(Team team, PieceType type)
{
	switch (type)
	{
		case PieceType::Pawn:
		{
			return (team == Team::Black ? m_BlackPawn : m_WhitePawn);
			break;
		}
		case PieceType::Rook:
		{
			return team == Team::Black ? m_BlackRook : m_WhiteRook;
			break;
		}
		case PieceType::Knight:
		{
			return team == Team::Black ? m_BlackKnight : m_WhiteKnight;
			break;
		}
		case PieceType::Bishop:
		{
			return team == Team::Black ? m_BlackBishop : m_WhiteBishop;
			break;
		}
		case PieceType::Queen:
		{
			return team == Team::Black ? m_BlackQueen : m_WhiteQueen;
			break;
		}
	}
	return nullptr;
}

std::shared_ptr<Texture> UILayer::GetTextTexture(PieceType type)
{
	switch (type)
	{
		case PieceType::Pawn:
		{
			return m_PawnDestroyed;
			break;
		}
		case PieceType::Rook:
		{
			return m_RookDestroyed;
			break;
		}
		case PieceType::Knight:
		{
			return m_KnightDestroyed;
			break;
		}
		case PieceType::Bishop:
		{
			return m_BishopDestroyed;
			break;
		}
		case PieceType::Queen:
		{
			return m_QueenDestroyed;
			break;
		}
	}
	return nullptr;
}

bool UILayer::OnMousePressed(MousePressedEvent& e)
{
	auto& gameInfo = GameData::GetGameInfo();
	auto& whosTurn = gameInfo.WhosTurn;
	bool isPromotion = gameInfo.StartPromotionAnimation;
	Team team = whosTurn == GameData::GameState::White ? Team::Black : Team::White;
	int stencil = Utils::GetStencilIndex();
	std::cout << "UILayer::Stencil index: " << stencil << std::endl;

	bool isEnabled = false;

	if (GameData::CheckmateCheck())
	{
		isEnabled = true;
		if (stencil == 1)
		{
			Application& app = Application::Get();
			app.ReturnToMenu();
		}
	}

	if (isPromotion)
	{
		isEnabled = true;
		switch (stencil)
		{
			case 10:
			{
				GameData::PromotionEnd(PieceType::Rook, team == Team::Black ? m_BlackRook : m_WhiteRook);
				break;
			}
			case 11:
			{
				GameData::PromotionEnd(PieceType::Knight, team == Team::Black ? m_BlackKnight : m_WhiteKnight);
				break;
			}
			case 12:
			{
				GameData::PromotionEnd(PieceType::Bishop, team == Team::Black ? m_BlackBishop : m_WhiteBishop);
				break;
			}
			case 13:
			{
				GameData::PromotionEnd(PieceType::Queen, team == Team::Black ? m_BlackQueen : m_WhiteQueen);
				break;
			}
		}
	}

	return isEnabled;
}
