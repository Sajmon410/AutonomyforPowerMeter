# LPRS2_2023
## AutonomyforPowerMeter <br>
Ovaj repozitorijum sadrzi 1 od 3 dela projekta koji ima za cilj da meri napon i jacinu struje i da te vrednosti skladisti na SD karticu i salje preko mreze i sve se to odvija u realnom vremenu.<br>
Ovaj deo koda predstavlja rad sa SD karticom a koristi i RT clock.<br>
Na arudino su od eksternih modula prikaceni jedan RT clock DS1302 i Arduino Micro SD card.<br>

##  Biblioteke
```C++
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <TimeLib.h>
#include <virtuabotixRTC.h>
#include <math.h>
```
## Dokumentacija koda
> Setup
- Prvo se setuje baud rate za serijsku komunikaciju na 9600 
- Inicijalizuje se objekat klase virtuabotixRTC i prosledjuju mu se parametri koji predstavljaju pinove koji se koriste za konekciju i onda se postavlja na neko zeljeno pocetno vreme.
```C++
p_obj=new virtuabotixRTC(6, 7, 4);
p_obj->setDS1302Time(18, 10, 10, 7, 12, 6, 2023);
```
- Pokusava se inicijalizacija SD kartice i ispisuje se rezultat.
> Loop
- Updatuje se stanje clock-a
```C++
  p_obj->updateTime();
```
- Pokusava se otvaranje fajla u write modu i ako je uspesno podaci o naponu, jacini struje i vremenu ocitavanja se upisuju u fajl.
```C++
File dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    Serial.println("***************************************************");
    Serial.println("Data written to file: " + data);
  } else {
    Serial.println("Error opening data file!");
  }
```
## Šeme
> Umesto pina 8 sa slike u nasem projektu koristimo pin 4
![sema](https://github.com/Sajmon410/AutonomyforPowerMeter/assets/120813343/aefc47a9-28c8-49ef-9267-f19778b421a8)<br>

![Micro-SD-Card-Module-with-Arduino](https://github.com/Sajmon410/AutonomyforPowerMeter/assets/120813343/46b3145f-1b61-453d-8592-71902dce31ec)


## Video
https://youtu.be/tLOTxwPPdV4<br>
