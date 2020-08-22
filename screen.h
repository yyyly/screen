#ifndef SCREEN_H
#define SCREEN_H

#include "screen_global.h"
#include "screentoolbar.h"
#include "cameradeviceimf.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QTimer>

class SCREENSHARED_EXPORT Screen : public QFrame
{
    Q_OBJECT
public:
    enum SelectState
    {
        SELECTED,
        UNSELECTED
    };
    enum PlayState
    {
       PLAY,
       UNPLAY
    };
    explicit Screen(int n,QWidget *parent = 0);
    SelectState setSelectState(SelectState state);
    int getNum(){return num;}
    QWidget* getPlayWidget();
    void settoolBarVisible(bool visible);
    void setTitle(const QString &str);
    void setToolTip(const QString &tooltip);
    void bindDevice(CameraDeviceImf* c, int channel = 0);
    CameraDeviceImf *getCameraDeviceImf(){return &imf;}
    int getChannel(){return channel;}
    int flag;//根据flag的值不同，按关闭键时动作不同，默认为0，仅发射信号。为1时关闭
    PlayState getPlayState(){return playState;}
    void setPlayState(const PlayState state);
    void startCountDown(int ms);
    QObject *returnPanent(){return  parent;}
    void setScreenNormal();
private:
    bool isMax;
    bool isClicked;
    //int timerN;
    ScreenToolBar *toolBar;
    int num;//第几号
    SelectState isSelect;
    PlayState playState;
    QWidget *playWidget;
    QVBoxLayout *vlayout;
    QString toolTip = QString("");
    CameraDeviceImf imf;
    int channel;
    CameraDeviceImf *pImf;
    QTimer *timer;//录像控制时间
    QTimer *timer1;//预览隐藏后控制时间
    QObject *parent;
    bool mouseIsPress;
    QPoint mousePos;
    QRect normalRect;
signals:
    void selectedStateIsChange(int n);
    void cameraClose(CameraDeviceImf& c,Screen *screen);
    void cameraHide();
    void capPicture(CameraDeviceImf& c);
    void soundCommond(CameraDeviceImf& c,SoundCommond commond);
    void stopPlay();
    void toMax(int n);
    void toNormal();
public slots:
    void soundButtonClicked(SoundCommond c);
    void capPicButtonClicked();
    void closeButtonClicked();
    void toMaxButtonClicked();
    void onTimeOut();
protected:
   bool event(QEvent *e);
   bool eventFilter(QObject *watched, QEvent *event);
   void paintEvent(QPaintEvent *event);
   void hideEvent(QHideEvent *event);
   void showEvent(QShowEvent *event);
   void mouseDoubleClickEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);

};

#endif // SCREEN_H
