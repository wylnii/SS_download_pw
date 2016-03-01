#include <QCoreApplication>
#include <downloader.h>
#include <QtGui/QTextDocument>
/*
 * 从http://www.ishadowsocks.com/网站自动下载最新的SS账号密码
 *
 * 只用于更新从上述网站上得到A|B|C服务器的密码
 *
 * gui-config-template.json 为模板文件，文件中的%A|%B|%C为相应的密码替代处，其他不变
 * 得到的gui-config.json文件只是把模板文件的%A|%B|%C替换为网站上的密码
 *
 * 此程序下的所有文件和shadowsocks程序放在同一目录下
 *
 */

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString url;
    if(argc > 1)
        url = argv[2];
    else
        url = "http://www.ishadowsocks.com/";

    Downloader *myDownLoader = new Downloader;
    myDownLoader->setURL(url);
    myDownLoader->startDownload();
    QEventLoop loop;
    QObject::connect(myDownLoader,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();

    QFile file(myDownLoader->fileName);
    if(file.open(QFile::ReadOnly))
    {
        QByteArray text = file.readAll();
        file.close();
        file.remove();//删除临时文件
        QString data = QString::fromUtf8(text);
        QRegExp exp("[A|B|C]密码:(\\d+)");
        int pos = 0;
        QFile config("gui-config-template.json");
        if(config.exists() && config.open(QFile::ReadWrite))
        {
            QString filePath = "./gui-config.json";
            qDebug()<<filePath;
            QString text_config = config.readAll();
            config.close();
            while ((pos = exp.indexIn(data,pos)) != -1)
            {
                pos += exp.matchedLength();
                text_config = text_config.replace(QString("%%1").arg(exp.cap(0).at(0).toLatin1()),exp.cap(1));
                qDebug()<<pos<<exp.capturedTexts();
            }
            QFile new_config(filePath);
            new_config.open(QFile::ReadWrite);
            new_config.write(text_config.toLocal8Bit());
            new_config.close();
            qDebug()<<text_config;
        }
    }
    system("pause");

    a.exit();
}
