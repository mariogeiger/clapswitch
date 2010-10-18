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


#define DISABLED 0
#define PENDING  1
#define RUNNING  2

#define MAXIMUM_BEAT 20

#define NEEDCOMPARE 0

#define START_TIMER_BEAT startTimer();

#define STOP_TIMER_BEAT stopTimer();

#define TIMER_BEAT_ISRUNNING timer->isActive()

volatile uint8_t beat;


uint8_t rec_beat[MAXIMUM_BEAT];
uint8_t rec_size;

uint8_t tmp_beat[MAXIMUM_BEAT];
uint8_t tmp_size;

uint8_t record_state;

uint8_t flag_clap;


uint8_t i;
uint16_t m, n;
uint16_t d;


void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        if (!TIMER_BEAT_ISRUNNING) {

            START_TIMER_BEAT;

            switch (record_state) {
            case DISABLED:
            case RUNNING:
                record_state = DISABLED;
                tmp_size = 0;
                break;
            case PENDING:
                record_state = RUNNING;
                rec_size = 0;
                break;
            default:
                break;
            }

        } else {

            if (record_state == RUNNING) {

                rec_beat[rec_size] = beat;
                qDebug("%d", rec_beat[rec_size]);
                rec_size++;

                beat = 0;

                if (rec_size == MAXIMUM_BEAT) {
                    STOP_TIMER_BEAT;
                }

            } else {

                tmp_beat[tmp_size] = beat;
                qDebug("%d %d", tmp_beat[tmp_size], rec_beat[tmp_size]);
                tmp_size++;

                beat = 0;

                if (tmp_size == rec_size) {
                    STOP_TIMER_BEAT;
                    this->compare();
                }

            }
        }
    }
}

void Widget::on_rec_clicked()
{
    STOP_TIMER_BEAT;
    record_state = PENDING;
    ui->rec->setEnabled(false);
}

void Widget::timercounter()
{
    beat++;
    if (beat == 0) {
            STOP_TIMER_BEAT;
    }
}

void Widget::startTimer()
{
    timer->start();
    ui->led->setText("listening...");
}

void Widget::stopTimer()
{
    qDebug("-");
    timer->stop();
    ui->led->clear();
    ui->rec->setEnabled(true);
}

void Widget::compare()
{
    for (i = 1; i < rec_size; ++i) {
        m = rec_beat[i - 1] * tmp_beat[i];
        n = tmp_beat[i - 1] * rec_beat[i];

        if (m > n)
            d = m - n;
        else
            d = n - m;

        if (d > (m + n) / (200 / 50)) {
            // test fail
            return;
        }
    }

    static uint8_t on = 0;
    on = !on;
    ui->power->setText(on ? "Power ON" : "Power OFF");
}
