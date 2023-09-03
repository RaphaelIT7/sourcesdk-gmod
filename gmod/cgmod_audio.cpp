#include "interface.h"
#include "tier3.h"
#include "cgmod_audio.h"

/*
CBassAudioStream
*/
CBassAudioStream::CBassAudioStream()
{
	// IDK
}

void CBassAudioStream::Init(IAudioStreamEvent* event)
{
	m_hStream = BASS_StreamCreateFileUser(STREAMFILE_NOBUFFER, BASS_STREAM_AUTOFREE, nullptr, nullptr);

	if (m_hStream == 0) {
		Warning("Couldn't create BASS audio stream (%i)", BASS_ErrorGetCode()); // ToDo: Use BassErrorToString(int)
	}
}

void CALLBACK CBassAudioStream::MyFileCloseProc(FILE* user)
{
	fclose(user);
}

QWORD CALLBACK CBassAudioStream::MyFileLenProc(FILE* user)
{
	struct stat s;
	fstat(fileno(user), &s);
	return s.st_size;
}

DWORD CALLBACK CBassAudioStream::MyFileReadProc(void *buffer, DWORD length, FILE *user)
{
	return fread(buffer, 1, length, user);
}

BOOL CALLBACK CBassAudioStream::MyFileSeekProc(QWORD offset, FILE *user)
{
	return !fseek(user, offset, SEEK_SET);
}

unsigned int CBassAudioStream::Decode(void* data, unsigned int size)
{
	unsigned int result = 0;

	if (data != nullptr) {
		result = BASS_ChannelGetData(reinterpret_cast<HSTREAM>(data), data, size);
	}

	return result;
}

int CBassAudioStream::GetOutputBits()
{
	Error("Not used");
	return 0;
}

int CBassAudioStream::GetOutputRate()
{
	BASS_CHANNELINFO info;

	if (BASS_ChannelGetInfo(m_hStream, &info)) {
		return info.freq;
	} else {
		return 0xAC44;
	}
}

int CBassAudioStream::GetOutputChannels()
{
	BASS_CHANNELINFO info;

	if (BASS_ChannelGetInfo(m_hStream, &info)) {
		return info.chans;
	} else {
		return 2;
	}
}

QWORD CBassAudioStream::GetPosition()
{
	QWORD position = 0;

	if (m_hStream != 0) {
		position = BASS_StreamGetFilePosition(m_hStream, BASS_FILEPOS_CURRENT);
	}

	return position;
}

void CBassAudioStream::SetPosition(unsigned int pos)
{
}

HSTREAM CBassAudioStream::GetHandle()
{
	return m_hStream;
}

/*
	CGMod_Audio
*/

CGMod_Audio g_CGMod_Audio;

int CGMod_Audio::Init(CreateInterfaceFn interfaceFactory)
{
	ConnectTier1Libraries( &interfaceFactory, 1 );
	ConnectTier2Libraries( &interfaceFactory, 1 );
	ConnectTier3Libraries( &interfaceFactory, 1 );

	BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 36);

	if(!BASS_Init(0, 0, BASS_DEVICE_DEFAULT, 0, nullptr)) {
		Warning("BASS_Init failed(%i)! Attempt 1.\n", BASS_ErrorGetCode());

		if(!BASS_Init(0, 0, BASS_DEVICE_DEFAULT, 0, nullptr)) {
			Warning("BASS_Init failed(%i)! Attempt 2.\n", BASS_ErrorGetCode());

			if(!BASS_Init(0, 0, BASS_DEVICE_3D | BASS_DEVICE_DEFAULT, 0, nullptr)) {
				Warning("BASS_Init failed(%i)! Attempt 3.\n", BASS_ErrorGetCode());

				if(!BASS_Init(0, 0, BASS_DEVICE_3D | BASS_DEVICE_DEFAULT, 0, nullptr)) {
					Warning("BASS_Init failed(%i)! Attempt 4.\n", BASS_ErrorGetCode());

					if(!BASS_Init(0, 0, 0, 0, nullptr)) {
						Warning("BASS_Init failed(%i)! Attempt 5.\n", BASS_ErrorGetCode());

						if(!BASS_Init(0, 0, 0, 0, nullptr)) {
							Warning("BASS_Init failed(%i)! Attempt 6.\n", BASS_ErrorGetCode());

							if(!BASS_Init(0, 0, 0, 0, nullptr)) {
								Error("Couldn't Init Bass (%i)!", BASS_ErrorGetCode());
							}
						}
					}
				}
			}
		}
	}

	BASS_SetConfig(BASS_CONFIG_BUFFER, 0x24);
	BASS_SetConfig(BASS_CONFIG_NET_BUFFER, 0x100000);
	BASS_SetConfig(BASS_CONFIG_3DALGORITHM, 0x3CA3D70A);

	float distf = (float)0x3CA3D70A;
	float rollf = (float)0x40E00000;
	float doppf = (float)0x41EC3871;

	BASS_Set3DFactors(distf, rollf, doppf);
	//BASS_Apply3D();

	return 1;
}

std::string CGMod_Audio::GetErrorString(int id)
{
	const char* error = g_BASSErrorStrings[id];
	if (error) {
		return error;
	}

	return "BASS_ERROR_UNKNOWN";
}

void CGMod_Audio::Shutdown()
{
	BASS_Free();
	BASS_PluginFree(0);
}

CBassAudioStream* CGMod_Audio::CreateAudioStream(IAudioStreamEvent* event)
{
	CBassAudioStream* pBassStream = new CBassAudioStream();
	pBassStream->Init(event);

	return pBassStream;
}

void CGMod_Audio::SetGlobalVolume(float volume)
{
	//float modifiedVolume = volume * (dword_9F24 - 0x1C91);

	int intVolume = static_cast<int>(volume);

	BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, intVolume);
	BASS_SetConfig(BASS_CONFIG_GVOL_MUSIC, intVolume);
	BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, intVolume);
}

void CGMod_Audio::StopAllPlayback()
{
	BASS_Stop();
	BASS_Start();
}

void CGMod_Audio::Update(unsigned int updatePeriod)
{
	BASS_Update(updatePeriod);
}

void CGMod_Audio::SetEar(Vector* earPosition, Vector* earForward, Vector* earUp, Vector* earVelocity)
{
    BASS_3DVECTOR earPos;
    earPos.x = earPosition->x;
    earPos.y = earPosition->y;
    earPos.z = earPosition->z;

    BASS_3DVECTOR earDir;
    earDir.x = earForward->x;
    earDir.y = earForward->y;
    earDir.z = earForward->z;

    BASS_3DVECTOR earUpVec;
    earUpVec.x = earUp->x;
    earUpVec.y = earUp->y;
    earUpVec.z = earUp->z;

    BASS_3DVECTOR earVel;
    earVel.x = earVelocity->x;
    earVel.y = earVelocity->y;
    earVel.z = earVelocity->z;

    BASS_Set3DPosition(&earPos, &earDir, &earUpVec, &earVel);

	/*
push    3CA3D70Ah = 0.155563f
push    40E00000h = 7.0f
push    41EC3871h = 29.1f
	*/
	BASS_Set3DFactors(0.155563f, 7.0f, 29.1f);
    BASS_Apply3D();
}

DWORD BASSFlagsFromString(const std::string& flagsString)
{
	DWORD flags = 0;

	if (flagsString.empty())
		return flags;

	/*if (flagsString.find("3d") != std::string::npos)
	{
		flags |= BASS_MUSIC_3D;
	}

	if (flagsString.find("mono") != std::string::npos)
	{
		flags |= BASS_MUSIC_MONO;
	}

	if (flagsString.find("noplay") != std::string::npos)
	{
		flags |= BASS_MUSIC_;
	}*/

	return flags;
}

int CGMod_Audio::PlayURL(const char* url, const char* flags, int* errorCode)
{
	*errorCode = 0;

	if (url == nullptr || flags == nullptr) {
		*errorCode = -1;
		return 0;
	}

	size_t urlLength = strlen(url);
	if (urlLength >= 0xFFFFFFF0) {
		*errorCode = -2;
		return 0;
	}

	char* urlCopy = new char[urlLength + 1];
	strcpy(urlCopy, url);

	DWORD bassFlags = BASSFlagsFromString(flags);

	HSTREAM stream = BASS_StreamCreateURL(urlCopy, 0, bassFlags, nullptr, nullptr);
	delete[] urlCopy;

	if (stream == 0) {
		*errorCode = BASS_ErrorGetCode();
		return 0;
	}

	return stream;
}

int CGMod_Audio::PlayFile(const char* filePath, const char* flags, int* errorCode)
{
	*errorCode = 0;

	if (filePath == nullptr || flags == nullptr) {
		*errorCode = -1;
		return 0;
	}

	size_t filePathLength = strlen(filePath);
	if (filePathLength >= 0xFFFFFFF0) {
		*errorCode = -2;
		return 0;
	}

	char* filePathCopy = new char[filePathLength + 1];
	strcpy(filePathCopy, filePath);

	DWORD bassFlags = BASSFlagsFromString(flags);

	HSTREAM stream = BASS_StreamCreateFile(FALSE, filePathCopy, 0, 0, bassFlags);
	delete[] filePathCopy;

	if (stream == 0) {
		*errorCode = BASS_ErrorGetCode();
		return 0;
	}

	if (!BASS_ChannelPlay(stream, TRUE)) {
		*errorCode = BASS_ErrorGetCode();
		BASS_StreamFree(stream);
		return 0;
	}

	return 1;
}

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CGMod_Audio, IGMod_Audio, "IGModAudio001", g_CGMod_Audio);