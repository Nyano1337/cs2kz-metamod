#pragma once

#include <string_view>

#include "common.h"
// #include "version_gen.h"

class KZPlugin;
extern KZPlugin g_KZPlugin;

class KZPlugin : public ISmmPlugin, public IMetamodListener
{
public:
	bool Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late);
	bool Unload(char *error, size_t maxlen);
	bool Pause(char *error, size_t maxlen);
	bool Unpause(char *error, size_t maxlen);
	void AddonInit();
	bool IsAddonMounted();
	void AllPluginsLoaded();

public:
	const char *GetAuthor()
	{
		return "";
	}

	const char *GetName()
	{
		return "";
	}

	const char *GetDescription()
	{
		return "";
	}

	const char *GetURL()
	{
		return "";
	}

	const char *GetLicense()
	{
		return "";
	}

	const char *GetVersion()
	{
		return "";
	}

	const char *GetDate()
	{
		return __DATE__;
	}

	const char *GetLogTag()
	{
		return "";
	}

	virtual void *OnMetamodQuery(const char *iface, int *ret) override;
	virtual void OnPluginLoad(PluginId id) override;
	virtual void OnPluginUnload(PluginId id) override;
	virtual void OnLevelInit(char const *pMapName, char const *pMapEntities, char const *pOldLevel, char const *pLandmarkName, bool loadGame,
							 bool background) override;

	bool simulatingPhysics = false;
	CGlobalVars serverGlobals;
	bool unloading = false;

private:
	void UpdateSelfMD5();
	char md5[33];
	std::string m_sCurrentMap;

public:
	std::string_view GetMD5()
	{
		return md5;
	}

	std::string_view GetCurrentMap()
	{
		return m_sCurrentMap;
	}
};
