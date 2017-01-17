import Level, Particle, GaoObject

def CreateObject():
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
		 
	GaoObject.WriteParticle(TempObject, TParticle)
	return TempObject

Ataker1 = CreateObject()
Ataker2 = CreateObject()
Ataker3 = CreateObject()
Ataker4 = CreateObject()
GaoObject.SetCord(Ataker1, -200, 100)
GaoObject.SetCord(Ataker2, -205, 100)
GaoObject.SetCord(Ataker3, -210, 100)
GaoObject.SetCord(Ataker4, -215, 100)

Transport = Level.SearchObjectByName("Transport")
print "AddrT:",Transport
if Transport != 0:
	GaoObject.AttackObject(Ataker1, Transport)
	GaoObject.AttackObject(Ataker2, Transport)
	GaoObject.AttackObject(Ataker3, Transport)
	GaoObject.AttackObject(Ataker4, Transport)

Level.AddGaoObject(Ataker1)
Level.AddGaoObject(Ataker2)
Level.AddGaoObject(Ataker3)
Level.AddGaoObject(Ataker4)

Level.Pause(5000)
Level.NextScript("pyscripts/test_mission1state3.py")