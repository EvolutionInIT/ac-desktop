#include "functions.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>

#include <QApplication>
#include <QScreen>
#include <QPixmap>
#include <QDateTime>
#include <QDir>

Functions::Functions() {
    // Constructor implementation (if any)
}




void captureScreenshot(const QString &saveDirectory, const QString &fileName = "") {
    // Get the current screen
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen) {
        qWarning("Failed to get the screen!");
        return;
    }

    // Capture the screenshot
    QPixmap screenshot = screen->grabWindow(0);

    // If no file name is provided, generate a default one using the current timestamp
    QString finalFileName;
    if (fileName.isEmpty()) {
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
        finalFileName = QString("screenshot_%1.png").arg(timestamp);
    } else {
        finalFileName = fileName.endsWith(".png") ? fileName : fileName + ".png";
    }

    // Full path for saving the screenshot
    QString fullPath = saveDirectory + "/" + finalFileName;

    // Save the screenshot
    if (!screenshot.save(fullPath)) {
        qWarning("Failed to save the screenshot!");
    } else {
        qDebug() << "Screenshot saved to:" << fullPath;
    }
}












#ifdef _WIN32
#include <windows.h>
#include <codecvt>
#include <tchar.h>

std::string Functions::GetActiveWindowProcess() {
    HWND hWnd = GetForegroundWindow();
    if (IsWindowVisible(hWnd)) {
        DWORD processID;
        GetWindowThreadProcessId(hWnd, &processID);

        TCHAR windowTitle[256];
        GetWindowText(hWnd, windowTitle, sizeof(windowTitle) / sizeof(TCHAR));

        if (_tcslen(windowTitle) > 0) {
            std::wstring wstr(windowTitle);
            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
            std::string str = convert.to_bytes(wstr);

            return str;
        }
    }
    return "Nothing";
}
#elif _linux_
#include <X11/Xlib.h>

std::string Functions::GetActiveWindowProcess() {
    Display* display = XOpenDisplay(NULL);
    if (!display) return "Unknown";

    Window root = DefaultRootWindow(display);
    Window window;
    int revert;
    XGetInputFocus(display, &window, &revert);

    char* windowName;
    XFetchName(display, window, &windowName);

    std::string result = windowName ? std::string(windowName) : "Unknown";
    XFree(windowName);
    XCloseDisplay(display);
    return result;
}
#elif _APPLE_
#include <ApplicationServices/ApplicationServices.h>

std::string Functions::GetActiveWindowProcess() {
    CFArrayRef windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
    if (windowList) {
        CFDictionaryRef windowInfo = (CFDictionaryRef)CFArrayGetValueAtIndex(windowList, 0);
        CFStringRef windowOwner = (CFStringRef)CFDictionaryGetValue(windowInfo, kCGWindowOwnerName);
        char buffer[256];
        CFStringGetCString(windowOwner, buffer, sizeof(buffer), kCFStringEncodingUTF8);
        CFRelease(windowList);
        return std::string(buffer);
    }
    return "Unknown";
}
#endif
