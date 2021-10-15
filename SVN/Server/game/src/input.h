//find;

	void		RespondChannelStatus(LPDESC desc, const char* pcData);

//add below;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
	void		ChangeChannel(LPDESC desc, const char* pcData);
#endif