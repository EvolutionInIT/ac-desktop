#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <locale>
#include <codecvt>

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#pragma warning(disable : 4996)

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
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QDebug>


#include "json.hpp"

#ifdef _WIN32
#include <windows.h>
#elif _linux_
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#elif _APPLE_
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifdef _WIN32
#include <windows.h>  // Windows-specific headers
#elif __linux__
#include <X11/Xlib.h> // Linux-specific headers (X11)
#include <X11/Xutil.h>
#elif __APPLE__
#include <ApplicationServices/ApplicationServices.h> // macOS-specific headers
#endif

class Functions
{
public:
    Functions();


    //JSON Functions
    using json = nlohmann::json;

    void createJsonFile(const std::string& email = "", const std::string& password = "", const std::string& jwtKey = "", const std::string& anotherKey = "") {
        // Get the application's directory path
        QString appDirPath = QCoreApplication::applicationDirPath();

        // Combine the directory path and file name (current date) to form the full path
        std::string filePath = (appDirPath + QDir::separator()).QString::toStdString() + "set" + ".json";
        // Создание JSON-объекта
        json j;
        j["email"] = email;
        j["password"] = password;
        j["jwt_key"] = jwtKey;
        j["another_key"] = anotherKey;

        // Открытие файла для записи
        std::ofstream file(filePath);
        if (file.is_open()) {
            file << j.dump(4);  // Pretty print with indent of 4 spaces
            file.close();
            std::cout << "JSON file created successfully: " << filePath << std::endl;
        } else {
            std::cerr << "Failed to create the JSON file." << std::endl;
        }
    }


    void insertIntoJson(const std::string& key, const std::string& value) {
        // Get the application's directory path
        QString appDirPath = QCoreApplication::applicationDirPath();

        // Combine the directory path and file name (current date) to form the full path
        std::string filePath = (appDirPath + QDir::separator()).QString::toStdString() + "set" + ".json";
        std::ifstream fileIn(filePath);
        if (!fileIn.is_open()) {
            std::cerr << "Could not open file: " << filePath << std::endl;
            return;
        }

        json j;
        fileIn >> j;
        fileIn.close();

        // Insert or update the key-value pair
        j[key] = value;

        // Write the updated JSON back to the file
        std::ofstream fileOut(filePath);
        if (fileOut.is_open()) {
            fileOut << j.dump(4);
            fileOut.close();
            std::cout << "Value inserted/updated successfully." << std::endl;
        } else {
            std::cerr << "Failed to write to the JSON file." << std::endl;
        }
    }

    void deleteFromJson(const std::string& key) {
        // Get the application's directory path
        QString appDirPath = QCoreApplication::applicationDirPath();

        // Combine the directory path and file name (current date) to form the full path
        std::string filePath = (appDirPath + QDir::separator()).QString::toStdString() + "set" + ".json";
        std::ifstream fileIn(filePath);
        if (!fileIn.is_open()) {
            std::cerr << "Could not open file: " << filePath << std::endl;
            return;
        }

        json j;
        fileIn >> j;
        fileIn.close();

        // Check if the key exists, then remove it
        if (j.contains(key)) {
            j.erase(key);

            // Write the updated JSON back to the file
            std::ofstream fileOut(filePath);
            if (fileOut.is_open()) {
                fileOut << j.dump(4);
                fileOut.close();
                std::cout << "Key deleted successfully." << std::endl;
            } else {
                std::cerr << "Failed to write to the JSON file." << std::endl;
            }
        } else {
            std::cerr << "Key not found in the JSON file." << std::endl;
        }
    }

    std::string getValueFromJson(const std::string& key) {
        // Get the application's directory path
        QString appDirPath = QCoreApplication::applicationDirPath();

        // Combine the directory path and file name (current date) to form the full path
        std::string filePath = (appDirPath + QDir::separator()).QString::toStdString() + "set" + ".json";
        // Проверка наличия файла
        std::ifstream fileIn(filePath);
        if (!std::filesystem::exists(filePath)) {
            std::cout << "File not found: " << filePath << std::endl;
            return "";
        }
        else if (!fileIn.is_open()) {
            std::cout << "Failed to open file: " << filePath << std::endl;
            return "";
        }
        else{
            json j;
            fileIn >> j;
            fileIn.close();
            // Возвращаем значение, если ключ существует, иначе пустую строку
            if (j.contains(key)) {
                return j[key].get<std::string>();
            } else {
                return "";
            }
        }
    }


    bool fileExists(const std::string& filePath) {
        std::ifstream file(filePath);
        return file.is_open();
    }














    bool createDatabase() {
        // Check if the connection already exists
        if (QSqlDatabase::contains("my_connection")) {
            QSqlDatabase::removeDatabase("my_connection");
        }

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "my_connection");

        // Get the application's directory path
        QString appDirPath = QCoreApplication::applicationDirPath();

        // Get the current date as a string in the format ddMMyyyy
        QString currentDate = QDateTime::currentDateTime().toString("ddMMyyyy");

        // Combine the directory path and file name (current date) to form the full path
        QString filePath = appDirPath + QDir::separator() + currentDate + ".db";
        db.setDatabaseName(filePath);
        //qDebug()<<filePath;

        if (!db.open()) {
            qDebug() << "Failed to open the database: " << db.lastError().text();
            return false;
        }

        // Create table
        QSqlQuery query(db);
        QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            start_time TEXT NOT NULL,
            end_time TEXT NOT NULL,
            task_id TEXT NOT NULL
        );
    )";

        if (!query.exec(createTableQuery)) {
            qDebug() << "Failed to create the table: " << query.lastError().text();
            return false;
        }

        //qDebug() << "Table created successfully or already exists.";
        db.close();
        return true;
    }

    bool insertIntoTable(const QString& startTime, const QString& endTime, const QString& taskId) {
        // Get the application's directory path
        QString appDirPath = QCoreApplication::applicationDirPath();

        // Get the current date as a string in the format ddMMyyyy
        QString currentDate = QDateTime::currentDateTime().toString("ddMMyyyy");

        // Combine the directory path and file name (current date) to form the full path
        QString filePath = appDirPath + QDir::separator() + currentDate + ".db";

        // Connect to SQLite database
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "tasks_connection");  // Avoid duplicate connection
        db.setDatabaseName(filePath);

        if (!db.open()) {
            qDebug() << "Failed to open the database: " << db.lastError().text();
            return false;
        }

        // Ensure table exists
        QSqlQuery createTableQuery(db);
        QString createTableSql = R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            start_time TEXT NOT NULL,
            end_time TEXT NOT NULL,
            task_id TEXT NOT NULL
        );
    )";

        if (!createTableQuery.exec(createTableSql)) {
            qDebug() << "Failed to create the table: " << createTableQuery.lastError().text();
            db.close();
            return false;
        }

        // Insert data into the table
        QSqlQuery query(db);
        query.prepare("INSERT INTO tasks (start_time, end_time, task_id) VALUES (:start_time, :end_time, :task_id)");
        query.bindValue(":start_time", startTime);
        query.bindValue(":end_time", endTime);
        query.bindValue(":task_id", taskId);

        if (!query.exec()) {
            qDebug() << "Failed to insert data: " << query.lastError().text();
            db.close();
            return false;
        }

        qDebug() << "Data inserted successfully!";
        db.close();  // Close the connection after operation
        return true;
    }

    void readFromTable() {
        // Get the application's directory path
        QString appDirPath = QCoreApplication::applicationDirPath();

        // Get the current date as a string in the format ddMMyyyy
        QString currentDate = QDateTime::currentDateTime().toString("ddMMyyyy");

        // Combine the directory path and file name (current date) to form the full path
        QString filePath = appDirPath + QDir::separator() + currentDate + ".db";

        // Connect to SQLite database
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "tasks_connection");  // Avoid duplicate connection
        db.setDatabaseName(filePath);

        if (!db.open()) {
            qDebug() << "Failed to open the database: " << db.lastError().text();
            return;
        }

        QSqlQuery query(db);
        query.prepare("SELECT id, start_time, end_time, task_id FROM tasks");

        if (!query.exec()) {
            qDebug() << "Failed to read data: " << query.lastError().text();
            db.close();
            return;
        }

        while (query.next()) {
            int id = query.value(0).toInt();
            QString startTime = query.value(1).toString();
            QString endTime = query.value(2).toString();
            QString taskId = query.value(3).toString();

            qDebug() << "ID:" << id << "Start Time:" << startTime << "End Time:" << endTime << "Task ID:" << taskId;
        }

        db.close();  // Close the connection after reading
    }












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
        if(rootY ==y && rootX ==x){
            j+=1;
            x =rootX;
            y =rootY;
        }else{
            j=0;
            i=0;
            x =rootX;
            y =rootY;
            return false;
        }
        if(j>limit){
            j=0;
            return true;
        }else{
            return false;
        }
    }

        XCloseDisplay(display);

#elif _APPLE_
        // macOS
        CGEventRef event = CGEventCreate(NULL);
        CGPoint mousePos = CGEventGetLocation(event);
        std::cout << "Mouse position: X=" << mousePos.x << " Y=" << mousePos.y << std::endl;
        if(cursorPos.y ==y && cursorPos.x ==x){
            j+=1;
            x =mousePos.x;
            y =mousePos.y;
        }else{
            j=0;
            i=0;
            x =mousePos.x;
            y =mousePos.y;
            return false;
        }
        if(j>limit){
            j=0;
            return true;
        }else{
            return false;
        }
    }
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

        XCloseDisplay(display);

#elif _APPLE_
        CGEventRef keyTrackingCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
            // Только для событий нажатия клавиш
            if (type == kCGEventKeyDown) {
                // Получаем код клавиши
                CGKeyCode keyCode = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

                std::cout << "Key pressed: " << keyCode << std::endl;
                keyb = true;  // Фиксируем факт нажатия клавиши
            }

            // Возвращаем событие для продолжения работы системы
            return event;
        }

        // Функция для отслеживания клавиатуры и проверки, прошло ли время без нажатий
        bool trackKeyboard(long long limit) {
            // Если событие клавиатуры обнаружено, сбрасываем счётчик
            if (keyb) {
                i = 0;
                j = 0;
                keyb = false;
                return false;  // Продолжаем отслеживание
            } else {
                i += 1;  // Увеличиваем счётчик при отсутствии клавиш
                keyb = false;
            }

            // Если превышен лимит времени без нажатия клавиш, возвращаем `true`
            if (i > limit) {
                i = 0;
                return true;  // Превышено время ожидания
            } else {
                return false;  // Продолжаем отслеживание
            }
        }

        // Функция для начала отслеживания клавиш
        void startKeyboardTracking() {
            // Создаём фильтр событий для клавиш
            CGEventMask eventMask = (1 << kCGEventKeyDown);

            // Создаём обработчик событий клавиатуры
            CFMachPortRef eventTap = CGEventTapCreate(
                kCGSessionEventTap,         // Перехват событий на уровне сессии
                kCGHeadInsertEventTap,      // Вставляем этот перехват до других обработчиков
                kCGEventTapOptionDefault,   // Обычные параметры
                eventMask,                  // Интересуемся только событиями нажатия клавиш
                keyTrackingCallback,        // Функция обратного вызова
                nullptr                     // Дополнительные данные не передаются
                );

            if (!eventTap) {
                std::cerr << "Не удалось создать обработчик событий." << std::endl;
                exit(1);
            }

            // Запускаем обработчик событий
            CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
            CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
            CGEventTapEnable(eventTap, true);

            std::cout << "Начало отслеживания клавиш..." << std::endl;
            CFRunLoopRun();  // Бесконечный цикл для отслеживания событий
        }
#endif
    }










    void captureScreenshots(const QString &saveDirectory, const QString &fileName = "") {
        // Получаем список всех экранов
        QList<QScreen *> screens = QGuiApplication::screens();
        if (screens.isEmpty()) {
            qWarning("Не удалось получить список экранов!");
            return;
        }

        // Проходим по всем экранам
        for (int i = 0; i < screens.size(); ++i) {
            QScreen *screen = screens[i];
            if (!screen) {
                qWarning() << "Не удалось получить экран" << i;
                continue;
            }

            // Делаем скриншот текущего экрана
            QPixmap screenshot = screen->grabWindow(0);

            // Если имя файла не предоставлено, создаём имя по умолчанию с использованием текущего времени и индекса экрана
            QString finalFileName;
            if (fileName.isEmpty()) {
                QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
                finalFileName = QString("screenshot_%1_screen%2.png").arg(timestamp).arg(i + 1);
            } else {
                // Добавляем индекс экрана к имени файла, если оно задано
                finalFileName = fileName.endsWith(".png") ? fileName : fileName + ".png";
                finalFileName = finalFileName.insert(finalFileName.lastIndexOf(".png"), QString("_screen%1").arg(i + 1));
            }

            // Полный путь для сохранения скриншота
            QString fullPath = saveDirectory + "/" + finalFileName;

            // Сохраняем скриншот
            if (!screenshot.save(fullPath)) {
                qWarning() << "Не удалось сохранить скриншот экрана" << i + 1;
            } else {
                qDebug() << "Скриншот экрана" << i + 1 << "сохранён в:" << fullPath;
            }
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










    std::string getCurrentTime() {
        std::time_t t1 = std::time(nullptr);
        std::tm t = *localtime(&t1);
        std::stringstream ss;
        ss << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec;
        return ss.str();
    }


    void getActiveWindowID() {
        createDatabase();
        static std::string previousWindowID;
        static std::string previousWindowStartTime;

        std::string windowID;
        std::string currentTime = getCurrentTime(); // Текущее время

#ifdef _WIN32
        HWND hwnd = GetForegroundWindow();
        if (hwnd) {
            std::stringstream ss;
            ss << hwnd;
            windowID = ss.str();

            // Если окно изменилось
            if (windowID != previousWindowID) {
                std::string endTime = currentTime; // Время окончания активности предыдущего окна
                insertIntoTable(QString::fromStdString(previousWindowStartTime), QString::fromStdString(endTime), QString::fromStdString(previousWindowID));
                // Обновляем предыдущее окно и время начала его активности
                std::cout << previousWindowID << std::endl;
                previousWindowID = windowID;
                previousWindowStartTime = getCurrentTime();
            }
        } else {
            std::cout << "No active window found" << std::endl;
        }

#elif __linux__
        Display* display = XOpenDisplay(nullptr);
        if (!display) {
            std::cerr << "Unable to open X display" << std::endl;
            return;
        }

        Window rootWindow = XDefaultRootWindow(display);
        Window activeWindow;
        int revert;
        XGetInputFocus(display, &activeWindow, &revert);

        std::stringstream ss;
        ss << activeWindow;
        windowID = ss.str();

        if (windowID != previousWindowID) {
            std::string endTime = currentTime;
            insertIntoTable(QString::fromStdString(previousWindowStartTime), QString::fromStdString(endTime), QString::fromStdString(previousWindowID));
            previousWindowID = windowID;
            previousWindowStartTime = currentTime;
        }

        XCloseDisplay(display);

#elif __APPLE__
        CFArrayRef windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
        if (windowList == nullptr) {
            std::cerr << "Unable to get window list" << std::endl;
            return;
        }

        for (CFIndex i = 0; i < CFArrayGetCount(windowList); i++) {
            CFDictionaryRef windowInfo = (CFDictionaryRef)CFArrayGetValueAtIndex(windowList, i);
            int32_t windowIDNum;
            CFNumberRef windowIDRef = (CFNumberRef)CFDictionaryGetValue(windowInfo, kCGWindowNumber);

            if (windowIDRef) {
                CFNumberGetValue(windowIDRef, kCFNumberSInt32Type, &windowIDNum);
                windowID = std::to_string(windowIDNum);

                if (windowID != previousWindowID) {
                    std::string endTime = currentTime;
                    insertIntoTable(QString::fromStdString(previousWindowStartTime), QString::fromStdString(endTime), QString::fromStdString(previousWindowID));
                    previousWindowID = windowID;
                    previousWindowStartTime = currentTime;
                }
            }
        }

        CFRelease(windowList);
#endif
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
