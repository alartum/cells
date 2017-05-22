#ifndef QSFMLWIDGET_HPP
#define QSFMLWIDGET_HPP

#include <QWidget>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class QSFMLWidget : public QWidget, protected sf::RenderWindow
{
    Q_OBJECT
public:
    explicit QSFMLWidget(QWidget *parent, const QPoint& pos, const QSize& size);
    virtual void showEvent(QShowEvent*);
    virtual QPaintEngine* paintEngine() const;
    virtual ~QSFMLWidget();
protected:
    void display();
signals:

public slots:
};


#endif // QSFMLWIDGET_HPP
