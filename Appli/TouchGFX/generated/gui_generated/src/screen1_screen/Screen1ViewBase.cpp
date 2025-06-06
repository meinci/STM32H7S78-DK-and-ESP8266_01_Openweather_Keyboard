/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen1ViewBase::Screen1ViewBase() :
    flexButtonCallback(this, &Screen1ViewBase::flexButtonCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    scalableImage1.setBitmap(touchgfx::Bitmap(BITMAP_COLLAGE_KONZEPT_FUR_WETTEREFFEKTE_ID));
    scalableImage1.setPosition(0, 0, 800, 480);
    scalableImage1.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    add(scalableImage1);

    boxWithBorder1.setPosition(0, 94, 269, 367);
    boxWithBorder1.setColor(touchgfx::Color::getColorFromRGB(47, 78, 98));
    boxWithBorder1.setBorderColor(touchgfx::Color::getColorFromRGB(45, 53, 107));
    boxWithBorder1.setBorderSize(5);
    boxWithBorder1.setVisible(false);
    add(boxWithBorder1);

    tA_Outdoor_Temp_1.setPosition(269, 288, 175, 45);
    tA_Outdoor_Temp_1.setColor(touchgfx::Color::getColorFromRGB(245, 250, 242));
    tA_Outdoor_Temp_1.setLinespacing(0);
    tA_Outdoor_Temp_1Buffer[0] = 0;
    tA_Outdoor_Temp_1.setWildcard(tA_Outdoor_Temp_1Buffer);
    tA_Outdoor_Temp_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_8HKD));
    tA_Outdoor_Temp_1.setVisible(false);
    add(tA_Outdoor_Temp_1);

    tA_Outdoor_Pres.setPosition(14, 378, 200, 45);
    tA_Outdoor_Pres.setColor(touchgfx::Color::getColorFromRGB(245, 250, 242));
    tA_Outdoor_Pres.setLinespacing(0);
    tA_Outdoor_PresBuffer[0] = 0;
    tA_Outdoor_Pres.setWildcard(tA_Outdoor_PresBuffer);
    tA_Outdoor_Pres.setTypedText(touchgfx::TypedText(T___SINGLEUSE_6MGE));
    add(tA_Outdoor_Pres);

    tA_Outdoor_Humi.setPosition(21, 333, 175, 45);
    tA_Outdoor_Humi.setColor(touchgfx::Color::getColorFromRGB(245, 250, 242));
    tA_Outdoor_Humi.setLinespacing(0);
    tA_Outdoor_HumiBuffer[0] = 0;
    tA_Outdoor_Humi.setWildcard(tA_Outdoor_HumiBuffer);
    tA_Outdoor_Humi.setTypedText(touchgfx::TypedText(T___SINGLEUSE_WTE2));
    add(tA_Outdoor_Humi);

    tA_Outdoor_Temp.setPosition(19, 288, 175, 45);
    tA_Outdoor_Temp.setColor(touchgfx::Color::getColorFromRGB(245, 250, 242));
    tA_Outdoor_Temp.setLinespacing(0);
    tA_Outdoor_TempBuffer[0] = 0;
    tA_Outdoor_Temp.setWildcard(tA_Outdoor_TempBuffer);
    tA_Outdoor_Temp.setTypedText(touchgfx::TypedText(T___SINGLEUSE_JSTH));
    add(tA_Outdoor_Temp);

    tA_Outdoor_City.setPosition(25, 240, 361, 48);
    tA_Outdoor_City.setColor(touchgfx::Color::getColorFromRGB(245, 250, 242));
    tA_Outdoor_City.setLinespacing(0);
    tA_Outdoor_CityBuffer[0] = 0;
    tA_Outdoor_City.setWildcard(tA_Outdoor_CityBuffer);
    tA_Outdoor_City.setTypedText(touchgfx::TypedText(T___SINGLEUSE_9PER));
    add(tA_Outdoor_City);

    tA_Description.setPosition(22, 194, 200, 50);
    tA_Description.setColor(touchgfx::Color::getColorFromRGB(247, 245, 245));
    tA_Description.setLinespacing(0);
    tA_Description.setWideTextAction(WIDE_TEXT_WORDWRAP);
    tA_DescriptionBuffer[0] = 0;
    tA_Description.setWildcard(tA_DescriptionBuffer);
    tA_Description.setTypedText(touchgfx::TypedText(T___SINGLEUSE_XHV0));
    add(tA_Description);

    image2.setXY(68, 94);
    image2.setBitmap(touchgfx::Bitmap(BITMAP__01D_2X_ID));
    add(image2);

    tA_Year.setPosition(83, 25, 51, 25);
    tA_Year.setColor(touchgfx::Color::getColorFromRGB(247, 245, 245));
    tA_Year.setLinespacing(0);
    tA_YearBuffer[0] = 0;
    tA_Year.setWildcard(tA_YearBuffer);
    tA_Year.setTypedText(touchgfx::TypedText(T___SINGLEUSE_THZU));
    add(tA_Year);

    tA_Month.setPosition(52, 25, 30, 25);
    tA_Month.setColor(touchgfx::Color::getColorFromRGB(247, 245, 245));
    tA_Month.setLinespacing(0);
    tA_MonthBuffer[0] = 0;
    tA_Month.setWildcard(tA_MonthBuffer);
    tA_Month.setTypedText(touchgfx::TypedText(T___SINGLEUSE_5U2A));
    add(tA_Month);

    tA_Day.setPosition(20, 25, 30, 25);
    tA_Day.setColor(touchgfx::Color::getColorFromRGB(247, 245, 245));
    tA_Day.setLinespacing(0);
    tA_DayBuffer[0] = 0;
    tA_Day.setWildcard(tA_DayBuffer);
    tA_Day.setTypedText(touchgfx::TypedText(T___SINGLEUSE_DKEQ));
    add(tA_Day);

    tA_Hour.setPosition(156, 25, 30, 25);
    tA_Hour.setColor(touchgfx::Color::getColorFromRGB(247, 245, 245));
    tA_Hour.setLinespacing(0);
    tA_HourBuffer[0] = 0;
    tA_Hour.setWildcard(tA_HourBuffer);
    tA_Hour.setTypedText(touchgfx::TypedText(T___SINGLEUSE_P907));
    add(tA_Hour);

    tA_Minute.setPosition(188, 25, 30, 25);
    tA_Minute.setColor(touchgfx::Color::getColorFromRGB(247, 245, 245));
    tA_Minute.setLinespacing(0);
    tA_MinuteBuffer[0] = 0;
    tA_Minute.setWildcard(tA_MinuteBuffer);
    tA_Minute.setTypedText(touchgfx::TypedText(T___SINGLEUSE_YXKY));
    add(tA_Minute);

    tA_SSID.setPosition(434, 25, 321, 27);
    tA_SSID.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    tA_SSID.setLinespacing(0);
    tA_SSIDBuffer[0] = 0;
    tA_SSID.setWildcard(tA_SSIDBuffer);
    tA_SSID.setTypedText(touchgfx::TypedText(T___SINGLEUSE_WV8T));
    add(tA_SSID);

    tA_SSIDList.setPosition(469, 94, 286, 306);
    tA_SSIDList.setColor(touchgfx::Color::getColorFromRGB(232, 2, 2));
    tA_SSIDList.setLinespacing(0);
    tA_SSIDList.setWideTextAction(WIDE_TEXT_WORDWRAP);
    tA_SSIDListBuffer[0] = 0;
    tA_SSIDList.setWildcard(tA_SSIDListBuffer);
    tA_SSIDList.setTypedText(touchgfx::TypedText(T___SINGLEUSE_OSRE));
    add(tA_SSIDList);

    flexButton1.setBoxWithBorderPosition(0, 0, 0, 0);
    flexButton1.setBorderSize(5);
    flexButton1.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    flexButton1.setAction(flexButtonCallback);
    flexButton1.setPosition(394, 0, 406, 74);
    add(flexButton1);

    flexButtonConnect.setBoxWithBorderPosition(0, 0, 0, 0);
    flexButtonConnect.setBorderSize(5);
    flexButtonConnect.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    flexButtonConnect.setIconBitmaps(Bitmap(BITMAP_ICON_THEME_IMAGES_HARDWARE_CAST_CONNECTED_70_70_E8F6FB_SVG_ID), Bitmap(BITMAP_ICON_THEME_IMAGES_HARDWARE_CAST_CONNECTED_70_70_ED1140_SVG_ID));
    flexButtonConnect.setIconXY(0, 0);
    flexButtonConnect.setAction(flexButtonCallback);
    flexButtonConnect.setPosition(307, 19, 60, 55);
    add(flexButtonConnect);

    flexButton_City.setBoxWithBorderPosition(0, 0, 269, 367);
    flexButton_City.setBorderSize(5);
    flexButton_City.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    flexButton_City.setAlpha(0);
    flexButton_City.setAction(flexButtonCallback);
    flexButton_City.setPosition(0, 94, 269, 367);
    add(flexButton_City);

    flexButton_SSIDList.setBoxWithBorderPosition(0, 0, 286, 306);
    flexButton_SSIDList.setBorderSize(5);
    flexButton_SSIDList.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    flexButton_SSIDList.setAlpha(0);
    flexButton_SSIDList.setAction(flexButtonCallback);
    flexButton_SSIDList.setPosition(469, 94, 286, 306);
    add(flexButton_SSIDList);
}

Screen1ViewBase::~Screen1ViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void Screen1ViewBase::setupScreen()
{

}

void Screen1ViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &flexButtonConnect)
    {
        //Interaction1
        //When flexButtonConnect clicked change screen to ScreenConnectSSID
        //Go to ScreenConnectSSID with screen transition towards West
        application().gotoScreenConnectSSIDScreenCoverTransitionWest();
    }
    if (&src == &flexButton1)
    {
        //Interaction2
        //When flexButton1 clicked call virtual function
        //Call flexbuttonShow_SSIDs
        flexbuttonShow_SSIDs();
    }
    if (&src == &flexButton_City)
    {
        //selectCity
        //When flexButton_City clicked change screen to ScreenKeyboard_City
        //Go to ScreenKeyboard_City with screen transition towards East
        application().gotoScreenKeyboard_CityScreenCoverTransitionEast();
    }
    if (&src == &flexButton_SSIDList)
    {
        //Hide_SSISList
        //When flexButton_SSIDList clicked call virtual function
        //Call hide_SSIDList
        hide_SSIDList();
    }
}
