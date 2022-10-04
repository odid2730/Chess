#pragma once
#include <AL/al.h>

class SoundSource
{
public:
	SoundSource(float pitch);
	~SoundSource();

	void Play(const ALuint buffer_to_play);

	void SetVolumn(float volumn);

	static std::shared_ptr<SoundSource> Create(float pitch);
private:
	ALuint m_Source;
	float m_Pitch = 1.0f;
	const float m_MaxGain = 0.1f;
	float m_Gain = 2.0f;
	float m_Position[3] = { 3.5f,3.5f,0 };
	float m_Velocity[3] = { 0,0,0 };
	bool m_LoopSound = false;
	ALuint m_Buffer = 0;
};
