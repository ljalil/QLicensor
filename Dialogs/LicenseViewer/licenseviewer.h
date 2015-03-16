#ifndef LICENSEVIEWER_H
#define LICENSEVIEWER_H

#include <QDialog>
#include <QFile>
#include "../../Core/licensemetadata.h"

namespace Ui {
class LicenseViewer;
}

class LicenseViewer : public QDialog
{
    Q_OBJECT

public:
    explicit LicenseViewer(QWidget *parent = 0);
    ~LicenseViewer();

private:
    Ui::LicenseViewer *ui;
    QFile *LicenseHTMLLoader;
public slots:
    void showLicense(License l);
};

#endif // LICENSEVIEWER_H
