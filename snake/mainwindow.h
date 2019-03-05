#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class QGraphicsScene;
class QGraphicsView;

class GameController;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void adjustViewSize();

private:
    void initScene();
    void initSceneBackground();

    bool event(QEvent *e);

    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QGraphicsView *view;

    GameController *game;
};

#endif // MAINWINDOW_H
