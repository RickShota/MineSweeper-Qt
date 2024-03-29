/**
 * @file common.h
 * @brief 包含了常用的函数和工具类，用于提供一些通用的功能
 * @author RickRone
 * @date 2024.3.14
 * @version Qt 6.6.2
 */
#ifndef COMMON_H
#define COMMON_H

#include <QSoundEffect>
#include <QDialog>
#include <QInputDialog>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QAction>
#include <QActionGroup>
#include <QWidget>
#include <QGraphicsView>
#include <QLCDNumber>
#include <QPushButton>
#include <QTimer>
#include <QVector>
#include <QPoint>
#include <QSpinBox>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <signal.h>
#include <time.h>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMainWindow>
#include <QSettings>


// 难度级别
enum gameLeve {
    LOW_LEVE = 0,
    MIDDLE_LEVE = 1,
    HEIGHT_LEVE = 2,
    CUSOM_LEVE = 3,
};
enum lowSet {
    L_RC = 9, // 行列
    L_MINENUM = 10, // 雷数
};
enum middleSet {
    M_RC = 16, // 行列
    M_MINENUM = 40, // 雷数
};
enum heightSet {
    H_RC = 25, // 行列
    H_MINENUM = 80, // 雷数
};
enum cusomSet {
    C_RC = 9, // 行列
    C_MINENUM = 10, // 雷数
};
// 图片大小
enum mapSet {
    MAP_W = 25,
    MAP_H = 25,
};

// 加载声音
inline void playSound(const QString &path) {
    static QSoundEffect sound;
    sound.setSource(QUrl::fromLocalFile(path));
    sound.play();
}

#endif // COMMON_H
