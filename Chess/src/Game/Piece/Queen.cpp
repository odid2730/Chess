#include "pch.h"
#include "Queen.h"

#include "Renderer/Renderer.h"

#include "Game/GameData.h"

Queen::Queen(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture)
	: Piece(team, position, texture)
{

}

Queen::~Queen()
{

}

bool Queen::MoveTo(int to)
{
	bool moved = false;
	char piece = m_Team == Team::Black ? 'Q' : 'q';

	glm::vec2 toOffsets[8] = { 
		{50,60},
		{60,70},
		{70,80},
		{80,90},
		{90,100},
		{100,110},
		{110,120},
		{120,130}
	};
	glm::vec2 deltaPosition[8] = {
		{0,				to - 50		},
		{to - 60,		to - 60		},
		{to - 70,		0			},
		{to - 80,		-(to - 80)	},
		{0,				-(to - 90)	},
		{-(to - 100),	-(to - 100)	},
		{-(to - 110),	0			},
		{-(to - 120),	to - 120	}
	};

	for (int i = 0; i < 8; i++)
	{
		if (to >= toOffsets[i].x && to < toOffsets[i].y)
		{
			int dx = deltaPosition[i].x, dy = deltaPosition[i].y;
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

void Queen::IsClicked()
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

void Queen::OnDestroy()
{
	GameData::AudioData& audioData = GameData::GetAudioData();
	switch (m_Team)
	{
		case Team::Black:
		{
			GameData::PlayAudio(audioData.GetBlackQueenSoundID());
			break;
		}
		case Team::White:
		{
			GameData::PlayAudio(audioData.GetWhiteQueenSoundID());
			break;
		}
	}
}

bool Queen::HasMovableRegion()
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
