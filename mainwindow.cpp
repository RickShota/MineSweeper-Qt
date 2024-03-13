#include "mainwindow.h"
// 主窗口类
MineSweep::MineSweep(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("扫雷");
    this->resize(500,500);
    this->setWindowIcon(QIcon(":/images/bong.png"));

    centralWd = new QWidget;
    this->setCentralWidget(centralWd);

    create_action();
    create_menu();

}

MineSweep::~MineSweep() {}

// 创建菜单
void MineSweep::create_menu() {
    QMenuBar *bar = menuBar();
    QMenu *gMenu = bar->addMenu("游戏");
    gMenu->addAction(newGameA);
    gMenu->addSeparator();
    gMenu->addAction(lowL);
    gMenu->addAction(midL);
    gMenu->addAction(heiL);
    gMenu->addAction(cusL);
    QMenu *aMenu = bar->addMenu("帮助");
    aMenu->addAction("关于此游戏");
    aMenu->addAction("关于Qt");
    this->setMenuBar(bar);
}
// 实现菜单功能
void MineSweep::create_action() {
    newGameA = new QAction("新游戏", this);
    newGameA->setShortcut(tr("ctrl+n"));
    lowL = new QAction("低难度");
    midL = new QAction("中等难度");
    heiL = new QAction("高难度");
    cusL = new QAction("地狱难度");
    colorA = new QAction("");
    soundA = new QAction("声音");
    heroA = new QAction("历史排行榜");
    exitA = new QAction("退出");
    aboutA = new QAction("关于");
}
