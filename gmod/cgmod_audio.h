#include <string>
#include "vaudio/ivaudio.h"

class IGMod_Audio
{
	virtual std::string GetErrorString(int) = 0;
	virtual void Init(void* (*)(const char*, int*)) = 0; // ToDo: Get the correct return value
	virtual void Shutdown() = 0; // ToDo: Get the correct return value
	virtual void CreateAudioStream(IAudioStreamEvent*) = 0; // ToDo: Get the correct return value
	virtual void SetGlobalVolume(float) = 0; // ToDo: Get the correct return value
	virtual void StopAllPlayback() = 0; // ToDo: Get the correct return value
	virtual void Update(unsigned int) = 0; // ToDo: Get the correct return value
	virtual void SetEar(Vector*, Vector*, Vector*, Vector*) = 0; // ToDo: Get the correct return value
	virtual void PlayURL(const char*, const char*, int*) = 0; // ToDo: Get the correct return value
	virtual void PlayFile(const char*, const char*, int*) = 0; // ToDo: Get the correct return value
}

class CGMod_Audio : public IGMod_Audio
{
	void Init(void* (*)(const char*, int*));
	std::string GetErrorString(int);
	void Shutdown();
	void CreateAudioStream(IAudioStreamEvent*);
	void SetGlobalVolume(float);
	void StopAllPlayback();
	void Update(unsigned int);
	void SetEar(Vector*, Vector*, Vector*, Vector*);
	void PlayURL(const char*, const char*, int*);
	void PlayFile(const char*, const char*, int*);
}