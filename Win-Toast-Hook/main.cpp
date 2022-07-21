#include "wintoastlib.h"

using namespace WinToastLib;

class CustomHandler : public IWinToastHandler {
public:
    void toastActivated() const {}
    void toastActivated(int actionIndex) const {}
    void toastDismissed(WinToastDismissalReason state) const {}
    void toastFailed() const {
        exit(0);
    }
};


enum Results {
    ToastClicked,					// user clicked on the toast
    ToastDismissed,					// user dismissed the toast
    ToastTimeOut,					// toast timed out
    ToastHided,						// application hid the toast
    ToastNotActivated,				// toast was not activated
    ToastFailed,					// toast failed
    SystemNotSupported,				// system does not support toasts
    UnhandledOption,				// unhandled option
    MultipleTextNotSupported,		// multiple texts were provided
    InitializationFailure,			// toast notification manager initialization failure
    ToastNotLaunched				// toast could not be launched
};


int main(void)
{
    if (!WinToast::isCompatible()) {
        std::wcerr << L"System version is wrong!" << std::endl;
        return Results::SystemNotSupported;
    }
    LPCWSTR  name = L"Zepta";
    WinToast::instance()->setAppName(name);
    WinToast::instance()->setAppUserModelId(L"12");


    if (!WinToast::instance()->initialize()) {
        std::wcerr << L"System version is wrong!" << std::endl;
        return Results::InitializationFailure;
    }

    WinToastTemplate templ(WinToastTemplate::Text02);
    templ.setTextField(L"Zepta Text", WinToastTemplate::FirstLine);
    templ.setAudioOption(WinToastTemplate::AudioOption::Default);
   
    WinToast::instance()->showToast(templ, new CustomHandler());

    Sleep(3000);

    exit(2);
}