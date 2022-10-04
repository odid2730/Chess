#include "pch.h"

#include "GameLayer.h"
#include "Core/Application.h"
#include "Core/Keycode.h"

#include "GameData.h"
#include "Utils/MousePicking.h"

#include <glm/glm.hpp>

GameLayer::GameLayer()
	: m_Camera(1200, 720, glm::vec3(3.5f, 3.5f, 0.0f))
{

}

void GameLayer::OnAttach()
{
	Application& app = Application::Get();
	//app.ActivateGame();
	std::cout << "OnAttach" << std::endl;
	
	// Texture loading
	m_GrayTile = Texture::Create("assets/textures/square gray light _2x_ns.png");
	m_BrownTile = Texture::Create("assets/textures/square brown light_2x_ns.png");
	//m_StatusTexture = Texture::Create("assets/textures/status.png");
	//m_Digit[0] = nullptr;
	//m_Digit[1] = Texture::Create("assets/textures/one.png");
	//m_Digit[2] = Texture::Create("assets/textures/two.png");
	//m_Digit[3] = Texture::Create("assets/textures/three.png");
	//m_Digit[4] = Texture::Create("assets/textures/four.png");
	//m_Digit[5] = Texture::Create("assets/textures/five.png");
	//m_Digit[6] = Texture::Create("assets/textures/six.png");
	//m_Digit[7] = Texture::Create("assets/textures/seven.png");
	//m_Digit[8] = Texture::Create("assets/textures/eight.png");

	//m_TurnIndicator = Texture::Create("assets/textures/turnindicator.png");

	//m_BlackWin = Texture::Create("assets/textures/blackwin.png");
	//m_WhiteWin = Texture::Create("assets/textures/whitewin.png");
	GameData::InitGame();

	GameData::AudioData& audioData = GameData::GetAudioData();
	GameData::StartBGM();

	/*
	m_PawnB = Texture::Create("assets/textures/b_pawn_2x_ns.png");
	m_RookB = Texture::Create("assets/textures/b_rook_2x_ns.png");
	m_BishopB = Texture::Create("assets/textures/b_bishop_2x_ns.png");
	m_KnightB = Texture::Create("assets/textures/b_knight_2x_ns.png");
	m_QueenB = Texture::Create("assets/textures/b_queen_2x_ns.png");
	m_KingB = Texture::Create("assets/textures/b_king_2x_ns.png");
	
	m_PawnW = Texture::Create("assets/textures/w_pawn_2x_ns.png");
	m_RookW = Texture::Create("assets/textures/w_rook_2x_ns.png");
	m_BishopW = Texture::Create("assets/textures/w_bishop_2x_ns.png");
	m_KnightW = Texture::Create("assets/textures/w_knight_2x_ns.png");
	m_QueenW = Texture::Create("assets/textures/w_queen_2x_ns.png");
	m_KingW = Texture::Create("assets/textures/w_king_2x_ns.png");
	
	// Add pieces
	
	for (int i = 0; i < 8; i++)
	{
		m_BlackPawn[i] = new Pawn(Team::Black, { i, 1.0f, 0.1f }, m_PawnB);
		m_Pieces.push_back(m_BlackPawn[i]);
	}
	m_BlackRook[0] = new Rook(Team::Black, { 0.0f , 0.0f, 0.1f }, m_RookB);
	m_Pieces.push_back(m_BlackRook[0]);
	m_BlackRook[1] = new Rook(Team::Black, { 7.0f , 0.0f, 0.1f }, m_RookB);
	m_Pieces.push_back(m_BlackRook[1]);
	
	m_BlackKnight[0] = new Knight(Team::Black, { 1.0f , 0.0f, 0.1f }, m_KnightB);
	m_Pieces.push_back(m_BlackKnight[0]);
	m_BlackKnight[1] = new Knight(Team::Black, { 6.0f , 0.0f, 0.1f }, m_KnightB);
	m_Pieces.push_back(m_BlackKnight[1]);
	
	m_BlackBishop[0] = new Bishop(Team::Black, { 2.0f , 0.0f, 0.1f }, m_BishopB);
	m_Pieces.push_back(m_BlackBishop[0]);
	m_BlackBishop[1] = new Bishop(Team::Black, { 5.0f , 0.0f, 0.1f }, m_BishopB);
	m_Pieces.push_back(m_BlackBishop[1]);
	
	for (int i = 0; i < 8; i++)
	{
		m_WhitePawn[i] = new Pawn(Team::White, { i, 6.0f, 0.1f }, m_PawnW);
		m_Pieces.push_back(m_WhitePawn[i]);
	}
	m_WhiteRook[0] = new Rook(Team::White, { 0.0f , 7.0f, 0.1f }, m_RookW);
	m_Pieces.push_back(m_WhiteRook[0]);
	m_WhiteRook[1] = new Rook(Team::White, { 7.0f , 7.0f, 0.1f }, m_RookW);
	m_Pieces.push_back(m_WhiteRook[1]);
	
	m_WhiteKnight[0] = new Knight(Team::White, { 1.0f , 7.0f, 0.1f }, m_KnightW);
	m_Pieces.push_back(m_WhiteKnight[0]);
	m_WhiteKnight[1] = new Knight(Team::White, { 6.0f , 7.0f, 0.1f }, m_KnightW);
	m_Pieces.push_back(m_WhiteKnight[1]);
	
	m_WhiteBishop[0] = new Bishop(Team::White, { 2.0f , 7.0f, 0.1f }, m_BishopW);
	m_Pieces.push_back(m_WhiteBishop[0]);
	m_WhiteBishop[1] = new Bishop(Team::White, { 5.0f , 7.0f, 0.1f }, m_BishopW);
	m_Pieces.push_back(m_WhiteBishop[1]);
	*/
}

void GameLayer::OnDetach()
{
	std::cout << "OnDetach" << std::endl;
}

void GameLayer::OnUpdate()
{
	const auto& pieces = GameData::GetPieces();
	auto& gameInfo = GameData::GetGameInfo();
	auto& whosTurn = gameInfo.WhosTurn;

	Renderer::BeginScene(m_Camera);

	m_Camera.OnUpdate();

	if (GameData::CheckmateCheck())
	{
		std::cout << "Checkmate!!!\n";
	}

	// Tile
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2 == 0)
				Renderer::DrawQuad({ j,i,-0.1f }, m_GrayTile, { 1.0f, 1.0f });
			else
				Renderer::DrawQuad({ j,i,-0.1f }, m_BrownTile, { 1.0f, 1.0f });
		}
	}

	// Pieces
	for (auto& piece : pieces)
	{
		switch (piece->GetTeam())
		{
			case Team::Black:
			{
				Renderer::DrawQuad(piece->GetPosition(), piece->GetTexture(), { 0.7f, 0.7f }, piece->GetPieceID());
				break;
			}
			case Team::White:
			{
				Renderer::DrawQuad(piece->GetPosition(), piece->GetTexture(), { 0.7f, 0.7f }, piece->GetPieceID(), 180.0f);
				break;
			}
		}
	}

	// Movable
	for (auto& piece : pieces)
	{
		if (((whosTurn == GameData::GameState::Black && piece->GetTeam() == Team::Black)
			|| (whosTurn == GameData::GameState::White && piece->GetTeam() == Team::White))
			&& piece->GetPieceID() == m_ClickedPieceID)
		{
			piece->IsClicked();
			break;
		}
	}
	Renderer::DrawQuad({ 3.5f, 3.5f, -0.5f }, { 0.6f, 0.498f, 0.317f, 1.0f }, { 8.1f, 8.1f });
	//0.8f, 0.698f, 0.517f
	// UI

	/*
	std::vector<std::pair<Piece*, int>> blackDestroyed = gameInfo.BlackDeadPieces;
	std::vector<std::pair<Piece*, int>> whiteDestroyed = gameInfo.WhiteDeadPieces;
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
	for (int i = 0; i < 5; i++)
	{
		//Renderer::DrawFixedQuad({ -7.665f + 0.73f * i, 4.28f, 0.95f }, { 0.2f, 0.3f, 0.4f, 1.0f }, { 0.7f, 0.7f });
		// Renderer::DrawFixedQuad({ -7.665f + 0.73f * i, 3.53f, 0.65f }, { 0.2f, 0.3f, 0.4f, 1.0f }, { 0.7f, 0.7f });
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
			Renderer::DrawFixedQuad({ m_XPosition, 2.5f, 1.0f }, m_WhiteWin, { 4.0f, 2.0f });
		}
		else
		{
			Renderer::DrawFixedQuad({ m_XPosition, 2.5f, 1.0f }, m_BlackWin, { 4.0f, 2.0f });
		}
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
	*/
	// Test
	if (m_MovableTest)
	{
		std::cout << "Test on" << std::endl;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (GameData::GetCounterpartMovableMap(i, j) == 'T')
					Renderer::DrawQuad({ j,i,0.9f }, { 0.6f, 0.3f, 0.2f, 1.0f }, { 1.0f, 1.0f });
			}
		}
	}
	Renderer::EndScene();
}

void GameLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<KeyPressedEvent>(std::bind(&GameLayer::OnKeyPressed, this, std::placeholders::_1));
	dispatcher.Dispatch<MousePressedEvent>(std::bind(&GameLayer::OnMousePressed, this, std::placeholders::_1));
}

bool GameLayer::OnKeyPressed(KeyPressedEvent& e)
{
	if (e.GetKeycode() == KEY_ESCAPE)
	{
		std::cout << "Key Handeled\n";
		Application& app = Application::Get();
		app.ActivateSettings();
		return true;
	}
	if (e.GetKeycode() == KEY_E)
	{
		m_MovableTest = !m_MovableTest;
		return true;
	}
	return false;
}

bool GameLayer::OnMousePressed(MousePressedEvent& e)
{
	GameData::AudioData& audioData = GameData::GetAudioData();
	auto& gameInfo = GameData::GetGameInfo();
	auto& whosTurn = gameInfo.WhosTurn;

	const auto& pieces = GameData::GetPieces();
	m_ClickedPieceID = Utils::GetStencilIndex();
	std::cout << "Stencil index: " << m_ClickedPieceID << std::endl;
	
	for (auto& piece : pieces)
	{
		if (piece->GetPieceID() == m_ClickedPieceID)
		{
			m_ClickedPiece = piece;
			break;
		}
	}
	if (m_ClickedPiece != nullptr)
	{
		bool moved = m_ClickedPiece->MoveTo(m_ClickedPieceID);
		if (moved)
		{
			GameData::SetCounterpartEnPassantable(false);
			switch (whosTurn)
			{
				case GameData::GameState::Black:
				{
					whosTurn = GameData::GameState::White;
					break;
				}
				case GameData::GameState::White:
				{
					whosTurn = GameData::GameState::Black;
					break;
				}
			}
			GameData::PlayImpact(audioData.GetTookSoundID());
			GameData::TurnChange();
			//m_Camera.TurnChange(3.0f);
		}
	}

	return true;
}