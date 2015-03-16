#ifndef LICENSEAPPLIER_H
#define LICENSEAPPLIER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>
#include <QTemporaryFile>
#include "licensemetadata.h"

class LicenseApplier : public QObject
{
    Q_OBJECT
public:
    explicit LicenseApplier(QObject *parent = 0);
    ~LicenseApplier();



    void setWorkingDir(const QString& dir);
    void setProjectName(const QString& name);
    void setProjectAuthor(const QString& author);
    void setProjectDate(const QString& date);
    void setProjectDescription(const QString& description);
    void resetAppliedFilesCounter();
    QString workingDir() const;
    QString projectName() const;
    QString projectAuthor() const;
    QString projectDate() const;
    QString projectDescription() const;
    int filesApplied() const;

private:
    QString workingDirectory;
    QString project,author,date,description;
    bool licenseFile;
    bool applyToSubdirectories;
    QDirIterator *iterator;
    QFile *iteratedFile;
    int numberOfFilesApplied;
signals:

public slots:
    void applyLicense(License license);
    void addFullLicenseFile(License license);
};

#endif // LICENSEAPPLIER_H
