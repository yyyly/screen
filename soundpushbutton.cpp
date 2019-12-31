#include "soundpushbutton.h"

SoundPushButton::SoundPushButton()
{
    state = SOUND_OFF;
}

void SoundPushButton::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    setButtonStyle(":/image/voice_off.png",4);
}

void SoundPushButton::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    if(state == SOUND_OFF)
    {
        state = SOUND_ON;
        emit sendSoundCommond(SOUND_PLAY);
        setButtonStyle(":/image/voice_on.png",4);
    }
    else {
        state = SOUND_OFF;
        emit sendSoundCommond(SOUND_STOP);
        setButtonStyle(":/image/voice_off.png",4);
    }
}

void SoundPushButton::setButtonStyle(QString imgsrc, int CutSec)
{
    int img_w=QPixmap(imgsrc).width();
    int img_h=QPixmap(imgsrc).height();
    int PicWidth = img_w/CutSec;
    this->setFixedSize(PicWidth,img_h);
    this->setStyleSheet(QString("QPushButton{border-width: 41px; border-image: url(%1) 0 0 0 %2 repeat repeat;border-width: 0px; border-radius: 0px;}")
    .append("QPushButton::hover{border-image: url(%1) 0 0 0 %3 repeat repeat;}")
    .append("QPushButton::pressed{border-image: url(%1) 0 0 0 %4 repeat repeat;}")
    .append("QPushButton::checked{border-image: url(%1) 0 0 0 %4 repeat repeat;}")
    .append("QPushButton::disabled{border-image: url(%1) 0 0 0 %5 repeat repeat;}")
    .arg(imgsrc).arg(0).arg(PicWidth*1).arg(PicWidth*2).arg(PicWidth*3));
}
