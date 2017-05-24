#define DEBUG
#include "../debug.h"
#include "gamewindow.hpp"

#include "field/field.hpp"
#include "item/item.hpp"
#include "model/model.hpp"
#include "matrix/matrix.hpp"
#include "model_manager/modelmanager.hpp"
#include "generate_map/generatemap.hpp"
#include "do_step/dostep.hpp"
#include "../config/tile_ids.hpp"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QFile>
#include <QTextStream>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    field_(this),
    time_(0)
{
    setCentralWidget(&field_);

    QMenu* fileMenu = menuBar()->addMenu(tr("&Options"));
    QAction* plot_action = fileMenu->addAction(tr("&Plots"));
    connect(plot_action, SIGNAL(triggered(bool)), this, SLOT(showPlot()));
    QAction* help_action = fileMenu->addAction(tr("&Help"));
    connect(help_action, SIGNAL(triggered(bool)), this, SLOT(showHelp()));

    help_.setReadOnly(true);
    QFile help_file("./help/help");
    if (!help_file.open(QIODevice::ReadOnly | QIODevice::Text))
           throw std::runtime_error("Can't open help file");
    QTextStream help_stream(&help_file);
    QString help_text = help_stream.readAll();
    help_doc_.setHtml(help_text);
    help_file.close();
    help_.setDocument(&help_doc_);

    initField();

    QMenu* gameMenu = menuBar()->addMenu(tr("&Game"));
    QAction* stop_action = gameMenu->addAction(tr("&Stop"));
    connect(stop_action, SIGNAL(triggered(bool)), &field_, SLOT(stop()));
    connect(stop_action, SIGNAL(triggered(bool)), &plot_timer_, SLOT(stop()));
    QAction* resume_action = gameMenu->addAction(tr("&Resume"));
    connect(resume_action, SIGNAL(triggered(bool)), &field_, SLOT(start()));
    connect(resume_action, SIGNAL(triggered(bool)), &plot_timer_, SLOT(start()));
    /*QAction* resume_action = gameMenu->addAction(tr("R&estart"));
    connect(resume_action, SIGNAL(triggered(bool)), &field_, SLOT(start()));
    connect(resume_action, SIGNAL(triggered(bool)), &plot_timer_, SLOT(start()));
*/
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    plot_.setMinimumSize(300, 300);
    plot_.setInteraction(QCP::iRangeZoom, true);
    plot_.setInteraction(QCP::iRangeDrag, true);

    plot_.setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
    plot_.legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    plot_.legend->setFont(legendFont);
    plot_.legend->setBrush(QBrush(QColor(255,255,255,230)));

    plot_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    plot_.xAxis->setLabel("Time");
    plot_.yAxis->setRange(0, field_.getTileSize().x * field_.getTileSize().y);
    plot_.yAxis->setLabel("Amount");

    plot_.addGraph();
    plot_.graph(0)->setName(QString(tr("Grasseating")));
    QPen green_pen;
    green_pen.setColor(Qt::darkGreen);
    green_pen.setWidthF(4);
    plot_.graph(0)->setPen(green_pen);

    plot_.addGraph();
    plot_.graph(1)->setName(QString(tr("Predator")));
    QPen red_pen;
    red_pen.setColor(Qt::darkRed);
    red_pen.setWidthF(4);
    plot_.graph(1)->setPen(red_pen);

    plot_timer_.setInterval(500);
    connect(&plot_timer_, SIGNAL(timeout()), this, SLOT(updatePlot()));
    plot_timer_.start();
}

void GameWindow::initField(){
    field_.loadConfig("./config/window_config.lua");

    GenerateComplexMap mapGenerator(10, 0.05, 0.21, 0.2);
    //GenerateRandomMap& gen = mapGenerator;
    field_.setGenerateMap(mapGenerator);
    field_.generateTiles();
    LOG("Map generated");

    GenerateRandomEntity entityGenerator(10, 1, 0, 30, 40, 1, 3, 9);
    field_.setGenerateEntities(entityGenerator);
    field_.generateEntities();

    std::shared_ptr< ModelManager > sample = std::make_shared< ModelManager >();
    sample->loadConfig("./config/mm_config.lua");
    LOG("Model manager initialized");
    RandomMoving RM(sample);
    field_.setDoStep(RM);
    field_.setModelManager(sample);
    field_.loadTileTextures();
    field_.loadEntityTextures();
    LOG("Textures loaded");

    field_.show();
    field_.start();
}

void GameWindow::closeEvent ( QCloseEvent * event ){
    help_.close();
    plot_.close();
}

void GameWindow::showPlot(){
    plot_.show();
}

void GameWindow::showHelp(){
    help_.show();
}

void GameWindow::updatePlot(){
    plot_.graph(0)->addData(time_, field_.getStatistics().at(OBJECT_GRASS_EATING_ID));
    plot_.graph(1)->addData(time_, field_.getStatistics().at(OBJECT_PREDATOR_ID));
    plot_.rescaleAxes();
    plot_.replot();
    time_++;
}

void GameWindow::restartField(){
    field_.generateTiles();
    field_.generateEntities();

}
