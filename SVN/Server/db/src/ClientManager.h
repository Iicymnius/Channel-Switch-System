//find;

	void		WeddingEnd(TPacketWeddingEnd* p);

//add below;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
	void		FindChannel(CPeer* pkPeer, DWORD dwHandle, TPacketChangeChannel* p);
#endif