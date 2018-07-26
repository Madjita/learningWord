#ifndef YANDEXSPEECHMODEL_H
#define YANDEXSPEECHMODEL_H

#include <QObject>

#include <yandexspeech.h>

#include <QMediaPlayer>
#include <QBuffer>

class YandexSpeechModel : public QObject
{
    Q_OBJECT
public:
    explicit YandexSpeechModel(QObject *parent = 0);

    QObject *qmlMediaPlayer;
    QMediaPlayer *player;
    QBuffer *buffer;

    YandexSpeech *ya;


    QVector<QByteArray> listArr;

signals:
    void signal_Get();
    void signal_Get2();

public slots:

    void slot_signal_Get();

    void slot_appendList(QByteArray arr);

    void slot_playVoice();

    void slot_stopVoice();
};

#endif // YANDEXSPEECHMODEL_H
