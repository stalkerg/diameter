import Level, Particle, GaoObject

Player = Level.SearchPlayer()
if Player != 0:
	cord = GaoObject.GetCord(Player)
	#print "SC:cord:",cord
	if cord[0]<-230 and cord[0]>-260 and cord[1]<-5 and cord[1]>-20:
		DGUI.PauseGame(True)
		DGUI.SetPopupVisible(True)
		DGUI.SetPopupText("Following you. Consider i'm not fast.")
		DGUI.SetPopupScriptOk("pyscripts/test_mission1d2_ok.py")
		DGUI.SetPopupFaceImage("texture/gui/other/noface.png")
		Transport = Level.SearchObjectByName("Transport")
		print "AddrT:",Transport
		if Transport != 0:
			GaoObject.FollowObject(Transport, Player)
		
		Level.NextScript("pyscripts/test_mission1state2.py")
		Level.Pause(7000)

Level.Pause(1000)