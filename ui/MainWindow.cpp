//
// Created by yusuf on 31.05.2026.
//

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent) :QMainWindow(parent){
    ui.setupUi(this);
    player.setLibrary(&library);
    setTreeWidget();
    setupConnections();
};

void MainWindow::setTreeWidget() {
    ui.treeWidget->setRootIsDecorated(false);
    ui.treeWidget->clear();
    ui.treeWidget->setColumnWidth(0, 400); // Name
    ui.treeWidget->setColumnWidth(1, 150); // Singer
    ui.treeWidget->setColumnWidth(2, 80);  // Duration
    ui.treeWidget->setColumnWidth(3, 100); // Size
    for (int i = 0 ;i < library.getTrackCount(); i++) {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui.treeWidget); //no memory leak here
        item->setText(0, QString::fromStdString(library.getTrack(i)->getTitle()));
        item->setText(1, QString::fromStdString(library.getTrack(i)->getArtist()));
        item->setText(2,QString::number(library.getTrack(i)->getDuration()));
        item->setText(3,QString::number(std::filesystem::file_size(library.getTrack(i)->getFilePath())));
    }
}


void MainWindow::setupConnections() {
    connect(ui.previousButton, &QPushButton::clicked, this, &MainWindow::onPreviousClicked);
    connect(ui.nextButton, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    connect(ui.playButton, &QPushButton::clicked, this, &MainWindow::onPlayPauseClicked);
    connect(ui.shuffleButton, &QPushButton::clicked, this, &MainWindow::onShuffleClicked);
    connect(ui.repeatAllButton, &QPushButton::clicked, this, &MainWindow::onRepeatAllClicked);
    connect(ui.repeatOneButton, &QPushButton::clicked, this, &MainWindow::onRepeatOneClicked);
    connect(ui.addPathButton, &QPushButton::clicked, this, &MainWindow::onAddPathClicked);



}

void MainWindow::onPlayPauseClicked() {
    if (player.getState() == MediaPlayer::State::Playing) {
        player.pause();
        ui.playButton->setText("Play");
    } else {
        player.play();
        ui.playButton->setText("Pause");
    }
}

void MainWindow::onNextClicked() {
    player.nextTrack();
    player.play();
}

void MainWindow::onPreviousClicked() {
    player.previousTrack();
}

void MainWindow::onPauseClicked() {
    player.pause();
}

void MainWindow::onShuffleClicked() {
    if (MediaPlayer::PlayMode::Shuffle != player.getPlayMode()) {
        player.setPlayMode(MediaPlayer::PlayMode::Shuffle);
    }else {
        player.setPlayMode(MediaPlayer::PlayMode::Normal);
    }
}

void MainWindow::onRepeatOneClicked() {
    if (MediaPlayer::PlayMode::RepeatOne != player.getPlayMode()) {
        player.setPlayMode(MediaPlayer::PlayMode::RepeatOne);
    }else {
        player.setPlayMode(MediaPlayer::PlayMode::Normal);
    }
}

void MainWindow::onRepeatAllClicked() {
    if (MediaPlayer::PlayMode::RepeatAll != player.getPlayMode()) {
        player.setPlayMode(MediaPlayer::PlayMode::RepeatAll);
    }else {
        player.setPlayMode(MediaPlayer::PlayMode::Normal);
    }
}

void MainWindow::onAddPathClicked() {
    library.loadFromDirectory(QFileDialog::getExistingDirectory().toStdString());
    player.setLibrary(&library);
    setTreeWidget();

}



