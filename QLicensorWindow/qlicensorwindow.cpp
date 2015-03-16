#include "qlicensorwindow.h"
#include "ui_qlicensorwindow.h"

QLicensorWindow::QLicensorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QLicensorWindow)
{
    ui->setupUi(this);
    this->InfoParser = new LicenseInformationParser;
    ui->ChooseLicense_ListWidget->setCurrentRow(0);
    QObject::connect(this,SIGNAL(updateRequest(QString)),InfoParser,SLOT(getInfoByName(QString)));
    QObject::connect(InfoParser,SIGNAL(infoReady(LicenseInformationParser::infoStack)),this,SLOT(updateLicenseData(LicenseInformationParser::infoStack)));
    QObject::connect(ui->actionLoadDirectory,SIGNAL(triggered()),this,SLOT(chooseDirectoryDialog()));
    QObject::connect(this,SIGNAL(directoryChoosen(QString)),this,SLOT(updateDirectoryView(QString)));
    QObject::connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(showAboutDialog()));
    QObject::connect(ui->actionAboutQtFramework,SIGNAL(triggered()),this,SLOT(showAboutQt()));
    QObject::connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
    QObject::connect(ui->actionCloseWorkingDirectory,SIGNAL(triggered()),this,SLOT(closeWorkingDir()));
    emit updateRequest("GPL");
    applier = new LicenseApplier();
}

QLicensorWindow::~QLicensorWindow()
{
    delete ui;
    delete InfoParser;
    delete applier;
}

void QLicensorWindow::updateLicenseData(LicenseInformationParser::infoStack stack)
{
    ui->LicenseName_Label->setText(stack.licenseName);
    ui->Author_Label->setText(stack.author);
    ui->LatestVersion_Label->setText(stack.latestVersion);
    ui->Publisher_Label->setText(stack.publisher);
    ui->Published_Label->setText(stack.published);
    ui->DFSGCompatible_Label->setText(stack.DFSGCompatible);
    ui->GPLCompatible_Label->setText(stack.GPLCompatible);
    ui->OSIApproved_Label->setText(stack.OSIApproved);
    ui->Copyleft_Label->setText(stack.copyleft);
    ui->Linking_Label->setText(stack.linking);
    ui->Website_Label->setText(stack.website);
    //QPixmap logo(":/Resources/Bitmap/"+stack.logo);
    ui->LicenseLogo_Label->setPixmap(stack.logo);
}

void QLicensorWindow::chooseDirectoryDialog()
{
    QString directoryPath = QFileDialog::getExistingDirectory(
                this,
                "Choose project root directory",
                QDir::homePath(),
                QFileDialog::ShowDirsOnly
                );
    emit directoryChoosen(directoryPath);

}

void QLicensorWindow::updateDirectoryView(QString directory)
{
    workingDir = directory;
    qDebug() << " QLicensorWindow::updateDirectoryView" << workingDir << endl;
    model = new QFileSystemModel(this);
    model->setRootPath(directory);
    ui->Directory_TreeView->setModel(model);
    ui->Directory_TreeView->setRootIndex(model->index(directory));
}

void QLicensorWindow::showAboutDialog()
{
    AboutDialog *about = new AboutDialog(this);
    if(about->exec() == QDialog::Accepted) {

    }
    delete about;
}

void QLicensorWindow::showAboutQt()
{
    QMessageBox::aboutQt(this,"About Qt Framework");
}

void QLicensorWindow::closeWorkingDir()
{
    this->workingDir.clear();


    ui->Directory_TreeView->reset();

}

void QLicensorWindow::on_ApplyLicense_PushButton_clicked() {

    if(!this->workingDir.isEmpty()) {
        applier->setWorkingDir(this->workingDir);
    } else {
        QMessageBox::critical(this,"Error : no working directory","No working directory is choosen, "
                                                                  "please choose one before continue");
        return;
    }
    applier->setProjectName(ui->ProjectName_LineEdit->text());
    applier->setProjectAuthor(ui->ProjectAuthor_LineEdit->text());
    applier->setProjectDate(ui->ProjectYear_LineEdit->text());
    applier->setProjectDescription(ui->ProjectDescription_LineEdit->text());

    if(ui->ProjectAuthor_LineEdit->text().isEmpty() ||
       ui->ProjectName_LineEdit->text().isEmpty()   ||
       ui->ProjectYear_LineEdit->text().isEmpty()   ||
       ui->ProjectDescription_LineEdit->text().isEmpty()) {
        QMessageBox::warning(this,"Warning : missing data","Notice that not providing project informations"
                                            " will not replace the metatags in license text"
                                            " that will be inserted");
    }



    QString choosen = this->list[ui->ChooseLicense_ListWidget->currentIndex().row()];
    if(ui->AddLICENSE_CheckBox->isChecked()) {
        //applier->addFullLicenseFile();
        if(choosen == "GPL")
            applier->addFullLicenseFile(GnuPublicLicense);
       else  if(choosen == "LGPL")
            applier->addFullLicenseFile(GnuLesserPublicLicense);
        else if(choosen == "Apache")
            applier->addFullLicenseFile(Apache);
        else if(choosen == "AGPL")
            applier->addFullLicenseFile(GnuAfferoPublicLicense);
        else if(choosen == "FDL")
            applier->addFullLicenseFile(GnuFreeDocumentLicense);
        else if(choosen == "BSD2")
            applier->addFullLicenseFile(BSD2Clause);
        else if(choosen == "BSD3")
            applier->addFullLicenseFile(BSD3Clause);
        else if(choosen == "BSD4")
            applier->addFullLicenseFile(BSD4Clause);
        else if(choosen == "MPL")
            applier->addFullLicenseFile(MozillaPublicLicense);
        else if(choosen == "MIT")
            applier->addFullLicenseFile(MIT);
        else if(choosen == "Eclipse")
            applier->addFullLicenseFile(EclipsePublicLicense);
        else if(choosen == "PD")
            applier->addFullLicenseFile(PublicDomain);
    }

    if(choosen == "GPL")
        applier->applyLicense(GnuPublicLicense);
    else if(choosen == "LGPL")
        applier->applyLicense(GnuLesserPublicLicense);
    else if(choosen == "Apache")
        applier->applyLicense(Apache);
    else if(choosen == "AGPL")
        applier->applyLicense(GnuAfferoPublicLicense);
    else if(choosen == "FDL")
        applier->applyLicense(GnuFreeDocumentLicense);
    else if(choosen == "BSD2")
        applier->applyLicense(BSD2Clause);
    else if(choosen == "BSD3")
        applier->applyLicense(BSD3Clause);
    else if(choosen == "BSD4")
        applier->applyLicense(BSD4Clause);
    else if(choosen == "MPL")
        applier->applyLicense(MozillaPublicLicense);
    else if(choosen == "MIT")
        applier->applyLicense(MIT);
    else if(choosen == "Eclipse")
        applier->applyLicense(EclipsePublicLicense);
    else if(choosen == "PD")
        applier->applyLicense(PublicDomain);

   ui->statusBar->showMessage("License header prepended successfully to " + QString::number(applier->filesApplied()) + " files");
    applier->resetAppliedFilesCounter();
}

void QLicensorWindow::on_ShowLicense_PushButton_clicked()
{
    viewer = new LicenseViewer(this);
    QString currentLicense = this->list[ui->ChooseLicense_ListWidget->currentIndex().row()];
    if(currentLicense == "GPL") {
        viewer->setWindowTitle("Gnu Public License");
        viewer->showLicense(GnuPublicLicense);
    }
    else if(currentLicense == "LGPL") {
        viewer->setWindowTitle("Gnu Lesser Public License");
        viewer->showLicense(GnuLesserPublicLicense);
    }

    else if(currentLicense == "Apache") {
        viewer->setWindowTitle("Apache License");
        viewer->showLicense(Apache);
    }
    else if(currentLicense == "AGPL"){
        viewer->setWindowTitle("Gnu Affero Public License");
        viewer->showLicense(GnuAfferoPublicLicense);
    }

    else if(currentLicense == "FDL") {
        viewer->setWindowTitle("Gnu Free Document License");
        viewer->showLicense(GnuFreeDocumentLicense);
    }

    else if(currentLicense == "BSD2") {
        viewer->setWindowTitle("BSD Clause-2 License");
        viewer->showLicense(BSD2Clause);
    }

    else if(currentLicense == "BSD3"){
        viewer->setWindowTitle("BSD Clause-3 License");
        viewer->showLicense(BSD3Clause);
    }

    else if(currentLicense == "BSD4"){
        viewer->setWindowTitle("BSD Clause-4 License");
        viewer->showLicense(BSD4Clause);
    }

    else if(currentLicense == "MPL"){
        viewer->setWindowTitle("Mozilla Public License");
        viewer->showLicense(MozillaPublicLicense);
    }

    else if(currentLicense == "MIT"){
        viewer->setWindowTitle("MIT License");
        viewer->showLicense(MIT);
    }

    else if(currentLicense == "Eclipse"){
        viewer->setWindowTitle("Eclipse Public License");
        viewer->showLicense(EclipsePublicLicense);
    }

    else if(currentLicense == "PD"){
        viewer->setWindowTitle("Public Domain (unlicened)");
        viewer->showLicense(PublicDomain);
    }

    if(viewer->exec() == QDialog::Accepted) {

    }
    delete viewer;
}

void QLicensorWindow::on_ChooseLicense_ListWidget_currentRowChanged(int currentRow)
{
    emit updateRequest(list[currentRow]);
}
