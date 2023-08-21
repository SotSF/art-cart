/// @file    DemoReel100.ino
/// @brief   FastLED "100 lines of code" demo reel, showing off some effects
/// @example DemoReel100.ino

#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#define DATA_PIN 32
#define CLK_PIN 33
#define LED_TYPE WS2801
#define COLOR_ORDER GRB

#define BRIGHTNESS 96
#define FRAMES_PER_SECOND 120

#define NUM_VIRTUAL_LEDS 100
CRGB virtualLeds[NUM_VIRTUAL_LEDS];

#define NUM_LEDS 372
CRGB leds[NUM_LEDS];

// generated with generateLedMapping.ts, copied from ledIndexToVirtualLedIndex.json
int ledIndexToVirtualLedIndex[NUM_LEDS] = {0, 4, 8, 13, 17, 21, 25, 31, 38, 44, 50, 55, 60, 65, 70, 75, 79, 83, 88, 92, 96, 96, 96, 93, 89, 86, 82, 79, 75, 70, 65, 60, 55, 50, 44, 38, 31, 25, 21, 17, 13, 8, 4, 0, 0, 0, 4, 8, 13, 17, 21, 25, 30, 35, 40, 45, 50, 56, 63, 69, 75, 79, 82, 86, 89, 93, 96, 96, 97, 94, 91, 88, 84, 81, 78, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5, 0, 0, 0, 0, 4, 8, 13, 17, 21, 25, 30, 35, 40, 45, 50, 56, 63, 69, 69, 69, 63, 56, 50, 47, 44, 41, 38, 34, 31, 28, 25, 20, 15, 10, 5, 0, 0, 0, 0, 5, 10, 15, 20, 25, 28, 31, 33, 36, 39, 42, 44, 47, 50, 55, 60, 65, 70, 70, 65, 60, 55, 50, 47, 44, 42, 39, 36, 33, 31, 28, 25, 20, 15, 10, 5, 0, 0, 0, 4, 8, 13, 17, 21, 25, 28, 31, 33, 36, 39, 42, 44, 47, 50, 55, 60, 65, 70, 70, 70, 65, 60, 55, 50, 47, 44, 41, 38, 34, 31, 28, 25, 20, 15, 10, 5, 0, 0, 0, 6, 13, 19, 25, 28, 31, 33, 36, 39, 42, 44, 47, 50, 55, 60, 65, 70, 70, 65, 60, 55, 50, 47, 44, 42, 39, 36, 33, 31, 28, 25, 20, 15, 10, 5, 0, 0, 0, 5, 10, 15, 20, 25, 28, 31, 33, 36, 39, 42, 44, 47, 50, 56, 63, 69, 69, 69, 63, 56, 50, 46, 43, 39, 36, 32, 29, 25, 20, 15, 10, 5, 0, 0, 0, 0, 5, 10, 15, 20, 25, 29, 32, 36, 39, 43, 46, 50, 56, 63, 69, 75, 79, 82, 86, 89, 93, 96, 96, 96, 93, 89, 86, 82, 79, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5, 0, 0, 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 79, 83, 88, 92, 96, 96, 93, 89, 86, 82, 79, 75, 70, 65, 60, 55, 50, 44, 38, 31, 25, 21, 17, 13, 8, 4, 0};

void setup()
{
    delay(3000); // 3 second delay for recovery

    // tell FastLED about the LED strip configuration
    // FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE, DATA_PIN, CLK_PIN, COLOR_ORDER>(virtualLeds, NUM_VIRTUAL_LEDS).setCorrection(TypicalLEDStrip);

    // set master brightness control
    FastLED.setBrightness(BRIGHTNESS);
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0;                  // rotating "base color" used by many of the patterns

void loop()
{
    // Call the current pattern function once, updating the 'leds' array
    gPatterns[gCurrentPatternNumber]();

    updateLedsFromVirtualLeds();

    // send the 'leds' array out to the actual LED strip
    FastLED.show();
    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);

    // do some periodic updates
    EVERY_N_MILLISECONDS(20) { gHue++; }   // slowly cycle the "base color" through the rainbow
    EVERY_N_SECONDS(10) { nextPattern(); } // change patterns periodically
}

void updateLedsFromVirtualLeds()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = virtualLeds[ledIndexToVirtualLedIndex[i]];
    }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
    // add one to the current pattern number, and wrap around at the end
    gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
}

void rainbow()
{
    // FastLED's built-in rainbow generator
    fill_rainbow(virtualLeds, NUM_VIRTUAL_LEDS, gHue, 7);
}

void rainbowWithGlitter()
{
    // built-in FastLED rainbow, plus some random sparkly glitter
    rainbow();
    addGlitter(80);
}

void addGlitter(fract8 chanceOfGlitter)
{
    if (random8() < chanceOfGlitter)
    {
        virtualLeds[random16(NUM_VIRTUAL_LEDS)] += CRGB::White;
    }
}

void confetti()
{
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy(virtualLeds, NUM_VIRTUAL_LEDS, 10);
    int pos = random16(NUM_VIRTUAL_LEDS);
    virtualLeds[pos] += CHSV(gHue + random8(64), 200, 255);
}

void sinelon()
{
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy(virtualLeds, NUM_VIRTUAL_LEDS, 20);
    int pos = beatsin16(13, 0, NUM_VIRTUAL_LEDS - 1);
    virtualLeds[pos] += CHSV(gHue, 255, 192);
}

void bpm()
{
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < NUM_VIRTUAL_LEDS; i++)
    { // 9948
        virtualLeds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
}

void juggle()
{
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy(virtualLeds, NUM_VIRTUAL_LEDS, 20);
    uint8_t dothue = 0;
    for (int i = 0; i < 8; i++)
    {
        virtualLeds[beatsin16(i + 7, 0, NUM_VIRTUAL_LEDS - 1)] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
}
