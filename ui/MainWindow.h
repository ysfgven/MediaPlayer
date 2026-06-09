//
// Created by yusuf on 31.05.2026.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_MainWindow.h"
#include "MediaLibrary.h"
#include "MediaPlayer.h"
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>



class MainWindow : public QMainWindow {
    Q_OBJECT


    public:
    MainWindow(QWidget* parent = nullptr);
    private:
    QTimer* progressTimer;
    Ui::MainWindow ui;
    MediaPlayer player;
    MediaLibrary library;
    void setTreeWidget();
    void setupConnections();
    bool eventFilter(QObject* obj, QEvent* event) override;


    private slots:
    void updateProgressBar();
    void onNextClicked();
    void onPreviousClicked();
    void onPauseClicked();
    void onPlayPauseClicked();
    void onShuffleClicked();
    void onRepeatOneClicked();
    void onRepeatAllClicked();
    void onAddPathClicked();
    void loadLastPath();
    void setupUI();
    void onVolumeChanged(int value);
    void onProgressChanged();


};


#endif //MAINWINDOW_H
