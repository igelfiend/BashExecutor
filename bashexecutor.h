#ifndef BASHEXECUTOR_H
#define BASHEXECUTOR_H

#include <QObject>
#include <QProcess>
#include <QSharedPointer>

class BashExecutor : public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer< QProcess > QProcessPtr;
    explicit BashExecutor(QObject *parent = nullptr);
    ~BashExecutor();

    bool runScript( const QString &filepath );

signals:
    void signalErrorMessage( const QString &msg );
    void signalOutput( const QString &output );

private slots:
    void slotReadData();
    void slotReadError();

public slots:

protected:
    QProcessPtr _process;
};

#endif // BASHEXECUTOR_H
