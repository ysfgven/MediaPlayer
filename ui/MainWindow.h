//
// Created by yusuf on 31.05.2026.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_MainWindow.h"
#include "MediaLibrary.h"
#include "MediaPlayer.h"



class MainWindow : public QMainWindow {
    Q_OBJECT


    public:
    MainWindow(QWidget* parent = nullptr);
    private:
    Ui::MainWindow ui;
    MediaPlayer player;
    MediaLibrary library;
    void setTreeWidget();
    void setupConnections();

    private slots:
    void onNextClicked();
    void onPreviousClicked();
    void onPauseClicked();
    void onPlayPauseClicked();
    void onShuffleClicked();
    void onRepeatOneClicked();
    void onRepeatAllClicked();
    void onAddPathClicked();


};


#endif //MAINWINDOW_H
