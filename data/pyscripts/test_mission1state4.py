import  Level, DGUI, GaoObject

Transport=Level.SearchObjectByName("Transport")
if Transport:
	cord = GaoObject.GetCord(Transport)
	if cord[0]<110 and cord[0]>90 and cord[1]<60 and cord[1]>40:
		DGUI.PauseGame(True)
		DGUI.SetPopupVisible(True)
		DGUI.SetPopupText("Well done! You deliver it.\nYou first mission end now.")
		DGUI.SetPopupScriptOk("pyscripts/test_mission1d4_ok.py")
		DGUI.SetPopupFaceImage("texture/gui/other/lucas.png")
else:
	DGUI.PauseGame(True)
	DGUI.SetPopupVisible(True)
	DGUI.SetPopupText("Oh shit - they explode it!\nYour fucking sun of beach!")
	DGUI.SetPopupScriptOk("pyscripts/test_mission1d4_ok.py")
	DGUI.SetPopupFaceImage("texture/gui/other/lucas.png")

Level.Pause(4000)