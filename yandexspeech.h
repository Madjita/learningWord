#ifndef YANDEXSPEECH_H
#define YANDEXSPEECH_H

#include <QObject>


#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QUrl>
#include <QUrlQuery>

#include <QThread>

#include <QMediaPlayer>
#include <QBuffer>


#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QResource>

#include <bdata.h>

class YandexSpeech : public QObject
{
    Q_OBJECT
public:
    explicit YandexSpeech(QObject *parent = 0);

    QNetworkAccessManager *mngr;
    QNetworkAccessManager *mngr2;

    QObject *qmlMediaPlayer;
    QMediaPlayer *player;
    QBuffer *buffer;


    QString textWord;
    QString textWordTranslate;


    QNetworkRequest request2;


    BData* bd;

signals:
    void playQML(QByteArray arr, QString file);
    void playQML2(QByteArray arr, QString file);

    void startQML(QString file);

public slots:
    void getResponse(QNetworkReply *reply);

    void getResponse2(QNetworkReply *reply);

    void prosecc();
    void prosecc2();

    void get(QString text);

    void get2(QString text);

    void setBd(BData* bdSet);


};

#endif // YANDEXSPEECH_H
