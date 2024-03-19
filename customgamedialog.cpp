/**
 * @file customgamedialog.cpp
 * @brief 自定义游戏难度弹窗类源文件
 * @author RickRone
 * @date 2024.3.15
 * @version Qt 6.6.2
 */
#include "customgamedialog.h"

CustomGameDialog::CustomGameDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("自定义难度");
    QLabel *label_1 = new QLabel("行 数");
    QLabel *label_2 = new QLabel("列 数");
    QLabel *label_3 = new QLabel("雷 数");
    // 列
    colSpinBox = new QSpinBox; // 数字输入框
    colSpinBox->setRange(1,100); // 设置范围
    colSpinBox->setSingleStep(5); // 设置步长
    colSpinBox->setValue(10); // 设置初始值
    // 行
    rowSpinBox = new QSpinBox;
    rowSpinBox->setRange(1,100);
    rowSpinBox->setSingleStep(5);
    rowSpinBox->setValue(10);
    // 雷数
    mineNumSpinBox = new QSpinBox;
    mineNumSpinBox->setRange(1,100);
    mineNumSpinBox->setSingleStep(1);
    mineNumSpinBox->setValue(10);
    // 按钮
    QPushButton *okBtn = new QPushButton("确 定");
    QPushButton *cancelBtn = new QPushButton("取 消");
    QGridLayout *gLayout = new QGridLayout(this);
    // 网格布局
    gLayout->addWidget(label_1, 0, 0);
    gLayout->addWidget(rowSpinBox, 0, 1);
    gLayout->addWidget(label_2, 1, 0);
    gLayout->addWidget(colSpinBox, 1, 1);
    gLayout->addWidget(label_3, 2, 0);
    gLayout->addWidget(mineNumSpinBox, 2, 1);
    gLayout->addWidget(okBtn, 3, 0);
    gLayout->addWidget(cancelBtn, 3, 1);

    this->connect(okBtn, &QPushButton::clicked, this, [=](){
                      //获取分量框中的数据
                      int row = rowSpinBox->value();
                      int col = colSpinBox->value();
                      int count = mineNumSpinBox->value();

                      //发送自定义游戏数据信号
                      emit this->signal_sendCustomset(row, col, count);
                      this->writeSettings();
                      this->close();
                  });

    this->connect(cancelBtn, &QPushButton::clicked, this, &CustomGameDialog::close);
}

// 读设置
void CustomGameDialog::readSettings() {
    QSettings *setting = new QSettings("MineSweeper","0315",this);
    setting->beginGroup("customGame");
    int row = setting->value("custom_row", 10).toInt();
    int col = setting->value("custom_col", 10).toInt();
    int mine = setting->value("custom_mine", 10).toInt();
    setting->endGroup();
    // 将读取到的值设置到自定义游戏对话框中的分量框
    rowSpinBox->setValue(row);
    colSpinBox->setValue(col);
    mineNumSpinBox->setValue(mine);
}
// 写设置
void CustomGameDialog::writeSettings() {
    QSettings *setting = new QSettings("MineSweeper","0315",this);
    setting->beginGroup("customGame");
    setting->setValue("custom_row", rowSpinBox->value());
    setting->setValue("custom_col", colSpinBox->value());
    setting->setValue("custom_mine", mineNumSpinBox->value());
    setting->endGroup();
}
