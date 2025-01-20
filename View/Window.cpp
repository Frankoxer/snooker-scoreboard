//
// Created by Frankoxer on 25-1-19.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Window.h" resolved

#include "Window.h"
#include "ui_Window.h"
#include <iostream>
#include <QPainter>

float spacing = 1.2;

Window::Window(QWidget *parent) :
    QWidget(parent), ui(new Ui::Window) {
    ui->setupUi(this);

    setFixedSize(750, 450);
}

Window::~Window() {
    delete ui;
}

QString Window::matchTypeToString(MatchType type) {
    switch (type) {
        case MatchType::LAST_128:
            return "Last 128";
        case MatchType::LAST_64:
            return "Last 64";
        case MatchType::LAST_32:
            return "Last 32";
        case MatchType::LAST_16:
            return "Last 16";
        case MatchType::QUARTER_FINAL:
            return "Quarter Final";
        case MatchType::SEMI_FINAL:
            return "Semi Final";
        case MatchType::FINAL:
            return "Final";
    }
}

void Window::updateIsPlayer1() {
    std::cout << "updateIsPlayer1: isPlayer1 = " << isPlayer1 << std::endl;
    // Remove previous circle labels if they exist
    if (player1CircleLabel) {
        delete player1CircleLabel;
        player1CircleLabel = nullptr;
    }
    if (player2CircleLabel) {
        delete player2CircleLabel;
        player2CircleLabel = nullptr;
    }

    // Create new circle labels
    player1CircleLabel = new QLabel(this);
    player2CircleLabel = new QLabel(this);

    QPixmap filledCircle(30, 30);
    filledCircle.fill(Qt::transparent);
    QPainter painter1(&filledCircle);
    painter1.setRenderHint(QPainter::Antialiasing);
    painter1.setBrush(Qt::black);
    painter1.drawEllipse(0, 0, 20, 20);

    QPixmap outlinedCircle(30, 30);
    outlinedCircle.fill(Qt::transparent);
    QPainter painter2(&outlinedCircle);
    painter2.setRenderHint(QPainter::Antialiasing);
    painter2.setBrush(Qt::NoBrush);
    painter2.setPen(QPen(Qt::black, 1));
    painter2.drawEllipse(0, 0, 20, 20);

    if (isPlayer1) {
        player1CircleLabel->setPixmap(filledCircle);
        player2CircleLabel->setPixmap(outlinedCircle);
    } else {
        player1CircleLabel->setPixmap(outlinedCircle);
        player2CircleLabel->setPixmap(filledCircle);
    }

    player1CircleLabel->setGeometry(width() / 2 - 50 - 230, 90, 30, 30); // Adjust the position and size
    player1CircleLabel->show();

    player2CircleLabel->setGeometry(width() / 2 + 50 + 200, 90, 30, 30); // Adjust the position and size
    player2CircleLabel->show();
}

void Window::updateScoreLabels() {
    if(player1CurrentScoreLabel) {
        delete player1CurrentScoreLabel;
        player1CurrentScoreLabel = nullptr;
    }
    if(player2CurrentScoreLabel) {
        delete player2CurrentScoreLabel;
        player2CurrentScoreLabel = nullptr;
    }

    // 选手 1 当前局得分
    player1CurrentScoreLabel = new QLabel(QString::number(currentFrame.player1_points), this);
    QFont currentScoreFont("SF Pro", 44, QFont::Bold);
    currentScoreFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    player1CurrentScoreLabel->setFont(currentScoreFont);
    player1CurrentScoreLabel->setAlignment(Qt::AlignRight);
    player1CurrentScoreLabel->setGeometry(width() / 2 - 70 - 200, 170, 200, 50); // Adjust the position and size
    player1CurrentScoreLabel->show();

    // 选手 2 当前局得分
    player2CurrentScoreLabel = new QLabel(QString::number(currentFrame.player2_points), this);
    player2CurrentScoreLabel->setFont(currentScoreFont);
    player2CurrentScoreLabel->setAlignment(Qt::AlignLeft);
    player2CurrentScoreLabel->setGeometry(width() / 2 + 70, 170, 200, 50); // Adjust the position and size
    player2CurrentScoreLabel->show();
}

void Window::foulRecolor(bool isFoul) {
    std::cout << "foulRecolor: isFoul = " << isFoul << std::endl;
    if (isPlayer1) {
        if (player1CircleLabel) {
            delete player1CircleLabel;
            player1CircleLabel = nullptr;
        }
        player1CircleLabel = new QLabel(this);
        QPixmap filledCircle(30, 30);
        filledCircle.fill(Qt::transparent);
        QPainter painter1(&filledCircle);
        painter1.setRenderHint(QPainter::Antialiasing);
        painter1.setBrush(isFoul ? Qt::red : Qt::black);
        painter1.drawEllipse(0, 0, 20, 20);
        player1CircleLabel->setPixmap(filledCircle);
        player1CircleLabel->setGeometry(width() / 2 - 50 - 230, 90, 30, 30); // Adjust the position and size
        player1CircleLabel->show();
    } else {
        if (player2CircleLabel) {
            delete player2CircleLabel;
            player2CircleLabel = nullptr;
        }
        player2CircleLabel = new QLabel(this);
        QPixmap filledCircle(30, 30);
        filledCircle.fill(Qt::transparent);
        QPainter painter1(&filledCircle);
        painter1.setRenderHint(QPainter::Antialiasing);
        painter1.setBrush(isFoul ? Qt::red : Qt::black);
        painter1.drawEllipse(0, 0, 20, 20);
        player2CircleLabel->setPixmap(filledCircle);
        player2CircleLabel->setGeometry(width() / 2 + 50 + 200, 90, 30, 30); // Adjust the position and size
        player2CircleLabel->show();
    }
}

void Window::initializeMatch(Match match, Frame frame, bool isPlayer1) {
    this->match = match;
    this->currentFrame = frame;
    this->isPlayer1 = isPlayer1;

    // 背景渐变色
    QPalette pal = palette();
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor("#FDC800")); // Top color
    gradient.setColorAt(1, Qt::white); // Bottom color
    pal.setBrush(QPalette::Window, QBrush(gradient));
    setAutoFillBackground(true);
    setPalette(pal);

    // 赛事名称
    QLabel *titleLabel = new QLabel("Masters 2025", this);
    QFont titleFont("SF Pro", 20, QFont::Bold);
    titleFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    titleLabel->setFont(titleFont);
    titleLabel->move(25, 15); // Position the label at the top-left corner
    titleLabel->show();

    // 比赛轮次
    QLabel *roundLabel = new QLabel(matchTypeToString(match.round), this);
    QFont roundFont("SF Pro", 20, QFont::Bold);
    roundFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    roundLabel->setFont(roundFont);
    roundLabel->setAlignment(Qt::AlignRight);
    QFontMetrics fm(roundLabel->font());
    int roundLabelWidth = fm.horizontalAdvance(roundLabel->text());
    roundLabel->setGeometry(width() - roundLabelWidth - 25, 15, roundLabelWidth, 30); // Adjust the position and size
    roundLabel->show();

    // 水平分割线
    QFrame *dividerLine = new QFrame(this);
    dividerLine->setFrameShape(QFrame::HLine);
    dividerLine->setGeometry(0, 50, width(), 4); // Position the divider line
    dividerLine->show();

    // 选手 1 名字
    QLabel *player1FirstNameLabel = new QLabel(QString::fromStdString(match.player1_name.first_name), this);
    QFont player1FirstNameFont("SF Pro", 18);
    player1FirstNameFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    player1FirstNameLabel->setFont(player1FirstNameFont);
    player1FirstNameLabel->setAlignment(Qt::AlignRight);
    player1FirstNameLabel->setGeometry(width() / 2 - 70 - 200, 70, 200, 20); // Adjust the position and size
    player1FirstNameLabel->show();

    QLabel *player1LastNameLabel = new QLabel(QString::fromStdString(match.player1_name.last_name), this);
    QFont player1LastNameFont("SF Pro", 24, QFont::Bold);
    player1LastNameFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    player1LastNameLabel->setFont(player1LastNameFont);
    player1LastNameLabel->setAlignment(Qt::AlignRight);
    player1LastNameLabel->setGeometry(width() / 2 - 70 - 200, 90, 200, 30); // Adjust the position and size
    player1LastNameLabel->show();

    // 选手 2 名字
    QLabel *player2FirstNameLabel = new QLabel(QString::fromStdString(match.player2_name.first_name), this);
    QFont player2FirstNameFont("SF Pro", 18);
    player2FirstNameFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    player2FirstNameLabel->setFont(player2FirstNameFont);
    player2FirstNameLabel->setAlignment(Qt::AlignLeft);
    player2FirstNameLabel->setGeometry(width() / 2 + 70, 70, 200, 20); // Adjust the position and size
    player2FirstNameLabel->show();

    QLabel *player2LastNameLabel = new QLabel(QString::fromStdString(match.player2_name.last_name), this);
    QFont player2LastNameFont("SF Pro", 24, QFont::Bold);
    player2LastNameFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    player2LastNameLabel->setFont(player2LastNameFont);
    player2LastNameLabel->setAlignment(Qt::AlignLeft);
    player2LastNameLabel->setGeometry(width() / 2 + 70, 90, 200, 30); // Adjust the position and size
    player2LastNameLabel->show();

    // 选手 1 获胜局数
    QLabel *player1FramesLabel = new QLabel(QString::number(match.player1_frames), this);
    QFont framesFont("SF Pro", 26);
    framesFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    player1FramesLabel->setFont(framesFont);
    player1FramesLabel->setAlignment(Qt::AlignRight);
    player1FramesLabel->setGeometry(width() / 2 - 70 - 200, 130, 200, 32); // Adjust the position and size
    player1FramesLabel->show();

    // 选手 2 获胜局数
    QLabel *player2FramesLabel = new QLabel(QString::number(match.player2_frames), this);
    player2FramesLabel->setFont(framesFont);
    player2FramesLabel->setAlignment(Qt::AlignLeft);
    player2FramesLabel->setGeometry(width() / 2 + 70, 130, 200, 32); // Adjust the position and size
    player2FramesLabel->show();

    // FRAMES 标签
    QLabel *framesLabel = new QLabel("FRAMES", this);
    QFont framesTextFont("SF Pro", 20, QFont::Bold);
    framesTextFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    framesLabel->setFont(framesTextFont);
    framesLabel->setAlignment(Qt::AlignCenter);
    framesLabel->setGeometry(width() / 2 - 50, 130, 100, 30); // Adjust the position and size
    framesLabel->show();

    // 总局数标签
    QLabel *totalFramesLabel = new QLabel("("  + QString::number(match.frames) + ")", this);
    QFont totalFramesFont("SF Pro", 10);
    totalFramesFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    totalFramesLabel->setFont(totalFramesFont);
    totalFramesLabel->setAlignment(Qt::AlignCenter);
    totalFramesLabel->setGeometry(width() / 2 - 50, 150, 100, 20); // Adjust the position and size
    totalFramesLabel->show();

    updateScoreLabels();

    // POINTS 标签
    QLabel *pointsLabel = new QLabel("POINTS", this);
    QFont pointsTextFont("SF Pro", 20, QFont::Bold);
    pointsTextFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    pointsLabel->setFont(pointsTextFont);
    pointsLabel->setAlignment(Qt::AlignCenter);
    pointsLabel->setGeometry(width() / 2 - 50, 180, 100, 30); // Adjust the position and size
    pointsLabel->show();

    // 当前操作选手状态
    updateIsPlayer1();
}

void Window::updateFrame(Frame frame, bool isPlayer1) {
    currentFrame = frame;
    this->isPlayer1 = isPlayer1;
    // 根据 isPlayer1 更改选手状态
    updateIsPlayer1();
    // 更新选手得分
    updateScoreLabels();
}

void Window::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_1:
            std::cout << "Key 1 Pressed" << std::endl;
            emit keyScorePressed(1);
            break;
        case Qt::Key_2:
            std::cout << "Key 2 Pressed" << std::endl;
            emit keyScorePressed(2);
            break;
        case Qt::Key_3:
            std::cout << "Key 3 Pressed" << std::endl;
            emit keyScorePressed(3);
            break;
        case Qt::Key_4:
            std::cout << "Key 4 Pressed" << std::endl;
            emit keyScorePressed(4);
            break;
        case Qt::Key_5:
            std::cout << "Key 5 Pressed" << std::endl;
            emit keyScorePressed(5);
            break;
        case Qt::Key_6:
            std::cout << "Key 6 Pressed" << std::endl;
            emit keyScorePressed(6);
            break;
        case Qt::Key_7:
            std::cout << "Key 7 Pressed" << std::endl;
            emit keyScorePressed(7);
            break;
        case Qt::Key_F:
            std::cout << "Key F Pressed" << std::endl;
            emit keyFPressed();
            break;
        case Qt::Key_Backspace:
            std::cout << "Key Backspace Pressed" << std::endl;
            emit keyBackSpacePressed();
            break;
        case Qt::Key_Enter:
            std::cout << "Key Enter Pressed" << std::endl;
            emit keyEnterPressed();
            break;
        case Qt::Key_Space:
            std::cout << "Key Space Pressed" << std::endl;
            emit keySpacePressed();
            break;
    }
}
