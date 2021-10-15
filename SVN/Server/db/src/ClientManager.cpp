//find;

		default:
			sys_err("Unknown header (header: %d handle: %d length: %d)", header, dwHandle, dwLength);
			break;

//add above;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
		case HEADER_GD_FIND_CHANNEL:
			FindChannel(peer, dwHandle, (TPacketChangeChannel*)data);
			break;
#endif

//add to bottom;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
void CClientManager::FindChannel(CPeer* requestPeer, DWORD dwHandle, TPacketChangeChannel* p)
{
	if (!p->lMapIndex || !p->channel)
		return;
	long lAddr = 0;
	WORD port = 0;
	for (const auto peer : m_peerList)
	{
		if (peer->GetChannel() != p->channel)
			continue;
		TMapLocation kMapLocation;
		thecore_memcpy(kMapLocation.alMaps, peer->GetMaps(), sizeof(kMapLocation.alMaps));
		for (const auto midx : kMapLocation.alMaps)
		{
			if (midx == p->lMapIndex)
			{
				char host[16];
				strlcpy(host, peer->GetPublicIP(), sizeof(kMapLocation.szHost));
				lAddr = inet_addr(host);
				port = peer->GetListenPort();
				break;
			}
		}
		if (lAddr && port)
			break;
	}
	TPacketReturnChannel r;
	r.lAddr = lAddr;
	r.port = port;
	requestPeer->EncodeHeader(HEADER_DG_CHANNEL_RESULT, dwHandle, sizeof(r));
	requestPeer->Encode(&r, sizeof(r));
}
#endif