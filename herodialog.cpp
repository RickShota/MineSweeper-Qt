#include "herodialog.h"
// 排行榜类
HeroDialog::HeroDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle("历史最佳");
    this->setWindowIcon(QIcon(":/images/flag.png"));
    this->resize(300, 200);

    QLabel *name1 = new QLabel("初  级");
    QLabel *name2 = new QLabel("中  级");
    QLabel *name3 = new QLabel("高  级");
    QLabel *name4 = new QLabel("自定义");

    lowrecordtimelabel = new QLabel("999"); //初级纪录时间
    middlerecordtimelabel = new QLabel("999"); //中级纪录时间
    heightrecordtimelabel = new QLabel("999"); //高级纪录时间
    minerecordtimelabel = new QLabel("999");

    lowrecordnamelabel = new QLabel("xxx"); //初级纪录姓名
    middlerecordnamelabel = new QLabel("xxx"); //中级纪录姓名
    heightrecordnamelabel = new QLabel("xxx"); //高级纪录姓名
    minerecordnamelabel = new QLabel("xxx");

    QPushButton *button1 = new QPushButton("清 空");
    this->connect(button1,SIGNAL(clicked(bool)),this,SLOT(slot_reset()));
    QPushButton *button2 = new QPushButton("取 消");
    this->connect(button2,SIGNAL(clicked(bool)),this,SLOT(close()));

    auto font = QFont("微软雅黑", 13, 10);
    QLabel *head1 = new QLabel("难  度");
    head1->setFont(font);
    QLabel *head2 = new QLabel("成绩（秒）");
    head2->setFont(font);
    QLabel *head3 = new QLabel("玩  家");
    head3->setFont(font);

    head1->setAlignment(Qt::AlignCenter);
    head2->setAlignment(Qt::AlignCenter);
    head3->setAlignment(Qt::AlignCenter);
    name1->setAlignment(Qt::AlignCenter);
    lowrecordtimelabel->setAlignment(Qt::AlignCenter);
    lowrecordnamelabel->setAlignment(Qt::AlignCenter);
    name2->setAlignment(Qt::AlignCenter);
    middlerecordtimelabel->setAlignment(Qt::AlignCenter);
    middlerecordnamelabel->setAlignment(Qt::AlignCenter);
    name3->setAlignment(Qt::AlignCenter);
    heightrecordtimelabel->setAlignment(Qt::AlignCenter);
    heightrecordnamelabel->setAlignment(Qt::AlignCenter);
    name4->setAlignment(Qt::AlignCenter);
    minerecordtimelabel->setAlignment(Qt::AlignCenter);
    minerecordnamelabel->setAlignment(Qt::AlignCenter);

    QGridLayout *glayout = new QGridLayout;
    glayout->addWidget(head1, 0, 0);
    glayout->addWidget(head2, 0, 1);
    glayout->addWidget(head3, 0, 2);

    glayout->addWidget(name1, 1, 0);
    glayout->addWidget(lowrecordtimelabel,1,1);
    glayout->addWidget(lowrecordnamelabel,1,2);

    glayout->addWidget(name2, 2, 0);
    glayout->addWidget(middlerecordtimelabel,2,1);
    glayout->addWidget(middlerecordnamelabel,2,2);

    glayout->addWidget(name3, 3, 0);
    glayout->addWidget(heightrecordtimelabel,3,1);
    glayout->addWidget(heightrecordnamelabel,3,2);

    glayout->addWidget(name4, 4, 0);
    glayout->addWidget(minerecordtimelabel,4,1);
    glayout->addWidget(minerecordnamelabel,4,2);

    // 水平
    QHBoxLayout *hblayout = new QHBoxLayout;
    hblayout->addWidget(button1);
    hblayout->addStretch();
    hblayout->addWidget(button2);

    // 垂直
    QVBoxLayout *vblayout = new QVBoxLayout(this);
    vblayout->addLayout(glayout);
    vblayout->addLayout(hblayout);
    this->readSettings();
}

void HeroDialog::readSettings()
{
    QSettings *settings = new QSettings("MineSweeper","0314", this);
    // 将读取到的数据设置到相应的分量框
    settings->beginGroup("hero");
    int low_time = settings->value("lowrecordtimelabel", "999").toInt();
    int middle_time = settings->value("middlerecordtimelabel", "999").toInt();
    int height_time = settings->value("heightrecordtimelabel", "999").toInt();
    int mine_time = settings->value("minerecordtimelabel", "999").toInt();
    QString low_name = settings->value("low_name", "xxx").toString();
    QString middle_name = settings->value("middle_name", "xxx").toString();
    QString height_name = settings->value("height_name", "xxx").toString();
    QString mine_name = settings->value("mine_name", "xxx").toString();
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
    lowrecordtimelabel->setText(QString().setNum(999));
    middlerecordtimelabel->setText(QString().setNum(999));
    heightrecordtimelabel->setText(QString().setNum(999));
    minerecordnamelabel->setText(QString().setNum(999));

    lowrecordnamelabel->setText("xxx");
    middlerecordnamelabel->setText("xxx");
    heightrecordnamelabel->setText("xxx");
    minerecordnamelabel->setText("xxx");
}


void HeroDialog::slot_reset()
{
    QSettings settings("MineSweeper","0314");
    settings.beginGroup("hero");
    settings.setValue("lowrecordtimelabel", 999);
    settings.setValue("middlerecordtimelabel", 999);
    settings.setValue("heightrecordtimelabel", 999);
    settings.setValue("minerecordtimelabel", 999);

    settings.setValue("low_name","xxx");
    settings.setValue("middle_name","xxx");
    settings.setValue("height_name","xxx");
    settings.setValue("mine_name","xxx");
    settings.endGroup();
    this->readSettings();
}
