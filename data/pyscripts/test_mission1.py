import  Level, DGUI

print "Mission1 Started"
DGUI.SetPopupVisible(True)
DGUI.SetPopupText("Hello my friend!. \nDon't worry - you have rosen \n\
here by the will of gods! You must know how\n\
to rule gadjets, surrounding you. You would \n\
for work for me - and i would tell you about \n\
this world. You haven't choice.")
DGUI.SetPopupSize(450,200)
DGUI.SetPopupPosition(200, 100)
DGUI.SetPopupEnableButtons(False, True, False) #Prev, Next, Ok
DGUI.SetPopupFaceImage("texture/gui/other/lucas.png")
DGUI.SetPopupScriptNext("pyscripts/test_mission1d1_next.py")
DGUI.PauseGame(True)

