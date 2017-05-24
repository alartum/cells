#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include <QMainWindow>
#include "../field/field.hpp"
#include <QTextEdit>
#include <QTextDocument>
#include "../lib/qcustomplot.h"
#include <QTimer>
#include <QMap>
#include <QVector>

class GameWindow : public QMainWindow
{
    Q_OBJECT
private:
    void initField();
    QTextDocument help_doc_;
    QTextEdit help_;
    Field field_;

    // PLOTTTING //
    QCustomPlot plot_;
    // Signals to get recent info
    QTimer plot_timer_;
    // Ticks passed from the start
    size_t time_;

protected:
    void closeEvent ( QCloseEvent * event );
public:
    explicit GameWindow(QWidget *parent = 0);
signals:

public slots:
    void showPlot();
    void showHelp();
    void updatePlot();
};

#endif // GAMEWINDOW_HPP
