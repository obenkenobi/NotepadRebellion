#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QPrinter>
#include <QPrintDialog>

const QString MainWindow::WINDOW_TITLE_APPENDER = " - NotepadRebellion";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    addToolBar(Qt::LeftToolBarArea, ui->toolBar);
    ui->toolBar->setMovable(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::window_title_append(QString name) {
    return name + MainWindow::WINDOW_TITLE_APPENDER;
}


void MainWindow::on_actionNew_triggered()
{
    filepath_ = "";
    ui->textEdit->setText("");
    this->setWindowTitle(window_title_append("new"));
}

void MainWindow::on_actionOpen_triggered()
{
    filepath_ = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath());
    QFile file(filepath_);
    this->setWindowTitle(window_title_append(filepath_));
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "File " + filepath_ + " not open");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    if(filepath_=="") {
        filepath_ = QFileDialog::getSaveFileName(this, "Open File", QDir::homePath());
        this->setWindowTitle(window_title_append(filepath_));
    }
    QFile file(filepath_);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "File " + filepath_ + " not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Open File", QDir::homePath());
    if(filepath_=="") {
        filepath_ = filename;
        this->setWindowTitle(window_title_append(filepath_));
    }
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "File " + filename + " not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionAbout_RebellionTXT_triggered()
{
    QString aboutText;
    aboutText += "Author : Goku\n";
    aboutText += "Date Created : April 7, 2020\n";
    aboutText += "(c) Notepad Rebellion (R)\n";
    QMessageBox::information(this, "About Notepad Rebellion", aboutText);
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit->setFont(font);
    }
}

void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Color");
    if(color.isValid()) {
        ui->textEdit->setTextColor(color);
    }
}

void MainWindow::on_actionBackground_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Color");
    if(color.isValid()) {
        ui->textEdit->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionBackground_Color_Edit_Text_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Color");
    QPalette palette;
    palette.setColor(QPalette::Base, color);
    if(color.isValid()) {
        ui->textEdit->setPalette(palette);
    }
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("");
    QPrintDialog dialogue(&printer, this);
    if(dialogue.exec() == QDialog::Rejected) {
        return;
    }
    ui->textEdit->print(&printer);
}
