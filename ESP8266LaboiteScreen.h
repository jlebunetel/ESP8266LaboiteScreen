#ifndef ESP8266LaboiteScreen_h
#define ESP8266LaboiteScreen_h

// Cette bibliothèque a pour but de proposer une interface commune de génération
// de buffers pour ensuite aller les transférer sur n'importe quel afficheur
// matriciel.
// Cette bibliothèque permet de également de générer les transitions. ??????

// Un buffer est constitué d'un tableau d'octets (8 bits).
// Chaque octet représente une ligne horizontale de 8 pixels.
// Les octets s'enchaînent de telle sorte que l'image est décrite à partir du
// pixel en haut à gauche, puis ligne par ligne.
// Pour une image en quatre couleurs (ex. : noir, rouge, vert, jaune), le buffer
// contient l'information de l'ensemble de l'image pour la première couleur
// (ex. : rouge) puis l'ensemble de l'image pour la seconde couleur (ex. : verte).
// De même, pour une image en huit couleur, le buffer contient à la suite
// l'information pour l'image Rouge, puis Verte et enfin Bleue.


// font definition
#define FONT_DEFAULT 1
#define FONT_5X7 1
#define FONT_4X6 2


// library interface description
class Bitmap {
  public:
    Bitmap(uint8_t width, uint8_t height, String raw);

  //private:
    uint8_t width;
    uint8_t height;
    String raw;
};


class Font {
  public:
    Font(uint8_t min, uint8_t max, uint8_t unknown, Bitmap* characters);
    Bitmap getBitmap(char c);

  //private:
    uint8_t min;
    uint8_t max;
    uint8_t unknown;
    Bitmap* characters = NULL;
};


class Screen {
  public:
    Screen(void);
    void clear();
    uint8_t* getBuffer();
    void setPixel(uint8_t x, uint8_t y);
    void drawBitmap(uint8_t x, uint8_t y, Bitmap bitmap);
    void print(uint8_t x, uint8_t y, char c, Font* font);
    void print(uint8_t x, uint8_t y, String s, uint8_t font_name);
    void print(uint8_t x, uint8_t y, String s) { print(x, y, s, FONT_DEFAULT); };

  //private:
    uint8_t* buffer = NULL; // pointeur qui peut contenir l'adresse du premier élément du tableau buffer déclaré dans la classe fille
    uint16_t buffer_lenght = 0;
    uint8_t width = 0;
    uint8_t height = 0;
    uint8_t colors = 0;
};

// 32 x 16 monochrome / 2 colors (on and off) / 1 layer (R)
#define BUFFER_32_16_2 64

class Screen_32_16_2 : public Screen {
  // hérite de la classe Screen
  public:
    Screen_32_16_2(void);
    void demo();

  private:
    uint8_t _buffer[BUFFER_32_16_2];
};

// 32 x 32 monochrome / 2 colors (on and off) / 1 layer (R)
#define BUFFER_32_32_2 128

// 32 x 16 bicolor / 4 colors (off, red, green, red + green) / 2 layers (RG)
#define BUFFER_32_16_4 128

// 32 x 16 RGB / 8 colors (xxx, Rxx, xGx, xxB, RGx, RxB, xGB, RGB) / 3 layers (RGB)
#define BUFFER_32_16_8 192

// 32 x 32 RGB / 8 colors
#define BUFFER_32_32_8 384



#endif
