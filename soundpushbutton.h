#ifndef SOUNDPUSHBUTTON_H
#define SOUNDPUSHBUTTON_H
#include <QPushButton>

enum SoundPushButtonState
{
    SOUND_ON,
    SOUND_OFF
};
enum SoundCommond
{
    SOUND_PLAY,
    SOUND_STOP
};

class SoundPushButton : public QPushButton
{
    Q_OBJECT

public:
    SoundPushButton();
    void setButtonStyle(QString imgsrc, int CutSec);
protected:
    void mousePressEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *event);
signals:
    void sendSoundCommond(SoundCommond c);
private:
    SoundPushButtonState state;
};

#endif // SOUNDPUSHBUTTON_H
