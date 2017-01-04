#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->labelFormCompletion->setStyleSheet(StyleSheetProvider::getDefaultStyleLabelForm());
    ui->labelFormCompletion2->setStyleSheet(StyleSheetProvider::getDefaultStyleLabelForm());

    bgMenu = new QButtonGroup;
    bgMenu->addButton(ui->pushButtonResume);
    bgMenu->addButton(ui->pushButtonActivity);
    bgMenu->addButton(ui->pushButtonWallet);
    bgMenu->addButton(ui->pushButtonFingerprint);
    bgMenu->addButton(ui->pushButtonSetting);


    ui->pushButtonScanFingerprint->setHidden(true);
    ui->pushButtonFinger1->setEnabled(false);
    ui->pushButtonFinger2->setEnabled(false);
    ui->pushButtonFinger3->setEnabled(false);
    ui->pushButtonFinger4->setEnabled(false);
    ui->pushButtonFinger5->setEnabled(false);

    /* Button group for button selection handling */
    bgFingerprint = new QButtonGroup;
    bgFingerprint->addButton(ui->pushButtonFinger1);
    bgFingerprint->addButton(ui->pushButtonFinger2);
    bgFingerprint->addButton(ui->pushButtonFinger3);
    bgFingerprint->addButton(ui->pushButtonFinger4);
    bgFingerprint->addButton(ui->pushButtonFinger5);
    ui->pushButtonFinger1->setHidden(true);
    ui->pushButtonFinger2->setHidden(true);
    ui->pushButtonFinger3->setHidden(true);
    ui->pushButtonFinger4->setHidden(true);
    ui->pushButtonFinger5->setHidden(true);
    selectedHand = None;

    secondStepForm = false;
    passwordChanged = false;
    loggedIn = false;
    forgottenPassword = false;
    userCreation = true;
    firstTimeShown = true;
    purchasesInfoMode = 0;
    numFingerprintScanned = -1;
    ui->checkBoxForm2->setHidden(true);

    /*
     *  Establecemos la tabla del tab principal
     */
    modelCardResume = new QStandardItemModel(4,2,this);
    ui->tableView->setModel(modelCardResume);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->setShowGrid(false);

    modelAdquisitionsResume = new QStandardItemModel(4,3,this);
    ui->tableViewAdquisitions->setModel(modelAdquisitionsResume);
    ui->tableViewAdquisitions->verticalHeader()->hide();
    ui->tableViewAdquisitions->horizontalHeader()->hide();
    ui->tableViewAdquisitions->setShowGrid(false);

    personalData = new QStringListModel(this);

    ui->listViewInitialData->setModel(personalData);

    /*
     *  Establecemos la tabla del tab de compras
     */

    modelTotalAdquisitions = new QStandardItemModel(4,3,this);

    ui->tableViewTotalAdquisitions->setModel(modelTotalAdquisitions);
    ui->tableViewTotalAdquisitions->verticalHeader()->hide();
    ui->tableViewTotalAdquisitions->horizontalHeader()->hide();
    ui->tableViewTotalAdquisitions->setShowGrid(false);

    /*
     *  Establecemos la tabla del tab de cartera
     */

    modelTotalCards = new QStandardItemModel(4,2,this);

    ui->tableViewCards->setModel(modelTotalCards);
    ui->tableViewCards->verticalHeader()->hide();
    ui->tableViewCards->horizontalHeader()->hide();
    ui->tableViewCards->setShowGrid(false);


    connect(ui->tableViewCards->selectionModel(), SIGNAL(currentRowChanged(QModelIndex ,QModelIndex )),
            this, SLOT(currentRowChanged(QModelIndex ,QModelIndex )));

    /*
     *  Establecer los valores de la pagina cargando...
     */

    movieMain = new QMovie(":/MyFiles/Images/spinner3.GIF");
    ui->labelLoadingPage->setMovie(movieMain);

    /*
     *  Establecer los valores de el formulario
     */

    QStringList list=(QStringList()<<"Tipo Documento" << "DNI");
    ui->comboBoxIdType->addItems(list);

    list=(QStringList()<<"Pais"<<"España"<<"Alemania"<<"EEUU");
    ui->comboBoxCountries->addItems(list);
    QDate today = QDate::currentDate();
    ui->dateEditForm->setDate(today);

    ui->lineEditNameForm->installEventFilter(this);
    ui->lineEditSurnameForm->installEventFilter(this);
    ui->lineEditIdForm->installEventFilter(this);
    ui->lineEditEmailForm->installEventFilter(this);
    ui->lineEditPassForm->installEventFilter(this);
    ui->lineEditPass2Form->installEventFilter(this);
    ui->lineEditPhoneForm->installEventFilter(this);
    ui->lineEditStreetForm->installEventFilter(this);
    ui->lineEditPostalForm->installEventFilter(this);
    ui->lineEditCityForm->installEventFilter(this);
    ui->comboBoxIdType->installEventFilter(this);
    ui->comboBoxCountries->installEventFilter(this);


    cardTypes.insert("visa","Visa");
    cardTypes.insert("amex","American Express");
    cardTypes.insert("maestro","Maestro");

    list=(QStringList()<<"Tipo Tarjeta" << "Visa" <<"American Express" <<"Maestro");
    ui->comboBoxCardTypeForm2->addItems(list);

    list=(QStringList()<<"Pais"<<"España"<<"Alemania"<<"EEUU");
    ui->comboBoxCountries->addItems(list);

    ui->dateEditForm->setDate(today);
    ui->lineEditPhoneForm->setValidator(new QIntValidator(this));
    ui->lineEditPostalForm->setValidator(new QIntValidator(this));
    ui->lineEditCardNumberForm2->setValidator(new QIntValidator(this));
    ui->lineEditCSCForm2->setValidator(new QIntValidator(this));

    ui->lineEditCardNumberForm2->installEventFilter(this);
    ui->lineEditCSCForm2->installEventFilter(this);
    ui->dueDateEditForm2->installEventFilter(this);
    ui->lineEditCardNumberForm2->setInputMask("9999-9999-9999-9999");
    ui->lineEditCSCForm2->setValidator(new QIntValidator(this));
    ui->lineEditCSCForm2->setMaxLength(3);
    ui->dueDateEditForm2->setMinimumDate(QDate::currentDate());

    pagination.insert(PAGE,1);
    pagination.insert(NUM_PAGES,0);    

    movieForm = new QMovie(":/MyFiles/Images/spinner3.GIF");
    ui->labelLoadingForm->setMovie(movieForm);


    connect(ui->actionChangePassword, SIGNAL(triggered()), this, SLOT(changePassword()));

    connect(ui->dateEditInitial, SIGNAL(dateChanged(QDate )),
            this, SLOT(dateChangedDateEditInitial(QDate )));

    connect(ui->lineEditPassword, SIGNAL(returnPressed()),
            this, SLOT(on_pushButtonIniciarSesion_clicked()));

    connect(&procFingerprint,SIGNAL(finishedProcessFingerprint(void )),
            this, SLOT(finishedMinutiaeExtration(void )));

    loadSettings();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changePassword(void )
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("Introduzca sus datos"));

    QList<QLineEdit *> fields;

    QLineEdit *lineEdit1 = new QLineEdit(&dialog);
    lineEdit1->setEchoMode(QLineEdit::Password);
    QString label = QString("Contraseña antigua");
    form.addRow(label, lineEdit1);

    QLineEdit *lineEdit2 = new QLineEdit(&dialog);
    lineEdit2->setEchoMode(QLineEdit::Password);
    QString label2 = QString("Nueva contraseña");
    form.addRow(label2, lineEdit2);

    QLineEdit *lineEdit3 = new QLineEdit(&dialog);
    lineEdit3->setEchoMode(QLineEdit::Password);
    QString label3 = QString("Repita la nueva contraseña");
    form.addRow(label3, lineEdit3);
    fields << lineEdit1;
    fields << lineEdit2;
    fields << lineEdit3;

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);

    buttonBox.button(QDialogButtonBox::Ok)->setText(tr("Aceptar"));
    buttonBox.button(QDialogButtonBox::Cancel)->setText(tr("Cancelar"));


    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {
        if(utils.comparePassword(lineEdit1->text(),key)) {
            if(utils.comparePassword(lineEdit2->text(),lineEdit3->text())) {
                key = QString(QCryptographicHash::hash(lineEdit2->text().toStdString().c_str(),QCryptographicHash::Sha512).toHex());
                saveSettings();
                QMessageBox msgBox(QMessageBox::Information, "Cambio contraseña maestra", tr("Contraseña cambiada con exito"), QMessageBox::Yes);
                msgBox.setButtonText(QMessageBox::Yes, "Aceptar");
                msgBox.exec();
            }
            else    {
                QMessageBox msgBox(QMessageBox::Information, "Cambio contraseña maestra", tr("Las nuevas contraseñas no coinciden"), QMessageBox::Yes);
                msgBox.setButtonText(QMessageBox::Yes, "Aceptar");
                msgBox.exec();
            }
        }
        else    {
            QMessageBox msgBox(QMessageBox::Information, "Cambio contraseña maestra", tr("La contraseña maestra no es valida"), QMessageBox::Yes);
            msgBox.setButtonText(QMessageBox::Yes, "Aceptar");
            msgBox.exec();
        }
    }

}


bool MainWindow::loadSettings()
{
    QSettings settings;
    key = settings.value("key").toString();
    idDevice = settings.value("idDevice").toString();
    keyDevice = settings.value("keyDevice").toString();

    if(key == "" || idDevice == "" || keyDevice == "" || !com.authenticateDevice(idDevice,keyDevice))  {
        QMessageBox msgBox(QMessageBox::Information, "Dispositivo no identificado",
                           "Hubo un problema al identificar su dispositivo", QMessageBox::Yes);
        msgBox.setButtonText(QMessageBox::Yes, "Aceptar");

        if (msgBox.exec() ) {
            return false;
        }

    }

    return true;

}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("key", key);
}


void MainWindow::dateChangedDateEditInitial(QDate date)
{
    ui->dateEditFinal->setMinimumDate(date);
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{

    if(secondStepForm)
    {
        if (event->type() == QEvent::FocusOut)
        {
            if(object == ui->lineEditNameForm)
                ui->lineEditNameForm->text().count() > 0 ? ui->lineEditNameForm->setPlaceholderText("Nombre") : ui->lineEditNameForm->setPlaceholderText("* Nombre");
            if(object == ui->lineEditSurnameForm)
                ui->lineEditSurnameForm->text().count() > 0 ? ui->lineEditSurnameForm->setPlaceholderText("Apellidos") : ui->lineEditSurnameForm->setPlaceholderText("* Apellidos");
            if(object == ui->lineEditIdForm)
                ui->lineEditIdForm->text().count() > 0 ? ui->lineEditIdForm->setPlaceholderText("Documento de identidad") : ui->lineEditIdForm->setPlaceholderText("* Documento de identidad");
            if(object == ui->lineEditEmailForm)
                ui->lineEditEmailForm->text().count() > 0 ? ui->lineEditEmailForm->setPlaceholderText("Email") : ui->lineEditEmailForm->setPlaceholderText("* Email");
            if(object == ui->lineEditPassForm)
                ui->lineEditPassForm->text().count() > 0 ? ui->lineEditPassForm->setPlaceholderText("Contraseña") : ui->lineEditPassForm->setPlaceholderText("* Contraseña");
            if(object == ui->lineEditPass2Form)
                ui->lineEditPass2Form->text().count() > 0 ? ui->lineEditPass2Form->setPlaceholderText("Repita la contraseña") : ui->lineEditPass2Form->setPlaceholderText("* Repita la contraseña");
            if(object == ui->lineEditPhoneForm)
                ui->lineEditPhoneForm->text().count() > 0 ? ui->lineEditPhoneForm->setPlaceholderText("Telefono") : ui->lineEditPhoneForm->setPlaceholderText("* Telefono");
            if(object == ui->lineEditStreetForm)
                ui->lineEditStreetForm->text().count() > 0 ? ui->lineEditStreetForm->setPlaceholderText("Calle") : ui->lineEditStreetForm->setPlaceholderText("* Calle");
            if(object == ui->lineEditPostalForm)
                ui->lineEditPostalForm->text().count() > 0 ? ui->lineEditPostalForm->setPlaceholderText("Codigo Postal") : ui->lineEditPostalForm->setPlaceholderText("* Codigo Postal");
            if(object == ui->lineEditCityForm)
                ui->lineEditCityForm->text().count() > 0 ? ui->lineEditCityForm->setPlaceholderText("Ciudad") : ui->lineEditCityForm->setPlaceholderText("* Ciudad");
        }
    }


    return QMainWindow::eventFilter(object, event);

}


void MainWindow::on_pushButtonIniciarSesion_clicked()
{    
    if(!utils.verifyID(ui->lineEditUserID->text()) || !utils.validateTextField(ui->lineEditPassword->text()))  {
        ui->labelErrorIniciarSesion->setText("Por favor, complete los datos correctamente");
        return ;
    }


    user.setId(ui->lineEditUserID->text());
    user.setPassword(ui->lineEditPassword->text());
    startLoadingPage();
    bool encontrado = com.login(user);
    forgottenPassword = false;

    if(encontrado)
    {
        ui->stackedWidgetMenuBar->setCurrentIndex(0);
        showResumePage();
        userCreation = false;
        secondStepForm = false;
        ui->checkBoxForm2->setHidden(false);
        ui->pushButtonResume->setChecked(true);
        loggedIn = true;
    }
    else
    {
        stopLoadingPage(0);
        ui->labelErrorIniciarSesion->setText("Los datos introducidos no son validos");
        return ;
    }


    ui->lineEditUserID->clear();
    ui->lineEditPassword->clear();

}


void MainWindow::showResumePage(void)
{
    QString string;
    if(user.getGender() == Male)
        string = "Bienvenido ";
    else
        string = "Bienvenida ";

    string.append(user.getName());
    string = "<ul>" + string + "</ul";
    ui->labelWelcome->setText(string);
    //Creacion valida
    QList<QStandardItem *> list;

    com.retrieveCards(user);
    modelCardResume->removeRows(0,modelCardResume->rowCount(QModelIndex()));

    if(user.getCards().size() == 0) {
        ui->stackedWidgetResumeCards->setCurrentIndex(1);
    }
    else
    {
        ui->stackedWidgetResumeCards->setCurrentIndex(0);
        for(int row = 0; row < user.getCards().size(); row++) {

            QStandardItem *logo = new QStandardItem;

            if(user.getCards().at(row).getCardType() == "mastercard")   {
                logo->setData(QVariant(QPixmap::fromImage(QImage(":/MyFiles/Images/Images/masterCardSmallLogo.jpg"))), Qt::DecorationRole);
                list.append(logo);
            }
            else if(user.getCards().at(row).getCardType() == "visa") {
                logo->setData(QVariant(QPixmap::fromImage(QImage(":/MyFiles/Images/visaSmallLogo.gif"))), Qt::DecorationRole);
                list.append(logo);
            }
            else if(user.getCards().at(row).getCardType() == "amex")
            {
                logo->setData(QVariant(QPixmap::fromImage(QImage(":/MyFiles/Images/amex.png"))), Qt::DecorationRole);
                list.append(logo);
            }


            list.append(new QStandardItem(cardTypes.value(user.getCards().at(row).getCardType())));

            modelCardResume->appendRow(list);
            list.clear();
        }

        ui->tableView->resizeColumnsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

    user.clearPurchases();
    com.retrievePurchaes(user, ui->dateEditInitial->date(),ui->dateEditFinal->date(),  Basic, 1);

    modelAdquisitionsResume->removeRows(0,modelAdquisitionsResume->rowCount(QModelIndex()));

    if(user.getPurchases().size() == 0) {
        ui->stackedWidgetResumePurchases->setCurrentIndex(1);
    }
    else
    {
        ui->stackedWidgetResumePurchases->setCurrentIndex(0);

        for(int row = 0; row < user.getPurchases().size(); row++) {

            list.append(new QStandardItem(user.getPurchases().at(row).getAmount()));
            list.append(new QStandardItem(user.getPurchases().at(row).getVenue()));
            list.append(new QStandardItem(user.getPurchases().at(row).getDate().toString("d/M/yyyy")));
            modelAdquisitionsResume->appendRow(list);
            list.clear();
        }

        ui->tableViewAdquisitions->resizeColumnsToContents();
        ui->tableViewAdquisitions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    }

    QStringList stringList;
    stringList <<  user.getName() <<  user.getSurname() << user.getEmail() << user.getStreet() << user.getCity();
    personalData->setStringList(stringList);

    stopLoadingPage(1);

}

void MainWindow::on_pushButtonRegistrarse_clicked()
{
    ui->stackedWidgetInputForm->setCurrentIndex(1);
}

void MainWindow::showPayments(int mode, bool moreResults)
{    
    QList<QStandardItem *> list;
    QStringList header = (QStringList()<<"Cantidad"<<"Moneda"<<"Establecimiento"<<"Fecha");
    QFont font = QFont( "Helvetica Neue", 16, QFont::Bold);

    if(mode == 0)
    {
        if(moreResults)
            pagination = com.retrievePurchaes(user, ui->dateEditInitial->date(),ui->dateEditFinal->date(),  Detail, pagination.value(PAGE));
    }
    else
    {
        if(moreResults)
            pagination = com.retrievePurchaes(user, ui->dateEditInitial->date(),ui->dateEditFinal->date(),  Detail, pagination.value(PAGE));

        QStandardItem *item0 = new QStandardItem(header.at(0));
        item0->setFont(font);
        QStandardItem *item1 = new QStandardItem(header.at(1));
        item1->setFont(font);
        QStandardItem *item2 = new QStandardItem(header.at(2));
        item2->setFont(font);
        QStandardItem *item3 = new QStandardItem(header.at(3));
        item3->setFont(font);
        list.append(item0);
        list.append(item1);
        list.append(item2);
        list.append(item3);

    }



    if(user.getPurchases().size() > 0)
    {
        ui->stackedWidgetPyamentHistory->setCurrentIndex(0);
        modelTotalAdquisitions->removeRows(0,modelTotalAdquisitions->rowCount(QModelIndex()));

        if(pagination.value(PAGE) < pagination.value(NUM_PAGES))    {
            ui->pushButtonMorePurchasesResults->setEnabled(true);
            ui->pushButtonMorePurchasesResults->setText("Mas resultados");
        }
        else    {
            ui->pushButtonMorePurchasesResults->setEnabled(false);
            ui->pushButtonMorePurchasesResults->setText("No hay mas resultados");
        }

        if(mode == 1)   {
            modelTotalAdquisitions->appendRow(list);
            list.clear();
        }

        for(int row = 0; row < user.getPurchases().size(); row++) {

            list.append(new QStandardItem(user.getPurchases().at(row).getAmount()));
            if(mode == 1)   {
                list.append(new QStandardItem(user.getPurchases().at(row).getCurrency()));
            }
            list.append(new QStandardItem(user.getPurchases().at(row).getVenue()));
            list.append(new QStandardItem(user.getPurchases().at(row).getDate().toString()));
            modelTotalAdquisitions->appendRow(list);
            list.clear();
        }
        ui->tableViewTotalAdquisitions->resizeColumnsToContents();
        ui->tableViewTotalAdquisitions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    else
    {
        ui->stackedWidgetPyamentHistory->setCurrentIndex(1);
    }

    stopLoadingPage(2);
}

void MainWindow::on_pushButtonShowPayments_clicked()
{    
    startLoadingPage();
    user.clearPurchases();
    pagination.insert(PAGE,1);
    pagination.insert(NUM_PAGES,0);
    showPayments(purchasesInfoMode,true);
}

void MainWindow::on_pushButtonSimple_clicked()
{
    startLoadingPage();
    purchasesInfoMode = 0;
    ui->pushButtonDetail->setChecked(false);
    showPayments(purchasesInfoMode, false);
}

void MainWindow::on_pushButtonDetail_clicked()
{
    startLoadingPage();
    purchasesInfoMode = 1;
    ui->pushButtonSimple->setChecked(false);
    showPayments(purchasesInfoMode, false);
}

void MainWindow::on_pushButtonActivity_clicked()
{
    QDate today = QDate::currentDate();
    QDate yesterday = today.addDays(-15);
    ui->dateEditInitial->setDate(yesterday);
    ui->dateEditFinal->setDate(today);

    user.clearPurchases();
    pagination.insert(PAGE,1);
    pagination.insert(NUM_PAGES,0);

    purchasesInfoMode = 0;
    ui->pushButtonSimple->setChecked(true);
    ui->pushButtonDetail->setChecked(false);

    startLoadingPage();
    showPayments(purchasesInfoMode, true);
}
void MainWindow::on_pushButtonMorePurchasesResults_clicked()
{
    int page = pagination.value(PAGE);
    page++;
    pagination.insert(PAGE,page);
    showPayments(purchasesInfoMode, true);
}


void MainWindow::on_pushButtoLogo_clicked()
{
    startLoadingPage();
    showResumePage();
    ui->pushButtonResume->setChecked(true);
}

void MainWindow::on_pushButtonResume_clicked()
{
    startLoadingPage();
    showResumePage();
}

void MainWindow::on_pushButtonWallet_clicked()
{

    startLoadingPage();
    QList<QStandardItem *> list;
    QString date;
    QString creditCardNumber = "XXXX-XXXX-XXXX-";

    com.retrieveCards(user);

    modelTotalCards->removeRows(0,modelTotalCards->rowCount(QModelIndex()));

    // Generate data
    for(int row = 0; row < user.getCards().size(); row++) {

        QStandardItem *logo = new QStandardItem;

        if(user.getCards().at(row).getCardType() == "maestro") {
            logo->setData(QVariant(QPixmap::fromImage(QImage(":/MyFiles/Images/maestro.png"))), Qt::DecorationRole);
            list.append(logo);
        }
        else if(user.getCards().at(row).getCardType() == "visa")
        {
            logo->setData(QVariant(QPixmap::fromImage(QImage(":/MyFiles/Images/visaSmallLogo.gif"))), Qt::DecorationRole);
            list.append(logo);
        }
        else if(user.getCards().at(row).getCardType() == "amex")
        {
            logo->setData(QVariant(QPixmap::fromImage(QImage(":/MyFiles/Images/amex.png"))), Qt::DecorationRole);
            list.append(logo);
        }

        list.append(new QStandardItem(cardTypes.value(user.getCards().at(row).getCardType())));
        creditCardNumber = creditCardNumber +  user.getCards().at(row).getShortCardNumber();
        list.append(new QStandardItem(creditCardNumber));

        if(user.getCards().at(row).getSelected())
            list.append(new QStandardItem("Principal"));

        modelTotalCards->appendRow(list);
        creditCardNumber = "XXXX-XXXX-XXXX-";
        date.clear();
        list.clear();
    }

    if(user.getCards().size() == 0) {
        ui->stackedWidgetTableViewCards->setCurrentIndex(1);
        ui->labelShowCardsInfo->hide();
    }
    else    {
        ui->stackedWidgetTableViewCards->setCurrentIndex(0);
        ui->tableViewCards->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableViewCards->resizeColumnsToContents();
        ui->tableViewCards->clearSelection();
        ui->stackedWidgetCardDetailInfo->setCurrentIndex(1);
        ui->labelShowCardsInfo->show();
    }

    stopLoadingPage(3);

}

void MainWindow::currentRowChanged(QModelIndex current,QModelIndex previous)
{        
    if(current.row() > -1)
    {
        ui->stackedWidgetCardDetailInfo->setCurrentIndex(0);

        MyCard tempCard = user.getCards().at(current.row());

        ui->cardTypeWalletWidget->setText(cardTypes.value(tempCard.getCardType()));
        QString expirationDate = tempCard.getExpirationMonth() + "/" + tempCard.getExpirationYear();
        ui->cardExpDateWalletWidget->setText(expirationDate);

        QString creditCardNumber = "XXXX - XXXX - XXXX - ";
        creditCardNumber = creditCardNumber +  tempCard.getShortCardNumber();
        QRect rect = ui->labelCreditCardIcon->rect();
        QLabel *labelCardNumber = new QLabel(ui->labelCreditCardIcon);
        QFont f( "Helvetica Neue", 16, QFont::Bold);
        labelCardNumber->setFont(f);
        labelCardNumber->setText(creditCardNumber);
        labelCardNumber->setGeometry(rect);
        labelCardNumber->setAlignment(Qt::AlignCenter);
        labelCardNumber->setStyleSheet("QLabel { color : white; }");
        labelCardNumber->show();

        ui->pushButtonWalletSelectCard->setEnabled(!tempCard.getSelected());
    }
}

void MainWindow::on_pushButtonWalletSelectCard_clicked()
{
    QModelIndexList indexList = ui->tableViewCards->selectionModel()->selectedIndexes();
    int row = indexList.at(0).row();
    MyCard newSelectedCar = user.getCards().at(row);

    if(com.selectPreferredCard(newSelectedCar))
    {
        emit on_pushButtonWallet_clicked();
    }
}

void MainWindow::on_pushButtonAddCreditCard_clicked()
{
    ui->stackedWidgetInputForm->setCurrentIndex(2);
    ui->stackedWidgetMain->setCurrentIndex(0);
}



void MainWindow::on_pushButtonDeleteCard_clicked()
{


    QModelIndexList indexList = ui->tableViewCards->selectionModel()->selectedIndexes();
    int row = indexList.at(0).row();
    MyCard deletedCard = user.getCards().at(row);
    MyCard selectedCard;
    selectedCard.setIdCard(NULL);

    QMessageBox msgBox;
    msgBox.setText(tr("Tarjetas"));
    msgBox.setInformativeText("¿Está seguro de que desea eliminar esta tarjeta?");
    QAbstractButton *myYesButton = msgBox.addButton(tr("Si"), QMessageBox::YesRole);
    QAbstractButton *myNoButton = msgBox.addButton(tr("No"), QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.exec();

    if(msgBox.clickedButton() == myYesButton)
    {
        if(deletedCard.getSelected())
        {
            deletedCard.setIdCard("noSelection");

            if(user.getCards().size() > 1)
            {
                QStringList items;
                QString creditCardBase = "XXXX-XXXX-XXXX-";
                QHash<int,QString> temp;

                for(int i=0; i<user.getCards().size(); i++) {
                    if(!user.getCards().at(i).getSelected())    {
                        temp.insert(i, creditCardBase + user.getCards().at(i).getShortCardNumber() + " " + user.getCards().at(i).getExpirationMonth() + "/" +  user.getCards().at(i).getExpirationYear());
                        items << temp.value(i);
                    }
                }

                QInputDialog inputDialog(this);
                inputDialog.setInputMode(QInputDialog::TextInput);
                inputDialog.setOkButtonText("Aceptar");
                inputDialog.setCancelButtonText("Cancelar");
                inputDialog.setWindowTitle("Tarjetas");
                inputDialog.setLabelText("Elige una de tus otras tarjetas como principal");
                inputDialog.setComboBoxItems(items);


                if( inputDialog.exec() && !items.isEmpty() )
                {
                    QString text = inputDialog.textValue();                    
                    deletedCard = user.getCards().at(temp.key(text));
                }
            }
        }

        startLoadingPage();
        com.deleteCard(user,deletedCard,selectedCard);
        stopLoadingPage(3);
        emit on_pushButtonWallet_clicked();

    }
    setWindowIcon( QIcon("cut.png"));

}

void MainWindow::on_pushButtonSetting_clicked()
{
    startLoadingPage();
    int rowCol;

    /*
     * Table Widget Personal Info
     */

    QSignalMapper *editPersonalInfoButtonSignalMapper = new QSignalMapper(this);

    QStringList data;
    data << user.getName();
    data << user.getSurname();
    data << user.getEmail();

    ui->tableWidgetPersonalInfo->setRowCount(data.size());
    ui->tableWidgetPersonalInfo->setColumnCount(COLSINFO);

    connect(editPersonalInfoButtonSignalMapper, SIGNAL(mapped(int)), this, SLOT(editPersonalInfo(int)));

    for(int row = 0; row < data.size(); row++) {
        QPushButton*  editButtonAddress= new QPushButton("Editar",ui->tableWidgetPersonalInfo);
        editButtonAddress->setStyleSheet("border: none; margin: 0px; padding: 0px; color: #03bff5");

        ui->tableWidgetPersonalInfo->setItem(row,0,new QTableWidgetItem(data.at(row)));
        ui->tableWidgetPersonalInfo->setCellWidget(row,1, editButtonAddress);

        rowCol = 1+row*COLSINFO;
        editPersonalInfoButtonSignalMapper->setMapping(editButtonAddress, rowCol);
        connect(editButtonAddress, SIGNAL(clicked()), editPersonalInfoButtonSignalMapper, SLOT(map()));
    }

    ui->tableWidgetPersonalInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetPersonalInfo->resizeColumnsToContents();

    /*
     * Table Widget Phones
     */


    QSignalMapper *editPhoneButtonSignalMapper = new QSignalMapper(this);
    QSignalMapper *deletePhoneButtonSignalMapper = new QSignalMapper(this);

    connect(editPhoneButtonSignalMapper, SIGNAL(mapped(int)), this, SLOT(editPhone(int)));
    connect(deletePhoneButtonSignalMapper, SIGNAL(mapped(int)), this, SLOT(deletePhone(int)));

    com.retrievePhones(user);

    ui->tableWidgetPhones->setRowCount(user.getPhones().size());
    ui->tableWidgetPhones->setColumnCount(COLSPHONE);

    for(int row = 0; row < user.getPhones().size(); row++) {

        QPushButton*  editButtonPhone= new QPushButton("Editar",ui->tableWidgetPhones);
        editButtonPhone->setStyleSheet("border: none; margin: 0px; padding: 0px; color: #03bff5");
        QPushButton* deleteButtonPhone = new QPushButton("Eliminar",ui->tableWidgetPhones);
        deleteButtonPhone->setStyleSheet("border: none; margin: 0px; padding: 0px; color: #03bff5");

        ui->tableWidgetPhones->setItem(row,0,new QTableWidgetItem(user.getPhones().at(row)));
        ui->tableWidgetPhones->setCellWidget(row,1, editButtonPhone);
        ui->tableWidgetPhones->setCellWidget(row,2, deleteButtonPhone);

        rowCol = 1+row*COLSPHONE;
        editPhoneButtonSignalMapper->setMapping(editButtonPhone, rowCol);
        connect(editButtonPhone, SIGNAL(clicked()), editPhoneButtonSignalMapper, SLOT(map()));

        rowCol = 2+row*COLSPHONE;
        deletePhoneButtonSignalMapper->setMapping(deleteButtonPhone, rowCol);
        connect(deleteButtonPhone, SIGNAL(clicked()), deletePhoneButtonSignalMapper, SLOT(map()));

    }

    ui->tableWidgetPhones->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetPhones->resizeColumnsToContents();


    /*
     * Widget Billing Address
     */

    ui->labelStreet->setText(user.getStreet());
    ui->labelPostcode->setText(user.getPostcode());
    ui->labelCity->setText(user.getCity());
    ui->labelCountry->setText(user.getCountry());

    if(user.getAccountBlocked())
        ui->pushButtonBlockAccount->setText("Desbloquear cuenta");
    if(user.getAccountBlocked())
        ui->pushButtonBlockAccount->setText("Bloquear cuenta");


    stopLoadingPage(5);
}

void MainWindow::btnOutClickSlot(int btn)
{    
    QMessageBox::critical(this, QString::number(btn), tr(""));
}

void MainWindow::editPersonalInfo(int rowCol)
{

    int row = rowCol/COLSINFO;
    QString text;
    QInputDialog inputDialog(this);
    inputDialog.setInputMode(QInputDialog::TextInput);
    inputDialog.setOkButtonText("Aceptar");
    inputDialog.setCancelButtonText("Cancelar");

    switch (row) {
    case 0:
        inputDialog.setWindowTitle("Nombre");
        inputDialog.setLabelText("Introduzca el nuevo nombre:");
        if(inputDialog.exec())  {
            text = inputDialog.textValue();
            if(utils.validateTextField(text))  {
                ui->labelAccountMessages->setText("    Procesando...");
                if(com.updateName(user,text))   {
                    ui->tableWidgetPersonalInfo->setItem(row,0,new QTableWidgetItem(text));
                    ui->labelAccountMessages->setText("    Cambiado con exito");
                }
                else    {
                    ui->labelAccountMessages->setText("    Ha habido un problema al realizar la actualizacion.");
                }

            }
            else    {
                ui->labelAccountMessages->setText("    El nombre no puede ser vacio");
            }
        }

        break;

    case 1:

        inputDialog.setWindowTitle("Apellidos");
        inputDialog.setLabelText("Introduzca los nuevos apellidos:");
        if(inputDialog.exec())  {
            text = inputDialog.textValue();
            if(utils.validateTextField(text))  {
                ui->labelAccountMessages->setText("    Procesando...");
                if(com.updateSurname(user,text))   {
                    ui->tableWidgetPersonalInfo->setItem(row,0,new QTableWidgetItem(text));
                    ui->labelAccountMessages->setText("    Cambiado con exito");
                }
                else    {
                    ui->labelAccountMessages->setText("    Ha habido un problema al realizar la actualizacion.");
                }

            }
            else    {
                ui->labelAccountMessages->setText("    El apellido no puede ser vacio");
            }
        }
        break;

    case 2:

        inputDialog.setWindowTitle("Email");
        inputDialog.setLabelText("Introduzca el nuevo email:");
        if(inputDialog.exec())  {
            if(utils.validateEmail(text))  {
                ui->labelAccountMessages->setText("    Procesando...");
                if(com.updateEmail(user,text))   {
                    ui->tableWidgetPersonalInfo->setItem(row,0,new QTableWidgetItem(text));
                    ui->labelAccountMessages->setText("    Cambiado con exito");
                }
                else    {
                    ui->labelAccountMessages->setText("    Ha habido un problema al realizar la actualizacion.");
                }

            }
            else    {
                ui->labelAccountMessages->setText("    El email no es valido");
            }
        }
        break;

    }

}


void MainWindow::editPhone(int rowCol)
{

    int row = rowCol/COLSPHONE;
    QInputDialog inputDialog;
    inputDialog.setOkButtonText("Aceptar");
    inputDialog.setCancelButtonText("Cancelar");


    inputDialog.setWindowTitle("Telefono");
    inputDialog.setLabelText("Introduzca el nuevo teléfono:");
    if(inputDialog.exec())  {
        QString text = inputDialog.textValue();
        ui->labelAccountMessages->setText("    Procesando...");
        if(utils.validateTextField(text))  {

            QString old = ui->tableWidgetPhones->item(row,0)->text();
            if(com.updatePhone(user,old,text))  {
                ui->labelAccountMessages->setText("    Cambio realizado con éxito");
                ui->tableWidgetPhones->setItem(row,0,new QTableWidgetItem(text));
            }
            else    {
                ui->labelAccountMessages->setText("    Ha habido un problema al realizar la actualizacion");
            }

        }
        else    {
            ui->labelAccountMessages->setText("    La cadena no puede ser vacia");
        }
    }



}

void MainWindow::deletePhone(int rowCol)
{

    int row = rowCol/COLSPHONE;


    if(row == 0)
    {
        ui->labelAccountMessages->setText("    No puede eliminar tu teléfono principal");
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Telefonos"));
        msgBox.setInformativeText("¿Realmente desea eliminar este teléfono?");
        QAbstractButton *myYesButton = msgBox.addButton(tr("Si"), QMessageBox::YesRole);
        QAbstractButton *myNoButton = msgBox.addButton(tr("No"), QMessageBox::NoRole);
        msgBox.setIcon(QMessageBox::Question);
        msgBox.exec();

        if(msgBox.clickedButton() == myYesButton) {
            QString old = ui->tableWidgetPhones->item(row,0)->text();
            ui->labelAccountMessages->setText("    Procesando...");
            if(com.deletePhone(user,old))   {
                ui->labelAccountMessages->setText("    Eliminación realizada con éxito");
                ui->tableWidgetPhones->removeRow(row);
            }
            else
                ui->labelAccountMessages->setText("    La cadena no puede ser vacia");
        } else {

        }

    }

}


void MainWindow::on_pushButtonAddPhone_clicked()
{

    bool ok;
    QInputDialog inputDialog;
    inputDialog.setCancelButtonText("Aceptar");
    inputDialog.setCancelButtonText("Cancelar");
    QString text = inputDialog.getText(this, tr("Introduzca el nuevo telefono"), tr("Teléfono:"), QLineEdit::Normal,tr(""), &ok );

    if( ok && !text.isEmpty() )
    {
        ui->labelAccountMessages->setText("    Procesando...");
        if(com.insertPhone(user,text))
            emit on_pushButtonSetting_clicked();
    }

}

void MainWindow::on_pushButtonSecondStepForm_clicked()
{

    bool filled = true;
    bool temp;
    QString message;

    temp = utils.validateTextField(ui->lineEditNameForm->text()) ? true : false;
    if(filled == true) filled = temp;
    if(!temp) ui->lineEditNameForm->setPlaceholderText("* Nombre");

    temp = utils.validateTextField(ui->lineEditSurnameForm->text()) ? true : false;
    if(filled == true) filled = temp;
    if(!temp) ui->lineEditSurnameForm->setPlaceholderText("* Apellidos");

    temp = ui->comboBoxIdType->currentIndex() > 0 ? true : false;
    if(filled == true) filled = temp;

    temp = false;
    if(!utils.verifyID(ui->lineEditIdForm->text())) {
        if(ui->lineEditIdForm->text().count() > 0) message = message + " DNI incorrecto. ";
        if(filled == true) filled = temp;
    }
    if(!temp) ui->lineEditIdForm->setPlaceholderText("* Documento de identidad");

    temp = false;
    if(!utils.isOver18(ui->dateEditForm->date()))    {
        message = message + "Debe ser mayor de edad. ";
        if(filled == true) filled = temp;
    }

    temp = false;
    if(!utils.validateEmail(ui->lineEditEmailForm->text()))    {
        if(ui->lineEditEmailForm->text().count() > 0) message = message + "Revise el email. ";
        if(filled == true) filled = temp;
        if(!temp) ui->lineEditEmailForm->setPlaceholderText("* Email");
    }

    temp = utils.validateTextField(ui->lineEditPassForm->text()) ? true : false;
    if(filled == true) filled = temp;
    if(!temp) ui->lineEditPassForm->setPlaceholderText("* Contraseña");

    temp = utils.validateTextField(ui->lineEditPass2Form->text()) ? true : false;
    if(filled == true) filled = temp;
    if(!temp) ui->lineEditPass2Form->setPlaceholderText("* Repita la contraseña");

    temp = false;
    if(utils.comparePassword(ui->lineEditPassForm->text(),ui->lineEditPass2Form->text()) == 0)    {
        message = message + "Revise las coinciden. ";
        if(filled == true) filled = temp;
    }

    temp = utils.validateTextField(ui->lineEditPhoneForm->text()) ? true : false;
    if(filled == true) filled = temp;
    if(!temp) ui->lineEditPhoneForm->setPlaceholderText("* Teléfono");

    temp = utils.validateTextField(ui->lineEditStreetForm->text()) ? true : false;
    if(filled == true) filled = temp;
    if(!temp) ui->lineEditStreetForm->setPlaceholderText("* Calle");

    temp = utils.validateTextField(ui->lineEditPostalForm->text()) ? true : false;
    if(filled == true) filled = temp;
    if(!temp) ui->lineEditPostalForm->setPlaceholderText("* Código Postal");

    temp = utils.validateTextField(ui->lineEditCityForm->text()) ? true : false;
    if(filled == true) filled = temp;
    if(!temp) ui->lineEditCityForm->setPlaceholderText("* Ciudad");

    temp = ui->comboBoxCountries->currentIndex() > 0 ? true : false;
    if(filled == true) filled = temp;

    if(filled == true)
    {
        user.setId(ui->lineEditIdForm->text());
        user.setEmail(ui->lineEditEmailForm->text());

        startLoadingForm();
        bool found = com.searchUser(user);

        if(found == false)
        {
            //Creacion valida
            stopLoadingForm(2);
            ui->labelFormCompletion->setText("");

            user.setName(ui->lineEditNameForm->text());
            user.setSurname(ui->lineEditSurnameForm->text());
            user.setPassword(ui->lineEditPassForm->text());
            user.setBirthday(ui->dateEditForm->date());
            user.setStreet(ui->lineEditStreetForm->text());
            user.setPostcode(ui->lineEditPostalForm->text());
            user.setCity(ui->lineEditCityForm->text());
            user.setCountry(ui->comboBoxCountries->currentText());
            user.setPhones(QStringList(ui->lineEditPhoneForm->text()));
            if(ui->radioButtonMaleForm->isChecked())
                user.setGender(Male);
            else
                user.setGender(Female);


        }
        else
        {
            stopLoadingForm(1);
            ui->labelFormCompletion->setStyleSheet(StyleSheetProvider::getErrorStyleLabelForm());
            ui->labelFormCompletion->setText("El email o DNI ya están registrados");
        }
    }
    else
    {
        ui->labelFormCompletion->setStyleSheet(StyleSheetProvider::getErrorStyleLabelForm());
        QString errors;
        errors = " Por favor, complete todos los campos. ";
        if(message != "") errors = errors + "\n" + message;
        ui->labelFormCompletion->setText(errors);
    }

    secondStepForm = true;
}

void MainWindow::on_pushButtonCreateAccoutForm_clicked()
{

    bool filled = true;
    bool temp = false;
    QString message;
    message = "";
    QString parsedCreditCard = utils.parseCreditCard(ui->lineEditCardNumberForm2->text());

    if(!utils.luhn(parsedCreditCard.toStdString()))    {
        message = message + " Numero de tarjeta no valido. ";
        if(filled == true) filled = temp;
    }

    temp = utils.isValidDate(ui->dueDateEditForm2->date()) ? true : false;
    if(filled == true) filled = temp;

    temp = ui->comboBoxCardTypeForm2->currentIndex() > 0 ? true : false;
    if(filled == true) filled = temp;

    temp = utils.validateTextField(ui->lineEditCSCForm2->text()) ? true : false;
    if(filled == true) filled = temp;
    if(!temp) ui->lineEditCSCForm2->setPlaceholderText("* CSC");

    if(filled == true)
    {
        startLoadingForm();

        MyCard tempCard;
        tempCard.setCardNumber(parsedCreditCard);
        tempCard.setShortCardNumber(utils.extractLastCardDigits(tempCard.getCardNumber()));
        tempCard.setCardType(cardTypes.key(ui->comboBoxCardTypeForm2->currentText()));
        tempCard.setCvv(ui->lineEditCSCForm2->text());
        tempCard.setExpirationMonth(QString::number(ui->dueDateEditForm2->date().month()));
        tempCard.setExpirationYear(QString::number(ui->dueDateEditForm2->date().year()));

        if(userCreation)
        {
            if(com.registerUser(user))
            {
                //Creacion valida
                tempCard.setSelected(true);
                startLoadingForm();
                if(com.insertCard(user,tempCard))    {
                    ui->labelFormCompletion->setText("");
                    stopLoadingForm(4);
                    ui->labelFingerprintWidgetInfo->setText("Para poder usar su cuenta debe introducir dos huellas dactilares");
                    numFingerprintScanned = 0;
                    ui->stackedWidgetMain->setCurrentIndex(4);
                }
                else    {
                    stopLoadingForm(2);
                    ui->labelFormCompletion2->setStyleSheet(StyleSheetProvider::getErrorStyleLabelForm());
                    ui->labelFormCompletion->setText("Los datos señalados ya se encuentran almacenados.");
                }

            }
            else
            {
                //No se puede crear
                ui->labelFormCompletion2->setStyleSheet(StyleSheetProvider::getErrorStyleLabelForm());
                ui->labelFormCompletion->setText("Los datos señalados ya se encuentran almacenados.");
            }
        }
        else
        {
            tempCard.setSelected(ui->checkBoxForm2->isChecked());
            startLoadingForm();
            if(com.insertCard(user,tempCard))    {
                ui->labelFormCompletion->setText("");
                emit on_pushButtonWallet_clicked();
            }
            else    {
                stopLoadingForm(2);
                ui->labelFormCompletion2->setStyleSheet(StyleSheetProvider::getErrorStyleLabelForm());
                ui->labelFormCompletion2->setText("Tarjeta no almancenada");
            }
        }

    }
    else
    {
        stopLoadingForm(2);
        ui->labelFormCompletion2->setStyleSheet(StyleSheetProvider::getErrorStyleLabelForm());
        message = "Complete todos los campos. \n" + message;
        ui->labelFormCompletion2->setText(message);

    }

    secondStepForm = true;

}

void MainWindow::on_pushButtonCloseSession_clicked()
{
    closeSession();
}


void MainWindow::on_pushButtonChangePassword_clicked()
{

    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("Introduzca sus datos"));

    QList<QLineEdit *> fields;

    QLineEdit *lineEdit1 = new QLineEdit(&dialog);
    lineEdit1->setEchoMode(QLineEdit::Password);
    QString label = QString("Contraseña antigua");
    form.addRow(label, lineEdit1);

    QLineEdit *lineEdit2 = new QLineEdit(&dialog);
    lineEdit2->setEchoMode(QLineEdit::Password);
    QString label2 = QString("Nueva contraseña");
    form.addRow(label2, lineEdit2);

    QLineEdit *lineEdit3 = new QLineEdit(&dialog);
    lineEdit3->setEchoMode(QLineEdit::Password);
    QString label3 = QString("Repita la nueva contraseña");
    form.addRow(label3, lineEdit3);
    fields << lineEdit1;
    fields << lineEdit2;
    fields << lineEdit3;

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);

    buttonBox.button(QDialogButtonBox::Ok)->setText(tr("Aceptar"));
    buttonBox.button(QDialogButtonBox::Cancel)->setText(tr("Cancelar"));


    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {
        if(utils.comparePassword(lineEdit1->text(),user.getPassword())) {
            if(utils.comparePassword(lineEdit2->text(),lineEdit3->text())) {
                if(com.updatePassword(user,lineEdit3->text()))
                {
                    ui->labelAccountMessages->setText("Cambiado con exito. Inicie sesion de nuevo.");
                    passwordChanged = true;
                    closeSession();
                }
            }
            else    {
                ui->labelAccountMessages->setText("Las password actuales no coinciden");
            }
        }
        else    {

            ui->labelAccountMessages->setText("La contraseña que no es valida");
        }
    }

}

void MainWindow::on_pushButtonBlockAccount_clicked()
{    
    QInputDialog inputDialog;
    inputDialog.setOkButtonText("Aceptar");
    inputDialog.setCancelButtonText("Cancelar");
    inputDialog.setWindowTitle("Bloquear Cuenta");
    inputDialog.setLabelText("¿Esta seguro que desea bloquear la cuenta? No podra realizar ninguna transaccion. \nIntroduzca su contraseña para continuar:");

    if(inputDialog.exec())  {
        QString text = inputDialog.textValue();
        if(utils.comparePassword(user.getPassword(),text))  {

            if(com.blockAccount(user))  {
                ui->labelAccountMessages->setText("Cambiado con exito");
                user.setAccountBlocked(!user.getAccountBlocked());
                if(user.getAccountBlocked())
                    ui->pushButtonBlockAccount->setText("Desbloquear cuenta");
                if(user.getAccountBlocked())
                    ui->pushButtonBlockAccount->setText("Bloquear cuenta");
            }
            else    {
                ui->labelAccountMessages->setText("Ha habido un problema al realizar la actualizacion.");
            }
        }
        else    {
            ui->labelAccountMessages->setText("Contraseña incorrecta");
        }
    }


}

void MainWindow::on_pushButtonDeleteAccount_clicked()
{

    QInputDialog inputDialog;
    inputDialog.setOkButtonText("Aceptar");
    inputDialog.setCancelButtonText("Cancelar");


    inputDialog.setWindowTitle("Eliminar Cuenta");
    inputDialog.setLabelText("¿Esta seguro que desea bloquear la cuenta? No podra recuperar su cuenta.\n Introduzca su contraseña para continar con la eliminación.");
    if(inputDialog.exec())  {
        QString text = inputDialog.textValue();

        if(utils.comparePassword(user.getPassword(),text))  {

            if(com.deleteAccount(user)) {
                ui->labelAccountMessages->setText("Cuenta eliminada");
                passwordChanged = true;
                closeSession();
            }
            else    {
                ui->labelAccountMessages->setText("Ha habido un problema al realizar la actualizacion.");
            }
        }
        else    {
            ui->labelAccountMessages->setText("Contraseña incorrecta");
        }
    }


}

void MainWindow::on_pushButtonCloseSession_2_clicked()
{
    closeSession();
}

void MainWindow::closeSession(void)
{
    if(com.logout() || passwordChanged)
    {
        ui->stackedWidgetMain->setCurrentIndex(0);
        ui->stackedWidgetMenuBar->setCurrentIndex(1);
        secondStepForm = false;
        userCreation = true;
        loggedIn = false;
        passwordChanged = false;
        ui->checkBoxForm2->setHidden(true);
        clearLocalInfo();
    }
}

void MainWindow::startLoadingForm(void)
{
    movieForm->start();
    ui->stackedWidgetInputForm->setCurrentIndex(3);

}

void MainWindow::stopLoadingForm(int nextIndex)
{
    movieForm->stop();
    ui->stackedWidgetInputForm->setCurrentIndex(nextIndex);
}

void MainWindow::startLoadingPage(void)
{
    movieMain->start();
    ui->stackedWidgetMain->setCurrentIndex(6);
    ui->stackedWidgetCardDetailInfo->setCurrentIndex(1);
    resetFingerprintWidget();
    ui->pushButtonFinger1->setHidden(true);
    ui->pushButtonFinger2->setHidden(true);
    ui->pushButtonFinger3->setHidden(true);
    ui->pushButtonFinger4->setHidden(true);
    ui->pushButtonFinger5->setHidden(true);
    ui->pushButtonLeftHand->setChecked(false);
    ui->pushButtonRightHand->setChecked(false);
}

void MainWindow::stopLoadingPage(int nextIndex)
{
    movieMain->stop();
    ui->stackedWidgetMain->setCurrentIndex(nextIndex);
}

void MainWindow::on_pushButtonScanFingerprint_clicked()
{
    bool scan = true;
    int times = 0;
    cv::Mat temp;
    QInputDialog inputDialog;
    inputDialog.setOkButtonText("Aceptar");
    inputDialog.setCancelButtonText("Cancelar");


    inputDialog.setWindowTitle("Contraseña");
    inputDialog.setLabelText("Por favor, autorice el proceso de lectura");
    if(inputDialog.exec())  {
        QString text = inputDialog.textValue();
        if(text == key) {

            while(scan && times < 100)
            {
                scanner.loadFromScanner().copyTo(temp);
                if(temp.rows > 200)
                {
                    boost::thread workerThread(&ProcessFingerprint::obtainMinutiaeFromSourceImageAsync, &procFingerprint,temp, 304);
                    ui->labelFingerprintWidgetInfo->setText("Espere mientar se realiza el proceso.");
                    resetFingerprintWidget();
                    scan = false;
                }
                else {
                    times++;
                }

                QThread::sleep(1);
            }
        }
        else    {
            QMessageBox msgBox(QMessageBox::Information, "Lectura de huellas", tr("La contraseña no es valida"), QMessageBox::Yes);
            msgBox.setButtonText(QMessageBox::Yes, "Aceptar");
            msgBox.exec();
        }
    }


    if(times >= 100)
        ui->labelFingerprintWidgetInfo->setText("Hay algun problema con el dispositivo, consulte con el dependiente.");
}

void MainWindow::finishedMinutiaeExtration(void )
{
    MyFingerprint fingerprint;
    fingerprint.fingerType = selectedFinger;
    fingerprint.handType = selectedHand;
    fingerprint.minutiaes = procFingerprint.minutiaeExtracted;


    if(!forgottenPassword)  {

        if(com.saveFingerprint(user,fingerprint))
        {

            ui->labelFingerprintWidgetInfo->setText("Huella almacenada con éxito.");

            numFingerprintScanned++;
            if(numFingerprintScanned > 0)   {
                ui->labelFingerprintWidgetInfo->setText("Huella almacenada con éxito. Introduzca una segunda huella");
                if(numFingerprintScanned == 2)  {
                    stopLoadingPage(0);
                    stopLoadingForm(4);
                    numFingerprintScanned = -1;
                }
            }
            else    {
                numFingerprintScanned = -1;
            }
        }
        else    {
            ui->labelFingerprintWidgetInfo->setText("Hubo algún problema durante el proceso. \n Por favor pruebe de nuevo");
            forgottenPassword = false;
        }
    }
    else {

        if(com.forgottenPassword(user,fingerprint))
        {
            ui->labelFingerprintWidgetInfo->setText("Su contraseña ha sido cambiada con exito.");
            QThread::sleep(2);
            clearLocalInfo();
            ui->stackedWidgetMain->setCurrentIndex(0);
        }
        else    {
            ui->labelFingerprintWidgetInfo->setText("Su huella no ha sido encontrada. Pruebe de nuevo.");

        }


    }

    ui->pushButtonFinger1->setHidden(true);
    ui->pushButtonFinger2->setHidden(true);
    ui->pushButtonFinger3->setHidden(true);
    ui->pushButtonFinger4->setHidden(true);
    ui->pushButtonFinger5->setHidden(true);
    ui->pushButtonLeftHand->setChecked(false);
    ui->pushButtonRightHand->setChecked(false);




}


void MainWindow::on_pushButtonFingerprint_clicked()
{

    ui->labelFingerprintWidgetInfo->setText("Añada sus huellas dactilares para disfrutar del sistema");
    ui->stackedWidgetMain->setCurrentIndex(4);
}

void MainWindow::resetFingerprintWidget(void)
{

    bgFingerprint->setExclusive(false);
    ui->pushButtonFinger1->setChecked(false);
    ui->pushButtonFinger2->setChecked(false);
    ui->pushButtonFinger3->setChecked(false);
    ui->pushButtonFinger4->setChecked(false);
    ui->pushButtonFinger5->setChecked(false);
    bgFingerprint->setExclusive(true);
    ui->pushButtonFinger1->setEnabled(true);
    ui->pushButtonFinger2->setEnabled(true);
    ui->pushButtonFinger3->setEnabled(true);
    ui->pushButtonFinger4->setEnabled(true);
    ui->pushButtonFinger5->setEnabled(true);
    ui->pushButtonScanFingerprint->setHidden(true);
}

void MainWindow::on_pushButtonLeftHand_clicked()
{
    ui->pushButtonFinger1->setHidden(false);
    ui->pushButtonFinger2->setHidden(false);
    ui->pushButtonFinger3->setHidden(false);
    ui->pushButtonFinger4->setHidden(false);
    ui->pushButtonFinger5->setHidden(false);
    ui->pushButtonFinger1->setText("Meñique");
    ui->pushButtonFinger2->setText("Anular");
    ui->pushButtonFinger3->setText("Corazón");
    ui->pushButtonFinger4->setText("Índice");
    ui->pushButtonFinger5->setText("Pulgar");
    ui->pushButtonRightHand->setChecked(false);
    resetFingerprintWidget();
    selectedHand = Left;
}


void MainWindow::on_pushButtonRightHand_clicked()
{
    ui->pushButtonFinger1->setHidden(false);
    ui->pushButtonFinger2->setHidden(false);
    ui->pushButtonFinger3->setHidden(false);
    ui->pushButtonFinger4->setHidden(false);
    ui->pushButtonFinger5->setHidden(false);
    ui->pushButtonFinger1->setText("Pulgar");
    ui->pushButtonFinger2->setText("Índice");
    ui->pushButtonFinger3->setText("Corazón");
    ui->pushButtonFinger4->setText("Anular");
    ui->pushButtonFinger5->setText("Meñique");
    ui->pushButtonLeftHand->setChecked(false);
    resetFingerprintWidget();
    selectedHand = Right;
}

void MainWindow::on_pushButtonFinger1_clicked()
{
    switch(selectedHand)
    {
    case Left:
        selectedFinger = Pinkie;
        break;
    case Right:
        selectedFinger = Thumb;
        break;
    default:
        break;
    }

    ui->pushButtonScanFingerprint->setHidden(false);

}

void MainWindow::on_pushButtonFinger2_clicked()
{
    switch(selectedHand)
    {
    case Left:
        selectedFinger = Ring;
        break;
    case Right:
        selectedFinger = Index;
        break;
    default:
        break;
    }

    ui->pushButtonScanFingerprint->setHidden(false);
}

void MainWindow::on_pushButtonFinger3_clicked()
{
    switch(selectedHand)
    {
    case Left:
        selectedFinger = Middle;
        break;
    case Right:
        selectedFinger = Middle;
        break;
    default:
        break;
    }

    ui->pushButtonScanFingerprint->setHidden(false);
}

void MainWindow::on_pushButtonFinger4_clicked()
{
    switch(selectedHand)
    {
    case Left:
        selectedFinger = Index;
        break;
    case Right:
        selectedFinger = Ring;
        break;
    default:
        break;
    }

    ui->pushButtonScanFingerprint->setHidden(false);
}

void MainWindow::on_pushButtonFinger5_clicked()
{
    switch(selectedHand)
    {
    case Left:
        selectedFinger = Thumb;
        break;
    case Right:
        selectedFinger = Pinkie;
        break;
    default:
        break;
    }

    ui->pushButtonScanFingerprint->setHidden(false);
}

void MainWindow::on_pushButtonEditAddress_clicked()
{
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Introduzca sus datos"));

    // Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;

    QLineEdit *lineEdit1 = new QLineEdit(&dialog);
    lineEdit1->setText(user.getStreet());
    QString label = QString("Calle: ");
    form.addRow(label, lineEdit1);

    QLineEdit *lineEdit2 = new QLineEdit(&dialog);
    lineEdit2->setText(user.getPostcode());
    QString label2 = QString("Codigo Postal: ");
    form.addRow(label2, lineEdit2);

    QLineEdit *lineEdit3 = new QLineEdit(&dialog);
    lineEdit3->setText(user.getCity());
    QString label3 = QString("Ciudad: ");
    form.addRow(label3, lineEdit3);

    QLineEdit *lineEdit4 = new QLineEdit(&dialog);
    lineEdit4->setText(user.getCountry());
    QString label4 = QString("Pais: ");
    form.addRow(label4, lineEdit4);

    fields << lineEdit1;
    fields << lineEdit2;
    fields << lineEdit3;
    fields << lineEdit4;

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);

    buttonBox.button(QDialogButtonBox::Ok)->setText(tr("Aceptar"));
    buttonBox.button(QDialogButtonBox::Cancel)->setText(tr("Cancelar"));

    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields

        ui->labelAccountMessages->setText("    Procesando...");
        if(com.updateAddress(user,lineEdit1->text(),lineEdit2->text(),lineEdit3->text(),lineEdit4->text()))
        {
            ui->labelAccountMessages->setText("    Cambiado con exito");
            emit on_pushButtonSetting_clicked();
        }
        else    {
            ui->labelAccountMessages->setText("    No se pudieron actualizar los campos");
        }



    }
}


void MainWindow::on_pushButtonGoBackToForm_clicked()
{
    if(!loggedIn)    {
        ui->stackedWidgetInputForm->setCurrentIndex(1);
        clearLocalInfo();
    }
    else    {
        ui->stackedWidgetMain->setCurrentIndex(3);
    }
}

void MainWindow::on_pushButtonBackToLanding_clicked()
{
    ui->stackedWidgetInputForm->setCurrentIndex(0);
    clearLocalInfo();
}

void MainWindow::clearLocalInfo()
{
    user.clearUser();
    pagination.insert(PAGE,1);
    forgottenPassword = false;
    secondStepForm = false;
    ui->labelFormCompletion->setStyleSheet(StyleSheetProvider::getDefaultStyleLabelForm());
    ui->labelFormCompletion->setText("");
    ui->labelFormCompletion2->setStyleSheet(StyleSheetProvider::getDefaultStyleLabelForm());
    ui->labelFormCompletion2->setText("");
}



void MainWindow::on_pushButtonForgottenPassword_clicked()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("Introduzca sus datos"));

    QList<QLineEdit *> fields;
    QLineEdit *lineEdit1 = new QLineEdit(&dialog);
    lineEdit1->setEchoMode(QLineEdit::Normal);
    QString label = QString("DNI");
    form.addRow(label, lineEdit1);

    QLineEdit *lineEdit2 = new QLineEdit(&dialog);
    lineEdit2->setEchoMode(QLineEdit::Normal);
    QString labe2 = QString("Email");
    form.addRow(labe2, lineEdit2);

    QLineEdit *lineEdit3 = new QLineEdit(&dialog);
    lineEdit3->setEchoMode(QLineEdit::Password);
    QString label3 = QString("Nueva Contraseña");
    form.addRow(label3, lineEdit3);

    QLineEdit *lineEdit4 = new QLineEdit(&dialog);
    lineEdit4->setEchoMode(QLineEdit::Password);
    QString label4 = QString("Repita la nueva Contraseña");
    form.addRow(label4, lineEdit4);
    fields << lineEdit1;
    fields << lineEdit2;
    fields << lineEdit3;
    fields << lineEdit4;

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {

        if(utils.comparePassword(lineEdit3->text(),lineEdit4->text())) {
            user.setId(lineEdit1->text());
            user.setEmail(lineEdit2->text());
            user.setPassword(lineEdit3->text());
            ui->stackedWidgetMain->setCurrentIndex(4);
            ui->labelFingerprintWidgetInfo->setText("Para recuperar su contraseña introduzca su huella");
            forgottenPassword = true;
        }
        else    {
            ui->labelAccountMessages->setText("    Las password actuales no coinciden");
        }


    }





}

void MainWindow::on_pushButtonLandingIcon_clicked()
{
    clearLocalInfo();
    ui->stackedWidgetMain->setCurrentIndex(0);
    ui->stackedWidgetMenuBar->setCurrentIndex(0);
}



void MainWindow::on_pushButtonResumeGoToCards_clicked()
{
    on_pushButtonWallet_clicked();
    ui->pushButtonResume->setChecked(false);
    ui->pushButtonWallet->setChecked(true);
}

void MainWindow::on_pushButtonResumeGoToPurchases_clicked()
{
    on_pushButtonActivity_clicked();
    ui->pushButtonResume->setChecked(false);
    ui->pushButtonActivity->setChecked(true);
}

void MainWindow::on_pushButtonResumeGoToSettings_clicked()
{
    on_pushButtonSetting_clicked();
    ui->pushButtonResume->setChecked(false);
    ui->pushButtonSetting->setChecked(true);
}
