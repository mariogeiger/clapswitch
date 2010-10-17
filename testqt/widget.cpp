#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(12);
    connect(timer, SIGNAL(timeout()), this, SLOT(timercounter()));
}

Widget::~Widget()
{
    delete ui;
}

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;


uint8_t rec_beat[20];
uint8_t rec_size;

uint8_t tmp_beat[20];
uint8_t tmp_size;

uint8_t counter;

uint8_t record = 0;

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        if (!timer->isActive()) {
            startTimer();

            if (record) {
                rec_size = 0;
            } else {
                tmp_size = 0;
            }
        } else {
            if (record) {
                qDebug("rec[%d] == %d", rec_size, counter);
                rec_beat[rec_size] = counter;
                rec_size++;
                startTimer();
            } else {
                if (tmp_size < rec_size) {
                    qDebug("tmp[%d] == %d, %d", tmp_size, counter, rec_beat[tmp_size]);
                    tmp_beat[tmp_size] = counter;
                    startTimer();
                }

                tmp_size++;

                if (tmp_size == rec_size) {
                    compare();
                    stopTimer();
                }
            }
        }
    }
}

void Widget::on_rec_clicked()
{
    record = 1;
    ui->rec->setEnabled(false);
}

void Widget::timercounter()
{
    counter++;
    if (counter == 255) {
        stopTimer();
    }
}

void Widget::startTimer()
{
//    qDebug("timer start");
    counter = 0;
    timer->start();
}

void Widget::stopTimer()
{
    qDebug("timer stop");
    timer->stop();
    record = 0;
    ui->rec->setEnabled(true);

}

void Widget::compare()
{
    qDebug("compare");

    uint8_t rec_first = rec_beat[0];
    uint8_t tmp_first = tmp_beat[0];

    uint8_t i;

    for (i = 1; i < rec_size; ++i) {
        uint16_t m = rec_first * tmp_beat[i];
        uint16_t n = tmp_first * rec_beat[i];

        uint16_t dif;
        if (m > n)
            dif = m - n;
        else
            dif = n - m;

        uint16_t err = (m + n) / 4;

        qDebug("%d / %d", dif, err);

        if (dif > err) {
            qDebug("error : %d", i);
            return;
        }

    }

    ui->power->setChecked(!ui->power->isChecked());
}
