#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.h"
#include <QMainWindow>
#include "minescene.h"

class MineSweep : public QMainWindow
{
    Q_OBJECT

public:
    MineSweep(QWidget *parent = nullptr);
    ~MineSweep();

    QWidget *centralWd; // 主程序界面
    QGraphicsView *mainView; // 主视图
    MineScene *mineScene; // 主场景
    QLCDNumber *mineNumLcd; // 雷数
    QLCDNumber *timeLcd; // 倒计时
    QPushButton *smileBtn; // 笑脸按钮
    int use_time; // 当前用时数
    QTimer *timer; // 定时器

    QAction *newGameA;
    QAction *lowL;
    QAction *midL;
    QAction *heiL;
    QAction *cusL;
    QAction *colorA;
    QAction *soundA;
    QAction *heroA;
    QAction *exitA;
    QAction *aboutA;

    void create_action(); // 创建行为
    void create_menu(); // 创建菜单

};
#endif // MAINWINDOW_H
