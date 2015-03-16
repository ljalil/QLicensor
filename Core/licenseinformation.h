#ifndef LICENSEINFORMATIONPARSER_H
#define LICENSEINFORMATIONPARSER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QDebug>
#include <QPixmap>
class LicenseInformationParser : public QObject
{
    Q_OBJECT
public:
    explicit LicenseInformationParser(QObject *parent = 0);
    ~LicenseInformationParser();

    struct infoStack{
        QString licenseName;
        QString author;
        QString latestVersion;
        QString publisher;
        QString published;
        QString DFSGCompatible;
        QString FSFApproved;
        QString OSIApproved;
        QString GPLCompatible;
        QString copyleft;
        QString linking;
        QString website;
        QPixmap logo;
    };

    infoStack *GPL;     //Gnu Public License
    infoStack *LGPL;    //GNU Lesser Public License
    infoStack *AGPL;    //Gnu Affero Public License
    infoStack *Apache;  //Apache License
    infoStack *MIT;     //MIT License
    infoStack *MPL;     //Mozilla Public License
    infoStack *FDL;     //GNU Free Document License
    infoStack *PD;      //Public Domain (Unlicense)
    infoStack *Eclipse; //Eclipse Public License
    infoStack *BSD2;   //BSD 2-Clause
    infoStack *BSD3;   //BSD 3-Clause
    infoStack *BSD4;   //BSD 4-Clause

signals:
    void infoReady(LicenseInformationParser::infoStack);
public slots:
    void getInfoByName(QString licenseName);
private:

};

#endif // LICENSEINFORMATIONPARSER_H
