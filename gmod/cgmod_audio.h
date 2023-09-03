#include <string>
#include "vaudio/ivaudio.h"
#include "bass.h"

class CBassAudioStream
{
public:
	CBassAudioStream();
	void Init(IAudioStreamEvent*);
	void CALLBACK MyFileCloseProc(FILE*);
	QWORD CALLBACK MyFileLenProc(FILE*);
	DWORD CALLBACK MyFileReadProc(void*, DWORD, FILE*);
	BOOL CALLBACK MyFileSeekProc(QWORD, FILE*);
	unsigned int Decode(void*, unsigned int);
	int GetOutputBits();
	int GetOutputRate();
	int GetOutputChannels();
	QWORD GetPosition();
	//QWORD GetPosition();
	void SetPosition(unsigned int);
	HSTREAM GetHandle();
private:
	HSTREAM m_hStream;
};

class GModChannelFFT_t; // Probably a struct.
class CGModAudioChannel
{
	void Destroy();
	void Stop(); // ToDo: Get the correct return value
	void Pause(); // ToDo: Get the correct return value
	void Play(); // ToDo: Get the correct return value
	void SetVolume(float); // ToDo: Get the correct return value
	float GetVolume(); // ToDo: Verify return value
	void SetPlaybackRate(float); // ToDo: Get the correct return value
	float GetPlaybackRate(); // ToDo: Verify return value
	void SetPos(Vector*, Vector*, Vector*);
	void GetPos(Vector*, Vector*, Vector*);
	void SetTime(double, bool); // ToDo: Get the correct return value
	double GetTime(); // ToDo: Verify return value
	void Set3DFadeDistance(float, float);
	void Get3DFadeDistace(float, float);
	void Set3DCone(int, int, float);
	void Get3DCone(int*, int*, float*);
	void GetState(); // ToDo: Get the correct return value
	void SetLooping(bool); // ToDo: Get the correct return value
	bool IsLooping(); // ToDo: Verify return value
	bool IsOnline();
	bool Is3D();
	bool IsBlockStreamed();
	bool IsValid();
	double GetLength();
	char* GetFileName(); // ToDo: Get the correct return value
	void GetSamplingRate(); // It probably returns an int or double.
	void GetBitsPerSample(); // ToDo: Get the correct return value
	void GetAverageBitRate(); // ToDo: Get the correct return value
	void GetLevel(float*, float*);
	void FFT(float*, GModChannelFFT_t);
	void SetChannelPan(float); // ToDo: Get the correct return value
	float GetChannelPan();
	void GetTags(int); // ToDo: Get the correct return value
	void Set3DEnabled(bool);
	bool Get3DEnabled();
	void Restart(); // ToDo: Get the correct return value
};

class IGMod_Audio
{
	virtual std::string GetErrorString(int) = 0;
	virtual int Init(CreateInterfaceFn) = 0;
	virtual void Shutdown() = 0;
	virtual CBassAudioStream* CreateAudioStream(IAudioStreamEvent*) = 0;
	virtual void SetGlobalVolume(float) = 0;
	virtual void StopAllPlayback() = 0;
	virtual void Update(unsigned int) = 0;
	virtual void SetEar(Vector*, Vector*, Vector*, Vector*) = 0;
	virtual int PlayURL(const char*, const char*, int*) = 0; // ToDo: Get the correct return value
	virtual int PlayFile(const char*, const char*, int*) = 0; // ToDo: Get the correct return value
};

class CGMod_Audio : public IGMod_Audio
{
	int Init(CreateInterfaceFn);
	std::string GetErrorString(int);
	void Shutdown();
	CBassAudioStream* CreateAudioStream(IAudioStreamEvent*);
	void SetGlobalVolume(float);
	void StopAllPlayback();
	void Update(unsigned int);
	void SetEar(Vector*, Vector*, Vector*, Vector*);
	int PlayURL(const char*, const char*, int*);
	int PlayFile(const char*, const char*, int*);
};

const char* g_BASSErrorStrings[] = {
	"BASS_OK",
	"BASS_ERROR_MEM",
	"BASS_ERROR_FILEOPEN",
	"BASS_ERROR_DRIVER",
	"BASS_ERROR_BUFLOST",
	"BASS_ERROR_HANDLE",
	"BASS_ERROR_FORMAT",
	"BASS_ERROR_POSITION",
	"BASS_ERROR_INIT",
	"BASS_ERROR_START",
	"BASS_ERROR_SSL",
	"BASS_ERROR_",
	"BASS_ERROR_",
	"BASS_ERROR_",
	"BASS_ERROR_ALREADY",
	"BASS_ERROR_NOTAUDIO",
	"BASS_ERROR_",
	"BASS_ERROR_",
	"BASS_ERROR_NOCHAN",
	"BASS_ERROR_ILLTYPE",
	"BASS_ERROR_ILLPARAM",
	"BASS_ERROR_NO3D",
	"BASS_ERROR_NOEAX",
	"BASS_ERROR_DEVICE",
	"BASS_ERROR_NOPLAY",
	"BASS_ERROR_FREQ",
	"BASS_ERROR_",
	"BASS_ERROR_NOTFILE",
	"BASS_ERROR_",
	"BASS_ERROR_NOHW",
	"BASS_ERROR_",
	"BASS_ERROR_EMPTY",
	"BASS_ERROR_NONET",
	"BASS_ERROR_CREATE",
	"BASS_ERROR_NOFX",
	"BASS_ERROR_",
	"BASS_ERROR_",
	"BASS_ERROR_NOTAVAIL",
	"BASS_ERROR_DECODE",
	"BASS_ERROR_DX",
	"BASS_ERROR_TIMEOUT",
	"BASS_ERROR_FILEFORM",
	"BASS_ERROR_SPEAKER",
	"BASS_ERROR_VERSION",
	"BASS_ERROR_CODEC",
	"BASS_ERROR_ENDED",
	"BASS_ERROR_BUSY",
	"BASS_ERROR_UNSTREAMABLE"
};