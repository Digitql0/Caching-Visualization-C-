#include <cmath>
#include <cstdlib>
#include <raylib.h>

// width and height of Window
int width = 800;
int height = 800;
const int rows = 50;
const int columns = 100;
const float padding = 20;
const float gridBorderThickness = 5;
const Color gridBorderColor = LIGHTGRAY;
float tileSize;
Vector2 gridOrigin;

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  // unsigned char, since Colors only take unsigned chars as parameters.
  bool hit;
  bool cached;
} Pixel;

Pixel pixels[rows][columns];

int main() {

  // Make the tileSize so it fills up the Screen
  tileSize = fminf(
      (float)(width - 2 * gridBorderThickness - 2 * padding) / columns,
      (float)(height / 2.0f - 2 * gridBorderThickness - 2 * padding) / rows);

  // Make the gridOrigin so it is perfectly in the middle
  gridOrigin.x = (width - tileSize * columns) / 2;
  gridOrigin.y = (height / 2.0f - tileSize * rows) / 2;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      unsigned char r = GetRandomValue(0, 255);
      unsigned char g = GetRandomValue(0, 255);
      unsigned char b = GetRandomValue(0, 255);
      bool hit = false;
      bool cached = false;
      pixels[i][j] = (Pixel){r, g, b, hit, cached};
      // Picking Three Random RGB values for the Randomized Color;
    }
  }

  // Making Window
  InitWindow(width, height, "Caching Visualization");

  while (!WindowShouldClose()) {

    // Drawing
    BeginDrawing();
    ClearBackground(GRAY);

    // Draw the Border of the Grid
    DrawRectangleLinesEx(
        (Rectangle){
            gridOrigin.x - gridBorderThickness,
            gridOrigin.y - gridBorderThickness,
            tileSize * columns + gridBorderThickness * 2,
            tileSize * rows + gridBorderThickness * 2,
        },
        gridBorderThickness, gridBorderColor);

    // Draw the Grid of Pixels
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        Color myColor = BLACK;
        myColor.a = 255; // Ensuring the Pixel is not transparent.
        if (pixels[i][j].hit == true) {
          if (pixels[i][j].cached == true) {
            myColor = LIME;
          } else {
            myColor = RED;
          }
        } else {
          myColor.r = pixels[i][j].r;
          myColor.g = pixels[i][j].g;
          myColor.b = pixels[i][j].b;
        }
        DrawRectangle(gridOrigin.x + j * tileSize, gridOrigin.y + i * tileSize,
                      tileSize, tileSize, myColor);
      }
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
