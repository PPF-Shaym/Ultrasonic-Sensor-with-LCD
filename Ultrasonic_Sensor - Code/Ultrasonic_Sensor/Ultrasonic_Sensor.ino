/* Fonctionnement d'un capteur ultrason HC-SR04 */
/* Auteur du projet Shaym */
/* Dans le cadre de mon projet TPE 2019 */
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

int trig = 8; /* Constantes pour la broche Trigger */
int echo = 9; /* Constantes pour la broche Echo */
const float SOUND_SPEED = 340.0 / 1000; /* Vitesse du son */

void setup()/** Fonction setup() */
{
Serial.begin(115200); /* Initialise le port serie */

/* Initialise les broches */
pinMode(trig, OUTPUT); 
digitalWrite(trig, LOW);
pinMode(echo, INPUT);

/* Affiche la date et le projet*/
lcd.begin(16,2);
lcd.setCursor(4,0);
lcd.print ("TPE 2019");
delay (2000);
lcd.clear();
}

void loop() /** Fonction loop() */
{
/* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10s sur la broche TRIGGER */
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);

 /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son echo (si il existe) */
long measure = pulseIn(echo,HIGH);

/* 3. Calcul la distance a partir du temps mesure */
  float distance_mm = measure / 2.0 * SOUND_SPEED; // ici c'est le calcul de la distance
   
  /* Affiche les resultats en mm, cm et m */
  Serial.print(F("Distance: "));
  Serial.print(distance_mm);
  Serial.print(F("mm ("));
  Serial.print(distance_mm / 10.0, 2);
  Serial.print(F("cm, "));
  Serial.print(distance_mm / 1000.0, 2);
  Serial.println(F("m)"));

  /* Affiche sur l'ecran LCD les resultats en cm */
  lcd.setCursor (4,0);
  lcd.print ("DISTANCE:");
  lcd.setCursor (0,1);
  lcd.print ("=====");
  lcd.setCursor (5,1);

  distance_mm = int(distance_mm);
  distance_mm = distance_mm / 10.0;
  lcd.print (distance_mm, 2);
  lcd.setCursor (9,1);
  lcd.print ("CM");
  lcd.setCursor (11,1);
  lcd.print ("=====");

delay(2000);/* Delai d'attente pour eviter d'afficher trop de resultats a la seconde */
}
