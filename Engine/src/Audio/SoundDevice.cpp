#include "pch.h"
#include "SoundDevice.h"

#include <AL/al.h>

SoundDevice::SoundDevice()
{
	m_ALCDevice = alcOpenDevice(nullptr);
	if (!m_ALCDevice)
		throw("failed to get sound device");

	m_ALCContext = alcCreateContext(m_ALCDevice, nullptr);
	if (!m_ALCContext)
		throw("Failed to set sound context");

	if (!alcMakeContextCurrent(m_ALCContext))
		throw("Failed to make context current");

	const ALCchar* name = nullptr;

	if (alcIsExtensionPresent(m_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
		name = alcGetString(m_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
	if (!name || alcGetError(m_ALCDevice) != AL_NO_ERROR)
		name = alcGetString(m_ALCDevice, ALC_DEVICE_SPECIFIER);
	std::cout << "Opend \"" << name << "\"\n";
}

SoundDevice::~SoundDevice()
{
	if (!alcMakeContextCurrent(nullptr))
		throw("Failed to set context to null");

	alcDestroyContext(m_ALCContext);
	if (m_ALCContext)
		throw("Failed to unset during close");
	if (!alcCloseDevice(m_ALCDevice))
		throw("Failed to close sound device");
}

std::shared_ptr<SoundDevice> SoundDevice::Create()
{
	return std::shared_ptr<SoundDevice>(new SoundDevice());
}
