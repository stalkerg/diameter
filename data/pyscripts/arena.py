import Level, Particle, GaoObject

print "New Attack Object scipt... RUN"
if Level.GetPlayerStart():
	print "Restart level..."
	Level.SetCalcSim(1)
	Level.Pause(5000)
else:
        TParticle =  Particle.NewParticle(30)
        Particle.SetSprite(TParticle, "sp009")
	Particle.SetnDirection(TParticle, 1.0, 1.0, 0.0)
	Particle.SetCor(TParticle, 0.0, 0.0, -0.1)
	Particle.SetnColor(TParticle, 1.0, 0.8, 1.0, 1.0)
	Particle.SetkColor(TParticle, 1.0, 0.0, 0.0, 0.0)
	Particle.SetSpeed(TParticle, 4, 400, 400)
	Particle.SetLife(TParticle, 0.6)
	Particle.Init(TParticle)
	
	TempObject = GaoObject.NewGaoObject()
	
	GaoObject.SetShipType(TempObject, 3)
	GaoObject.SetExplosion(TempObject, "sp011", "sp012")
	rnd = Level.Random(30)
	if rnd < 10:
		GaoObject.SetName(TempObject, "BlackWar")
		GaoObject.SetModel(TempObject, "Ship2")
		GaoObject.SetTypeGun(TempObject, 1)
		GaoObject.SetParticlePos(TempObject,1, 1, 0, 0)
		GaoObject.SetParamsHS(TempObject,
				     50.0,   #Shield
				     50.0,   #MaxShield
				     0.5,    #SpeedRShield
				     20.0,   #Health
				     20.0,   #MaxHealth
				     100.0,  #GunEnergy
				     100.0,  #MaxGunEnergy
				     0.6)    #SpeedRGunEnergy
	
		GaoObject.SetPFS(TempObject,
				 20.0, #Max Power
				 2.0,  #Mass
				 55)   #Speed Rotation
	elif rnd >= 10 and rnd < 25:
		GaoObject.SetName(TempObject, "DragonFly")
		GaoObject.SetModel(TempObject, "Ship1")
		GaoObject.SetTypeGun(TempObject, 2)
		GaoObject.SetParticlePos(TempObject,1, 1, 0, 0)
		GaoObject.SetParamsHS(TempObject,
				     30.0,   #Shield
				     30.0,   #MaxShield
				     0.5,    #SpeedRShield
				     10.0,   #Health
				     10.0,   #MaxHealth
				     100.0,  #GunEnergy
				     100.0,  #MaxGunEnergy
				     0.6)    #SpeedRGunEnergy
	
		GaoObject.SetPFS(TempObject,
				 14.0, #Max Power
				 1.0,  #Mass
				 150)   #Speed Rotation
	elif rnd>=25:
		GaoObject.SetName(TempObject, "DarkBomb")
		GaoObject.SetModel(TempObject, "Ship4")
		GaoObject.SetTypeGun(TempObject, 1)
		GaoObject.SetParticlePos(TempObject,1, 1, 0, 0.85)
		GaoObject.SetParamsHS(TempObject,
				     80.0,   #Shield
				     80.0,   #MaxShield
				     0.5,    #SpeedRShield
				     20.0,   #Health
				     20.0,   #MaxHealth
				     100.0,  #GunEnergy
				     100.0,  #MaxGunEnergy
				     0.6)    #SpeedRGunEnergy
	
		GaoObject.SetPFS(TempObject,
				 25.0, #Max Power
				 2.0,  #Mass
				 70)   #Speed Rotation
	
	GaoObject.WriteParticle(TempObject, TParticle)
	
	GaoObject.SetCord(TempObject, Level.Random(200)-100, Level.Random(200)-100)
	#GaoObject.SetCord(0, 0)
	
	Player = Level.SearchPlayer()
	if Player != 0:
	        GaoObject.AttackObject(TempObject, Player)
	Level.AddGaoObject(TempObject)
	Level.Pause(15000)