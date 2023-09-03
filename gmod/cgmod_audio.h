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

class GModChannelFFT_t; // Probably a struct.
// void* = Unsure of the return value
class CGModAudioChannel
{
	void Destroy();
	void* Stop();
	void* Pause();
	void* Play();
	void* SetVolume(float);
	float GetVolume(); // ToDo: Verify return value
	void* SetPlaybackRate(float);
	float GetPlaybackRate(); // ToDo: Verify return value
	void SetPos(Vector*, Vector*, Vector*);
	void GetPos(Vector*, Vector*, Vector*);
	void* SetTime(double, bool);
	double GetTime(); // ToDo: Verify return value
	void Set3DFadeDistance(float, float);
	void Get3DFadeDistace(float, float);
	void Set3DCone(int, int, float);
	void Get3DCone(int*, int*, float*);
	void* GetState();
	void* SetLooping(bool);
	bool IsLooping(); // ToDo: Verify return value
	bool IsOnline();
	bool Is3D();
	bool IsBlockStreamed();
	bool IsValid();
	double GetLength();
	char* GetFileName();
	void* GetSamplingRate(); // It probably returns an int or double.
	void* GetBitsPerSample();
	void* GetAverageBitRate();
	void GetLevel(float*, float*);
	void FFT(float*, GModChannelFFT_t);
	void* SetChannelPan(float);
	float GetChannelPan();
	void* GetTags(int);
	void Set3DEnabled(bool);
	bool Get3DEnabled();
	void* Restart();
}