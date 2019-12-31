#ifndef SCREENTOOLBAR_H
#define SCREENTOOLBAR_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QPaintEvent>
#include "soundpushbutton.h"

class ScreenToolBar : public QFrame
{
    Q_OBJECT

public:
    explicit ScreenToolBar(QWidget *parent = 0);
    ~ScreenToolBar();
    QLabel* getTitleLable();
    void setButtonStyles(QPushButton *button, QString imgsrc, int CutSec);
public:
    QLabel *title;
    SoundPushButton *soundButton;
    QPushButton *capPicButton;
    QPushButton *closeButton;
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // SCREENTOOLBAR_H
