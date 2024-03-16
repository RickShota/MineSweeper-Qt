/**
 * @file mainwindow.h
 * @brief 主程序窗口头文件
 * @author RickRone
 * @date 2024.3.14
 * @version Qt 6.6.2
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.h"
#include "minescene.h"
#include "herodialog.h"
#include "customgamedialog.h"

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
    // QPoint m_dragPosition; // 鼠标位置

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
    void readsettings(); // 读当前游戏设置
    void writesettings(); // 写当前游戏设置

    // void wheelEvent(QWheelEvent *event) override;
    // void mousePressEvent(QMouseEvent *event) override;
    // void mouseMoveEvent(QMouseEvent *event) override;
    // void mouseDoubleClickEvent(QMouseEvent *event) override;

public slots:
    void slot_newgame(); // 开始新游戏槽
    void slot_newgamebyleve(QAction *); // 点击游戏级别行为开始新游戏槽
    void slot_acceptCutsomvale(int,int,int); // 接收自定义游戏设置槽
    // void slot_colorchanged(); // 设置颜色的槽
    void slot_soundchanged(); // 设置声音的槽
    void slot_herochecked(); // 显示英雄榜的槽
    void slot_about(); // 显示about扫雷的槽
    void slot_updatehero(); // 更新英雄榜的槽
    void slot_displayMineNum(int); // 显示雷数的槽
    void slot_displayTime(); // 显示时间的槽

};
#endif // MAINWINDOW_H
