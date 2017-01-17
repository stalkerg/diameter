import  DGUI

DGUI.SetPopupText("Fly to little gas cloud to find transport\n\
tractor and deliver it safe and sound \n\
to coords 100,50. Be careful - pirate \n\
zondes could attack you")
DGUI.SetPopupEnableButtons(False, False, True) #Prev, Next, Ok
DGUI.SetPopupScriptOk("pyscripts/test_mission1d1_ok.py")

