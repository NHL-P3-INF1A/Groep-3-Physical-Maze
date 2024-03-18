// ==== [ Color for specific light ] ==========================================
void setPixelRgb(int pixel, uint8_t red, uint8_t green, uint8_t blue) 
{
    strip.setPixelColor(pixel, strip.Color(red, green, blue));
    strip.show();
}

void setPixelByName(int pixel, const int color[])
{
  strip.setPixelColor(pixel, strip.Color(color[0], color[1], color[2]));
  strip.show();
}

void blinkLed(int pixel)
{
  static unsigned long timer;
  static boolean LedState = false;
  if(millis() > timer)
  {
    LedState = !LedState;
    setPixelByName(pixel, LedState ? ORANGE : WHITE);
    timer = (millis() + 250);
  }
}
