#include "screentoolbar.h"
#include <QHBoxLayout>
#include <QPalette>
#include <QStyleOption>
#include <QPainter>
ScreenToolBar::ScreenToolBar(QWidget *parent) :
    QFrame(parent),
    title(new QLabel),
    soundButton(new SoundPushButton),
    capPicButton(new QPushButton),
    closeButton(new QPushButton),
    toMaxButton(new QPushButton)
{
    setFixedHeight(22);
    //设置背景
    /*setAutoFillBackground(true);
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background,Qt::black);
    setPalette(palette);*/
    soundButton->setFixedSize(20,20);
    capPicButton->setFixedSize(20,20);
    closeButton->setFixedSize(20,20);
    toMaxButton->setFixedSize(20,20);
    setButtonStyles(closeButton,":/image/close.png",4);
    setButtonStyles(capPicButton,":/image/capture.png",4);
    setButtonStyles(toMaxButton,":/image/fullScreen.png",4);
    title->setStyleSheet(QString("QLabel{color: white;}"));
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setMargin(0);
    hLayout->addWidget(toMaxButton);
    hLayout->addStretch();
    hLayout->addWidget(title);
    hLayout->addStretch();
    hLayout->addWidget(soundButton);
    hLayout->addWidget(capPicButton);
    hLayout->addWidget(closeButton);
    setLayout(hLayout);
}

ScreenToolBar::~ScreenToolBar()
{

}


QLabel* ScreenToolBar::getTitleLable()
{
    return title;
}

void ScreenToolBar::setButtonStyles(QPushButton *button, QString imgsrc, int CutSec)
{
    int img_w=QPixmap(imgsrc).width();
    int img_h=QPixmap(imgsrc).height();
    int PicWidth = img_w/CutSec;
    button->setFixedSize(PicWidth,img_h);
    button->setStyleSheet(QString("QPushButton{border-width: 41px; border-image: url(%1) 0 0 0 %2 repeat repeat;border-width: 0px; border-radius: 0px;}")
    .append("QPushButton::hover{border-image: url(%1) 0 0 0 %3 repeat repeat;}")
    .append("QPushButton::pressed{border-image: url(%1) 0 0 0 %4 repeat repeat;}")
    .append("QPushButton::checked{border-image: url(%1) 0 0 0 %4 repeat repeat;}")
    .append("QPushButton::disabled{border-image: url(%1) 0 0 0 %5 repeat repeat;}")
    .arg(imgsrc).arg(0).arg(PicWidth*1).arg(PicWidth*2).arg(PicWidth*3));
}

void ScreenToolBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
