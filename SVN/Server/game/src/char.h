//find;

	int				GetSyncHackCount() { return m_iSyncHackCount; }

//add below;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
public:
	bool			SwitchChannel(long newAddr, WORD newPort);
	bool			StartChannelSwitch(long newAddr, WORD newPort);
#endif