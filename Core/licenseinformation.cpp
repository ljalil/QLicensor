#include "licenseinformation.h"
#include <QUrl>
LicenseInformationParser::LicenseInformationParser(QObject *parent) : QObject(parent)
{
    GPL = new infoStack
            {
            "GNU General Public License",
            "Free Software Foundation",
            "3.0",
            "Free Software Foundation",
            "",
            "",
            "<font color='green'>Yes</font>",
            "<font color='green'>Yes</font>",
            "<font color='green'>Yes</font>",
            "<font color='green'>Yes</font>",
            "<font color='green'>Yes</font>",
            "<a href='http://www.gnu.org/licenses/'>www.gnu.org/...</a>",
            QPixmap(":Resources/Bitmap/GPLv3.png")
            };

    LGPL = new infoStack
            {
            "GNU Lesser General Public License",
            "Free Software Foundation",
            "3.0",
            "Free Software Foundation",
            "",
            "",
            "<font color='green'>Yes</font>",
            "<font color='green'>Yes</font>",
            "<font color='green'>Yes</font>",
            "<font color='green'>Yes</font>",
            "<font color='green'>Yes</font>",
            "<a href='http://www.gnu.org/licenses/'>www.gnu.org/...</a>",
            QPixmap(":Resources/Bitmap/LGPLv3.png")
            };

    AGPL = new infoStack
            {
            "GNU Affero General Public License",
            "Free Software Foundation",
            "3.0",
            "Free Software Foundation",
            "19 November 2007",
            "",
            "<font color='green'>Yes</font>",
            "",
            "",
            "",
            "",
            "<a href='http://www.gnu.org/licenses/'>www.gnu.org/...</a>",
            QPixmap(":Resources/Bitmap/AGPLv3.png")
            };

    FDL = new infoStack
            {
            "GNU Free Document License",
            "Free Software Foundation",
            "3.0",
            "Free Software Foundation",
            "",
            "",
            "<font color='green'>Yes</font>",
            "",
            "",
            "",
            "",
            "<a href='www.fsf.com'>www.fsf.org</a>",
            QPixmap(":/Resources/Bitmap/GFDL_Logo.svg")
            };

    MPL = new infoStack
            {
            "Mozilla Public License",
            "Mozilla Foundation",
            "3.0",
            "Mozilla Foundation",
            "",
            "",
            "<font color='green'>Yes</font>",
            "",
            "",
            "",
            "",
            "",
            QPixmap(":/Resources/Bitmap/MPL.png")
            };

    MIT = new infoStack
            {
            "MIT License",
            "Free Software Foundation",
            "3.0",
            "Free Software Foundation",
            "",
            "",
            "Yes",
            "",
            "",
            "",
            "",
            "",
            QPixmap(":Resources/Bitmap/GPLv3.png")
            };

    Apache = new infoStack
            {
            "Apache License",
            "Apache Software Foundation",
            "2.0",
            "Apache Software Foundation",
            "January 2004",
            "<font color='green'>Yes</font>",
            "<font color='green'>Yes</font>",
            "<font color='green'>Yes</font>",
            "<font color='green'>Yes</font>",
            "<font color='red'>No</font>",
            "<font color='green'>Yes</font>",
            "<a href='https://www.apache.org/licenses'>www.apache.org/...</a>",
            QPixmap(":/Resources/Bitmap/Apache.png")
            };

    PD = new infoStack
    {
    "Public Domain",
    "Public Domain",
    "--",
    "Public Domain",
    "--",
    "--",
    "--",
    "--",
    "--",
    "--",
    "--",
    "--",
    QPixmap(":/Resources/Bitmap/PD.png")
    };

    Eclipse = new infoStack
    {
    "Eclipse Public License",
    "Eclipse Foundation",
    "1.0",
    "Eclipse Foundation",
    "February 2004",
    "<font color='green'>Yes</font>",
    "<font color='green'>Yes</font>",
    "<font color='green'>Yes</font>",
    "<font color='red'>No</font>",
    "Limited",
    "<font color='green'>Yes</font>",
    "<a href='www.eclipse.org/org/documents/epl-v10'>www.eclipse.org/...</a>",
    QPixmap(":Resources/Bitmap/GPLv3.png")
    };

    BSD2 = new infoStack
    {
    "Simplified BSD License",
    "The FreeBSD Project",
    "--",
    "Public Domain",
    "--",
    "<font color='green'>Yes</font>",
    "<font color='green'>Yes</font>",
    "<font color='green'>Yes</font>",
    "<font color='green'>Yes</font>",
    "<font color='red'>No</font>",
    "<font color='green'>Yes</font>",
    "--",
    QPixmap(":Resources/Bitmap/GPLv3.png")
    };


    BSD3 = new infoStack
    {
    "New BSD License",
    "Regents of the University of California",
    "--",
    "Public Domain",
    "22 July 1999",
    "<font color='green'>Yes</font>",
    "<font color='green'>Yes</font>",
    "<font color='green'>Yes</font>",
    "<font color='green'>Yes</font>",
    "<font color='red'>No</font>",
    "<font color='green'>Yes</font>",
    "--",
    QPixmap(":Resources/Bitmap/GPLv3.png")
    };

    BSD4 = new infoStack
    {
    "BSD License",
    "Regents of the University of California",
    "--",
    "Public Domain",
    "1990",
    "<font color='green'>Yes</font>",
    "<font color='green'>Yes</font>",
    "<font color='red'>No</font>",
    "<font color='red'>No</font>",
    "<font color='red'>No</font>",
    "<font color='green'>Yes</font>",
    "--",
    QPixmap(":Resources/Bitmap/GPLv3.png")
    };
}

LicenseInformationParser::~LicenseInformationParser()
{

}

void LicenseInformationParser::getInfoByName(QString licenseName)
{
    if (licenseName == "GPL")
        emit infoReady(*this->GPL);
    else if (licenseName == "LGPL")
        emit infoReady(*this->LGPL);
    else if (licenseName == "AGPL")
        emit infoReady(*this->AGPL);
    else if (licenseName == "Apache")
        emit infoReady(*this->Apache);
    else if (licenseName == "MIT")
        emit infoReady(*this->MIT);
    else if (licenseName == "MPL")
        emit infoReady(*this->MPL);
    else if (licenseName == "FDL")
        emit infoReady(*this->FDL);
    else if (licenseName == "BSD2")
        emit infoReady(*this->BSD2);
    else if (licenseName == "BSD3")
        emit infoReady(*this->BSD3);
    else if (licenseName == "BSD4")
        emit infoReady(*this->BSD4);
    else if (licenseName == "Eclipse")
        emit infoReady(*this->Eclipse);
    else if (licenseName == "PD")
        emit infoReady(*this->PD);
}

