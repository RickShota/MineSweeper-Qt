/**
 * @file mainwindow.cpp
 * @brief 主程序窗口源文件
 * @author RickRone
 * @date 2024.3.14
 * @version Qt 6.6.2
 */
#include "mainwindow.h"

MineSweep::MineSweep(QWidget *parent)
    : QMainWindow(parent), centralWd(0), mainView(0), mineScene(0), mineNumLcd(0), timeLcd(0), smileBtn(0), timer(0)
{
    this->setWindowTitle("扫雷");
    this->setWindowIcon(QIcon(":/images/R-C.png"));

    create_action();
    create_menu();
    slot_newgame();
}

MineSweep::~MineSweep() {
    if(timer) {
        timer->stop();
        delete timer;
    }
}

// 实现行为
void MineSweep::create_action() {
    newGameA = new QAction(tr("开局(&N)"), this);
    // newGameA->setCheckable(true);
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

    // colorA = new QAction(tr("颜色(&C)"), this);
    // colorA->setCheckable(true);
    // colorA->setChecked(true);
    // connect(colorA, SIGNAL(triggered(bool)), this, SLOT(slot_colorchanged()));

    soundA = new QAction(tr("声音(&S)"), this);
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
    // gMenu->addAction(colorA);
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
void MineSweep::readsettings() {
    QSettings settings("MineSweeper","0314");
    settings.beginGroup("currentleve");
    // 默认值为low
    mineScene->m_crrentLeve = settings.value("currentleve", LOW_LEVE).toInt();
    mineScene->m_sceneRow = settings.value("m_scenerow",L_RC).toInt();
    mineScene->m_sceneCol = settings.value("m_scenecol",L_RC).toInt();
    mineScene->m_mineNum = settings.value("currentminesum",L_MINENUM).toInt();
    settings.endGroup();

    settings.beginGroup("sound");
    mineScene->m_soundOpen = settings.value("soundOpen", true).toBool();
    settings.endGroup();
    // 根据读取的声音设置更新声音操作状态
    soundA->setCheckable(true);
    soundA->setChecked(mineScene->m_soundOpen);
}

// 写当前游戏设置
void MineSweep::writesettings() {
    QSettings settings ("MineSweeper","0314");
    settings.beginGroup("currentleve");
    settings.setValue("currentleve", mineScene->m_crrentLeve);
    settings.setValue("m_scenerow", mineScene->m_sceneRow);
    settings.setValue("m_scenecol", mineScene->m_sceneCol);
    settings.setValue("currentminesum", mineScene->m_mineNum);
    settings.endGroup();
}

// 开始新游
void MineSweep::slot_newgame() {
    // 清理旧对象
    if(centralWd)
        centralWd->deleteLater();
    if(mainView)
        mainView->deleteLater();
    if(mineScene)
        mineScene->deleteLater();
    if(mineNumLcd)
        mineNumLcd->deleteLater();
    if(timeLcd)
        timeLcd->deleteLater();
    if(smileBtn)
        smileBtn->deleteLater();
    if(timer) {
        timer->stop();
        timer->deleteLater();
    }
    // 创建主界面
    centralWd = new QWidget(this);
    setCentralWidget(centralWd);
    // LED灯
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::red);
    mineNumLcd = new QLCDNumber;
    mineNumLcd->setPalette(pa);
    timeLcd = new QLCDNumber;
    timeLcd->setPalette(pa);
    // 笑脸按钮
    smileBtn = new QPushButton;
    smileBtn->setFixedSize(30,30);
    smileBtn->setIcon(QIcon(":/images/smile.png"));
    connect(smileBtn, SIGNAL(clicked(bool)), this, SLOT(slot_newgame()));
    // 水平布局
    QHBoxLayout *hL = new QHBoxLayout;
    hL->addWidget(mineNumLcd);
    hL->addStretch();
    hL->addWidget(smileBtn);
    hL->addStretch();
    hL->addWidget(timeLcd);
    // 主窗口>主视图>主场景
    mainView = new QGraphicsView;
    mineScene = new MineScene;
    mainView->setScene(mineScene);
    // 读取状态
    this->readsettings();
    if(mineScene->m_soundOpen) {
        playSound(":/sounds/start.wav");
    }
    // qDebug() << "slot_newgame() readsettingsOK";
    // 垂直布局
    QVBoxLayout *vL = new QVBoxLayout(centralWd);
    vL->addLayout(hL);
    vL->addWidget(mainView);
    // 场景开始信号->开始新游戏槽
    connect(mineScene, &MineScene::sig_sceneNewGame, this, &MineSweep::slot_newgame);
    // 场景显示雷数信号->显示雷数的槽
    connect(mineScene, &MineScene::sig_scenedisplayMineNum, this, &MineSweep::slot_displayMineNum);
    // 成功过关信号->更新英雄榜的槽
    connect(mineScene, &MineScene::sig_successPassGame, this, &MineSweep::slot_updatehero);
    // 游戏级别
    if(mineScene->m_crrentLeve == LOW_LEVE)
        lowL->setChecked(true);
    else if(mineScene->m_crrentLeve == MIDDLE_LEVE)
        midL->setChecked(true);
    else if(mineScene->m_crrentLeve == HEIGHT_LEVE)
        heiL->setChecked(true);
    else if(mineScene->m_crrentLeve == CUSOM_LEVE)
        cusL->setChecked(true);
    // 动态调整布局
    int autoW = mineScene->m_sceneCol * MAP_W;
    int autoH = mineScene->m_sceneRow * MAP_H;
    mineScene->setSceneRect(0, 0, autoW, autoH);
    mainView->setFixedSize(autoW + 5, autoH + 5);
    this->setFixedSize(autoW + 25, autoH + 80);
    // 初始化LCD
    use_time = 0;
    mineNumLcd->display(mineScene->m_mineNum);
    timeLcd->display(use_time);
    // 定时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MineSweep::slot_displayTime);
    // 初始化场景
    mineScene->initscene();
    // 启动定时器
    timer->start(1000);
}
// 点击游戏级别行为开始新游戏
void MineSweep::slot_newgamebyleve(QAction *act) {
    if (act == lowL) {
        mineScene->m_sceneCol = L_RC;
        mineScene->m_sceneRow = L_RC;
        mineScene->m_mineNum = L_MINENUM;
        mineScene->m_crrentLeve = LOW_LEVE;
    } else if (act == midL) {
        mineScene->m_sceneCol = M_RC;
        mineScene->m_sceneRow = M_RC;
        mineScene->m_mineNum = M_MINENUM;
        mineScene->m_crrentLeve = MIDDLE_LEVE;
    } else if (act == heiL) {
        mineScene->m_sceneCol = H_RC;
        mineScene->m_sceneRow = H_RC;
        mineScene->m_mineNum = H_MINENUM;
        mineScene->m_crrentLeve = HEIGHT_LEVE;
    } else if (act == cusL) {
        CustomGameDialog *custom = new CustomGameDialog(this);
        this->connect(custom, &CustomGameDialog::signal_sendCustomset, this, &MineSweep::slot_acceptCutsomvale);
        custom->exec();
    }
    // 写入到注册表
    this->writesettings();
    // 开始新游戏
    this->slot_newgame();
}
// 接收自定义游戏设置
void MineSweep::slot_acceptCutsomvale(int row, int col ,int mine) {
    mineScene->m_crrentLeve = CUSOM_LEVE;
    mineScene->m_sceneRow = row;
    mineScene->m_sceneCol = col;
    mineScene->m_mineNum = mine;
    // 写入到注册表
    this->writesettings();
    // 开始新游戏
    this->slot_newgame();
}
// 设置颜色
// void MineSweep::slot_colorchanged() { }
// 设置声音
void MineSweep::slot_soundchanged() {
    this->mineScene->m_soundOpen = !mineScene->m_soundOpen;
    soundA->setChecked(mineScene->m_soundOpen);
    QSettings settings ("MineSweeper","0314");
    settings.beginGroup("sound");
    settings.setValue("soundOpen", mineScene->m_soundOpen);
    settings.endGroup();
    this->update();
}
// 显示英雄榜
void MineSweep::slot_herochecked() {
    HeroDialog heroD(this);
    heroD.exec();
}
// 显示about扫雷
void MineSweep::slot_about() {
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("关于扫雷");
    QPixmap pixmap(":/images/R-C.png");
    QIcon icon(pixmap.scaled(64, 64, Qt::KeepAspectRatio));
    msgBox->setIconPixmap(icon.pixmap(QSize(64, 64)));


    QString detail = tr("<p style='font-size: 14px; font-weight: bold;'>游戏名称: 扫雷</p>"
                        "<p style='font-size: 12px;'>游戏版本: 1.0.1</p>"
                        "<p style='font-size: 12px;'>游戏作者: RickRone</p>"
                        "<p style='font-size: 12px;'>Qt版本: 6.6.2</p>"
                        "<p style='font-size: 12px;'>发布日期: 2024.3.14</p>");
    msgBox->setText(detail);
    msgBox->setStyleSheet("QLabel { width: 300px; height: 100px}");
    msgBox->show();
}
// 更新英雄榜的槽
void MineSweep::slot_updatehero() {
    QSettings settings("MineSweeper", "0314");
    int recordTime = 999;
    QString newname;
    switch (mineScene->m_crrentLeve) {
    case LOW_LEVE:
        settings.beginGroup("hero");
        recordTime = settings.value("lowrecordtimelabel", 999).toInt();
        settings.endGroup();
        if(use_time < recordTime) {
            bool ok = true;
            newname = QInputDialog::getText(this, tr("新纪录"), "破纪录了！敢问阁下尊姓大名: " ,QLineEdit::Normal, "姓名", &ok);
            if(ok) {
                settings.beginGroup("hero");
                settings.setValue("lowrecordtimelabel", use_time);
                settings.setValue("low_name", newname);
                settings.endGroup();
            }
        }
        break;
    case MIDDLE_LEVE:
        settings.beginGroup("hero");
        recordTime = settings.value("middlerecordtimelabel", 999).toInt();
        settings.endGroup();
        if(use_time<recordTime) {
            bool ok;
            newname = QInputDialog::getText(this,tr("新纪录"),"破纪录了！敢问阁下尊姓大名: ",QLineEdit::Normal,"匿名",&ok);
            if(ok) {
                settings.beginGroup("hero");
                settings.setValue("middlerecordtimelabel",use_time);
                settings.setValue("middle_name",newname);
                settings.endGroup();
            }
        }
        break;
    case HEIGHT_LEVE:
        settings.beginGroup("hero");
        recordTime = settings.value("heightrecordtimelabel", 999).toInt();
        settings.endGroup();
        if(use_time<recordTime) {
            bool ok;
            newname = QInputDialog::getText(this,tr("新纪录"),"破纪录了！敢问阁下尊姓大名: ",QLineEdit::Normal,"姓名",&ok);
            if(ok) {
                settings.beginGroup("hero");
                settings.setValue("heightrecordtimelabel",use_time);
                settings.setValue("height_name", newname);
                settings.endGroup();
            }
        }
        break;
    case CUSOM_LEVE:
        settings.beginGroup("hero");
        recordTime = settings.value("minerecordtimelabel", 999).toInt();
        settings.endGroup();
        if(use_time<recordTime) {
            bool ok;
            newname = QInputDialog::getText(this,tr("新纪录"),"破纪录了！敢问阁下尊姓大名: ",QLineEdit::Normal,"姓名",&ok);
            if(ok) {
                settings.beginGroup("hero");
                settings.setValue("minerecordtimelabel",use_time);
                settings.setValue("mine_name",newname);
                settings.endGroup();
            }
        }
        break;
    }

    // 显示信息,游戏结束,是否继续,继续重新开始,取消则关闭游戏
    auto ret = QMessageBox::question(this,"游戏结束","游戏结束，是否继续?",QMessageBox::Ok,QMessageBox::Cancel);
    if(ret == QMessageBox::Ok)
        slot_newgame();
    else
        this->close();
}
// 显示雷数的槽
void MineSweep::slot_displayMineNum(int num) {
    mineNumLcd->display(mineScene->m_mineNum - num);
}
// 显示时间的槽
void MineSweep::slot_displayTime() {
    if(!mineScene->m_isGameOver) {
        this->use_time++;
        this->timeLcd->display(use_time);
        if(mineScene->m_soundOpen && soundA->isChecked())
            playSound(":/sounds/time.wav");
    } else {
        timer->stop();
    }
}

