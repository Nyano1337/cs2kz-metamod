#include "kz_style.h"
//#include "version_gen.h"

#define STYLE_NAME       "LegacyJump"
#define STYLE_NAME_SHORT "LGJ"

class KZLegacyJumpStylePlugin : public ISmmPlugin, public IMetamodListener
{
public:
	bool Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late);
	bool Unload(char *error, size_t maxlen);
	bool Pause(char *error, size_t maxlen);
	bool Unpause(char *error, size_t maxlen);

public:
	const char *GetAuthor()
	{
		return "";
	}

	const char *GetName()
	{
		return "CS2KZ-Style-LegacyJump";
	}

	const char *GetDescription()
	{
		return "LegacyJump style plugin for CS2KZ";
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
};

class KZLegacyJumpStyleService : public KZStyleService
{
	using KZStyleService::KZStyleService;

public:
	virtual const char *GetStyleName() override
	{
		return STYLE_NAME;
	}

	virtual const char *GetStyleShortName() override
	{
		return STYLE_NAME_SHORT;
	}

	virtual const CVValue_t *GetTweakedConvarValue(const char *name) override;
	virtual void Init() override;
	virtual void Cleanup() override;
	virtual void OnProcessMovement() override;
};
