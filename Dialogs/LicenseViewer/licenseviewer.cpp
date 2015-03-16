#include "licenseviewer.h"
#include "ui_licenseviewer.h"

LicenseViewer::LicenseViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LicenseViewer)
{
    ui->setupUi(this);
    LicenseHTMLLoader = new QFile();
}

LicenseViewer::~LicenseViewer()
{
    delete ui;
}

void LicenseViewer::showLicense(License l)
{
    QString html;
    switch(l) {
    case GnuPublicLicense:
        LicenseHTMLLoader->setFileName(":/Documents/GNU Public License/GPL_HTML.html");
        LicenseHTMLLoader->open(QIODevice::ReadOnly | QIODevice::Text);
         html = (LicenseHTMLLoader->readAll());
        ui->LicenseHTMLViewer_WebView->setHtml(html);
        LicenseHTMLLoader->close();
        break;

    case GnuLesserPublicLicense:
        LicenseHTMLLoader->setFileName(":/Documents/GNU Lesser Public License/LGPL_HTML.html");
        LicenseHTMLLoader->open(QIODevice::ReadOnly | QIODevice::Text);
         html = (LicenseHTMLLoader->readAll());
        ui->LicenseHTMLViewer_WebView->setHtml(html);
        LicenseHTMLLoader->close();
        break;

    case GnuAfferoPublicLicense:
        LicenseHTMLLoader->setFileName(":/Documents/GNU Affero GPL/AGPL_HTML.html");
        LicenseHTMLLoader->open(QIODevice::ReadOnly | QIODevice::Text);
         html = (LicenseHTMLLoader->readAll());
        ui->LicenseHTMLViewer_WebView->setHtml(html);
        LicenseHTMLLoader->close();
        break;

    case GnuFreeDocumentLicense:
        LicenseHTMLLoader->setFileName(":/Documents/GNU Free Document License/GFDL_HTML.html");
        LicenseHTMLLoader->open(QIODevice::ReadOnly | QIODevice::Text);
        html = (LicenseHTMLLoader->readAll());
        ui->LicenseHTMLViewer_WebView->setHtml(html);
        LicenseHTMLLoader->close();
        break;

    case MozillaPublicLicense:
        LicenseHTMLLoader->setFileName(":/Documents/Mozilla Public License/MPL_HTML.html");
        LicenseHTMLLoader->open(QIODevice::ReadOnly | QIODevice::Text);
        html = (LicenseHTMLLoader->readAll());
        ui->LicenseHTMLViewer_WebView->setHtml(html);
        LicenseHTMLLoader->close();
        break;

    case EclipsePublicLicense:
        LicenseHTMLLoader->setFileName(":/Documents/Eclipse Public License/EPL_HTML.html");
        LicenseHTMLLoader->open(QIODevice::ReadOnly | QIODevice::Text);
        html = (LicenseHTMLLoader->readAll());
        ui->LicenseHTMLViewer_WebView->setHtml(html);
        LicenseHTMLLoader->close();
        break;
    }
}
