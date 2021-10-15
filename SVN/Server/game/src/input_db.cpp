//find;

bool GetServerLocation(TAccountTable& rTab, BYTE bEmpire)

//add above;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
void CInputDB::ChangeChannel(LPDESC d, const char* pcData)
{
	if (!d || !d->GetCharacter())
	{
		sys_err("Change channel request with empty or invalid description handle!");
		return;
	}
	TPacketReturnChannel* p = (TPacketReturnChannel*)pcData;
	if (!p->lAddr || !p->port)
	{
		std::string pName = d->GetCharacter()->GetName();
		d->GetCharacter()->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("CANNOT_CHANGE_CHANNEL"));
		sys_err("Can't switch channel for player %s!", pName.c_str());
		return;
	}
	d->GetCharacter()->StartChannelSwitch(p->lAddr, p->port);
}
#endif

//find again;

	default:
		return (-1);

//add above;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
	case HEADER_DG_CHANNEL_RESULT:
		ChangeChannel(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;
#endif