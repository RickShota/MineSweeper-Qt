/**
 * @file main.cpp
 * @brief 程序入口文件
 * @author RickRone
 * @date 2024.3.13
 * @version Qt 6.6.2
 */
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MineSweep w;
    w.show();
    return a.exec();
}
