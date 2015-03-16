#include "licenseapplier.h"

LicenseApplier::LicenseApplier(QObject *parent) : QObject(parent)
{
    numberOfFilesApplied = 0;
}

LicenseApplier::~LicenseApplier()
{

}

void LicenseApplier::setWorkingDir(const QString &dir)
{
    this->workingDirectory = dir;
}

void LicenseApplier::setProjectName(const QString &name)
{
    this->project = name;
}

void LicenseApplier::setProjectAuthor(const QString &author)
{
    this->author = author;
}

void LicenseApplier::setProjectDate(const QString &date)
{
    this->date = date;
}

void LicenseApplier::setProjectDescription(const QString &description)
{
    this->description = description;
}

void LicenseApplier::resetAppliedFilesCounter()
{
    this->numberOfFilesApplied = 0;
}

QString LicenseApplier::workingDir() const
{
    return this->workingDirectory;
}

QString LicenseApplier::projectName() const
{
    return this->project;
}

QString LicenseApplier::projectAuthor() const
{
    return this->author;
}

QString LicenseApplier::projectDate() const
{
    return this->date;
}

QString LicenseApplier::projectDescription() const
{
    return this->projectDescription();
}

int LicenseApplier::filesApplied() const
{
    return this->numberOfFilesApplied;
}

void LicenseApplier::applyLicense(License license)
{
    QFile *iteratedFile;
    QFile *resFile;
    QStringList fileList;
    QFileInfo fileInfo;
    iterator = new QDirIterator(this->workingDirectory,QDirIterator::Subdirectories);

    switch(license) {
    case Apache:
        resFile = new QFile(":/Documents/Apache/Apache_HEADER.txt");
        break;

    case GnuPublicLicense:
        resFile = new QFile(":/Documents/GNU Public License/GPL_Header.txt");
        break;

    case GnuLesserPublicLicense:
        resFile = new QFile(":/Documents/GNU Lesser Public License/LGPL_HEADER.txt");
        break;

    case GnuAfferoPublicLicense:
        resFile = new QFile(":/Documents/GNU Affero GPL/AGPL_TEXT.txt");
        break;

    case GnuFreeDocumentLicense:
        resFile = new QFile("qrc:/Documents/GNU Free Document License/GFDL_HEADER.txt");
        break;

    case BSD2Clause:
        resFile = new QFile(":/Documents/BSD 2-Clause/BSD2Clause_HEADER.txt");
        break;

    case BSD3Clause:
        resFile = new QFile(":/Documents/BSD 3-Clause/BSD3Clause_HEADER.txt");
        break;

    case BSD4Clause:
        resFile = new QFile(":/Documents/GNU Lesser Public License/LGPL_HEADER.txt");
        break;

    case MozillaPublicLicense:
        resFile = new QFile(":/Documents/Mozilla Public License/MPL_HEADER.txt");
        break;

    case MIT:
        resFile = new QFile("qrc:/Documents/MIT License/MIT_HEADER.txt");
        break;

    case EclipsePublicLicense:
        resFile = new QFile("qrc:/Documents/Eclipse Public License/EPL_HEADER.txt");
        break;

    case PublicDomain:
        resFile = new QFile(":/Documents/Public Domain/PD_HEADER.txt");
        break;
    }

    if(!resFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file";
        return;
    }

    //TODO : REPLACE ${TEMPLATE} WITH REAL INFO
    QString licenseHeader(resFile->readAll());
    delete resFile;

    licenseHeader.replace("${PROJECT}",this->project);
    licenseHeader.replace("${AUTHOR}",this->author);
    licenseHeader.replace("${YEAR}",this->date);


    while(iterator->hasNext()) {
        fileInfo.setFile(iterator->next());
        if(fileInfo.isFile() && !fileInfo.fileName().contains("LICENSE"))
            fileList.append(fileInfo.filePath());
    }

    iteratedFile = new QFile();

    for(int i = 0; i < fileList.size(); i++) {
        iteratedFile->setFileName(fileList[i]);

        //comments with ( /* ... */ )
        if(!iteratedFile->open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << "Cannot open the file";

        }
        iteratedFile->seek(0);
        if(iteratedFile->fileName().endsWith(".c")    ||
                iteratedFile->fileName().endsWith(".cpp")  ||
                iteratedFile->fileName().endsWith(".cxx")  ||
                iteratedFile->fileName().endsWith(".h")    ||
                iteratedFile->fileName().endsWith(".hxx")  ||
                iteratedFile->fileName().endsWith(".cs")   ||
                iteratedFile->fileName().endsWith(".java") ||
                iteratedFile->fileName().endsWith(".css")  ||
                iteratedFile->fileName().endsWith(".scala")  ||
                iteratedFile->fileName().endsWith(".groovy")  ||
                iteratedFile->fileName().endsWith(".pl")){

            QString specializedHeader = licenseHeader;
            specializedHeader.prepend("/*\n");
            specializedHeader.replace('\n',"\n * ");
            specializedHeader.append("\n*/\n\n");
            QTemporaryFile *tempContent = new QTemporaryFile();
            if(!tempContent->open())  {
                qDebug() << "Cannot create a temporary file, disk full?" << endl;
            } else {
                tempContent->write(specializedHeader.toUtf8());
                tempContent->write(iteratedFile->readAll());
                tempContent->seek(0);
                iteratedFile->seek(0);
                iteratedFile->write(tempContent->readAll());
                ++numberOfFilesApplied;
                tempContent->close();
                delete tempContent;
            }

        }

        //comments with ( ''' ... ''' )
        else if(iteratedFile->fileName().endsWith(".py") ||
                iteratedFile->fileName().endsWith(".pyx")) {
            QString specializedHeader = licenseHeader;
            specializedHeader.prepend("\"\"\"\n");
            specializedHeader.append("\n\"\"\"\n\n");
            QTemporaryFile *tempContent = new QTemporaryFile();
            if(!tempContent->open())  {
                qDebug() << "Cannot create a temporary file, disk full?" << endl;
            } else {
                tempContent->write(specializedHeader.toUtf8());
                tempContent->write(iteratedFile->readAll());
                tempContent->seek(0);
                iteratedFile->seek(0);
                iteratedFile->write(tempContent->readAll());
                ++numberOfFilesApplied;
                tempContent->close();
                delete tempContent;
            }

        }

        //comments with ( #... )
        else if(iteratedFile->fileName().endsWith(".rb")   || //Ruby
                iteratedFile->fileName().endsWith(".R")    || //R Lang
                iteratedFile->fileName().endsWith(".yaml") || //Yaml
                iteratedFile->fileName().endsWith(".tcl")  || //TCL
                iteratedFile->fileName().endsWith(".pro")  || //Qt Project File
                iteratedFile->fileName().endsWith(".sh")) {   //Shell Script
            QString specializedHeader = licenseHeader;
            specializedHeader.prepend("# ");//TOFIX: first line not applied for a fucking reason
            specializedHeader.replace('\n',"\n# ");
            specializedHeader.append("\n\n");
            QTemporaryFile *tempContent = new QTemporaryFile();
            if(!tempContent->open())  {
                qDebug() << "Cannot create a temporary file, disk full?" << endl;
            } else {
                tempContent->write(specializedHeader.toUtf8());
                tempContent->write(iteratedFile->readAll());
                tempContent->seek(0);
                iteratedFile->seek(0);
                iteratedFile->write(tempContent->readAll());
                ++numberOfFilesApplied;
                tempContent->close();
                delete tempContent;
            }

        }

        //comments with ( <!-- ... --> )
        else if(iteratedFile->fileName().endsWith(".html") ||
                iteratedFile->fileName().endsWith(".htm") ||
                iteratedFile->fileName().endsWith(".xml")) {
            QString specializedHeader = licenseHeader;
            specializedHeader.prepend("<!--\n");
            specializedHeader.append("-->\n\n");
            QTemporaryFile *tempContent = new QTemporaryFile();
               if(!tempContent->open())  {
                qDebug() << "Cannot create a temporary file, disk full?" << endl;
            } else {
                tempContent->write(specializedHeader.toUtf8());
                tempContent->write(iteratedFile->readAll());
                tempContent->seek(0);
                iteratedFile->seek(0);
                iteratedFile->write(tempContent->readAll());
                ++numberOfFilesApplied;
                tempContent->close();
                delete tempContent;
            }

        }
        iteratedFile->close();
    }
    delete iteratedFile;
}

void LicenseApplier::addFullLicenseFile(License license)
{
    QFile *licenseFile = new QFile(workingDirectory+"LICENSE.txt");
    QFile *resLicenseFile;

    switch(license) {
    case Apache:
        resLicenseFile = new QFile(":/Documents/Apache/Apache_TEXT.txt");
        break;

    case GnuPublicLicense:
        resLicenseFile = new QFile(":/Documents/GNU Public License/GPL_TEXT.txt");
        break;

    case GnuLesserPublicLicense:
        resLicenseFile = new QFile(":/Documents/GNU Lesser Public License/LGPL_TEXT.txt");
        break;

    case GnuAfferoPublicLicense:
        resLicenseFile = new QFile(":/Documents/GNU Affero GPL/AGPL_TEXT.txt");
        break;

    case GnuFreeDocumentLicense:
        resLicenseFile = new QFile(":/Documents/GNU Free Document License/GFDL_TEXT.txt");
        break;

    case BSD2Clause:
        resLicenseFile = new QFile(":/Documents/GNU Lesser Public License/LGPL_TEXT.txt");
        break;

    case BSD3Clause:
        resLicenseFile = new QFile(":/Documents/GNU Lesser Public License/LGPL_TEXT.txt");
        break;

    case BSD4Clause:
        resLicenseFile = new QFile(":/Documents/GNU Lesser Public License/LGPL_TEXT.txt");
        break;

    case MozillaPublicLicense:
        resLicenseFile = new QFile("qrc:/Documents/Mozilla Public License/MPL_TEXT.txt");
        break;

    case MIT:
        resLicenseFile = new QFile(":/Documents/GNU Lesser Public License/LGPL_TEXT.txt");
        break;

    case EclipsePublicLicense:
        resLicenseFile = new QFile("qrc:/Documents/Eclipse Public License/EPL_TEXT.txt");
        break;

    case PublicDomain:
        resLicenseFile = new QFile(":/Documents/GNU Lesser Public License/LGPL_TEXT.txt");
        break;
    }

    if(!licenseFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot create the file";
        return;
    }

    if(!resLicenseFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open the file";
        return;
    }

    licenseFile->write(resLicenseFile->readAll());
    licenseFile->flush();
    licenseFile->close();
    resLicenseFile->close();

    delete resLicenseFile;
    delete licenseFile;
}
