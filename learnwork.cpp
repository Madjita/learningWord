#include "learnwork.h"

LearnWork::LearnWork(QObject *parent) : QObject(parent),
    Step(0),
    countReplay(3),
    m_ListProverkaItem(new QList<QObject*>()),
    m_listFolder(new QList<QObject*>()),
    flagReplay(false)
{


}

const QList<QObject *> LearnWork::listProverka() const
{
    return *m_ListProverkaItem;
}

const QList<QObject *> LearnWork::listFolder() const
{
    return *m_listFolder;
}

void LearnWork::setBd(BData *bdSet)
{
    bd = bdSet;

    QSqlQueryModel* SQL_id  =  bd->zaprosQueryModel("SELECT DISTINCT folder.Id,[NameFolder],[IdNameFolderIn] FROM  folder"
                                                    " Where folder.IdNameFolderIn = 0",1);

    QSqlQueryModel* SQL_id_folder;

    QSqlQueryModel* SQL_id_word;

    QString Id;
    QString Name;
    QString IdNameFolderIn;
    QString Id_in;
    QString Name_in;
    QString IdNameFolderIn_in;
    QDir dir;
    QString folder;
    QString rootFolder;

    m_ListProverkaItem->clear();
    m_listFolder->clear();

    //пройти по всем папкам и найти с id папки остальные папки
    for(int i=0;i< SQL_id->rowCount();i++)
    {

        Id = SQL_id->data(SQL_id->index(i,0), Qt::EditRole).toString();
        Name = SQL_id->data(SQL_id->index(i,1), Qt::EditRole).toString();
        IdNameFolderIn = SQL_id->data(SQL_id->index(i,2), Qt::EditRole).toString();

        folder = Name;

        if(!dir.mkdir(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first() + "/" + "LearningWord"+ "/" + folder))
        {
            rootFolder = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first() + "/" + "LearningWord"+ "/" + folder;

            qDebug () << "Папка "+folder+" уже созданна в директории LearningWord";

            folderList.append(new FolderList(Id,Name,IdNameFolderIn));

            m_listFolder->append(folderList.last());

            SQL_id_folder  =  bd->zaprosQueryModel("SELECT DISTINCT [NameFolder] FROM  folder"
                                                   " Where folder.IdNameFolderIn = "+Id+"",2);


            if(dir.mkdir(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first() + "/" + "LearningWord"+ "/" + folder+ "/" + "image"))
            {
                qDebug () << "Создали папку image в директории LearningWord";
            }
            else
            {
                qDebug () << "Папка image уже созданна в директории LearningWord";
            }


            for(int j=0;j< SQL_id_folder->rowCount();j++)
            {
                Id_in = SQL_id_folder->data(SQL_id_folder->index(j,0), Qt::EditRole).toString();
                Name_in = SQL_id_folder->data(SQL_id_folder->index(j,1), Qt::EditRole).toString();
                IdNameFolderIn_in = SQL_id_folder->data(SQL_id_folder->index(j,2), Qt::EditRole).toString();

                folderList.last()->setNextFolderList(new FolderList(Id_in,Name_in,IdNameFolderIn_in));

            }

            SQL_id_word  =  bd->zaprosQueryModel("SELECT Word.Id,[Word],[Transcription],[Translation],[Image],[routeSound],[routeSoundTranslate] FROM Word"
                                                 " JOIN Link_folder_word ON Link_folder_word.IdWord = Word.id"
                                                 " Join folder ON Link_folder_word.IdFolder = folder.id"
                                                 " Where folder.Id = "+Id+"",3);




            for(int j=0;j< SQL_id_word->rowCount();j++)
            {

                QString Id = SQL_id_word->data(SQL_id_word->index(j,0), Qt::EditRole).toString();
                QString Word = SQL_id_word->data(SQL_id_word->index(j,1), Qt::EditRole).toString();
                QString Transcription = SQL_id_word->data(SQL_id_word->index(j,2), Qt::EditRole).toString();
                QString Translation = SQL_id_word->data(SQL_id_word->index(j,3), Qt::EditRole).toString();
                QString Image = SQL_id_word->data(SQL_id_word->index(j,4), Qt::EditRole).toString();


                //file:///storage/emulated/0/LearningWord/
                QString routeSound ="file://" + rootFolder +"/" + SQL_id_word->data(SQL_id_word->index(j,5), Qt::EditRole).toString();
                QString routeSoundTranslate ="file://" + rootFolder +"/" +  SQL_id_word->data(SQL_id_word->index(j,6), Qt::EditRole).toString();



                folderList.last()->setWordListMy(new WordList(Id,Word,Transcription,Translation,Image,routeSound,routeSoundTranslate));

                m_ListProverkaItem->append(folderList.last()->WordListMy[j]);
                //Сделать загрузку на страницу по другому через папку а не на прямую

            }


            emit ListProverkaChanged(*m_ListProverkaItem);
        }
        else
        {
            qDebug () << "Папка "+folder+" не созданна в директории LearningWord. Удаление из базы";
            bd->zaprosQueryModel("DELETE [IdNameFolderIn] FROM  folder  Where folder.NameFolder = "+folder+"");
        }

    }

    emit listFolderChanged(*m_listFolder);


}

void LearnWork::startWork()
{
    //  QSqlQueryModel* SQL_id  =  bd->zaprosQueryModel("SELECT * FROM Word");

    Step = 0;



    countReplayStep = countReplay;


    emit signal_Next(folderList.last()->WordListMy[Step]->routeSound,folderList.last()->WordListMy[Step]->routeSoundTranslate,folderList.last()->WordListMy[Step]->Image);


    //    for(int i=0;i< SQL_id->rowCount();i++)
    //    {
    //        qDebug () <<folderList.last()->WordListMy.last()->Id;
    //        qDebug () <<folderList.last()->WordListMy.last()->Word;
    //        qDebug () <<folderList.last()->WordListMy.last()->Transcription;
    //        qDebug () <<folderList.last()->WordListMy.last()->Translation;
    //        qDebug () <<folderList.last()->WordListMy.last()->Image;

    //        qDebug () <<folderList.last()->WordListMy.last()->routeSound;
    //        qDebug () <<folderList.last()->WordListMy.last()->routeSoundTranslate;

    //    }


}

void LearnWork::startNext()
{
    Step++;

    if(Step < 18)
    {
        emit signal_Next(folderList.last()->WordListMy[Step]->routeSound,folderList.last()->WordListMy[Step]->routeSoundTranslate,folderList.last()->WordListMy[Step]->Image);
    }
    else
    {
        Step = 0;

        if(flagReplay)
        {
            startWork();
        }
    }
}

int LearnWork::slot_countReplay()
{
    countReplayStep --;

    if(countReplayStep < 0 )
    {
        countReplayStep = countReplay;
        countReplayStep --;
    }

    return countReplayStep;
}

void LearnWork::slot_setReplay(int replay)
{
    countReplay = replay;
}

void LearnWork::slot_setFlagReplay(bool replay)
{
    flagReplay = replay;
}



WordList::WordList(QString IdGet, QString WordGet, QString TranscriptionGet, QString TranslationGet, QString ImageGet, QString routeSoundGet, QString routeSoundTranslateGet, QObject *parent):
    Id(IdGet),
    Word(WordGet),
    Transcription(TranscriptionGet),
    Translation(TranslationGet),
    Image(ImageGet),
    routeSound(routeSoundGet),
    routeSoundTranslate(routeSoundTranslateGet)
{

}

const QString &WordList::WordQML() const
{
    return Word;
}

const QString &WordList::TranslationQML() const
{
    return Translation;
}



FolderList::FolderList(QString IdGet, QString NameGet, QString IdNameFolderInGet, QObject *parent):
    Id(IdGet),
    Name(NameGet),
    IdNameFolderIn(IdNameFolderInGet),
    m_ListProverkaItem2(new QList<QObject*>()),
    m_listFolder2(new QList<QObject*>())
{
    m_listFolder2->clear();
    m_ListProverkaItem2->clear();

}

const QString &FolderList::NameQML() const
{
    return Name;
}

const QList<QObject *> FolderList::listProverka2() const
{
    return  *m_ListProverkaItem2;
}

const QList<QObject *> FolderList::listFolder2() const
{
    return *m_listFolder2;
}

void FolderList::setNextFolderList(FolderList *itemFolder)
{
    nextFolderList.append(itemFolder);

    m_listFolder2->append(itemFolder);

    emit listFolderChanged2(*m_listFolder2);
}

void FolderList::setWordListMy(WordList *itemWord)
{
    WordListMy.append(itemWord);

    m_ListProverkaItem2->append(itemWord);

    emit ListProverkaChanged2(*m_ListProverkaItem2);
}

QString FolderList::countFolder()
{
    return QString::number(nextFolderList.count());
}

QString FolderList::countWordTerm()
{
    return QString::number(WordListMy.count());
}



