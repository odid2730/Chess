#include "pch.h"
#include "King.h"

#include "Renderer/Renderer.h"
#include "Game/GameData.h"

King::King(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture)
	: Piece(team, position, texture)
{

}

King::~King()
{

}

bool King::MoveTo(int to)
{
	bool moved = false;
	char piece = m_Team == Team::Black ? 'W' : 'w';

	glm::vec2 deltaPosition[8] = {
		{0, 1}, { 1, 1}, { 1, 0}, { 1,-1},
		{0,-1}, {-1,-1}, {-1, 0}, {-1, 1}
	};

	for (int i = 0; i < 8; i++)
	{
		if (to == 51 + i)
		{
			int dx = deltaPosition[i].x, dy = deltaPosition[i].y;
			if (IsEnemy(m_Position.y + dy, m_Position.x + dx))
				GameData::KillPiece(m_Position.x + dx, m_Position.y + dy);
			GameData::SetMap(m_Position.y, m_Position.x, 'N');
			m_Position.x += dx; m_Position.y += dy;
			GameData::SetMap(m_Position.y, m_Position.x, piece);
			moved = true;

			auto& gameinfo = GameData::GetGameInfo();
			if (m_Team == Team::Black)
				gameinfo.IsBlackKingMoved = true;
			else
				gameinfo.IsWhiteKingMoved = true;
			break;
		}
	}
	// left castling
	if (to == 60)
	{
		GameData::DoLeftCastling();
		moved = true;
	}
	// right castling
	else if (to == 61)
	{
		GameData::DoRightCastling();
		moved = true;
	}

	return moved;
}

void King::IsClicked()
{
	const GameData::GameInfo& gameInfo = GameData::GetGameInfo();
	glm::vec4 redColor = gameInfo.RedColor;
	glm::vec4 blueColor = gameInfo.BlueColor;

	glm::vec2 directions[8] = {
		{0,1},
		{1,1},
		{1,0},
		{1,-1},
		{0,-1},
		{-1,-1},
		{-1,0},
		{-1,1}
	};

	for (int direction = 0; direction < 8; direction++)
	{
		int stencilOffset = 50;
		int xDirection = directions[direction].x;
		int yDirection = directions[direction].y;

		int movedXPos = m_Position.x + xDirection;
		int movedYPos = m_Position.y + yDirection;
		if (InBound(movedXPos, movedYPos))
		{
			if (WillBeCheckmate(movedXPos, movedYPos))
			{
				continue;
			}
			if (IsEnemy(movedYPos, movedXPos))
			{
				Renderer::DrawQuad({ movedXPos, movedYPos, 0.2f }, redColor, { 1.0f, 1.0f }, stencilOffset + direction + 1);
			}
			else if (!IsAlly(movedYPos, movedXPos))
			{
				Renderer::DrawQuad({ movedXPos, movedYPos, 0.2f }, blueColor, { 1.0f, 1.0f }, stencilOffset + direction + 1);
			}
		}
	}
	if (CanBeLeftCastling())
	{
		int movedX = m_Position.x + (m_Team == Team::Black ? -2 : 2);
		int movedY = m_Position.y;
		Renderer::DrawQuad({ movedX, movedY, 0.2f }, { 0.8f, 0.8f, 0.2f, 0.5f }, { 1.0f, 1.0f }, 60);
		
		int rookX = m_Team == Team::Black ? 0 : 7;
		int rookY = m_Team == Team::Black ? 0 : 7;
		Renderer::DrawQuad({ rookX, rookY, 0.2f }, { 0.8f, 0.8f, 0.2f, 0.5f }, { 1.0f, 1.0f }, 60);
	}
	if (CanBeRightCastling())
	{
		int movedX = m_Position.x + (m_Team == Team::Black ? 2 : -2);
		int movedY = m_Position.y;
		Renderer::DrawQuad({ movedX, movedY, 0.2f }, { 0.8f, 0.8f, 0.2f, 0.5f }, { 1.0f, 1.0f }, 61);

		int rookX = m_Team == Team::Black ? 7 : 0;
		int rookY = m_Team == Team::Black ? 0 : 7;
		Renderer::DrawQuad({ rookX, rookY, 0.2f }, { 0.8f, 0.8f, 0.2f, 0.5f }, { 1.0f, 1.0f }, 61);
	}
}

void King::OnDestroy()
{
	// King is never destroyed.
}

bool King::HasMovableRegion()
{
	glm::vec2 directions[8] = {
		{0,1},
		{1,1},
		{1,0},
		{1,-1},
		{0,-1},
		{-1,-1},
		{-1,0},
		{-1,1}
	};
	m_MovableRegion = 0;
	for (int direction = 0; direction < 8; direction++)
	{
		int stencilOffset = 50;
		int xDirection = directions[direction].x;
		int yDirection = directions[direction].y;

		int movedXPos = m_Position.x + xDirection;
		int movedYPos = m_Position.y + yDirection;
		if (InBound(movedXPos, movedYPos))
		{
			if (WillBeCheckmate(movedXPos, movedYPos))
			{
				continue;
			}
			if (IsAlly(movedYPos, movedXPos))
				continue;
			
			m_MovableRegion++;
		}
	}
	return m_MovableRegion > 0;
}

bool King::WillBeCheckmate(int xPos, int yPos)
{
	bool isMate = false;

	GameData::CalculateNextCounterpartMovableMap(this, xPos, yPos);
	if (GameData::GetNextCounterpartMovableMap(yPos, xPos) == 'T')
	{
		isMate = true;
	}

	return isMate;
}

bool King::CanBeLeftCastling()
{
	bool canBeLeftCastling = true;
	
	const auto& gameinfo = GameData::GetGameInfo();
	bool isLeftRookMoved = m_Team == Team::Black ? gameinfo.IsLeftBlackRookMoved : gameinfo.IsLeftWhiteRookMoved;
	bool isKingMoved = m_Team == Team::Black ? gameinfo.IsBlackKingMoved : gameinfo.IsWhiteKingMoved;

	// Left rook and king are moved?
	if (isLeftRookMoved || isKingMoved)
		canBeLeftCastling = false;

	switch (m_Team)
	{
		case Team::Black:
		{
			if (GameData::GetMap(0,1) != 'N' || GameData::GetMap(0, 2) != 'N' || GameData::GetMap(0, 3) != 'N')
				canBeLeftCastling = false;
			break;
		}
		case Team::White:
		{
			if (GameData::GetMap(7, 5) != 'N' || GameData::GetMap(7, 6) != 'N')
				canBeLeftCastling = false;
			break;
		}
	}

	if (GameData::IsCurrentlyCheck())
		canBeLeftCastling = false;
	return canBeLeftCastling;
}

bool King::CanBeRightCastling()
{
	bool canBeRightCastling = true;

	const auto& gameinfo = GameData::GetGameInfo();
	bool isRightRookMoved = m_Team == Team::Black ? gameinfo.IsRightBlackRookMoved : gameinfo.IsRightWhiteRookMoved;
	bool isKingMoved = m_Team == Team::Black ? gameinfo.IsBlackKingMoved : gameinfo.IsWhiteKingMoved;

	// Right rook and king are moved?
	if (isRightRookMoved || isKingMoved)
		canBeRightCastling = false;

	switch (m_Team)
	{
		case Team::Black:
		{
			if (GameData::GetMap(0, 5) != 'N' || GameData::GetMap(0, 6) != 'N')
				canBeRightCastling = false;
			break;
		}
		case Team::White:
		{
			if (GameData::GetMap(7, 1) != 'N' || GameData::GetMap(7, 2) != 'N' || GameData::GetMap(7, 3) != 'N')
				canBeRightCastling = false;
			break;
		}
	}

	if (GameData::IsCurrentlyCheck())
		canBeRightCastling = false;
	return canBeRightCastling;
}