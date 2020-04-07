#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static const QString WINDOW_TITLE_APPENDER;

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionAbout_RebellionTXT_triggered();

    void on_actionFont_triggered();

    void on_actionColor_triggered();

    void on_actionBackground_Color_triggered();

    void on_actionBackground_Color_Edit_Text_triggered();

    void on_actionPrint_triggered();

private:
    QString window_title_append(QString name);
    Ui::MainWindow *ui;
    QString filepath_;
};

#endif // MAINWINDOW_H
