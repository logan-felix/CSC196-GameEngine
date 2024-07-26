#pragma once
#include <fmod.hpp>
#include <map>
#include <string>

class Audio
{
public:
	Audio() = default;
	~Audio() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	bool AddSound(const std::string& name);
	bool PlaySound(const std::string& name);
	void StopSound();
	bool isSoundPlaying();

private:
	FMOD::System* m_audio{ nullptr };
	FMOD::Channel* m_channel{ nullptr };
	std::map<std::string, FMOD::Sound*> m_sounds;
};