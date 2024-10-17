#include "mainwindow.h"
#include "functions.h"


#include <QApplication>



int main(int argc, char *argv[]) {
    // Запуск потоков для отслеживания событий и анализа данных
    QApplication a(argc, argv);
    Functions func;
    MainWindow w;
    w.show();

    // Поток для анализа
    // Ожидание завершения потоков (в данном примере они бесконечны, поэтому не завершатся)
    return a.exec();
}
