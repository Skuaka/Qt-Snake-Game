#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "ui_mainwindow.h"
#include "gamecontroller.h"
#include "food.h"
#include "snake.h"

GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    snake(new Snake(*this)),
    score(0)
{
    timer.start( 1000/33 );

    Food *a1 = new Food(0, -50);
    scene.addItem(a1);

    scene.addItem(snake);
    scene.installEventFilter(this);

    resume();
    paused = false;
}

GameController::~GameController()
{
}

void GameController::snakeAteFood(Snake *snake, Food *food)
{
    scene.removeItem(food);
    QTimer::singleShot(0, [=](){ delete food; });

    score++;
    emit changeScore(score);

    addNewFood();
}

void GameController::snakeHitWall(Snake *snake, Wall *wall)
{
}

void GameController::snakeAteItself(Snake *snake)
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::handleKeyPressed(QKeyEvent *event)
{
    if(event->key() == Qt::Key_P)
        if(paused){
            resume();
            paused = false;
        }
        else{
            pause();
            paused = true;
        }

    if(paused)
        return;

    switch (event->key()) {
        case Qt::Key_Left:
            if(snake->getMoveDirection() == Snake::MoveRight)
                return;
            snake->setMoveDirection(Snake::MoveLeft);
            break;
        case Qt::Key_Right:
            if(snake->getMoveDirection() == Snake::MoveLeft)
                return;
            snake->setMoveDirection(Snake::MoveRight);
            break;
        case Qt::Key_Up:
            if(snake->getMoveDirection() == Snake::MoveDown)
                return;
            snake->setMoveDirection(Snake::MoveUp);
            break;
        case Qt::Key_Down:
            if(snake->getMoveDirection() == Snake::MoveUp)
                return;
            snake->setMoveDirection(Snake::MoveDown);
            break;
    }
}

void GameController::addNewFood()
{
    int x, y;

    do {
        x = (int(qrand() % 200)-100) / 10;
        y = (int(qrand() % 200)-100) / 10;

        x *= 10;
        y *= 10;
    } while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));

    Food *food = new Food(x , y);
    scene.addItem(food);
}

void GameController::gameOver()
{
    scene.clear();

    score = 0;
    emit changeScore(0);

    snake = new Snake(*this);
    scene.addItem(snake);
    addNewFood();
}

void GameController::pause()
{
    disconnect(&timer, SIGNAL(timeout()),
               &scene, SLOT(advance()));
}

void GameController::resume()
{
    connect(&timer, SIGNAL(timeout()),
            &scene, SLOT(advance()));
}

bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}
