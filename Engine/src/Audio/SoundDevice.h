#pragma once

#include <AL/alc.h>
#include <AL/al.h>

class SoundDevice
{
public:
	SoundDevice();
	~SoundDevice();

	static std::shared_ptr<SoundDevice> Create();

private:
	ALCdevice* m_ALCDevice;
	ALCcontext* m_ALCContext;
};