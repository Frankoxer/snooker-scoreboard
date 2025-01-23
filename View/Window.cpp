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

    setFixedSize(750, 360);
    whiteTextPalette.setColor(QPalette::WindowText, Qt::white);
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

void Window::updateFrameNumber() {
    if(player1FramesLabel) {
        delete player1FramesLabel;
        player1FramesLabel = nullptr;
    }
    if(player2FramesLabel) {
        delete player2FramesLabel;
        player2FramesLabel = nullptr;
    }

    unsigned int player1_frames = 0;
    unsigned int player2_frames = 0;

    for(auto it = match.frame_list.begin(); it != match.frame_list.end(); it++) {
        if(it->player1_points > it->player2_points) {
            player1_frames++;
        } else {
            player2_frames++;
        }
    }

    // 选手 1 获胜局数
    player1FramesLabel = new QLabel(QString::number(player1_frames), this);
    QFont framesFont("SF Pro", 26);
    framesFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    player1FramesLabel->setFont(framesFont);
    player1FramesLabel->setAlignment(Qt::AlignRight);
    player1FramesLabel->setGeometry(width() / 2 - 70 - 200, 140, 200, 32); // Adjust the position and size
    player1FramesLabel->setPalette(whiteTextPalette);
    player1FramesLabel->show();

    // 选手 2 获胜局数
    player2FramesLabel = new QLabel(QString::number(player2_frames), this);
    player2FramesLabel->setFont(framesFont);
    player2FramesLabel->setAlignment(Qt::AlignLeft);
    player2FramesLabel->setGeometry(width() / 2 + 70, 140, 200, 32); // Adjust the position and size
    player2FramesLabel->setPalette(whiteTextPalette);
    player2FramesLabel->show();
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
    painter1.setBrush(Qt::white);
    painter1.drawEllipse(0, 0, 20, 20);

    // QPixmap outlinedCircle(30, 30);
    // outlinedCircle.fill(Qt::transparent);
    // QPainter painter2(&outlinedCircle);
    // painter2.setRenderHint(QPainter::Antialiasing);
    // painter2.setBrush(Qt::NoBrush);
    // painter2.setPen(QPen(Qt::white, 1));
    // painter2.drawEllipse(0, 0, 20, 20);

    if (isPlayer1) {
        player1CircleLabel->setPixmap(filledCircle);
        // player2CircleLabel->setPixmap(outlinedCircle);
    } else {
        // player1CircleLabel->setPixmap(outlinedCircle);
        player2CircleLabel->setPixmap(filledCircle);
    }

    player1CircleLabel->setGeometry(width() / 2 - 50 - 230, 80, 30, 30); // Adjust the position and size
    player1CircleLabel->show();

    player2CircleLabel->setGeometry(width() / 2 + 50 + 200, 80, 30, 30); // Adjust the position and size
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
    player1CurrentScoreLabel->setGeometry(width() / 2 - 70 - 200, 190, 200, 50); // Adjust the position and size
    player1CurrentScoreLabel->setPalette(whiteTextPalette);
    player1CurrentScoreLabel->show();

    // 选手 2 当前局得分
    player2CurrentScoreLabel = new QLabel(QString::number(currentFrame.player2_points), this);
    player2CurrentScoreLabel->setFont(currentScoreFont);
    player2CurrentScoreLabel->setAlignment(Qt::AlignLeft);
    player2CurrentScoreLabel->setGeometry(width() / 2 + 70, 190, 200, 50); // Adjust the position and size
    player2CurrentScoreLabel->setPalette(whiteTextPalette);
    player2CurrentScoreLabel->show();
}

void Window::updateBreakLabels(unsigned int player1_break, unsigned int player2_break) {
    if(player1CurrentBreakLabel) {
        delete player1CurrentBreakLabel;
        player1CurrentBreakLabel = nullptr;
    }
    if(player2CurrentBreakLabel) {
        delete player2CurrentBreakLabel;
        player2CurrentBreakLabel = nullptr;
    }

    // 选手 1 当前局最高分
    player1CurrentBreakLabel = new QLabel(QString::number(player1_break) + "(" + QString::number(currentFrame.player1_max_break) + ")", this);
    QFont currentBreakFont("SF Pro", 28);
    currentBreakFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    player1CurrentBreakLabel->setFont(currentBreakFont);
    player1CurrentBreakLabel->setAlignment(Qt::AlignRight);
    player1CurrentBreakLabel->setGeometry(width() / 2 - 70 - 200, 270, 200, 30); // Adjust the position and size
    player1CurrentBreakLabel->setPalette(whiteTextPalette);
    player1CurrentBreakLabel->show();

    // 选手 2 当前局最高分
    player2CurrentBreakLabel = new QLabel("(" + QString::number(currentFrame.player2_max_break) + ")" + QString::number(player2_break), this);
    player2CurrentBreakLabel->setFont(currentBreakFont);
    player2CurrentBreakLabel->setAlignment(Qt::AlignLeft);
    player2CurrentBreakLabel->setGeometry(width() / 2 + 70, 270, 200, 30); // Adjust the position and size
    player2CurrentBreakLabel->setPalette(whiteTextPalette);
    player2CurrentBreakLabel->show();
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
        painter1.setBrush(isFoul ? Qt::red : Qt::white);
        painter1.setPen(QPen(Qt::red, 0));
        painter1.drawEllipse(0, 0, 20, 20);
        player1CircleLabel->setPixmap(filledCircle);
        player1CircleLabel->setGeometry(width() / 2 - 50 - 230, 80, 30, 30); // Adjust the position and size
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
        painter1.setBrush(isFoul ? Qt::red : Qt::white);
        painter1.setPen(QPen(Qt::red, 0));
        painter1.drawEllipse(0, 0, 20, 20);
        player2CircleLabel->setPixmap(filledCircle);
        player2CircleLabel->setGeometry(width() / 2 + 50 + 200, 80, 30, 30); // Adjust the position and size
        player2CircleLabel->show();
    }
}

void Window::initializeMatch(Match match, Frame frame, bool isPlayer1) {
    this->match = match;
    this->currentFrame = frame;
    this->isPlayer1 = isPlayer1;

    // 标题栏背景
    QLabel *title_background = new QLabel(this);
    title_background->setGeometry(0, 0, width(), 50);
    QPalette pal_titlebar = title_background->palette();
    pal_titlebar.setColor(QPalette::Window, QColor("#0C0932"));
    title_background->setAutoFillBackground(true);
    title_background->setPalette(pal_titlebar);
    title_background->show();

    // 赛事名称
    QLabel *titleLabel = new QLabel(QString::fromStdString(match.tournament_name), this);
    QFont titleFont("SF Pro", 20, QFont::Bold);
    titleFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    titleLabel->setFont(titleFont);
    titleLabel->setPalette(whiteTextPalette);
    titleLabel->move(25, 15); // Position the label at the top-left corner
    titleLabel->show();

    // 比赛轮次
    QLabel *roundLabel = new QLabel(matchTypeToString(match.round), this);
    QFont roundFont("SF Pro", 20, QFont::Bold);
    roundFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    roundLabel->setFont(roundFont);
    roundLabel->setPalette(whiteTextPalette);
    roundLabel->setAlignment(Qt::AlignRight);
    QFontMetrics fm(roundLabel->font());
    int roundLabelWidth = fm.horizontalAdvance(roundLabel->text());
    roundLabel->setGeometry(width() - roundLabelWidth - 25, 15, roundLabelWidth, 30); // Adjust the position and size
    roundLabel->show();

    // 选手姓名背景
    QLabel *player_background = new QLabel(this);
    player_background->setGeometry(0, 50, width(), 125 - 50);
    QPalette pal_player = player_background->palette();
    pal_player.setColor(QPalette::Window, QColor("#110E43"));
    player_background->setAutoFillBackground(true);
    player_background->setPalette(pal_player);
    player_background->show();

    // 选手 1 名字，强制全部大写
    QLabel *player1FirstNameLabel = new QLabel(QString::fromStdString(match.player1_name.first_name).toUpper(), this);
    QFont player1FirstNameFont("SF Pro", 18);
    player1FirstNameFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    player1FirstNameLabel->setFont(player1FirstNameFont);
    player1FirstNameLabel->setPalette(whiteTextPalette);
    player1FirstNameLabel->setAlignment(Qt::AlignRight);
    player1FirstNameLabel->setGeometry(width() / 2 - 70 - 200, 62, 200, 20); // Adjust the position and size
    player1FirstNameLabel->show();

    QLabel *player1LastNameLabel = new QLabel(QString::fromStdString(match.player1_name.last_name).toUpper(), this);
    QFont player1LastNameFont("SF Pro", 24, QFont::Bold);
    player1LastNameFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    player1LastNameLabel->setFont(player1LastNameFont);
    player1LastNameLabel->setPalette(whiteTextPalette);
    player1LastNameLabel->setAlignment(Qt::AlignRight);
    player1LastNameLabel->setGeometry(width() / 2 - 70 - 200, 82, 200, 30); // Adjust the position and size
    player1LastNameLabel->show();

    // 选手 2 名字
    QLabel *player2FirstNameLabel = new QLabel(QString::fromStdString(match.player2_name.first_name).toUpper(), this);
    QFont player2FirstNameFont("SF Pro", 18);
    player2FirstNameFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    player2FirstNameLabel->setFont(player2FirstNameFont);
    player2FirstNameLabel->setPalette(whiteTextPalette);
    player2FirstNameLabel->setAlignment(Qt::AlignLeft);
    player2FirstNameLabel->setGeometry(width() / 2 + 70, 62, 200, 20); // Adjust the position and size
    player2FirstNameLabel->show();

    QLabel *player2LastNameLabel = new QLabel(QString::fromStdString(match.player2_name.last_name).toUpper(), this);
    QFont player2LastNameFont("SF Pro", 24, QFont::Bold);
    player2LastNameFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    player2LastNameLabel->setFont(player2LastNameFont);
    player2LastNameLabel->setPalette(whiteTextPalette);
    player2LastNameLabel->setAlignment(Qt::AlignLeft);
    player2LastNameLabel->setGeometry(width() / 2 + 70, 82, 200, 30); // Adjust the position and size
    player2LastNameLabel->show();

    updateFrameNumber();

    // FRAMES、POINTS、BREAK 背景
    QLabel *frames_background = new QLabel(this);
    frames_background->setGeometry(0, 125, width(), 320 - 125);
    QPalette pal_frames = frames_background->palette();
    pal_frames.setColor(QPalette::Window, QColor("#201567"));
    frames_background->setAutoFillBackground(true);
    frames_background->setPalette(pal_frames);
    frames_background->show();

    // FRAMES 标签
    QLabel *framesLabel = new QLabel("FRAMES", this);
    QFont framesTextFont("SF Pro", 20, QFont::Bold);
    framesTextFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    framesLabel->setFont(framesTextFont);
    framesLabel->setPalette(whiteTextPalette);
    framesLabel->setAlignment(Qt::AlignCenter);
    framesLabel->setGeometry(width() / 2 - 50, 140, 100, 30); // Adjust the position and size
    framesLabel->show();

    // 总局数标签
    QLabel *totalFramesLabel = new QLabel("("  + QString::number(match.frames) + ")", this);
    QFont totalFramesFont("SF Pro", 10);
    totalFramesFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    totalFramesLabel->setFont(totalFramesFont);
    totalFramesLabel->setPalette(whiteTextPalette);
    totalFramesLabel->setAlignment(Qt::AlignCenter);
    totalFramesLabel->setGeometry(width() / 2 - 50, 160, 100, 20); // Adjust the position and size
    totalFramesLabel->show();

    updateFrameNumber();

    updateScoreLabels();

    // POINTS 标签
    QLabel *pointsLabel = new QLabel("POINTS", this);
    QFont pointsTextFont("SF Pro", 20, QFont::Bold);
    pointsTextFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    pointsLabel->setFont(pointsTextFont);
    pointsLabel->setPalette(whiteTextPalette);
    pointsLabel->setAlignment(Qt::AlignCenter);
    pointsLabel->setGeometry(width() / 2 - 50, 200, 100, 30); // Adjust the position and size
    pointsLabel->show();

    updateBreakLabels(0, 0);

    // BREAK 标签
    QLabel *breakLabel = new QLabel("BREAK", this);
    QFont breakTextFont("SF Pro", 20, QFont::Bold);
    breakTextFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    breakLabel->setFont(breakTextFont);
    breakLabel->setPalette(whiteTextPalette);
    breakLabel->setAlignment(Qt::AlignCenter);
    breakLabel->setGeometry(width() / 2 - 50, 270, 100, 30); // Adjust the position and size
    breakLabel->show();

    // 当前操作选手状态
    updateIsPlayer1();

    // 操作提示背景
    QLabel *instruction_background = new QLabel(this);
    instruction_background->setGeometry(0, 320, width(), 360 - 320);
    QPalette pal_instruction = instruction_background->palette();
    pal_instruction.setColor(QPalette::Window, QColor("#120B42"));
    instruction_background->setAutoFillBackground(true);
    instruction_background->setPalette(pal_instruction);
    instruction_background->show();

    // 操作提示
    QLabel *instructionLabel = new QLabel("1-7: score   F: foul   Space: exchange   Enter: confirm", this);
    QFont instructionFont("SF Pro", 12);
    instructionFont.setLetterSpacing(QFont::AbsoluteSpacing, spacing);
    instructionLabel->setFont(instructionFont);
    instructionLabel->setPalette(whiteTextPalette);
    instructionLabel->setAlignment(Qt::AlignCenter);
    instructionLabel->setGeometry(0, 320, width(), 40); // Adjust the position and size
}

void Window::updateFrame(Frame frame, bool isPlayer1, unsigned int player1_break, unsigned int player2_break) {
    currentFrame = frame;
    this->isPlayer1 = isPlayer1;
    // 根据 isPlayer1 更改选手状态
    updateIsPlayer1();
    // 更新选手得分
    updateScoreLabels();
    // 更新选手单杆得分
    updateBreakLabels(player1_break, player2_break);
}

void Window::showNewFrame(Match match, Frame frame) {
    this->match = match;
    currentFrame = frame;
    this->isPlayer1 = true;
    updateScoreLabels();
    updateBreakLabels(0, 0);
    updateFrameNumber();
    updateIsPlayer1();
    updateBreakLabels(0, 0);
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
        case Qt::Key_Return:
            std::cout << "Key Enter Pressed" << std::endl;
            emit keyEnterPressed();
            break;
        case Qt::Key_Space:
            std::cout << "Key Space Pressed" << std::endl;
            emit keySpacePressed();
            break;
    }
}
