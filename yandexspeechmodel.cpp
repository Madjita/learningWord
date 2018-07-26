#include "yandexspeechmodel.h"

YandexSpeechModel::YandexSpeechModel(QObject *parent) : QObject(parent)
{

    ya = new YandexSpeech();



    QObject::connect(this,&YandexSpeechModel::signal_Get,ya,&YandexSpeech::get,Qt::QueuedConnection);
    QObject::connect(this,&YandexSpeechModel::signal_Get2,ya,&YandexSpeech::get2,Qt::QueuedConnection);



    ya->moveToThread(new QThread);

    QObject::connect(ya->thread(),&QThread::started,ya,&YandexSpeech::prosecc);

    ya->thread()->start();

    QObject::connect(ya,&YandexSpeech::playQML,this,&YandexSpeechModel::slot_playVoice);

    player = new QMediaPlayer();

    buffer = new QBuffer(player);

    QObject::connect(player,&QMediaPlayer::stateChanged,this,&YandexSpeechModel::slot_stopVoice);

}

void YandexSpeechModel::slot_signal_Get()
{
    emit signal_Get();
}

void YandexSpeechModel::slot_playVoice()
{
    for(int i=0;i < listArr.count();i++)
    {
        buffer->close();

        buffer->setData(listArr[i]);
        buffer->open(QIODevice::ReadOnly);

        player->setMedia(QMediaContent(),buffer);

        player->play();

    }

}
void YandexSpeechModel::slot_appendList(QByteArray arr)
{

    listArr.append(arr);

    if(listArr.count() <3)
    {
     emit signal_Get2();
    }

}

void YandexSpeechModel::slot_stopVoice()
{
//    qDebug () << player->state() ;

//    if( player->state() ==  player->StoppedState)
//    {
//        emit signal_Get2();
//    }
}

