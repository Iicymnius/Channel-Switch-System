#find;

	"y" : (SCREEN_HEIGHT - 298) /2,

#change;

	"y" : (SCREEN_HEIGHT - 328) /2,

#find again;

	"height" : 298,

#change;

	"height" : 328,

#find again;

			"height" : 298,

#change;

			"height" : 328,

#find again;

				{
					"name" : "game_option_button",
					"type" : "button",

					"x" : 10,
					"y" : 117,

					"text" : uiScriptLocale.GAMEOPTION_TITLE,

					"default_image" : ROOT + "XLarge_Button_01.sub",
					"over_image" : ROOT + "XLarge_Button_02.sub",
					"down_image" : ROOT + "XLarge_Button_03.sub",
				},

#add below;

				# if app.ENABLE_CHANNEL_SWITCH_SYSTEM:
				{
					"name" : "movechannel_button",
					"type" : "button",

					"x" : 10,
					"y" : 147,#Esc menüsündeki konumunu buradan ayarlamanýz gerekecek.

					"text" : uiScriptLocale.SYSTEM_MOVE_CHANNEL,

					"default_image" : ROOT + "XLarge_Button_01.sub",
					"over_image" : ROOT + "XLarge_Button_02.sub",
					"down_image" : ROOT + "XLarge_Button_03.sub",
				},