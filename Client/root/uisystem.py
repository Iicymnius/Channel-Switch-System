#find;

		self.gameOptionDlg = None

#add below;

		if app.ENABLE_CHANNEL_SWITCH_SYSTEM:
			self.moveChannelDlg = None

#find again;

		self.GetChild("cancel_button").SAFE_SetEvent(self.Close)

#add below;

		if app.ENABLE_CHANNEL_SWITCH_SYSTEM:
			self.GetChild("movechannel_button").SAFE_SetEvent(self.__ClickMoveChannelButton)

#find again;

		self.GetChild("cancel_button").SAFE_SetEvent(self.Close)

#add below;

		if app.ENABLE_CHANNEL_SWITCH_SYSTEM:
			self.GetChild("movechannel_button").SAFE_SetEvent(self.__ClickMoveChannelButton)

#find again;

	def OnPressExitKey(self):

#add above;

	if app.ENABLE_CHANNEL_SWITCH_SYSTEM:
		def __ClickMoveChannelButton(self):
			self.Close()
			if self.moveChannelDlg:
				self.moveChannelDlg.Show()
			else:
				moveChannelDlg = MoveChannelDialog()
				moveChannelDlg.Show()
				self.moveChannelDlg = moveChannelDlg

#add to bottom;

if app.ENABLE_CHANNEL_SWITCH_SYSTEM:
	class MoveChannelDialog(ui.ScriptWindow):
		def __init__(self):
			ui.ScriptWindow.__init__(self)
			self.__LoadDialog()
			self.StartChannelNumber = 0
			self.IsShow = False

		def __del__(self):
			ui.ScriptWindow.__del__(self)

		def __LoadDialog(self) :
			try:
				pyScrLoader = ui.PythonScriptLoader()
				pyScrLoader.LoadScriptFile(self, "UIScript/MoveChannelDialog.py")
			except:
				import exception as exception
				exception.Abort("MoveChannelDialog.__LoadDialog")


			self.ParentBoard = self.GetChild("MoveChannelBoard")
			self.ChildBoard = self.GetChild("BlackBoard")
			self.GetChild("MoveChannelTitle").SetCloseEvent(ui.__mem_func__(self.Close))

			self.ChannelList = []
			cnt = 5
			cnt = cnt - 1

			self.DlgWidht = 190
			self.BlackBoardHeight = 23*cnt + 5*(cnt-1) + 13
			self.DlgHeight = self.BlackBoardHeight + 75

			self.AcceptBtn = ui.MakeButton(self.ParentBoard, 13, self.DlgHeight - 33, "", "d:/ymir work/ui/public/", "acceptbutton00.sub", "acceptbutton01.sub", "acceptbutton02.sub")
#			self.AcceptBtn.SetText( localeInfo.MOVE_CHANNEL_SELECT )
			self.AcceptBtn.SetEvent(ui.__mem_func__(self.AcceptButton))
			self.CloseBtn = ui.MakeButton(self.ParentBoard, self.DlgWidht - 73, self.DlgHeight - 33, "", "d:/ymir work/ui/public/", "canclebutton00.sub", "canclebutton01.sub", "canclebutton02.sub")
#			self.CloseBtn.SetText( localeInfo.MOVE_CHANNEL_CANCEL )
			self.CloseBtn.SetEvent(ui.__mem_func__(self.Close))

			for i in xrange(cnt):
				btn = ui.MakeButton(self.ChildBoard, 8, 6 + i*28, "", "d:/ymir work/ui/game/myshop_deco/", "select_btn_01.sub", "select_btn_02.sub", "select_btn_03.sub")
				btn.SetText("Kanal {0}".format(int(i+1)))
				btn.SetEvent(ui.__mem_func__(self.__SelectChannel), i+1)
				self.ChannelList.append(btn)

			self.ParentBoard.SetSize(self.DlgWidht, self.DlgHeight)
			self.ChildBoard.SetSize(self.DlgWidht - 26, self.BlackBoardHeight)
			self.SetSize(self.DlgWidht, self.DlgHeight)
			self.UpdateRect()

		def __SelectChannel(self, idx):
			self.ChangeChannelNumber = idx

			for btn in self.ChannelList:
				btn.SetUp()
				btn.Enable()

			self.ChannelList[idx-1].Down()
			self.ChannelList[idx-1].Disable()

		def AcceptButton(self):
			if self.ChangeChannelNumber == self.StartChannelNumber:
				return

			net.SendChatPacket("/channel " + str(self.ChangeChannelNumber))
			self.Close()

		def Show(self) :
			ui.ScriptWindow.Show(self)

			self.StartChannelNumber = constInfo.channel_idx
			self.__SelectChannel(self.StartChannelNumber)

			self.IsShow = True

		def Close(self):
			self.Hide()

			self.IsShow = False

		def OnPressEscapeKey(self):
			self.Close()
			return True

		def IsShowWindow(self):
			return self.IsShow