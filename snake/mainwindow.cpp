#include <QGraphicsView>
#include <QTimer>
#include <QEvent>
#include "constants.h"
#include "gamecontroller.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      game(new GameController(*scene, this)),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalLayout_2->addWidget(view);

    resize(690, 600);
    this->setWindowTitle("Snake");

    initScene();
    initSceneBackground();

    QObject::connect(game, &GameController::changeScore,
                     [=](int s){ui->label_score_num->setText(QString::number(s));} );

    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
}

MainWindow::~MainWindow()
{
    
}

bool MainWindow::event(QEvent *e)
{
    if (e->type() == QEvent::Resize) {
        adjustViewSize();
        return true;
    }
    return QWidget::event(e);
}
void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);
}

void MainWindow::initScene()
{
    scene->setSceneRect(-99, -99, 209, 209);
}

void MainWindow::initSceneBackground()
{
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));
}
