#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QTimer *timer;
    void keyPressEvent(QKeyEvent *event);
    void startTimer();
    void stopTimer();
    void compare();

private slots:
    void on_rec_clicked();
    void timercounter();
};

#endif // WIDGET_H
