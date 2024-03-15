#include "herodialog.h"
// 排行榜类
HeroDialog::HeroDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle("英雄榜");
    this->setWindowIcon(QIcon(":/images/flag.png"));

    QLabel *name1 = new QLabel("初级");
    QLabel *name2 = new QLabel("中级");
    QLabel *name3 = new QLabel("高级");
    QLabel *name4 = new QLabel("自定义");

    lowrecordtimelabel = new QLabel("0"); //初级纪录时间
    middlerecordtimelabel = new QLabel("0"); //中级纪录时间
    heightrecordtimelabel = new QLabel("0"); //高级纪录时间
    minerecordtimelabel = new QLabel("0");

    lowrecordnamelabel = new QLabel("匿名"); //初级纪录姓名
    middlerecordnamelabel = new QLabel("匿名"); //中级纪录姓名
    heightrecordnamelabel = new QLabel("匿名"); //高级纪录姓名
    minerecordnamelabel = new QLabel("匿名");

    QPushButton *button1 = new QPushButton("清 空");
    this->connect(button1,SIGNAL(clicked(bool)),this,SLOT(slot_reset()));
    QPushButton *button2 = new QPushButton("取 消");
    this->connect(button2,SIGNAL(clicked(bool)),this,SLOT(close()));

    QGridLayout *glayout = new QGridLayout;
    glayout->addWidget(name1,0,0);
    glayout->addWidget(lowrecordtimelabel,0,1);
    glayout->addWidget(name2,1,0);

    glayout->addWidget(middlerecordtimelabel,1,1);
    glayout->addWidget(name3,2,0);
    glayout->addWidget(heightrecordtimelabel,2,1);
    glayout->addWidget(name4,3,0);

    glayout->addWidget(minerecordtimelabel,3,1);
    glayout->addWidget(lowrecordnamelabel,0,2);
    glayout->addWidget(middlerecordnamelabel,1,2);
    glayout->addWidget(heightrecordnamelabel,2,2);

    glayout->addWidget(minerecordnamelabel,3,2);

    //水平
    QHBoxLayout *hblayout = new QHBoxLayout;
    hblayout->addWidget(button1);
    hblayout->addStretch();
    hblayout->addWidget(button2);

    //垂直
    QVBoxLayout *vblayout = new QVBoxLayout(this);
    vblayout->addLayout(glayout);
    vblayout->addLayout(hblayout);
    this->readSettings(); //执行readsettings
}

void HeroDialog::readSettings()
{
    QSettings *settings = new QSettings("MineSweeper","0314", this);
    // 将读取到的数据设置到相应的分量框
    settings->beginGroup("hero");
    int low_time = settings->value("lowrecordtimelabel", "0").toInt();
    int middle_time = settings->value("middlerecordtimelabel", "0").toInt();
    int height_time = settings->value("heightrecordtimelabel", "0").toInt();
    int mine_time = settings->value("minerecordtimelabel", "0").toInt();
    QString low_name = settings->value("low_name", "匿名").toString();
    QString middle_name = settings->value("middle_name", "匿名").toString();
    QString height_name = settings->value("height_name", "匿名").toString();
    QString mine_name = settings->value("mine_name", "匿名").toString();
    settings->endGroup();

    //更新数据
    lowrecordtimelabel->setText(QString::number(low_time));
    middlerecordtimelabel->setText(QString::number(middle_time));
    heightrecordtimelabel->setText(QString::number(height_time));
    minerecordtimelabel->setText(QString::number(mine_time));

    lowrecordnamelabel->setText(low_name);
    middlerecordnamelabel->setText(middle_name);
    heightrecordnamelabel->setText(height_name);
    minerecordnamelabel->setText(mine_name);
}


void HeroDialog::initHeroRecord()
{
    lowrecordtimelabel->setText(QString().setNum(0));
    middlerecordtimelabel->setText(QString().setNum(0));
    heightrecordtimelabel->setText(QString().setNum(0));
    minerecordnamelabel->setText(QString().setNum(0));

    lowrecordnamelabel->setText("匿名");
    middlerecordnamelabel->setText("匿名");
    heightrecordnamelabel->setText("匿名");
    minerecordnamelabel->setText("匿名");
}


void HeroDialog::slot_reset()
{
    //创建一个QSettings对象，并指定配置文件路径和应用程序名称作为参数。
    QSettings settings("MineSweeper","0314");
    //调用beginGroup()函数指定配置文件中的组名为"hero"
    settings.beginGroup("hero");

    //通过setValue()函数将低级别、中级别、高级别的最短用时设置为999，并将对应的玩家姓名设置为"匿名"。
    settings.setValue("lowrecordtimelabel", 0);
    settings.setValue("middlerecordtimelabel", 0);
    settings.setValue("heightrecordtimelabel", 0);
    settings.setValue("minerecordtimelabel", 0);

    settings.setValue("low_name","匿名");
    settings.setValue("middle_name","匿名");
    settings.setValue("height_name","匿名");
    settings.setValue("mine_name","匿名");

    settings.endGroup();
    this->readSettings();
}
