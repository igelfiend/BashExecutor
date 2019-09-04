#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>

#include "bashexecutor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    BashExecutor executor;

    connect( &executor,               &BashExecutor::signalOutput,
             ui->plainTextEditOutput, &QPlainTextEdit::appendPlainText );
    connect( &executor,               &BashExecutor::signalErrorMessage,
             ui->plainTextEditErrors, &QPlainTextEdit::appendPlainText );

    executor.runScript( ui->lineEditPathToScript->text() );
}
