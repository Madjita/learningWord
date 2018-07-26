#ifndef LEARNWORK_H
#define LEARNWORK_H

#include <QObject>

#include <QtDebug>

#include <bdata.h>

#include <QSysInfo>


class WordList;

class FolderList : public QObject
{
    Q_OBJECT
   public:
    explicit FolderList(QString IdGet,QString NameGet,QString IdNameFolderInGet,QObject *parent = 0);


    QString Id;
    QString Name;
    QString IdNameFolderIn;

    //Name
    Q_PROPERTY(QString NameQML READ NameQML NOTIFY NameChanged)
    const QString & NameQML() const;



    Q_PROPERTY(QList<QObject*> listProverka2 READ listProverka2 NOTIFY ListProverkaChanged2);

    const QList<QObject*> listProverka2() const;

    QList<QObject*>* m_ListProverkaItem2;


    Q_PROPERTY(QList<QObject*> listFolder2 READ listFolder2 NOTIFY listFolderChanged2);

    const QList<QObject*> listFolder2() const;

    QList<QObject*>* m_listFolder2;





    QVector<FolderList*> nextFolderList;

    QVector<WordList *> WordListMy;


    void setNextFolderList(FolderList*);

    void setWordListMy(WordList*);

signals:
    void NameChanged(QString);

    void ListProverkaChanged2(QList<QObject*>);
    void listFolderChanged2(QList<QObject*>);


public slots :
    QString countFolder();

    QString countWordTerm();


};

class WordList : public QObject
{
    Q_OBJECT
   public:
    explicit WordList(QString IdGet,QString WordGet,QString TranscriptionGet,QString TranslationGet,QString ImageGet,QString routeSoundGet,QString routeSoundTranslateGet,QObject *parent = 0);


    QString Id;
    QString Word;
    QString Transcription;
    QString Translation;
    QString Image;
    QString routeSound;
    QString routeSoundTranslate;

    //Word
    Q_PROPERTY(QString WordQML READ WordQML NOTIFY WordChanged)
    const QString & WordQML() const;

    //Translation
    Q_PROPERTY(QString TranslationQML READ TranslationQML NOTIFY TranslationChanged)
    const QString &TranslationQML() const;


signals:
    void WordChanged(QString);
    void TranslationChanged(QString);


};


class LearnWork : public QObject
{
    Q_OBJECT
public:
    explicit LearnWork(QObject *parent = 0);

    BData* bd;



   // WordList Word[18];

    QVector<FolderList*> folderList;

    int Step;
    int countReplay;
    int countReplayStep;

    bool flagReplay;

    Q_PROPERTY(QList<QObject*> listProverka READ listProverka NOTIFY ListProverkaChanged);

    const QList<QObject*> listProverka() const;

    QList<QObject*>* m_ListProverkaItem;


    Q_PROPERTY(QList<QObject*> listFolder READ listFolder NOTIFY listFolderChanged);

    const QList<QObject*> listFolder() const;

    QList<QObject*>* m_listFolder;

signals:

    void signal_StartWork();

    void signal_Next(QString fileSound,QString fileSoundTranslate, QString fileImage);

    void ListProverkaChanged(QList<QObject*>);

    void listFolderChanged(QList<QObject*>);


public slots:

    void setBd(BData* bdSet);


    void startWork();

    void startNext();


    int slot_countReplay();

    void slot_setReplay(int replay);

    void slot_setFlagReplay(bool replay);



};

#endif // LEARNWORK_H
