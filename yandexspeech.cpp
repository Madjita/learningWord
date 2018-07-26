#include "yandexspeech.h"


YandexSpeech::YandexSpeech(QObject *parent) : QObject(parent)
{

    player = new QMediaPlayer();
    buffer = new QBuffer(player);
}

void YandexSpeech::getResponse(QNetworkReply *reply)
{
    if( reply->error() == QNetworkReply::NoError )
    {
        //QString data = QString::fromUtf8( reply->readAll() );


        QByteArray arr = reply->readAll();

        qDebug() << arr;



        //        buffer->setData(arr);
        //        buffer->open(QIODevice::ReadOnly);

        //        player->setMedia(QMediaContent(),buffer);

        //        player->play();

#if defined(Q_OS_WIN)


        QFile saveFile(QDir::currentPath()+"/"+textWord+".wav");
        saveFile.open(QIODevice::WriteOnly);
        qDebug () <<QDir::currentPath();

        if (saveFile.isOpen()){



            qDebug() << "Hellow write";
            saveFile.write(arr);
        }

        saveFile.close();

        emit playQML(arr,QDir::currentPath()+"/"+textWord+".wav");

#elif defined(Q_OS_ANDROID)

        // QFile saveFile(QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first()+"/"+textWord+".wav"); //+"/qml/"+QString("/music/zap.wav"));


        QFile saveFile(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first()+ "/" + "LearningWord"+"/"+textWord+".wav"); //+"/qml/"+QString("/music/zap.wav"));
        saveFile.open(QIODevice::WriteOnly);


        // qDebug () <<QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first()+ "/"+textWord+".wav";


        if (saveFile.isOpen()){



            qDebug() << "Hellow write";
            saveFile.write(arr);
        }

        saveFile.close();

        emit playQML(arr,"file://"+QString(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first()+ "/" + "LearningWord"+"/"+textWord+".wav"));

#endif



        // Q_INIT_RESOURCE(qml);


    }


    qDebug () <<  reply->error();

    // Мы сами должны освободить память для reply
    // Однако делать это через delete нельзя
    reply->deleteLater();
}

void YandexSpeech::getResponse2(QNetworkReply *reply)
{
    if( reply->error() == QNetworkReply::NoError )
    {
        //QString data = QString::fromUtf8( reply->readAll() );


        QByteArray arr = reply->readAll();

        qDebug() << arr;



        //        buffer->setData(arr);
        //        buffer->open(QIODevice::ReadOnly);

        //        player->setMedia(QMediaContent(),buffer);

        //        player->play();

#if defined(Q_OS_WIN)


        QFile saveFile(QDir::currentPath()+"/"+textWordTranslate+".wav");
        saveFile.open(QIODevice::WriteOnly);
        qDebug () <<QDir::currentPath();

        if (saveFile.isOpen()){



            qDebug() << "Hellow write";
            saveFile.write(arr);
        }

        saveFile.close();

        emit playQML2(arr,QDir::currentPath()+"/"+textWordTranslate+".wav");

#elif defined(Q_OS_ANDROID)

        // QFile saveFile(QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first()+"/"+textWordTranslate+".wav"); //+"/qml/"+QString("/music/zap.wav"));


        QFile saveFile(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first()+ "/" + "LearningWord"+"/"+textWordTranslate+".wav"); //+"/qml/"+QString("/music/zap.wav"));
        saveFile.open(QIODevice::WriteOnly);


        //   qDebug () <<QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first()+ "/"+textWordTranslate+".wav";



        if (saveFile.isOpen()){



            qDebug() << "Hellow write";
            saveFile.write(arr);
        }

        saveFile.close();

        emit playQML2(arr,"file://"+QString(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first()+ "/" + "LearningWord"+"/"+textWordTranslate+".wav"));

#endif



        // Q_INIT_RESOURCE(qml);


    }


    qDebug () <<  reply->error();

    // Мы сами должны освободить память для reply
    // Однако делать это через delete нельзя
    reply->deleteLater();
}

void YandexSpeech::prosecc()
{
    mngr = new QNetworkAccessManager();

    connect(mngr,&QNetworkAccessManager::finished,this,&YandexSpeech::getResponse);

}

void YandexSpeech::prosecc2()
{
    mngr2 = new QNetworkAccessManager();

    connect(mngr2,&QNetworkAccessManager::finished,this,&YandexSpeech::getResponse2);
}



void YandexSpeech::get(QString text)
{

    qDebug () << text;

    textWord = text;

    textWordTranslate = textWord + "Translate";


    QString language = "en-US"; //en-SU; Hellow%20my%20friend

    //    QNetworkRequest request2(QUrl("https://tts.voicetech.yandex.net/generate?text="+text+"&format=mp3&lang="+language+"&speaker=jane&emotion=good&key=cfc7ce97-9320-4e12-8ce6-72e156fc3089"));


    request2.setUrl(QUrl("https://tts.voicetech.yandex.net/generate?text="+text+"&format=mp3&lang="+language+"&speaker=jane&emotion=good&key=cfc7ce97-9320-4e12-8ce6-72e156fc3089"));

    mngr->get(request2);
}

void YandexSpeech::get2(QString text)
{

    QString language = "ru-RU"; //en-SU;

    request2.setUrl(QUrl("https://tts.voicetech.yandex.net/generate?text="+text+"&format=mp3&lang="+language+"&speaker=jane&emotion=good&key=cfc7ce97-9320-4e12-8ce6-72e156fc3089"));

    mngr2->get(request2);
}

void YandexSpeech::setBd(BData *bdSet)
{
    bd = bdSet;
}

