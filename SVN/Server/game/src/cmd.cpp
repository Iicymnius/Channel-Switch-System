//find;

ACMD(do_duel);

//add below;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
ACMD(do_change_channel);
#endif

//find again;

		{ "duel",				do_duel,				0,		POS_DEAD,	GM_LOW_WIZARD	},

//add below;

#ifdef ENABLE_CHANNEL_SWITCH_SYSTEM
		{ "channel",			do_change_channel,		0,		POS_DEAD,	GM_PLAYER	},
#endif