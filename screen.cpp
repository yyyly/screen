#include "screen.h"
#include<QEvent>
#include<QPainter>
#include<QColor>
#include<QRectF>
#include<QMouseEvent>
#include<QGraphicsView>
Screen::Screen(int n,QWidget *parent) :
    QFrame(parent),
    toolBar(new ScreenToolBar(this)),
    playWidget(new QWidget()),
    num(n),
    isSelect(SelectState::UNSELECTED),
    playState(PlayState::UNPLAY),
    flag(0),
    pImf(nullptr),
    timer(new QTimer(this)),
    timer1(new QTimer(this))
{
    vlayout = new QVBoxLayout();
    vlayout->setSpacing(0);
    vlayout->setMargin(0);
    //vlayout->addWidget(toolBar);
    vlayout->addWidget(playWidget);
    setLayout(vlayout);
    toolBar->setVisible(false);
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->parent = parent;
    connect(toolBar->soundButton,SIGNAL(sendSoundCommond(SoundCommond)),
            this,SLOT(soundButtonClicked(SoundCommond)));
    connect(toolBar->capPicButton,SIGNAL(clicked()),this,SLOT(capPicButtonClicked()));
    connect(toolBar->closeButton,SIGNAL(clicked()),this,SLOT(closeButtonClicked()));
    connect(timer,&QTimer::timeout,this,&Screen::onTimeOut);
    connect(timer1,&QTimer::timeout,this,&Screen::onTimeOut);
}

bool Screen::eventFilter(QObject *watched, QEvent *event)
{
    if(watched != parent)
        return false;
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    QGraphicsView *view = qobject_cast<QGraphicsView *>(watched);
    switch(event->type())
    {
    case QEvent::MouseButtonPress:
        {
            if(mouseEvent->button() == Qt::LeftButton)
            {
                mouseIsPress = true;
                mousePos = view->mapFromScene(0,0);
            }
        }
            break;
    case QEvent::MouseMove:
        {
            if(mouseIsPress)
            {
                QPoint p1 =  view->mapFromScene(0,0);
                int x = p1.x() - mousePos.x() + pos().x();
                int y = p1.y() - mousePos.y() + pos().y();
                setGeometry(x,y,this->width(),this->height());
                mousePos = p1;
            }
        }
            break;
    case QEvent::MouseButtonRelease:
        {
            mouseIsPress = false;
        }
            break;
    default:
        break;
    }
    return  false;
}

void Screen::startCountDown(int ms)
{
    timer->stop();
    timer->start(ms);
}

void Screen::onTimeOut()
{
    if(!pImf)
    {
        return;
    }
    timer->stop();
    emit stopPlay();
}

Screen::SelectState Screen::setSelectState(SelectState state)
{
    isSelect = state;
    this->update();
    return isSelect;
}

bool Screen::event(QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress||e->type() == QEvent::MouseMove)
    {
        return true;
    }
    else if (e->type() == QEvent::MouseButtonRelease)
    {
        if(isSelect == SelectState::UNSELECTED)
        {
            isSelect = SelectState::SELECTED;
            emit(selectedStateIsChange(num));
        }
        return true;
    }
    else
        return QFrame::event(e);
}


void Screen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    if(isSelect == SelectState::SELECTED)
    {
        painter.setPen(Qt::green);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawRect(1,1,this->width()-2,this->height()-2);
    }
    if(!toolTip.isEmpty())
    {
        //QRectF rect(10,10,80,40);
        painter.setPen(Qt::red);
        painter.drawText(this->rect(),Qt::AlignCenter,QString("%1").arg(toolTip));
    }
}

QWidget* Screen::getPlayWidget()
{
    return playWidget;
}

void Screen::settoolBarVisible(bool visible)
{
    if(!visible)
        toolBar->setVisible(false);
    else
    {
        toolBar->setVisible(true);
        vlayout->insertWidget(0,toolBar);
    }
}

void Screen::setTitle(const QString &str)
{
    toolBar->getTitleLable()->setText(str);
}

void Screen::setToolTip(const QString &tooltip)
{
    toolTip = tooltip;
    update();
}

void Screen::soundButtonClicked(SoundCommond c)
{
    emit soundCommond(imf,c);
}

void Screen::capPicButtonClicked()
{
    emit capPicture(imf);
}

void Screen::closeButtonClicked()
{
    if(flag == 0)
    {
        emit cameraClose(*pImf,this);//此处信号的参数是全局变量的引用，槽函数会修改全局变量的状态
    }
    else {
        //emit cameraClose(imf,this);//此处信号的参数是全局变量的复制，槽函数对全局变量没有影响
        emit cameraHide();
        this->hide();
    }

}

void Screen::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event)
    if(timer1->isActive())
    {
        return;
    }
    else
    {
        timer1->start(30000);
    }
    if(flag == 1)
    {
        parent->removeEventFilter(this);
    }
}

void Screen::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    if(timer1->isActive())
    {
        timer1->stop();
    }
    if(flag == 1)
    {
        parent->installEventFilter(this);
    }

}

void Screen::bindDevice(CameraDeviceImf *c, int channel)
{
    if(!(c == nullptr))
    imf = *c;
    pImf = c;
    this->channel = channel;
}
