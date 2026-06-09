//
// Created by yusuf on 31.05.2026.
//

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget* parent) :QMainWindow(parent){
    ui.setupUi(this);
    loadLastPath();
    player.setLibrary(&library);
    progressTimer = new QTimer(this);
    progressTimer->start(500);
    setupUI();
    setupConnections();
};


void MainWindow::setupUI() {
    ui.playButton->setIcon(QIcon(":/icons/play.svg"));
    ui.playButton->setIconSize(QSize(24, 24));
    ui.playButton->setText("");

    ui.previousButton->setIcon(QIcon(":/icons/previous.svg"));
    ui.previousButton->setIconSize(QSize(24, 24));
    ui.previousButton->setText("");

    ui.nextButton->setIcon(QIcon(":/icons/next.svg"));
    ui.nextButton->setIconSize(QSize(24, 24));
    ui.nextButton->setText("");

    ui.repeatAllButton->setIcon(QIcon(":/icons/repeat.svg"));
    ui.repeatAllButton->setIconSize(QSize(24, 24));
    ui.repeatAllButton->setText("");

    ui.repeatOneButton->setIcon(QIcon(":/icons/repeatOne.svg"));
    ui.repeatOneButton->setIconSize(QSize(24, 24));
    ui.repeatOneButton->setText("");

    ui.shuffleButton->setIcon(QIcon(":/icons/shuffle.svg"));
    ui.shuffleButton->setIconSize(QSize(24, 24));
    ui.shuffleButton->setText("");
    setTreeWidget();

    QSettings settings;
    int volume = settings.value("volume", 50).toInt();
    ui.volumeSlider->setValue(volume);
    player.setVolume(volume);

    ui.volumeIcon->setPixmap(QIcon(":/icons/volumeHigh.svg").pixmap(24, 24));

}

void MainWindow::loadLastPath() {
    QSettings settings;
    QString path = settings.value("lastPath", "").toString();
    if (path.isEmpty()) {
        QFileDialog dialog(this);
        dialog.setWindowTitle("Select music folder ");
        dialog.setFileMode(QFileDialog::Directory);
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        QString selectedPath = QFileDialog::getExistingDirectory(&dialog);
        settings.setValue("lastPath", selectedPath);
        library.loadFromDirectory(selectedPath.toStdString());
    }else {
        library.loadFromDirectory(path.toStdString());
    }
}

void MainWindow::setTreeWidget() {
    ui.treeWidget->setRootIsDecorated(false);
    ui.treeWidget->clear();
    ui.treeWidget->setColumnWidth(0, 400); // Name
    ui.treeWidget->setColumnWidth(1, 150); // Singer
    ui.treeWidget->setColumnWidth(2, 80);  // Duration
    ui.treeWidget->setColumnWidth(3, 100); // Size
    int seconds,min,size;
    for (int i = 0 ;i < library.getTrackCount(); i++) {
        min = library.getTrack(i)-> getDuration()/60;
        seconds = library.getTrack(i)-> getDuration()%60;
        size = std::filesystem::file_size(library.getTrack(i)->getFilePath()) / (1024.0 * 1024.0);
        QTreeWidgetItem* item = new QTreeWidgetItem(ui.treeWidget); //no memory leak here
        item->setText(0, QString::fromStdString(library.getTrack(i)->getTitle()));
        item->setText(1, QString::fromStdString(library.getTrack(i)->getArtist()));
        item->setText(2,QString::number(min) + ":" + QString::number(seconds).rightJustified(2, '0'));
        item->setText(3, QString::number(size) + " MB");
    }
}

void MainWindow::setupConnections() {
    connect(ui.previousButton, &QPushButton::clicked, this, &MainWindow::onPreviousClicked);
    connect(ui.nextButton, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    connect(ui.playButton, &QPushButton::clicked, this, &MainWindow::onPlayPauseClicked);
    connect(ui.shuffleButton, &QPushButton::clicked, this, &MainWindow::onShuffleClicked);
    connect(ui.repeatAllButton, &QPushButton::clicked, this, &MainWindow::onRepeatAllClicked);
    connect(ui.repeatOneButton, &QPushButton::clicked, this, &MainWindow::onRepeatOneClicked);
    connect(ui.addPathBtn, &QAction::triggered, this, &MainWindow::onAddPathClicked);
    connect(progressTimer, &QTimer::timeout, this, &MainWindow::updateProgressBar);
    connect(ui.volumeSlider, &QSlider::valueChanged, this, &MainWindow::onVolumeChanged);
    connect(ui.progressSlider, &QSlider::sliderMoved, this, &MainWindow::onProgressChanged);
    connect(ui.treeWidget, &QTreeWidget::itemClicked, this, &MainWindow::onTrackClicked);
    connect(ui.searchBar, &QLineEdit::textChanged, this, &MainWindow::onSearchChanged);
    ui.progressSlider->installEventFilter(this);



}

void MainWindow::onSearchChanged(const QString &text) {
    for (int i = 0; i < ui.treeWidget->topLevelItemCount(); i++){
        QTreeWidgetItem* item = ui.treeWidget->topLevelItem(i);
        bool match = item->text(0).contains(text, Qt::CaseInsensitive) || item->text(1).contains(text, Qt::CaseInsensitive);
        item->setHidden(!match);
    }
}

void MainWindow::onTrackClicked(QTreeWidgetItem *item, int column) {
    player.selectTrack(ui.treeWidget->indexOfTopLevelItem(item));
    ui.playButton->setIcon(QIcon(":/icons/play.svg"));
}

void MainWindow::onProgressChanged() {
    if (player.getCurrentTrack() == nullptr) return;
    float seconds = (ui.progressSlider->value() / 100.0f) * player.getCurrentTrack()->getDuration();
    player.seekTo(seconds);
}

void MainWindow::onVolumeChanged(int value) {
    QSettings settings;
    settings.setValue("volume", value);
    player.setVolume(value);

    if (value == 0)
        ui.volumeIcon->setPixmap(QIcon(":/icons/mute.svg").pixmap(24, 24));
    else if (value < 50)
        ui.volumeIcon->setPixmap(QIcon(":/icons/volumeLow.svg").pixmap(24, 24));
    else
        ui.volumeIcon->setPixmap(QIcon(":/icons/volumeHigh.svg").pixmap(24, 24));

}

void MainWindow::onPlayPauseClicked() {
    if (player.getState() == MediaPlayer::State::Playing) {
        player.pause();
        ui.playButton->setIcon(QIcon(":/icons/play.svg"));
    } else {
        player.play();
        ui.playButton->setIcon(QIcon(":/icons/pause.svg"));
    }
}

void MainWindow::onNextClicked() {
    player.nextTrack();
    player.play();
    ui.playButton->setIcon(QIcon(":/icons/pause.svg"));
}

void MainWindow::onPreviousClicked() {
    player.previousTrack();
    player.play();
    ui.playButton->setIcon(QIcon(":/icons/pause.svg"));
}

void MainWindow::onPauseClicked() {
    player.pause();
}

void MainWindow::onShuffleClicked() {
    if (MediaPlayer::PlayMode::Shuffle != player.getPlayMode()) {
        player.setPlayMode(MediaPlayer::PlayMode::Shuffle);
        ui.shuffleButton->setProperty("active", true);

        ui.repeatAllButton->setProperty("active", false);
        ui.repeatOneButton->setProperty("active", false);

        ui.repeatAllButton->style()->unpolish(ui.repeatAllButton);
        ui.repeatAllButton->style()->polish(ui.repeatAllButton);
        ui.repeatOneButton->style()->unpolish(ui.repeatOneButton);
        ui.repeatOneButton->style()->polish(ui.repeatOneButton);
    } else {
        player.setPlayMode(MediaPlayer::PlayMode::Normal);
        ui.shuffleButton->setProperty("active", false);
    }
    ui.shuffleButton->style()->unpolish(ui.shuffleButton);
    ui.shuffleButton->style()->polish(ui.shuffleButton);
}

void MainWindow::onRepeatOneClicked() {
    if (MediaPlayer::PlayMode::RepeatOne != player.getPlayMode()) {
        player.setPlayMode(MediaPlayer::PlayMode::RepeatOne);
        ui.repeatOneButton->setProperty("active", true);

        ui.shuffleButton->setProperty("active", false);
        ui.repeatAllButton->setProperty("active", false);

        ui.repeatAllButton->style()->unpolish(ui.repeatAllButton);
        ui.repeatAllButton->style()->polish(ui.repeatAllButton);
        ui.shuffleButton->style()->unpolish(ui.shuffleButton);
        ui.shuffleButton->style()->polish(ui.shuffleButton);
    }else {
        player.setPlayMode(MediaPlayer::PlayMode::Normal);
        ui.repeatOneButton->setProperty("active", false);
    }
    ui.repeatOneButton->style()->unpolish(ui.repeatOneButton);
    ui.repeatOneButton->style()->polish(ui.repeatOneButton);
}

void MainWindow::onRepeatAllClicked() {
    if (MediaPlayer::PlayMode::RepeatAll != player.getPlayMode()) {
        player.setPlayMode(MediaPlayer::PlayMode::RepeatAll);
        ui.repeatAllButton->setProperty("active", true);

        ui.shuffleButton->setProperty("active", false);
        ui.repeatOneButton->setProperty("active", false);

        ui.shuffleButton->style()->unpolish(ui.shuffleButton);
        ui.shuffleButton->style()->polish(ui.shuffleButton);
        ui.repeatOneButton->style()->unpolish(ui.repeatOneButton);
        ui.repeatOneButton->style()->polish(ui.repeatOneButton);

    }else {
        player.setPlayMode(MediaPlayer::PlayMode::Normal);
        ui.repeatAllButton->setProperty("active", false);
    }
    ui.repeatAllButton->style()->unpolish(ui.repeatAllButton);
    ui.repeatAllButton->style()->polish(ui.repeatAllButton);
}

void MainWindow::onAddPathClicked() {
    library.loadFromDirectory(QFileDialog::getExistingDirectory().toStdString());
    player.setLibrary(&library);
    setTreeWidget();

}

void MainWindow::updateProgressBar() {
    if (player.getState() == MediaPlayer::State::Playing) {
        int duration = player.getCurrentTrack()->getDuration();
        float position = player.getCurrentPosition();
        if (position>0) {
            ui.progressSlider->setValue(position/duration*100);
        }
        if (player.isAtEnd()) {
            player.nextTrack();
        }
    }


}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (obj == ui.progressSlider && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        float ratio = (float)mouseEvent->pos().x() / ui.progressSlider->width();
        int value = ratio * ui.progressSlider->maximum();
        ui.progressSlider->setValue(value);
        onProgressChanged();
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}



