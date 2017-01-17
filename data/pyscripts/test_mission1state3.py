import  Level, DGUI

DGUI.SetPopupVisible(True)
DGUI.SetPopupText("He he, I destroy you tradeship.")
DGUI.SetPopupEnableButtons(False, False, True) #Prev, Next, Ok
DGUI.SetPopupFaceImage("texture/gui/other/magnaguard.png")
DGUI.SetPopupScriptNext("pyscripts/test_mission1d2_ok.py")
DGUI.PauseGame(True)

Level.NextScript("pyscripts/test_mission1state4.py")
Level.Pause(4000)