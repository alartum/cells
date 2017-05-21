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
    virtual void OnInit();
protected:
    void display();
private:
    bool is_init_;
signals:

public slots:
};


#endif // QSFMLWIDGET_HPP
