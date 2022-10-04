#include "pch.h"
#include "Rook.h"
#include "Renderer/Renderer.h"

#include "../GameData.h"

Rook::Rook(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture)
	: Piece(team, position, texture)
{
	if (m_Team == Team::Black)
	{
		if (position.x == 0 && position.y == 0)
			m_Direction = PieceDirection::Left;
		if (position.x == 7 && position.y == 0)
			m_Direction = PieceDirection::Right;
	}
	else if (m_Team == Team::White)
	{
		if (position.x == 7 && position.y == 7)
			m_Direction = PieceDirection::Left;
		if (position.x == 0 && position.y == 7)
			m_Direction = PieceDirection::Right;
	}
}

Rook::~Rook()
{
}

bool Rook::MoveTo(int to)
{
	bool moved = false;
	char piece = m_Team == Team::Black ? 'R' : 'r';

	glm::vec2 toOffsets[4] = {
		{50,60},
		{60,70},
		{70,80},
		{80,90},
	};

	glm::vec2 deltaPositions[4] = {
		{0,			  (to - 50)},
		{(to - 60),           0},
		{0,          -(to - 70)},
		{-(to - 80),	      0},
	};

	for (int i = 0; i < 4; i++)
	{
		if (to >= toOffsets[i].x && to < toOffsets[i].y)
		{
			int dx = deltaPositions[i].x, dy = deltaPositions[i].y;
			if (IsEnemy(m_Position.y + dy, m_Position.x + dx))
				GameData::KillPiece(m_Position.x + dx, m_Position.y + dy);
			GameData::SetMap(m_Position.y, m_Position.x, 'N');
			m_Position.x += dx; m_Position.y += dy;
			GameData::SetMap(m_Position.y, m_Position.x, piece);

			moved = true;

			auto& gameinfo = GameData::GetGameInfo();
			
			if (m_Team == Team::Black)
			{
				if (m_Direction == PieceDirection::Left)
					gameinfo.IsLeftBlackRookMoved = true;
				else if (m_Direction == PieceDirection::Right)
					gameinfo.IsRightBlackRookMoved = true;
			}
			else if (m_Team == Team::White)
			{
				if (m_Direction == PieceDirection::Left)
					gameinfo.IsLeftWhiteRookMoved = true;
				else if (m_Direction == PieceDirection::Right)
					gameinfo.IsRightWhiteRookMoved = true;
			}
			break;
		}
	}
	return moved;
}

void Rook::IsClicked()
{
	const auto& gameInfo = GameData::GetGameInfo();
	glm::vec4 blueColor = gameInfo.BlueColor;
	glm::vec4 redColor = gameInfo.RedColor;

	glm::vec2 directions[4] = {
		{0,1},
		{1,0},
		{0,-1},
		{-1,0}
	};

	for (int direction = 0; direction < 4; direction++)
	{
		int stencilOffset = 50 + 10 * direction;
		int xDirection = directions[direction].x;
		int yDirection = directions[direction].y;

		for (int i = 1; i < 8; i++)
		{
			int movedXPos = m_Position.x + i * xDirection;
			int movedYPos = m_Position.y + i * yDirection;

			if (InBound(movedXPos, movedYPos))
			{
				if (WillBeCheckmate(movedXPos, movedYPos))
				{
					if (!IsBlank(movedYPos, movedXPos))
						break;
					continue;
				}
				if (IsEnemy(movedYPos, movedXPos))
				{
					Renderer::DrawQuad({ movedXPos, movedYPos, 0.2f }, redColor, { 1.0f, 1.0f }, stencilOffset + i);
					break;
				}
				if (IsAlly(movedYPos, movedXPos))
					break;
				Renderer::DrawQuad({ movedXPos, movedYPos, 0.2f }, blueColor, { 1.0f, 1.0f }, stencilOffset + i);
			}
			else
			{
				// Out of bounds
				break;
			}
		}
	}
}

void Rook::OnDestroy()
{
	auto& gameInfo = GameData::GetGameInfo();

	switch (m_Team)
	{
		case Team::Black:
		{
			if (m_Direction == PieceDirection::Left)
			{
				gameInfo.IsLeftBlackRookMoved = true;
			}
			else if (m_Direction == PieceDirection::Right)
			{
				gameInfo.IsRightBlackRookMoved = true;
			}
			break;
		}
		case Team::White:
		{
			if (m_Direction == PieceDirection::Left)
			{
				gameInfo.IsLeftWhiteRookMoved = true;
			}
			else if (m_Direction == PieceDirection::Right)
			{
				gameInfo.IsRightWhiteRookMoved = true;
			}
			break;
		}
	}

	GameData::AudioData& audioData = GameData::GetAudioData();
	switch (m_Team)
	{
		case Team::Black:
		{
			GameData::PlayAudio(audioData.GetBlackRookSoundID());
			break;
		}
		case Team::White:
		{
			GameData::PlayAudio(audioData.GetWhiteRookSoundID());
			break;
		}
	}
}

bool Rook::HasMovableRegion()
{
	glm::vec2 directions[4] = {
		{0,1},
		{1,0},
		{0,-1},
		{-1,0}
	};
	m_MovableRegion = 0;
	for (int direction = 0; direction < 4; direction++)
	{
		int xDirection = directions[direction].x;
		int yDirection = directions[direction].y;

		for (int i = 1; i < 8; i++)
		{
			int movedXPos = m_Position.x + i * xDirection;
			int movedYPos = m_Position.y + i * yDirection;

			if (InBound(movedXPos, movedYPos))
			{
				if (WillBeCheckmate(movedXPos, movedYPos))
				{
					if (!IsBlank(movedYPos, movedXPos))
						break;
					continue;
				}
				if (IsAlly(movedYPos, movedXPos))
					break;
				m_MovableRegion++;
			}
			else
			{
				// Out of bounds
				break;
			}
		}
	}
	return m_MovableRegion > 0;
}