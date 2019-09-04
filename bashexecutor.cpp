#include "bashexecutor.h"

#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QApplication>

BashExecutor::BashExecutor(QObject *parent)
    : QObject( parent )
    , _process( new QProcess() )
{
    connect( _process.get(), &QProcess::readyReadStandardOutput,
             this,           &BashExecutor::slotReadData );
    connect( _process.get(), &QProcess::readyReadStandardError,
             this,           &BashExecutor::slotReadError );

}

BashExecutor::~BashExecutor()
{
    _process->kill();
}

bool BashExecutor::runScript(const QString &filepath)
{
    QFileInfo fileInfo( filepath );

    QString pwd = fileInfo.dir().path();
    QString shortFilename = fileInfo.fileName();

    qDebug() << "pwd:            " << pwd;
    qDebug() << "short filename: " << shortFilename;
    qDebug() << "executed file:  " << "." << QDir::separator() << shortFilename;

    _process->setWorkingDirectory( pwd );
    _process->start( "/bin/bash", QStringList() << shortFilename );e

    if( !_process->waitForStarted() )
    {
        QString error = QString("Starting of \"%1\" was failed").arg( filepath );
        qCritical().noquote().nospace() << error;
        emit signalErrorMessage( error );
        return false;
    }

    if( !_process->waitForFinished() )
    {
        QString error = QString("Waiting for finish of \"%1\" was failed").arg( filepath );
        qCritical().noquote().nospace() << error;
        emit signalErrorMessage( error );
        return false;
    }

    return (_process->exitCode() == 0);
}

void BashExecutor::slotReadData()
{
    QString data = _process->readAllStandardOutput();
    qDebug() << data;
    emit signalOutput( data );
    qApp->processEvents();
}

void BashExecutor::slotReadError()
{
    QString error = _process->readAllStandardError();
    qCritical() << error;
    emit signalErrorMessage( error );
    qApp->processEvents();
}
