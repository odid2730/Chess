#include "pch.h"
#include "Knight.h"

#include "Renderer/Renderer.h"
#include "../GameData.h"

#include <thread>

Knight::Knight(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture)
	: Piece(team, position, texture)
{
}

Knight::~Knight()
{
}

bool Knight::MoveTo(int to)
{
	bool moved = false;
	char piece = m_Team == Team::Black ? 'K' : 'k';

	int toValues[8] = { 50,51,52,53,54,55,56,57 };
	glm::vec2 deltaPositions[8] = {
		{1,2},
		{2,1},
		{2,-1},
		{1,-2},
		{-1,-2},
		{-2,-1},
		{-2,1},
		{-1,2}
	};

	for (int i = 0; i < 8; i++)
	{
		if (to == toValues[i])
		{
			int dx = deltaPositions[i].x, dy = deltaPositions[i].y;

			if (IsEnemy(m_Position.y + dy, m_Position.x + dx))
				GameData::KillPiece(m_Position.x + dx, m_Position.y + dy);
			GameData::SetMap(m_Position.y, m_Position.x, 'N');
			m_Position.x += dx; m_Position.y += dy;
			GameData::SetMap(m_Position.y, m_Position.x, piece);

			moved = true;
			break;
		}
	}
	return moved;
}

void Knight::IsClicked()
{
	//     8 1 
	//    7   2
	//      K
	//    6   3
	//     5 4
	glm::vec2 toPos[8] = {
		{1,2},
		{2,1},
		{2,-1},
		{1,-2},
		{-1,-2},
		{-2,-1},
		{-2,1},
		{-1,2}
	};

	const auto& gameInfo = GameData::GetGameInfo();
	glm::vec4 blueColor = gameInfo.BlueColor;
	glm::vec4 redColor = gameInfo.RedColor;

	for (int i = 0; i < 8; i++)
	{
		int movedXPos = m_Position.x + toPos[i].x;
		int movedYPos = m_Position.y + toPos[i].y;

		if (InBound(movedXPos, movedYPos))//m_Position.x + toPos[i][0] >= 0.0f && m_Position.x + toPos[i][0] <= 7.0f && m_Position.y + toPos[i][1] >= 0.0f && m_Position.y + toPos[i][1] <= 7.0f)
		{
			if (WillBeCheckmate(movedXPos, movedYPos))
				continue;
			if (IsBlank(movedYPos, movedXPos))
				Renderer::DrawQuad({ movedXPos, movedYPos, 0.2f }, blueColor, { 1.0f, 1.0f }, 50 + i);
			if (IsEnemy(movedYPos, movedXPos))
				Renderer::DrawQuad({ movedXPos, movedYPos, 0.2f }, redColor, { 1.0f, 1.0f }, 50 + i);
		}
	}
}

void Knight::OnDestroy()
{
	GameData::AudioData& audioData = GameData::GetAudioData();
	switch (m_Team)
	{
		case Team::Black:
		{
			GameData::PlayAudio(audioData.GetBlackKnightSoundID());
			break;
		}
		case Team::White:
		{
			GameData::PlayAudio(audioData.GetWhiteKnightSoundID());
			break;
		}
	}
}

bool Knight::HasMovableRegion()
{
	glm::vec2 toPos[8] = {
		{1,2},
		{2,1},
		{2,-1},
		{1,-2},
		{-1,-2},
		{-2,-1},
		{-2,1},
		{-1,2}
	};
	m_MovableRegion = 0;
	for (int i = 0; i < 8; i++)
	{
		int movedXPos = m_Position.x + toPos[i].x;
		int movedYPos = m_Position.y + toPos[i].y;

		if (InBound(movedXPos, movedYPos))
		{
			if (WillBeCheckmate(movedXPos, movedYPos))
				continue;
			if (IsAlly(movedYPos, movedXPos))
				continue;
			m_MovableRegion++;
		}
	}
	return m_MovableRegion > 0;
}
