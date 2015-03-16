#ifndef QLICENSORWINDOW_H
#define QLICENSORWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QMessageBox>
#include "Core/licenseinformation.h"
#include "Core/licenseapplier.h"
#include "Dialogs/LicenseViewer/licenseviewer.h"
#include "Dialogs/AboutDialog/aboutdialog.h"

namespace Ui {
class QLicensorWindow;
}

class QLicensorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QLicensorWindow(QWidget *parent = 0);
    ~QLicensorWindow();

private:
    Ui::QLicensorWindow *ui;
    LicenseInformationParser *InfoParser;
    QFileSystemModel *model;
    LicenseApplier *applier;
    QString workingDir;
    QString list[12] = {"GPL","LGPL","AGPL","FDL","BSD2","BSD3","BSD4","Apache","MPL","MIT","Eclipse","PD"};

    LicenseViewer *viewer;
signals:
    void updateRequest(QString license);
    void directoryChoosen(QString directory);
public slots:
    void updateLicenseData(LicenseInformationParser::infoStack stack);
    void chooseDirectoryDialog();
    void updateDirectoryView(QString directory);
    void showAboutDialog();
    void showAboutQt();
    void closeWorkingDir();

private slots:
    void on_ApplyLicense_PushButton_clicked();
    void on_ShowLicense_PushButton_clicked();
    void on_ChooseLicense_ListWidget_currentRowChanged(int currentRow);
};

#endif // QLICENSORWINDOW_H
