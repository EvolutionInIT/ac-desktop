#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <QString>
#include <QApplication>
#include <QScreen>
#include <QPixmap>
#include <QDateTime>
#include <QDir>
#include <QApplication>
#include <QCursor>
#include <QDateTime>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

#ifdef _WIN32
#include <windows.h>
#elif _linux_
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#elif _APPLE_
#include <ApplicationServices/ApplicationServices.h>
#endif

class Functions
{
public:
    Functions();

    long long lasttime;
    int i =0;
    int j =0;
    int y =0;
    int x =0;
    bool keyb;


    bool trackMouse(long long limit) {
#ifdef _WIN32
        // Windows
        POINT cursorPos;
        if (GetCursorPos(&cursorPos)) {
            std::cout << "Mouse position: X=" << cursorPos.x << " Y=" << cursorPos.y << std::endl;
            if(cursorPos.y ==y && cursorPos.x ==x){
                j+=1;
                x =cursorPos.x;
                y =cursorPos.y;
            }else{
                j=0;
                i=0;
                x =cursorPos.x;
                y =cursorPos.y;
                return false;
            }
            if(j>limit){
                j=0;
                return true;
            }else{
                return false;
            }
        }

#elif _linux_
        // Linux
        Display* display = XOpenDisplay(NULL);
        if (display == NULL) {
            std::cerr << "Unable to open X display" << std::endl;
            return;
        }

        Window root = DefaultRootWindow(display);
        int rootX, rootY, winX, winY;
        unsigned int mask;
        Window returnedWindow;
        XQueryPointer(display, root, &returnedWindow, &rootX, &rootY, &winX, &winY, &mask);
        std::cout << "Mouse position: X=" << rootX << " Y=" << rootY << std::endl;

        XCloseDisplay(display);

#elif _APPLE_
        // macOS
        CGEventRef event = CGEventCreate(NULL);
        CGPoint mousePos = CGEventGetLocation(event);
        std::cout << "Mouse position: X=" << mousePos.x << " Y=" << mousePos.y << std::endl;
        CFRelease(event);
#endif
    }

    bool trackKeyboard(long long limit) {
#ifdef _WIN32
        // Windows
        for (int key = 8; key <= 190; key++) {
            if (GetAsyncKeyState(key) & 0x8000) {
                std::cout << "Key pressed: " << key << std::endl;
                keyb = true;
            }
        }
        if(keyb){
            i =0;
            j =0;
            keyb = false;
            return false;
        }else{
            i+=1;
            keyb = false;
        }
        if (i > limit){
            i=0;
            return true;
        }else{
            return false;
        }


#elif _linux_
        // Linux
        Display* display = XOpenDisplay(NULL);
        if (display == NULL) {
            std::cerr << "Unable to open X display" << std::endl;
            return;
        }

        char keys[32];
        XQueryKeymap(display, keys);
        for (int i = 0; i < 256; i++) {
            if (keys[i / 8] & (1 << (i % 8))) {
                std::cout << "Key pressed: " << i << std::endl;
            }
        }

        XCloseDisplay(display);

#elif _APPLE_
        // macOS
        // Note: macOS does not provide a simple way to check all key states like Windows or Linux.
        // You may want to use an external library for more comprehensive key tracking.
        // This is a placeholder for the keyboard tracking code.
        std::cout << "Keyboard tracking on macOS is not implemented in this example." << std::endl;
#endif
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


    std::string GetActiveWindowProcess();


    std::string convertMilliseconds(long long milliseconds) {
        // Calculate the number of hours, minutes, seconds, and milliseconds
        long long hours = milliseconds / (1000 * 60 * 60);
        milliseconds %= (1000 * 60 * 60);
        long long minutes = milliseconds / (1000 * 60);
        milliseconds %= (1000 * 60);
        long long seconds = milliseconds / 1000;
        long long millis = milliseconds % 1000;

        // Create the string using stringstream
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << hours << ":"
           << std::setfill('0') << std::setw(2) << minutes << ":"
           << std::setfill('0') << std::setw(2) << seconds << "."
           << std::setfill('0') << std::setw(3) << millis;

        return ss.str();
    }
    void Check(){
        std::cout<<i<<std::endl;
        std::cout<<j<<std::endl;
    }
public slots:
    void reciveData(long long Lol)
    {
        lasttime = Lol;
    }
};

#endif // FUNCTIONS_H
