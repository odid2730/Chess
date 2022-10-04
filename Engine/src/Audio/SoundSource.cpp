#include "pch.h"
#include "SoundSource.h"


SoundSource::SoundSource(float pitch)
    : m_Gain(pitch)
{
	alGenSources(1, &m_Source);
	alSourcef(m_Source, AL_PITCH, m_Pitch);
	alSourcef(m_Source, AL_GAIN, m_Gain);
	alSource3f(m_Source, AL_POSITION, m_Position[0], m_Position[1], m_Position[2]);
	alSource3f(m_Source, AL_VELOCITY, m_Velocity[0], m_Velocity[1], m_Velocity[2]);
	alSourcei(m_Source, AL_LOOPING, m_LoopSound);
	alSourcei(m_Source, AL_BUFFER, m_Buffer);
}

SoundSource::~SoundSource()
{
	alDeleteSources(1, &m_Source);
}

void SoundSource::Play(const ALuint buffer_to_play)
{
	if (buffer_to_play != m_Buffer)
	{
		m_Buffer = buffer_to_play;
		alSourcei(m_Source, AL_BUFFER, (ALint)m_Buffer);
	}
	alSourcePlay(m_Source);

	ALint state = AL_PLAYING;
    ALuint error = alGetError();
	std::cout << "playing sound\n";
	while (state == AL_PLAYING && error == AL_NO_ERROR)
	{
		//std::cout << "currently playing sound\n";
		alGetSourcei(m_Source, AL_SOURCE_STATE, &state);
	}
    if (error != AL_NO_ERROR)
    {
        std::cerr << "***ERROR***\n";
        switch (error)
        {
            case AL_INVALID_NAME:
                std::cerr << "AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function";
                break;
            case AL_INVALID_ENUM:
                std::cerr << "AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function";
                break;
            case AL_INVALID_VALUE:
                std::cerr << "AL_INVALID_VALUE: an invalid value was passed to an OpenAL function";
                break;
            case AL_INVALID_OPERATION:
                std::cerr << "AL_INVALID_OPERATION: the requested operation is not valid";
                break;
            case AL_OUT_OF_MEMORY:
                std::cerr << "AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory";
                break;
            default:
                std::cerr << "UNKNOWN AL ERROR: " << error;
        }
        std::cerr << std::endl;
    }
	std::cout << "done playing sound\n";
}

void SoundSource::SetVolumn(float volumn)
{
    m_Gain = m_MaxGain * volumn;
    alSourcef(m_Source, AL_GAIN, m_Gain);
}

std::shared_ptr<SoundSource> SoundSource::Create(float pitch)
{
    return std::shared_ptr<SoundSource>(new SoundSource(pitch));
}
