#include <QGuiApplication>
#include <QQmlApplicationEngine>

//////////////////////////////
#include <QTextToSpeech>
#include <QLoggingCategory>

//////////////////
#include <QQmlContext>
/////////////////
#include <QProcess>

#include <yandexspeech.h>
#include <bdata.h>
#include <learnwork.h>


//////////////////////////

#include <QSysInfo>

#include <QStandardPaths>
#include <QSettings>
#include <QQuickStyle>

int main(int argc, char *argv[])
{

    if ( QSysInfo::WindowsVersion == QSysInfo::WV_WINDOWS10 )
        qDebug() << "Program is being run in Windows 10.";


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    QSettings settings;
    QString style = QQuickStyle::name();
    if (!style.isEmpty())
        settings.setValue("style", style);
    else
        QQuickStyle::setStyle(settings.value("style").toString());


    QQmlApplicationEngine engine;


    QLoggingCategory::setFilterRules(QStringLiteral("qt.speech.tts=true \n qt.speech.tts.*=true"));

    QTextToSpeech *m_speech = new QTextToSpeech();


    YandexSpeech *ya = new YandexSpeech();


#if defined(Q_OS_ANDROID)
    QDir dir;

    if(dir.mkdir(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first() + "/" + "LearningWord"))
    {
        qDebug () << "Создали папку LearningWord в стартовой директории";
    }
    else
    {
        qDebug () << "Папка  LearningWord уже созданна в стартовой директории";
    }

    if(dir.mkdir(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first() + "/" + "LearningWord"+ "/" + "bd"))
    {
        qDebug () << "Создали папку bd в директории LearningWord";
    }
    else
    {
        qDebug () << "Папка bd уже созданна в директории LearningWord";
    }




#endif



    BData* BD = new BData(); // Создали класс для работы с базой данных

    BD->moveToThread(new QThread()); //Поместили класс для работы с БД в новый поток.

    BD->thread()->start(); // Запускаем поток класса для работы с БД

    BD->connect(); // Подключаемся к БД



    ya->setBd(BD);


    LearnWork* learnWork = new LearnWork();

    learnWork->setBd(BD);


//    QFileSystemModel qdm;
//    qdm.setFilter( QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files );

//    const QString root = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).first() + "/" + "LearningWord";
//    qdm.setRootPath(root);




//    QObject::connect(&qdm, &QFileSystemModel::directoryLoaded, [&](const QString& path){
//        //Update model index after directory completely loaded
//        engine.rootContext()->setContextProperty("myModelIndex", qdm.index(path));
//    });

//    engine.rootContext()->setContextProperty("myModelIndex", qdm.index(""));
//    engine.rootContext()->setContextProperty("myFileModel", &qdm);


    engine.rootContext()->setContextProperty("ya", ya);
    engine.rootContext()->setContextProperty("m_speech", m_speech);
    engine.rootContext()->setContextProperty("learnWork", learnWork);


    engine.load(QUrl(QLatin1String("qrc:/main.qml")));





    // qDebug() << QProcess::systemEnvironment();



    return app.exec();
}
