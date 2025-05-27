#ifndef KEYBOARD_LAYOUT
#define KEYBOARD_LAYOUT

#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/hal/Types.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include "BitmapDatabase.hpp"

using namespace touchgfx;

/**
 * Array specifying the keys used in the CustomKeyboard.
 */
static const Keyboard::Key keyArray[30] =
{
    { 1, Rect(17, 115, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 2, Rect(17 + 56, 115, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 3, Rect(17 + 56 * 2, 115, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 4, Rect(17 + 56 * 3, 115, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 5, Rect(17 + 56 * 4, 115, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 6, Rect(17 + 56 * 5, 115, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 7, Rect(17 + 56 * 6, 115, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 8, Rect(17 + 56 * 7, 115, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    { 9, Rect(17 + 56 * 8, 115, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {10, Rect(17 + 56 * 9, 115, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {11, Rect(17 + 56 * 10, 115, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},

    {12, Rect(17, 210, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {13, Rect(17 + 56, 210, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {14, Rect(17 + 56 * 2, 210, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {15, Rect(17 + 56 * 3, 210, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {16, Rect(17 + 56 * 4, 210, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {17, Rect(17 + 56 * 5, 210, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {18, Rect(17 + 56 * 6, 210, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {19, Rect(17 + 56 * 7, 210, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {20, Rect(17 + 56 * 8, 210, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {21, Rect(17 + 56 * 9, 210, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {22, Rect(17 + 56 * 10, 210, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},

    {23, Rect(125, 295, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {24, Rect(125 + 56, 295, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {25, Rect(125 + 56 * 2, 295, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {26, Rect(125 + 56 * 3, 295, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {27, Rect(125 + 56 * 4, 295, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {28, Rect(125 + 56 * 5, 295, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {29, Rect(125 + 56 * 6, 295, 40, 55), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID},
    {30, Rect(180, 385, 252, 55), BITMAP_KEYBOARD_SPACE_HIGHLIGHTED_ID}
};

/**
 * Callback areas for the special buttons on the CustomKeyboard.
 */
static Keyboard::CallbackArea callbackAreas[3] =
{
    {Rect(15, 300, 81, 65), 0, BITMAP_KEYBOARD_KEY_SHIFT_HIGHLIGHTED_ID},     // caps-lock
    {Rect(515, 300, 81, 65), 0, BITMAP_KEYBOARD_KEY_DELETE_HIGHLIGHTED_ID},  // backspace
    {Rect(15, 385, 81, 65), 0, BITMAP_KEYBOARD_KEY_NUM_HIGHLIGHTED_ID},       // mode
};

/**
 * The layout for the CustomKeyboard.
 */
static const Keyboard::Layout layout =
{
    BITMAP_KEYBOARD_BACKGROUND_ID,
    keyArray,
    30,
    callbackAreas,
    3,
    Rect(15, 20, 11 * 50, 100),
	//Rect(15, 10, 11 * 28, 40),
    TypedText(T_ENTEREDTEXT),
#if !defined(USE_BPP) || USE_BPP==16
    0xFFFF,
#elif USE_BPP==24
    0xFFFFFF,
#elif USE_BPP==4
    0xF,
#elif USE_BPP==2
    0x3,
#else
#error Unknown USE_BPP
#endif
    Typography::KEYBOARD,
    0
};

#endif
