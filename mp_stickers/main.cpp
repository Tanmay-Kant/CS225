#include "Image.h"
#include "StickerSheet.h"

int main() {

Image sticker1, sticker2, output;
sticker1.readFromFile("alma.png");
sticker2.readFromFile("i.png");

StickerSheet pictureOutput(sticker1, 10);
pictureOutput.addSticker(sticker2, 100, 50);
pictureOutput.addSticker(sticker2, 50, 100);
pictureOutput.addSticker(sticker2, 0, 200);
pictureOutput.addSticker(sticker2, 200, 0);

pictureOutput.addSticker(sticker2, 600, 50);
pictureOutput.addSticker(sticker2, 550, 100);
pictureOutput.addSticker(sticker2, 500, 200);
pictureOutput.addSticker(sticker2, 650, 0);

output = pictureOutput.render();
output.writeToFile("myImage.png");
  return 0;
}
