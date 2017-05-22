#include "qsfmlwidget.hpp"

#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif

#include <iostream>
#define DEBUG
#include "../debug.h"

QSFMLWidget::QSFMLWidget(QWidget* parent, const QPoint& pos, const QSize& size) :
    QWidget(parent),
    sf::RenderWindow(static_cast<sf::WindowHandle>(winId()))
{
    sf::RenderWindow::setActive(false);
    sf::RenderWindow::setVisible(false);

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
    sf::RenderWindow::setActive(true);
    sf::RenderWindow::setVisible(true);
}


QPaintEngine* QSFMLWidget::paintEngine() const
{
    return 0;
}


void QSFMLWidget::display(){
    sf::RenderWindow::display();
    update();
}
