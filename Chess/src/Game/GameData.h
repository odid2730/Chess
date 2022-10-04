#pragma once

#include "Piece/Piece.h"
#include "Audio/SoundDevice.h"
#include "Audio/SoundBuffer.h"
#include "Audio/SoundSource.h"

#include <glm/glm.hpp>

#include <vector>
#include <functional>

namespace GameData {

	enum class GameState
	{
		None = 0, Black, White, End
	};

	struct GameInfo
	{
		GameState WhosTurn = GameState::Black;

		glm::vec4 BlueColor = { 0.2f, 0.3f, 0.8f, 0.5f };
		glm::vec4 RedColor = { 0.8f, 0.1f, 0.2f, 0.5f };
		
		// Castling
		bool IsLeftBlackRookMoved = false;
		bool IsRightBlackRookMoved = false;
		bool IsBlackKingMoved = false;

		bool IsLeftWhiteRookMoved = false;
		bool IsRightWhiteRookMoved = false;
		bool IsWhiteKingMoved = false;

		// Promotion
		bool StartPromotionAnimation = false; // this will be used in ui layer.
		Piece* BePromotedPiece = nullptr;

		bool JustDestroyedPiece = false;
		Team JustDestroyedPieceTeam = Team::None;
		PieceType JustDestroyedPieceType = PieceType::None;

		std::vector<std::pair<Piece*, int>> BlackDeadPieces;
		std::vector<std::pair<Piece*, int>> WhiteDeadPieces;
	};

	struct AudioData
	{
	public:
		SoundDevice Device;
		
		SoundSource BGMSpeaker{ 0.1f };

		void SetVolumn(float volumn) { Volumn = volumn; BGMSpeaker.SetVolumn(Volumn); }

		float GetVolumn() { return Volumn; }

		uint32_t GetBGMID() { return BgmBuffer.GetSoundID(); }

		uint32_t GetBlackPawnSoundID() { return BlackPawnDestroyBuffer.GetSoundID(); }
		uint32_t GetBlackRookSoundID() { return BlackRookDestroyBuffer.GetSoundID(); }
		uint32_t GetBlackKnightSoundID() { return BlackKnightDestroyBuffer.GetSoundID(); }
		uint32_t GetBlackBishopSoundID() { return BlackBishopDestroyBuffer.GetSoundID(); }
		uint32_t GetBlackQueenSoundID() { return BlackQueenDestroyBuffer.GetSoundID(); }

		uint32_t GetWhitePawnSoundID() { return WhitePawnDestroyBuffer.GetSoundID(); }
		uint32_t GetWhiteRookSoundID() { return WhiteRookDestroyBuffer.GetSoundID(); }
		uint32_t GetWhiteKnightSoundID() { return WhiteKnightDestroyBuffer.GetSoundID(); }
		uint32_t GetWhiteBishopSoundID() { return WhiteBishopDestroyBuffer.GetSoundID(); }
		uint32_t GetWhiteQueenSoundID() { return WhiteQueenDestroyBuffer.GetSoundID(); }

		uint32_t GetTookSoundID() { return TookBuffer.GetSoundID(); }
	private:
		float Volumn = 1.0f;

		SoundBuffer BgmBuffer{ "assets/audio/Pendulum-Waltz-Audionautix.ogg" };
		SoundBuffer BlackPawnDestroyBuffer{ "assets/audio/BlackPawnDestroy.flac" };
		SoundBuffer BlackRookDestroyBuffer{ "assets/audio/BlackRookDestroy.flac" };
		SoundBuffer BlackKnightDestroyBuffer{ "assets/audio/BlackKnightDestroy.flac" };
		SoundBuffer BlackBishopDestroyBuffer{ "assets/audio/BlackBishopDestroy.flac" };
		SoundBuffer BlackQueenDestroyBuffer{ "assets/audio/BlackQueenDestroy.flac" };

		SoundBuffer WhitePawnDestroyBuffer{ "assets/audio/WhitePawnDestroy.flac" };
		SoundBuffer WhiteRookDestroyBuffer{ "assets/audio/WhiteRookDestroy.flac" };
		SoundBuffer WhiteKnightDestroyBuffer{ "assets/audio/WhiteKnightDestroy.flac" };
		SoundBuffer WhiteBishopDestroyBuffer{ "assets/audio/WhiteBishopDestroy.flac" };
		SoundBuffer WhiteQueenDestroyBuffer{ "assets/audio/WhiteQueenDestroy.flac" };

		SoundBuffer TookBuffer{ "assets/audio/took.flac" };

	};

	void InitGame();
	GameInfo& GetGameInfo();
	// Audio
	AudioData& GetAudioData();
	void StartBGM();
	void PlayAudio(uint32_t id);
	void PlayImpact(uint32_t id);

	char GetMap(int row, int col);
	void SetMap(int row, int col, char c);
	void TurnChange();
	void SetCounterpartMovableMap(int row, int col);
	char GetCounterpartMovableMap(int row, int col);
	void SetNextCounterpartMovableMap(int row, int col, char c);
	char GetNextCounterpartMovableMap(int row, int col);
	void CalculateNextCounterpartMovableMap(Piece* piece, int xPos, int yPos);
	bool IsCurrentlyCheck();
	bool WillBeCheckmate(int xPos, int yPos);
	bool CheckmateCheck();

	void DoLeftCastling();
	void DoRightCastling();

	void MakePiece(int xPos, int yPos, PieceType pieceType, const std::shared_ptr<Texture>& texture);
	void PromotionStart(Piece* bePromotedPiece);
	void PromotionEnd(PieceType pieceType, const std::shared_ptr<Texture>& texture);

	void SetCounterpartEnPassantable(bool enabled); // 상대 턴이 끝나면 내 기물들은 앙파상 당할 수 없음. 턴이 끝나면 상대기물 언앙파상에이블
	int IsEnPassantable(Piece* piece);				// cant = 0, left = 1, right = 2

	void ResetJustDestroyedPieceData();

	const std::vector<Piece*>& GetPieces();
	void KillPiece(float x, float y);
}