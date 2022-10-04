#include "pch.h"
#include "Pawn.h"
#include "Renderer/Renderer.h"

#include "../GameData.h"
#include "Utils/MousePicking.h"

#include <glm/gtc/matrix_transform.hpp>

#include <thread>
#include "Audio/SoundSource.h"

Pawn::Pawn(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture)
	: Piece(team, position, texture)
{
	

}

Pawn::~Pawn()
{
}

bool Pawn::MoveTo(int to)
{
	bool moved = false;
	char piece = m_Team == Team::Black ? 'P' : 'p';
	switch (to)
	{
		// 전진
		case 50:
		{
			int amount = m_Team == Team::Black ? 1 : -1;
			GameData::SetMap(m_Position.y, m_Position.x, 'N');
			m_Position.y = m_Position.y + amount;
			GameData::SetMap(m_Position.y, m_Position.x, piece);
			
			m_FirstMove = false;
			m_CanBeKilledByEnPassant = false;
			moved = true;
			break;
		}
		// 두 칸 전진
		case 51:
		{
			int amount = m_Team == Team::Black ? 2 : -2;
			GameData::SetMap(m_Position.y, m_Position.x, 'N');
			m_Position.y = m_Position.y + amount;
			GameData::SetMap(m_Position.y, m_Position.x, piece);
			
			m_FirstMove = false;
			m_CanBeKilledByEnPassant = true;
			moved = true;
			break;
		}
		// 우상단 TODO: 해당 칸에 있던 기물 죽이기
		case 52:
		{
			int amount = m_Team == Team::Black ? 1 : -1;

			GameData::KillPiece(m_Position.x + amount, m_Position.y + amount);

			GameData::SetMap(m_Position.y, m_Position.x, 'N');
			m_Position.x = m_Position.x + amount; m_Position.y = m_Position.y + amount;
			GameData::SetMap(m_Position.y, m_Position.x, piece);

			m_FirstMove = false;
			m_CanBeKilledByEnPassant = false;
			moved = true;
			break;
		}
		// 좌상단
		case 53:
		{
			int amount = m_Team == Team::Black ? 1 : -1;

			GameData::KillPiece(m_Position.x - amount, m_Position.y + amount);

			GameData::SetMap(m_Position.y, m_Position.x, 'N');
			m_Position.x = m_Position.x - amount; m_Position.y = m_Position.y + amount;
			GameData::SetMap(m_Position.y, m_Position.x, piece);

			m_FirstMove = false;
			m_CanBeKilledByEnPassant = false;
			moved = true;
			break;
		}
		// Left enpassant
		case 54:
		{
			int amount = m_Team == Team::Black ? 1 : -1;

			GameData::KillPiece(m_Position.x - amount, m_Position.y);
			GameData::SetMap(m_Position.y, m_Position.x - amount, 'N');

			GameData::SetMap(m_Position.y, m_Position.x, 'N');
			m_Position.x = m_Position.x - amount; m_Position.y = m_Position.y + amount;
			GameData::SetMap(m_Position.y, m_Position.x, piece);

			m_FirstMove = false;
			m_CanBeKilledByEnPassant = false;
			moved = true;
			break;
		}
		// Right enpassant
		case 55:
		{
			int amount = m_Team == Team::Black ? 1 : -1;

			GameData::KillPiece(m_Position.x + amount, m_Position.y);
			GameData::SetMap(m_Position.y, m_Position.x + amount, 'N');

			GameData::SetMap(m_Position.y, m_Position.x, 'N');
			m_Position.x = m_Position.x + amount; m_Position.y = m_Position.y + amount;
			GameData::SetMap(m_Position.y, m_Position.x, piece);

			m_FirstMove = false;
			m_CanBeKilledByEnPassant = false;
			moved = true;
			break;
		}
	}
	
	if (m_Team == Team::Black)
	{
		if (m_Position.y == 7.0f)
			Promotion();
	}
	else if (m_Team == Team::White)
	{
		if (m_Position.y == 0.0f)
			Promotion();
	}

	return moved;
}

void Pawn::IsClicked()
{
	// 전진
	const auto& gameInfo = GameData::GetGameInfo();
	glm::vec4 blueColor = gameInfo.BlueColor;
	glm::vec4 redColor = gameInfo.RedColor;
	{
		int amount = m_Team == Team::Black ? 1 : -1;
		int movedX = m_Position.x;
		int movedY = m_Position.y + amount;

		if (InBound(movedX, movedY))
		{
			if (!WillBeCheckmate(movedX, movedY))
			{
				if (IsBlank(movedY, movedX))
				{
					Renderer::DrawQuad({ movedX, movedY, 0.2f }, blueColor, { 1.0f, 1.0f }, 50);

					amount = m_Team == Team::Black ? 2 : -2;
					movedY = m_Position.y + amount;
					if (m_FirstMove && IsBlank(movedY, movedX))
					{
						Renderer::DrawQuad({ movedX, movedY, 0.2f }, blueColor, { 1.0f, 1.0f }, 51);
					}
				}
			}
		}
	}

	// 우상단
	{
		int delta = m_Team == Team::Black ? 1 : -1;
		int movedX = m_Position.x + delta;
		int movedY = m_Position.y + delta;

		if (InBound(movedX, movedY))
		{
			if (!WillBeCheckmate(movedX, movedY))
			{
				if (IsEnemy(movedY, movedX))
					Renderer::DrawQuad({ movedX, movedY, 0.2f }, redColor, { 1.0f, 1.0f }, 52);
			}
		}
	}
	// 좌상단
	{
		int delta = m_Team == Team::Black ? 1 : -1;
		int movedX = m_Position.x - delta;
		int movedY = m_Position.y + delta;

		if (InBound(movedX, movedY))
		{
			if (!WillBeCheckmate(movedX, movedY))
			{
				if (IsEnemy(movedY, movedX))
					Renderer::DrawQuad({ movedX, movedY, 0.2f }, redColor, { 1.0f, 1.0f }, 53);
			}
		}
	}

	// 앙파상
	{
		int isEnPassantable = GameData::IsEnPassantable(this);
		
		if (isEnPassantable == 1) // left
		{
			int deltaX = m_Team == Team::Black ? -1 : 1;
			int deltaY = m_Team == Team::Black ? 1 : -1;
			int movedX = m_Position.x + deltaX;
			int movedY = m_Position.y + deltaY;

			Renderer::DrawQuad({ movedX, movedY, 0.2f }, { 0.8f, 0.8f, 0.2f, 0.5f }, { 1.0f, 1.0f }, 54);
		}
		else if (isEnPassantable == 2) // right
		{
			int deltaX = m_Team == Team::Black ? 1 : -1;
			int deltaY = m_Team == Team::Black ? 1 : -1;
			int movedX = m_Position.x + deltaX;
			int movedY = m_Position.y + deltaY;

			Renderer::DrawQuad({ movedX, movedY, 0.2f }, { 0.8f, 0.8f, 0.2f, 0.5f }, { 1.0f, 1.0f }, 55);
		}
	}
}

void Pawn::OnDestroy()
{
	GameData::AudioData& audioData = GameData::GetAudioData();
	switch (m_Team)
	{
		case Team::Black:
		{
			GameData::PlayAudio(audioData.GetBlackPawnSoundID());
			break;
		}
		case Team::White:
		{
			GameData::PlayAudio(audioData.GetWhitePawnSoundID());
			break;
		}
	}
}

bool Pawn::HasMovableRegion()
{
	m_MovableRegion = 0;
	// 전진
	{
		int amount = m_Team == Team::Black ? 1 : -1;
		int movedX = m_Position.x;
		int movedY = m_Position.y + amount;

		if (InBound(movedX, movedY))
		{
			if (!WillBeCheckmate(movedX, movedY))
			{
				if (IsBlank(movedY, movedX))
				{
					m_MovableRegion++;
				}
			}
		}
	}

	// 우상단
	{
		int delta = m_Team == Team::Black ? 1 : -1;
		int movedX = m_Position.x + delta;
		int movedY = m_Position.y + delta;

		if (InBound(movedX, movedY))
		{
			if (!WillBeCheckmate(movedX, movedY))
			{
				if (IsEnemy(movedY, movedX))
					m_MovableRegion++;
			}
		}
	}
	// 좌상단
	{
		int delta = m_Team == Team::Black ? 1 : -1;
		int movedX = m_Position.x - delta;
		int movedY = m_Position.y + delta;

		if (InBound(movedX, movedY))
		{
			if (!WillBeCheckmate(movedX, movedY))
			{
				if (IsEnemy(movedY, movedX))
					m_MovableRegion++;
			}
		}
	}
	return m_MovableRegion > 0;
}

void Pawn::Promotion()
{
	GameData::PromotionStart(this);
}
