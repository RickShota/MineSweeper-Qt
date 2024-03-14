#include "mainwindow.h"
// 主窗口类
MineSweep::MineSweep(QWidget *parent)
    : QMainWindow(parent), centralWd(0), mainView(0), mineScene(0), mineNumLcd(0), timeLcd(0), smileBtn(0), timer(0)
{
    this->setWindowTitle("扫雷");
    this->resize(400,500);
    this->setWindowIcon(QIcon(":/images/bong.png"));

    centralWd = new QWidget(this);
    setCentralWidget(centralWd);

    create_action();
    create_menu();
    slot_newgame();
}

MineSweep::~MineSweep() {}

// 实现行为
void MineSweep::create_action() {
    newGameA = new QAction(tr("新游戏(&N)"), this);
    newGameA->setCheckable(true);
    connect(newGameA, SIGNAL(triggered(bool)), this, SLOT(slot_newgame()));

    lowL = new QAction(tr("初级(&B)"), this);
    lowL->setCheckable(true);
    lowL->setChecked(true);

    midL = new QAction(tr("中级(&M)"), this);
    midL->setCheckable(true);

    heiL = new QAction(tr("高级(&E)"), this);
    heiL->setCheckable(true);

    cusL = new QAction(tr("自定义(&D)"), this);
    cusL->setCheckable(true);
    // 行为组
    QActionGroup *levelGroup = new QActionGroup(this);
    levelGroup->addAction(lowL);
    levelGroup->addAction(midL);
    levelGroup->addAction(heiL);
    levelGroup->addAction(cusL);
    connect(levelGroup, SIGNAL(triggered(QAction*)), this, SLOT(slot_newgamebyleve(QAction*)));

    colorA = new QAction(tr("颜色(&C)"), this);
    colorA->setCheckable(true);
    colorA->setChecked(true);
    connect(colorA, SIGNAL(triggered(bool)), this, SLOT(slot_colorchanged()));

    soundA = new QAction(tr("声音开关(&S)"), this);
    soundA->setCheckable(true);
    soundA->setChecked(true);
    connect(soundA, SIGNAL(triggered(bool)), this, SLOT(slot_soundchanged()));

    heroA = new QAction(tr("历史排行榜(&T)"), this);
    connect(heroA, SIGNAL(triggered(bool)), this, SLOT(slot_herochecked()));

    exitA = new QAction(tr("退出游戏(&X)"), this);
    connect(exitA, SIGNAL(triggered(bool)), this, SLOT(close()));

    aboutA = new QAction(tr("关于(&i)"), this);
    connect(aboutA, SIGNAL(triggered(bool)), this, SLOT(slot_about()));
}

// 创建菜单
void MineSweep::create_menu() {
    QMenuBar *bar = menuBar();
    QMenu *gMenu = bar->addMenu(tr("游戏(&G)"));
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

    QMenu *aMenu = bar->addMenu(tr("帮助(&H)"));
    aMenu->addAction(aboutA);
    this->setMenuBar(bar);
}

// 读当前游戏设置
void MineSweep::readsettings() {}

// 写当前游戏设置
void MineSweep::writesettings() {}

// 开始新游
void MineSweep::slot_newgame() {
    qDebug() << "slot_newgame(): in\n";
    // 清理旧对象
    mineScene->deleteLater();
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::red);
    // LED灯
    mineNumLcd = new QLCDNumber;
    mineNumLcd->setPalette(pa);
    timeLcd = new QLCDNumber;
    timeLcd->setPalette(pa);
    mineNumLcd->display(0);
    timeLcd->display(0);
    // 笑脸按钮
    smileBtn = new QPushButton;
    smileBtn->setFixedSize(30,30);
    smileBtn->setIcon(QIcon(":/images/smile.png"));
    // 水平布局
    QHBoxLayout *hL = new QHBoxLayout;
    hL->addWidget(mineNumLcd);
    hL->addStretch();
    hL->addWidget(smileBtn);
    hL->addStretch();
    hL->addWidget(timeLcd);
    // 主视图>主场景
    mainView = new QGraphicsView;
    mineScene = new MineScene;
    mainView->setScene(mineScene);
    // 垂直布局
    QVBoxLayout *vL = new QVBoxLayout(centralWd);
    vL->addLayout(hL);
    vL->addWidget(mainView);
    qDebug() << "slot_newgame(): layout has done\n";
    // 场景开始信号->开始新游戏槽
    connect(mineScene, SIGNAL(sig_sceneNewGame()),
            this, SLOT(slot_newgame()));
    qDebug() << "slot_newgame(): sig_sceneNewGame\n";
    // 场景显示雷数信号->显示雷数的槽
    connect(mineScene, SIGNAL(sig_scenedisplayMineNum(int)),
            this, SLOT(slot_displayMineNum(int)));
    qDebug() << "slot_newgame(): sig_scenedisplayMineNum\n";
    // 动态设置场景，主视图，主窗口大小
    // mainView->setFixedSize(mineScene->width(), mineScene->height() + hb->sizeHint().height());
    qDebug() << "slot_newgame(): setFixedSize()\n";
    // 定时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MineSweep::slot_displayTime);
    // 初始化场景
    mineScene->initscene();
    // 启动定时器
    // timer->start(100000);
    qDebug() << "slot_newgame(): timer\n";
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

