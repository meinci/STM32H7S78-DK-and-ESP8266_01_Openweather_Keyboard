#ifndef SCREENCONNECTSSIDPRESENTER_HPP
#define SCREENCONNECTSSIDPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenConnectSSIDView;

class ScreenConnectSSIDPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenConnectSSIDPresenter(ScreenConnectSSIDView& v);
    // Deklaration der Methode mit exakt derselben Signatur:
           void onInputReceived(const touchgfx::Unicode::UnicodeChar* ssid,
                                const touchgfx::Unicode::UnicodeChar* password);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ScreenConnectSSIDPresenter() {}

private:
    ScreenConnectSSIDPresenter();

    ScreenConnectSSIDView& view;
};

#endif // SCREENCONNECTSSIDPRESENTER_HPP
