#include "mainwindow.h"
// 主窗口类
MineSweep::MineSweep(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("扫雷");
    this->resize(400,500);
    this->setWindowIcon(QIcon(":/images/bong.png"));

    centralWd = new QWidget(this);
    setCentralWidget(centralWd);
    // LED灯+按钮
    mineNumLcd = new QLCDNumber;
    mineNumLcd->setStyleSheet("QLCDNumber { color: red; }");
    timeLcd = new QLCDNumber;
    timeLcd->setStyleSheet("QLCDNumber { color: red; }");
    smileBtn = new QPushButton;
    smileBtn->setFixedSize(30,30);
    smileBtn->setIcon(QIcon(":/images/smile.png"));
    // 水平布局
    QHBoxLayout *hb = new QHBoxLayout;
    hb->addWidget(mineNumLcd);
    hb->addStretch();
    hb->addWidget(smileBtn);
    hb->addStretch();
    hb->addWidget(timeLcd);
    // 游戏区
    mainView = new QGraphicsView;
    mineScene = new MineScene(this);
    mainView->setScene(mineScene);
    // 垂直布局
    QVBoxLayout *vb = new QVBoxLayout(centralWd);
    vb->addLayout(hb);
    vb->addWidget(mainView);

    timer = new QTimer(this);

    create_action();
    create_menu();
    // slot_newgame();
}

MineSweep::~MineSweep() {}

// 实现菜单功能
void MineSweep::create_action() {
    newGameA = new QAction(tr("新游戏"), this);
    newGameA->setShortcut(tr("ctrl+n"));
    connect(newGameA, SIGNAL(triggered(bool)), this, SLOT(slot_newgame()));

    lowL = new QAction(tr("低难度"), this);
    lowL->setCheckable(true);
    lowL->setChecked(true);

    midL = new QAction(tr("中等难度"), this);
    midL->setCheckable(true);

    heiL = new QAction(tr("高难度"), this);
    heiL->setCheckable(true);

    cusL = new QAction(tr("自定义难度"), this);
    cusL->setCheckable(true);

    QActionGroup *levelGroup = new QActionGroup(this);
    levelGroup->addAction(lowL);
    levelGroup->addAction(midL);
    levelGroup->addAction(heiL);
    levelGroup->addAction(cusL);
    connect(levelGroup, SIGNAL(triggered(QAction*)), this, SLOT(slot_newgamebyleve(QAction*)));

    colorA = new QAction(tr("颜色开关"), this);
    colorA->setCheckable(true);
    colorA->setChecked(true);
    connect(colorA, SIGNAL(triggered(bool)), this, SLOT(slot_colorchanged()));

    soundA = new QAction(tr("声音开关"), this);
    soundA->setCheckable(true);
    soundA->setChecked(true);
    connect(soundA, SIGNAL(triggered(bool)), this, SLOT(slot_soundchanged()));

    heroA = new QAction(tr("历史排行榜"), this);
    heroA->setShortcut(tr("ctrl+h"));
    connect(heroA, SIGNAL(triggered(bool)), this, SLOT(slot_herochecked()));

    exitA = new QAction(tr("退出游戏"), this);
    exitA->setShortcut(tr("ctrl+q"));
    connect(exitA, SIGNAL(triggered(bool)), this, SLOT(close()));

    aboutA = new QAction(tr("关于"), this);
    aboutA->setShortcut(tr("ctrl+i"));
    connect(aboutA, SIGNAL(triggered(bool)), this, SLOT(slot_about()));
}

// 创建菜单
void MineSweep::create_menu() {
    QMenuBar *bar = menuBar();
    QMenu *gMenu = bar->addMenu(tr("游戏(G)"));
    gMenu->addAction(newGameA);
    gMenu->addSeparator();
    gMenu->addAction(lowL);
    gMenu->addAction(midL);
    gMenu->addAction(heiL);
    gMenu->addAction(cusL);
    gMenu->addSeparator();
    gMenu->addAction(colorA);
    gMenu->addAction(soundA);
    gMenu->addSeparator();
    gMenu->addAction(heroA);
    gMenu->addSeparator();
    gMenu->addAction(exitA);

    QMenu *aMenu = bar->addMenu(tr("帮助(H)"));
    aMenu->addAction(aboutA);
    this->setMenuBar(bar);
}

// 读当前游戏设置
void MineSweep::readsettings() {}

// 写当前游戏设置
void MineSweep::writesettings() {}

// 开始新游
void MineSweep::slot_newgame() {

}
// 点击游戏级别行为开始新游戏
void MineSweep::slot_newgamebyleve(QAction *) {

}
// 接收自定义游戏设置
void MineSweep::slot_acceptCutsomvale(int,int,int) {
}
// 设置颜色
void MineSweep::slot_colorchanged() {
}
// 设置声音
void MineSweep::slot_soundchanged() {
}
// 显示英雄榜
void MineSweep::slot_herochecked() {
}
// 显示about扫雷
void MineSweep::slot_about() {
    QMessageBox::aboutQt(this,"关于");
}
// 更新英雄榜的槽
void MineSweep::slot_updatehero() {
}
// 显示雷数的槽
void MineSweep::slot_displayMineNum(int) {
}
// 显示时间的槽
void MineSweep::slot_displayTime() {
}

