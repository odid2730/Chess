#pragma once

#include <AL/al.h>

#include <vector>

class SoundBuffer
{
public:
	SoundBuffer(const char* filename);
	~SoundBuffer();

	ALuint addSoundEffect(const char* filename);
	bool removeSoundEffect(const ALuint& buffer);

	uint32_t GetSoundID() const { return m_SoundID; }

	static std::shared_ptr<SoundBuffer> Create(const char* filename);
private:
	uint32_t m_SoundID = 0;
	std::vector<ALuint> m_SoundEffectBuffers;
};

