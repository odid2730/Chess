#include "GameData.h"

#include "Engine.h"

#include "Piece/Pawn.h"
#include "Piece/Rook.h"
#include "Piece/Knight.h"
#include "Piece/Bishop.h"
#include "Piece/Queen.h"
#include "Piece/King.h"

#include <thread>

namespace GameData {

	static char map[8][8] = {
		{'r','k','b','q','w','b','k','r'},
		{'p','p','p','p','p','p','p','p'},
		{'N','N','N','N','N','N','N','N'},
		{'N','N','N','N','N','N','N','N'},
		{'N','N','N','N','N','N','N','N'},
		{'N','N','N','N','N','N','N','N'},
		{'P','P','P','P','P','P','P','P'},
		{'R','K','B','Q','W','B','K','R'}
	};

	static char counterpartMovable[8][8];
	static char nextCounterpartMovable[8][8];
	static GameInfo s_GameInfo;

	// Audio
	static AudioData s_AudioData;
	
	AudioData& GetAudioData()
	{
		return s_AudioData;
	}

	void StartBGM()
	{
		//std::shared_ptr<SoundSource> Speaker = SoundSource::Create(0.1f * s_AudioData.GetVolumn());
		std::thread thread(std::bind(&SoundSource::Play, &s_AudioData.BGMSpeaker, std::placeholders::_1), s_AudioData.GetBGMID());
		thread.detach();
	}

	void PlayAudio(uint32_t id)
	{
		std::shared_ptr<SoundSource> Speaker = SoundSource::Create(1.0f * s_AudioData.GetVolumn());
		std::thread thread(std::thread(std::bind(&SoundSource::Play, Speaker, std::placeholders::_1), id));
		thread.detach();
	}

	void PlayImpact(uint32_t id)
	{
		std::shared_ptr<SoundSource> Speaker = SoundSource::Create(2.0f * s_AudioData.GetVolumn());
		std::thread thread(std::thread(std::bind(&SoundSource::Play, Speaker, std::placeholders::_1), id));
		thread.detach();
	}

	static std::vector<Piece*> s_Pieces;

	void InitGame()
	{
		// Texture loading
		std::shared_ptr<Texture> m_GrayTile = Texture::Create("assets/textures/square gray light _2x_ns.png");
		std::shared_ptr<Texture> m_BrownTile = Texture::Create("assets/textures/square brown light_2x_ns.png");

		std::shared_ptr<Texture> m_PawnB = Texture::Create("assets/textures/b_pawn_2x_ns.png");
		std::shared_ptr<Texture> m_RookB = Texture::Create("assets/textures/b_rook_2x_ns.png");
		std::shared_ptr<Texture> m_BishopB = Texture::Create("assets/textures/b_bishop_2x_ns.png");
		std::shared_ptr<Texture> m_KnightB = Texture::Create("assets/textures/b_knight_2x_ns.png");
		std::shared_ptr<Texture> m_QueenB = Texture::Create("assets/textures/b_queen_2x_ns.png");
		std::shared_ptr<Texture> m_KingB = Texture::Create("assets/textures/b_king_2x_ns.png");
		
		std::shared_ptr<Texture> m_PawnW = Texture::Create("assets/textures/w_pawn_2x_ns.png");
		std::shared_ptr<Texture> m_RookW = Texture::Create("assets/textures/w_rook_2x_ns.png");
		std::shared_ptr<Texture> m_BishopW = Texture::Create("assets/textures/w_bishop_2x_ns.png");
		std::shared_ptr<Texture> m_KnightW = Texture::Create("assets/textures/w_knight_2x_ns.png");
		std::shared_ptr<Texture> m_QueenW = Texture::Create("assets/textures/w_queen_2x_ns.png");
		std::shared_ptr<Texture> m_KingW = Texture::Create("assets/textures/w_king_2x_ns.png");

		for (int i = 0; i < 8; i++)
			s_Pieces.push_back(new Pawn(Team::Black, { i, 1.0f, 0.1f }, m_PawnB));

		s_Pieces.push_back(new Rook(Team::Black, { 0.0f , 0.0f, 0.1f }, m_RookB));
		s_Pieces.push_back(new Rook(Team::Black, { 7.0f , 0.0f, 0.1f }, m_RookB));

		s_Pieces.push_back(new Knight(Team::Black, { 1.0f , 0.0f, 0.1f }, m_KnightB));
		s_Pieces.push_back(new Knight(Team::Black, { 6.0f , 0.0f, 0.1f }, m_KnightB));

		s_Pieces.push_back(new Bishop(Team::Black, { 2.0f , 0.0f, 0.1f }, m_BishopB));
		s_Pieces.push_back(new Bishop(Team::Black, { 5.0f , 0.0f, 0.1f }, m_BishopB));
		
		s_Pieces.push_back(new Queen(Team::Black, { 3.0f , 0.0f, 0.1f }, m_QueenB));
		s_Pieces.push_back(new King(Team::Black, { 4.0f , 0.0f, 0.1f }, m_KingB));
		//White
		for (int i = 0; i < 8; i++)
			s_Pieces.push_back(new Pawn(Team::White, { i, 6.0f, 0.1f }, m_PawnW));

		s_Pieces.push_back(new Rook(Team::White, { 0.0f , 7.0f, 0.1f }, m_RookW));
		s_Pieces.push_back(new Rook(Team::White, { 7.0f , 7.0f, 0.1f }, m_RookW));

		s_Pieces.push_back(new Knight(Team::White, { 1.0f , 7.0f, 0.1f }, m_KnightW));
		s_Pieces.push_back(new Knight(Team::White, { 6.0f , 7.0f, 0.1f }, m_KnightW));

		s_Pieces.push_back(new Bishop(Team::White, { 2.0f , 7.0f, 0.1f }, m_BishopW));
		s_Pieces.push_back(new Bishop(Team::White, { 5.0f , 7.0f, 0.1f }, m_BishopW));

		s_Pieces.push_back(new Queen(Team::White, { 3.0f , 7.0f, 0.1f }, m_QueenW));
		s_Pieces.push_back(new King(Team::White, { 4.0f , 7.0f, 0.1f }, m_KingW));
	}

	GameInfo& GetGameInfo()
	{
		return s_GameInfo;
	}

	char GetMap(int row, int col)
	{
		row = 7 - row;
		return map[row][col];
	}

	void SetMap(int row, int col, char c)
	{
		row = 7 - row;
		map[row][col] = c;
	}

	static bool InBound(int xPos, int yPos)
	{
		if (xPos >= 0 && xPos < 8 && yPos >= 0 && yPos < 8)
			return true;
		return false;
	}

	static bool IsBlank(int xPos, int yPos)
	{
		return GetMap(yPos, xPos) == 'N';
	}
	
	static bool IsEnemy(int xPos, int yPos)
	{
		GameState whosTurn = s_GameInfo.WhosTurn;
		bool isEnemy = false;
		char piece = GetMap(yPos, xPos);

		switch (whosTurn)
		{
			case GameState::Black:
			{
				if (piece == 'P' || piece == 'R' || piece == 'K' || piece == 'B' || piece == 'Q' || piece == 'W')
				//if (piece == 'p' || piece == 'r' || piece == 'k' || piece == 'b' || piece == 'q' || piece == 'w')
					isEnemy = true;
				break;
			}
			case GameState::White:
			{
				if (piece == 'p' || piece == 'r' || piece == 'k' || piece == 'b' || piece == 'q' || piece == 'w')
				//if (piece == 'P' || piece == 'R' || piece == 'K' || piece == 'B' || piece == 'Q' || piece == 'W')
					isEnemy = true;
				break;
			}
		}

		return isEnemy;
	}

	static char GetPieceTypeToChar(Team team, PieceType type)
	{
		switch (type)
		{
			case PieceType::Pawn:
			{
				return team == Team::Black ? 'P' : 'p';
				break;
			}
			case PieceType::Rook:
			{
				return team == Team::Black ? 'R' : 'r';
				break;
			}
			case PieceType::Knight:
			{
				return team == Team::Black ? 'K' : 'k';
				break;
			}
			case PieceType::Bishop:
			{
				return team == Team::Black ? 'B' : 'b';
				break;
			}
			case PieceType::Queen:
			{
				return team == Team::Black ? 'Q' : 'q';
				break;
			}
			case PieceType::King:
			{
				return team == Team::Black ? 'W' : 'w';
				break;
			}
		}
		// Unknown piece type
		std::cout << "Unknown piece type\n";
		return 'N';
	}

	void TurnChange()
	{
		// reset
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
				counterpartMovable[i][j] = 'F';
		}
		Team enemy = s_GameInfo.WhosTurn == GameState::Black ? Team::White : Team::Black;

		for (const auto& piece : s_Pieces)
		{
			if (piece->GetTeam() == enemy)
			{
				PieceType type = piece->GetType();

				int xPos = piece->GetPosition().x;
				int yPos = piece->GetPosition().y;

				switch (type)
				{
					case PieceType::Pawn:
					{
						// p
						//* *
						int movedX = xPos - 1;
						int movedY = enemy == Team::White ? yPos - 1 : yPos + 1;
						if (InBound(movedX, movedY))
						{
							if (IsBlank(movedX, movedY) || IsEnemy(movedX, movedY))
								SetCounterpartMovableMap(movedY, movedX);
						}

						movedX = xPos + 1;
						if (InBound(movedX, movedY))
						{
							if ((IsBlank(movedX, movedY) || IsEnemy(movedX, movedY)))
								SetCounterpartMovableMap(movedY, movedX);
						}
						break;
					}
					
					case PieceType::Rook:
					{
						//  *
						//  *
						//**r**
						//  *
						//  *
						glm::vec2 directions[4] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
						for (int direction = 0; direction < 4; direction++)
						{
							int xDirection = directions[direction].x;
							int yDirection = directions[direction].y;

							for (int i = 1; i < 8; i++)
							{
								int movedX = xPos + i * xDirection;
								int movedY = yPos + i * yDirection;

								if (InBound(movedX, movedY))
								{
									if (IsBlank(movedX, movedY))
										SetCounterpartMovableMap(movedY, movedX);
									else if (IsEnemy(movedX, movedY))
									{
										SetCounterpartMovableMap(movedY, movedX);
										break;
									}
									else break;
								}
								else break;
							}
						}
						break;
					}
					
					case PieceType::Knight:
					{
						glm::vec2 deltaPos[8] = {
							{1,2}, {2,1}, {2,-1}, {1,-2},
							{-1,-2}, {-2,-1}, {-2,1}, {-1,2}
						};
						for (int i = 0; i < 8; i++)
						{
							int movedX = xPos + deltaPos[i].x;
							int movedY = yPos + deltaPos[i].y;

							if (InBound(movedX, movedY))
							{
								if (IsBlank(movedX, movedY) || IsEnemy(movedX, movedY))
									SetCounterpartMovableMap(movedY, movedX);
							}
						}
						break;
					}

					case PieceType::Bishop:
					{
						glm::vec2 directions[4] = { {1,1}, {1,-1}, {-1,-1}, {-1,1} };
						for (int direction = 0; direction < 4; direction++)
						{
							int xDirection = directions[direction].x;
							int yDirection = directions[direction].y;

							for (int i = 1; i < 8; i++)
							{
								int movedX = xPos + i * xDirection;
								int movedY = yPos + i * yDirection;

								if (InBound(movedX, movedY))
								{
									if (IsBlank(movedX, movedY))
										SetCounterpartMovableMap(movedY, movedX);
									else if (IsEnemy(movedX, movedY))
									{
										SetCounterpartMovableMap(movedY, movedX);
										break;
									}
									else break;
								}
								else break;
							}
						}
						break;
					}

					case PieceType::Queen:
					{
						glm::vec2 directions[8] = {
							{0,1}, {1,1}, {1,0}, {1,-1},
							{0,-1}, {-1,-1}, {-1,0}, {-1,1}
						};
						for (int direction = 0; direction < 8; direction++)
						{
							int xDirection = directions[direction].x;
							int yDirection = directions[direction].y;

							for (int i = 1; i < 8; i++)
							{
								int movedX = xPos + i * xDirection;
								int movedY = yPos + i * yDirection;

								if (InBound(movedX, movedY))
								{
									if (IsBlank(movedX, movedY))
										SetCounterpartMovableMap(movedY, movedX);
									else if (IsEnemy(movedX, movedY))
									{
										SetCounterpartMovableMap(movedY, movedX);
										break;
									}
									else break;
								}
								else break;
							}
						}
						break;
					}

					case PieceType::King:
					{
						glm::vec2 directions[8] = {
							{0,1}, {1,1}, {1,0}, {1,-1},
							{0,-1}, {-1,-1}, {-1,0}, {-1,1}
						};
						for (int direction = 0; direction < 8; direction++)
						{
							int xDirection = directions[direction].x;
							int yDirection = directions[direction].y;

							int movedX = xPos + xDirection;
							int movedY = yPos + yDirection;

							if (InBound(movedX, movedY))
							{
								if (IsBlank(movedX, movedY) || IsEnemy(movedX, movedY))
									SetCounterpartMovableMap(movedY, movedX);
							}
						}

						break;
					}
				}
			}
		}
	}

	void SetCounterpartMovableMap(int row, int col)
	{
		row = 7 - row;
		counterpartMovable[row][col] = 'T';
	}

	char GetCounterpartMovableMap(int row, int col)
	{
		row = 7 - row;
		return counterpartMovable[row][col];
	}

	void SetNextCounterpartMovableMap(int row, int col, char c)
	{
		row = 7 - row;
		nextCounterpartMovable[row][col] = c;
	}

	char GetNextCounterpartMovableMap(int row, int col)
	{
		row = 7 - row;
		return nextCounterpartMovable[row][col];
	}

	void CalculateNextCounterpartMovableMap(Piece* piece, int xPos, int yPos)
	{
		// reset
		int oldXPos = piece->GetPosition().x;
		int oldYPos = piece->GetPosition().y;
		Team team = piece->GetTeam();
		PieceType type = piece->GetType();
		char oldPieceName = GetMap(yPos, xPos);
		char pieceName = GetPieceTypeToChar(team, type);

		// pretend
		Piece* destroyedPiece = nullptr;
		for (const auto& p : s_Pieces)
		{
			if (p->GetPosition().x == xPos && p->GetPosition().y == yPos)
			{
				destroyedPiece = p;
				destroyedPiece->SetPosition(100, 100);
			}
		}
		piece->SetPosition(xPos, yPos);
		SetMap(yPos, xPos, pieceName);
		SetMap(oldYPos, oldXPos, 'N');

		TurnChange();
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				SetNextCounterpartMovableMap(i, j, GetCounterpartMovableMap(i, j));
			}
		}

		// back
		if (destroyedPiece != nullptr)
		{
			destroyedPiece->SetPosition(xPos, yPos);
		}
		piece->SetPosition(oldXPos, oldYPos);
		SetMap(yPos, xPos, oldPieceName);
		SetMap(oldYPos, oldXPos, pieceName);

		TurnChange();
	}

	bool IsCurrentlyCheck()
	{
		GameState whosTurn = s_GameInfo.WhosTurn;
		Team team = whosTurn == GameState::Black ? Team::Black : Team::White;

		int kingXPos = 0;
		int kingYPos = 0;
		for (const auto& piece : s_Pieces)
		{
			if (piece->GetTeam() == team && piece->GetType() == PieceType::King)
			{
				kingXPos = piece->GetPosition().x;
				kingYPos = piece->GetPosition().y;
			}
		}
		return GetCounterpartMovableMap(kingYPos, kingXPos) == 'T';
	}

	bool WillBeCheckmate(int xPos, int yPos)
	{
		GameState whosTurn = s_GameInfo.WhosTurn;
		Team team = whosTurn == GameState::Black ? Team::Black : Team::White;

		int kingXPos = 100;
		int kingYPos = 100;
		for (const auto& piece : s_Pieces)
		{
			if (piece->GetType() == PieceType::King && piece->GetTeam() == team)
			{
				kingXPos = piece->GetPosition().x;
				kingYPos = piece->GetPosition().y;
			}
		}
		if (kingXPos == 100 && kingYPos == 100)
			std::cout << "Error: Where is the king?" << std::endl;
		return GetNextCounterpartMovableMap(kingYPos, kingXPos) == 'T';
	}

	bool CheckmateCheck()
	{
		bool isCheckmate = true;

		Team team = s_GameInfo.WhosTurn == GameState::Black ? Team::Black : Team::White;

		for (const auto& piece : s_Pieces)
		{
			if (piece->GetTeam() == team)
			{
				if (piece->HasMovableRegion())
				{
					isCheckmate = false;
					break;
				}
			}
		}

		return isCheckmate;
	}

	void DoLeftCastling()
	{
		Team team = s_GameInfo.WhosTurn == GameState::Black ? Team::Black : Team::White;
		
		Piece* king = nullptr;
		Piece* leftRook = nullptr;

		for (const auto& piece : s_Pieces)
		{
			if (piece->GetTeam() == team)
			{
				if (piece->GetType() == PieceType::King)
					king = piece;
				if (piece->GetType() == PieceType::Rook)
				{
					if (((Rook*)piece)->GetDirection() == PieceDirection::Left)
						leftRook = piece;
				}
			}
		}

		char kingChar = team == Team::Black ? 'W' : 'w';
		int kingX = king->GetPosition().x;
		int kingY = king->GetPosition().y;
		int rookX = leftRook->GetPosition().x;
		int rookY = leftRook->GetPosition().y;

		char rookChar = team == Team::Black ? 'R' : 'r';
		int movedKingX = team == Team::Black ? kingX - 2 : kingX + 2;
		int movedKingY = kingY;
		int movedRookX = team == Team::Black ? rookX + 3 : rookX - 2;
		int movedRookY = rookY;

		SetMap(kingY, kingX, 'N');
		SetMap(movedKingY, movedKingX, kingChar);
		SetMap(rookY, rookX, 'N');
		SetMap(movedRookY, movedRookX, rookChar);
		king->SetPosition(movedKingX, movedKingY);
		leftRook->SetPosition(movedRookX, movedRookY);

		if (team == Team::Black)
		{
			s_GameInfo.IsBlackKingMoved = true;
			s_GameInfo.IsLeftBlackRookMoved = true;
		}
		else if (team == Team::White)
		{
			s_GameInfo.IsWhiteKingMoved = true;
			s_GameInfo.IsLeftWhiteRookMoved = true;
		}
	}

	void DoRightCastling()
	{
		Team team = s_GameInfo.WhosTurn == GameState::Black ? Team::Black : Team::White;

		Piece* king = nullptr;
		Piece* rightRook = nullptr;

		for (const auto& piece : s_Pieces)
		{
			if (piece->GetTeam() == team)
			{
				if (piece->GetType() == PieceType::King)
					king = piece;
				if (piece->GetType() == PieceType::Rook)
				{
					if (((Rook*)piece)->GetDirection() == PieceDirection::Right)
						rightRook = piece;
				}
			}
		}

		char kingChar = team == Team::Black ? 'W' : 'w';
		int kingX = king->GetPosition().x;
		int kingY = king->GetPosition().y;
		int rookX = rightRook->GetPosition().x;
		int rookY = rightRook->GetPosition().y;

		char rookChar = team == Team::Black ? 'R' : 'r';
		int movedKingX = team == Team::Black ? kingX + 2 : kingX - 2;
		int movedKingY = kingY;
		int movedRookX = team == Team::Black ? rookX - 2 : rookX + 3;
		int movedRookY = rookY;

		SetMap(kingY, kingX, 'N');
		SetMap(movedKingY, movedKingX, kingChar);
		SetMap(rookY, rookX, 'N');
		SetMap(movedRookY, movedRookX, rookChar);
		king->SetPosition(movedKingX, movedKingY);
		rightRook->SetPosition(movedRookX, movedRookY);

		if (team == Team::Black)
		{
			s_GameInfo.IsBlackKingMoved = true;
			s_GameInfo.IsRightBlackRookMoved = true;
		}
		else if (team == Team::White)
		{
			s_GameInfo.IsWhiteKingMoved = true;
			s_GameInfo.IsRightWhiteRookMoved = true;
		}
	}

	void MakePiece(int xPos, int yPos, PieceType pieceType, const std::shared_ptr<Texture>& texture)
	{
		Team team = s_GameInfo.WhosTurn == GameState::Black ? Team::White : Team::Black;

		switch (pieceType)
		{
			case PieceType::Rook:
			{
				s_Pieces.push_back(new Rook(team, { xPos, yPos, 0.1f }, texture));
				SetMap(yPos, xPos, team == Team::Black ? 'R' : 'r');
				break;
			}
			case PieceType::Knight:
			{
				s_Pieces.push_back(new Knight(team, { xPos, yPos, 0.1f }, texture));
				SetMap(yPos, xPos, team == Team::Black ? 'K' : 'k');
				break;
			}
			case PieceType::Bishop:
			{
				s_Pieces.push_back(new Bishop(team, { xPos, yPos, 0.1f }, texture));
				SetMap(yPos, xPos, team == Team::Black ? 'B' : 'b');
				break;
			}
			case PieceType::Queen:
			{
				s_Pieces.push_back(new Queen(team, { xPos, yPos, 0.1f }, texture));
				SetMap(yPos, xPos, team == Team::Black ? 'Q' : 'q');
				break;
			}
		}
	}

	void PromotionStart(Piece* bePromotedPiece)
	{
		s_GameInfo.BePromotedPiece = bePromotedPiece;
		s_GameInfo.StartPromotionAnimation = true;
	}

	void PromotionEnd(PieceType pieceType, const std::shared_ptr<Texture>& texture)
	{
		int xPos = s_GameInfo.BePromotedPiece->GetPosition().x;
		int yPos = s_GameInfo.BePromotedPiece->GetPosition().y;
		KillPiece(xPos, yPos);

		MakePiece(xPos, yPos, pieceType, texture);

		s_GameInfo.StartPromotionAnimation = false;
	}

	void SetCounterpartEnPassantable(bool enabled)
	{
		const auto& whosTurn = s_GameInfo.WhosTurn;
		Team team = whosTurn == GameState::Black ? Team::White : Team::Black;
		
		for (const auto& piece : s_Pieces)
		{
			if (piece->GetTeam() == team && piece->GetType() == PieceType::Pawn)
			{
				((Pawn*)piece)->SetCanBeKilledByEnPassant(enabled);
			}

		}
	}

	int IsEnPassantable(Piece* piece)
	{
		const auto& whosTurn = s_GameInfo.WhosTurn;
		Team team = whosTurn == GameState::Black ? Team::White : Team::Black;

		int xPos = piece->GetPosition().x;
		int yPos = piece->GetPosition().y;

		int canBeKilledByEnPassantPiece = 0;
		for (const auto& piece : s_Pieces)
		{
			if (piece->GetTeam() == team && piece->GetType() == PieceType::Pawn)
			{
				Pawn* pawn = (Pawn*)piece;
				int offset = whosTurn == GameState::Black ? -1 : 1;
				int candidateX = xPos + offset;
				int candidateY = yPos;
				if (InBound(candidateX, candidateY))
				{
					if (pawn->GetPosition().x == candidateX && pawn->GetPosition().y == candidateY && pawn->GetCanBeKilledByEnPassant())
					{
						canBeKilledByEnPassantPiece = 1;
						break;
					}
				}
			}
		}
		for (const auto& piece : s_Pieces)
		{
			if (piece->GetTeam() == team && piece->GetType() == PieceType::Pawn)
			{
				Pawn* pawn = (Pawn*)piece;
				int offset = whosTurn == GameState::Black ? 1 : -1;
				int candidateX = xPos + offset;
				int candidateY = yPos;
				if (InBound(candidateX, candidateY))
				{
					if (pawn->GetPosition().x == candidateX && pawn->GetPosition().y == candidateY && pawn->GetCanBeKilledByEnPassant())
					{
						canBeKilledByEnPassantPiece = 2;
						break;
					}
				}
			}
		}
		return canBeKilledByEnPassantPiece;
	}

	void ResetJustDestroyedPieceData()
	{
		s_GameInfo.JustDestroyedPiece = false;
		s_GameInfo.JustDestroyedPieceTeam = Team::None;
		s_GameInfo.JustDestroyedPieceType = PieceType::None;
	}

	const std::vector<Piece*>& GetPieces()
	{
		return s_Pieces;
	}

	void KillPiece(float x, float y)
	{
		for (std::vector<Piece*>::iterator it = s_Pieces.begin(); it != s_Pieces.end(); it++)
		{
			Piece* piece = *it;
			float xPosition = piece->GetPosition().x;
			float yPosition = piece->GetPosition().y;

			if (xPosition == x && yPosition == y)
			{
				s_GameInfo.JustDestroyedPiece = true;
				s_GameInfo.JustDestroyedPieceTeam = piece->GetTeam();
				s_GameInfo.JustDestroyedPieceType = piece->GetType();

				if (piece->GetTeam() == Team::Black)
				{
					if (s_GameInfo.BlackDeadPieces.empty())
						s_GameInfo.BlackDeadPieces.push_back({ *it, 1 });
					else
					{
						Piece* alreadyDeadType = nullptr;
						for (auto& dead : s_GameInfo.BlackDeadPieces)
						{
							Piece* deadPiece = dead.first;
							int count = dead.second;
							if (piece->GetType() == deadPiece->GetType())
							{
								alreadyDeadType = deadPiece;
								dead.second++;
								break;
							}
						}
						if (alreadyDeadType == nullptr)
							s_GameInfo.BlackDeadPieces.push_back({ *it, 1 });
					}
				}
				else
				{
					if (s_GameInfo.WhiteDeadPieces.empty())
						s_GameInfo.WhiteDeadPieces.push_back({ *it, 1 });
					else
					{
						Piece* alreadyDeadType = nullptr;
						for (auto& dead : s_GameInfo.WhiteDeadPieces)
						{
							Piece* deadPiece = dead.first;
							int count = dead.second;
							if (piece->GetType() == deadPiece->GetType())
							{
								alreadyDeadType = deadPiece;
								dead.second++;
								break;
							}
						}
						if (alreadyDeadType == nullptr)
							s_GameInfo.WhiteDeadPieces.push_back({ *it, 1 });
					}
				}
				piece->OnDestroy();
				s_Pieces.erase(it);
				break;
			}
		}
	}
}