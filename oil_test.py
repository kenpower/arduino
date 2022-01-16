

duration=0
cm=0
count = 0

def loop(mm):
  emptyDistance = 1080
  fullDistance = 120
  volume = 900
  litresPerMM = volume/1040
  litresPerDay = 3
  usableVolume = 900.0 * (960.0 /1040.0)
  
  #mm = getDistance() 

  oilLevelAboveEmpty = emptyDistance - mm

  volumeRemaining = oilLevelAboveEmpty * litresPerMM

  volumeToOrder = usableVolume - volumeRemaining
  daysLeft = volumeRemaining /litresPerDay
  percentFull= (volumeRemaining*100) / usableVolume

  #volumeToOrder=mm

  #delay(1000)

  res=""
  res+=str(percentFull)
  res+="%"
  
  #lcd.setCursor(8,0)
  res+="Days:"
  res+=str(daysLeft)
  

  res+="Order "
  res+=str(volumeToOrder)
  res+="litres"
   
  return res


d=0
print(F"{d} => {loop(d)}")
d=120
print(F"{d} => {loop(d)}")
d=500
print(F"{d} => {loop(d)}")
d=960
print(F"{d} => {loop(d)}")
d=1080
print(F"{d} => {loop(d)}")
