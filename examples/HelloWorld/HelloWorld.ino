// Librairie à adapter en fonction de l'afficheur utilisé
#include <ESP8266LaboiteMAX72XX.h>
LedMatrixPanel afficheur;

// Librairie pour générer les buffers
#include <ESP8266LaboiteScreen.h>
Screen_32_16_2 image;

void setup() {
  // display initialization
  afficheur.init();
  afficheur.intensity(0);

  // hello world !
  image.demo();
  afficheur.display(image.getBuffer());
}

void loop() {
  delay(1000);
}
