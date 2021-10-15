//find;

	HEADER_GD_AUTH_LOGIN		= 100,

//add above;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
	HEADER_GD_FIND_CHANNEL		= 99,
#endif

//find again;

	HEADER_DG_MAP_LOCATIONS		= 0xfe,

//add above;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
	HEADER_DG_CHANNEL_RESULT	= 184,
#endif

//find again;

typedef struct SChannelStatus
{
	[...]
} TChannelStatus;

//add below;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
typedef struct
{
	long lMapIndex;
	int channel;
} TPacketChangeChannel;

typedef struct
{
	long lAddr;
	WORD port;
} TPacketReturnChannel;
#endif