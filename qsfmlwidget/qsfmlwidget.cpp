#include "qsfmlwidget.hpp"

#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif

#include <iostream>


QSFMLWidget::QSFMLWidget(QWidget* parent, const QPoint& pos, const QSize& size) :
    QWidget(parent)
{
    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);
    // Setup the widget geometry
    move(pos);
    resize(size);
}


QSFMLWidget::~QSFMLWidget() {}


void QSFMLWidget::showEvent(QShowEvent*)
{
    if (!is_init_)
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
#ifdef Q_WS_X11
        XFlush(QX11Info::display());
#endif
        // Create the SFML window with the widget handle
        sf::RenderWindow::create(static_cast<sf::WindowHandle>(winId()));
        // Let the derived class do its specific stuff
        OnInit();
        is_init_ = true;
    }
}


QPaintEngine* QSFMLWidget::paintEngine() const
{
    return 0;
}


void QSFMLWidget::display(){
    sf::RenderWindow::display();
    update();
}

void QSFMLWidget::OnInit() {}
