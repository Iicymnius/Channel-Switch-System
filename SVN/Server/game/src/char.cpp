//add to bottom;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
bool CHARACTER::SwitchChannel(long newAddr, WORD newPort)
{
	if (!IsPC() || !GetDesc() || !CanWarp())
		return false;
	long x = GetX();
	long y = GetY();
	long lAddr = newAddr;
	long lMapIndex = GetMapIndex();
	WORD wPort = newPort;
	if (lMapIndex >= 10000)
	{
		sys_err("Invalid change channel request from dungeon %d!", lMapIndex);
		return false;
	}
	if (g_bChannel == 99)
	{
		sys_err("%s attempted to change channel from CH99, ignoring req.", GetName());
		return false;
	}
	Stop();
	Save();
	if (GetSectree())
	{
		GetSectree()->RemoveEntity(this);
		ViewCleanup();
		EncodeRemovePacket(this);
	}
	m_lWarpMapIndex = lMapIndex;
	m_posWarp.x = x;
	m_posWarp.y = y;
	sys_log(0, "ChangeChannel %s, %ld %ld map %ld to port %d", GetName(), x, y, GetMapIndex(), wPort);
	TPacketGCWarp p;
	p.bHeader = HEADER_GC_WARP;
	p.lX = x;
	p.lY = y;
	p.lAddr = lAddr;
	p.wPort = wPort;
	GetDesc()->Packet(&p, sizeof(p));
	char buf[256];
	snprintf(buf, sizeof(buf), "%s Port%d Map%ld x%ld y%ld", GetName(), wPort, GetMapIndex(), x, y);
	LogManager::instance().CharLog(this, 0, "CHANGE_CH", buf);
	return true;
}

EVENTINFO(switch_channel_info)
{
	DynamicCharacterPtr ch;
	int secs;
	long newAddr;
	WORD newPort;
	switch_channel_info()
		: ch(),
		secs(0),
		newAddr(0),
		newPort(0)
	{
	}
};

EVENTFUNC(switch_channel)
{
	switch_channel_info* info = dynamic_cast<switch_channel_info*>(event->info);
	if (!info)
	{
		sys_err("No switch channel event info!");
		return 0;
	}
	LPCHARACTER    ch = info->ch;
	if (!ch)
	{
		sys_err("No char to work on for the switch.");
		return 0;
	}
	if (!ch->GetDesc())
		return 0;
	if (info->secs > 0)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Channel switch in %d seconds."), info->secs);
		--info->secs;
		return PASSES_PER_SEC(1);
	}
	ch->SwitchChannel(info->newAddr, info->newPort);
	ch->m_pkTimedEvent = NULL;
	return 0;
}

bool CHARACTER::StartChannelSwitch(long newAddr, WORD newPort)
{
	if (IsHack(false, true, 10))
		return false;
	switch_channel_info* info = AllocEventInfo<switch_channel_info>();
	info->ch = this;
	info->secs = CanWarp() && !IsPosition(POS_FIGHTING) ? 3 : 10;
	info->newAddr = newAddr;
	info->newPort = newPort;
	m_pkTimedEvent = event_create(switch_channel, info, 1);
	ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Channel switch starting."));
	return true;
}
#endif