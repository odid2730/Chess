#include "pch.h"
#include "Piece.h"

#include "Game/GameData.h"

static int id = 1;

Piece::Piece(const Team& team, const glm::vec3& position, const std::shared_ptr<Texture>& texture)
	: m_Team(team), m_Position(position), m_Texture(texture)
{
	m_PieceID = id++;
}

bool Piece::InBound(float xPos, float yPos)
{
	if (xPos >= 0.0f && xPos <= 7.0f && yPos >= 0.0f && yPos <= 7.0f)
		return true;
	return false;
}

bool Piece::IsAlly(int row, int col)
{
	char piece = GameData::GetMap(row, col);
	bool isAlly = false;

	switch (m_Team)
	{
		case Team::Black:
		{
			if (piece == 'P' || piece == 'R' || piece == 'K' || piece == 'B' || piece == 'Q' || piece == 'W')
				isAlly = true;
			break;
		}
		case Team::White:
		{
			if (piece == 'p' || piece == 'r' || piece == 'k' || piece == 'b' || piece == 'q' || piece == 'w')
				isAlly = true;
			break;
		}
	}
	return isAlly;
}

bool Piece::IsEnemy(int row, int col)
{
	char piece = GameData::GetMap(row, col);
	bool isEnemy = false;

	switch (m_Team)
	{
		case Team::Black:
		{
			if (piece == 'p' || piece == 'r' || piece == 'k' || piece == 'b' || piece == 'q' || piece == 'w')
				isEnemy = true;
			break;
		}
		case Team::White:
		{
			if (piece == 'P' || piece == 'R' || piece == 'K' || piece == 'B' || piece == 'Q' || piece == 'W')
				isEnemy = true;
			break;
		}
	}
	return isEnemy;
}

bool Piece::IsBlank(int row, int col)
{
	return GameData::GetMap(row,col) == 'N';
}

bool Piece::WillBeCheckmate(int xPos, int yPos)
{
	bool isMate = false;

	GameData::CalculateNextCounterpartMovableMap(this, xPos, yPos);
	if (GameData::WillBeCheckmate(xPos,yPos))//GameData::GetNextCounterpartMovableMap(yPos, xPos) == 'T')
	{
		isMate = true;
	}

	return isMate;
}
