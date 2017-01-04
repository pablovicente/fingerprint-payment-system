#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtSql>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>

#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>

#include "communication.h"
#include "myuser.h"
#include "mycard.h"
#include "mypurchases.h"
#include "utils.h"
#include "Fingerprint/myfingerprint.h"
#include "Fingerprint/fingerprintloader.h"
#include "Fingerprint/processfingerprint.h"
#include "stylesheetprovider.h"
#include "Constants.h"

#include <boost/thread.hpp>

#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QInputDialog>
#include <QDebug>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QMovie>


#include <QAction>
#include <QSettings>
#include <QMessageBox>
#include <QInputDialog>
#include <QButtonGroup>

/*! \mainpage Aplicación de escritorio
 *
 * Este documento recoge la documentación asocidada a la
 * aplicacion de escritorio desarrollada.
 *
 */

namespace Ui {
class MainWindow;
}

/*!
 * \brief The MainWindow class Clase principal que controla la interfaz
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();





public slots:
    bool loadSettings();

private slots:

    void saveSettings();

    void finishedMinutiaeExtration(void );

    void dateChangedDateEditInitial(QDate );

    void on_pushButtonIniciarSesion_clicked();
    void on_pushButtonRegistrarse_clicked();

    void on_pushButtonShowPayments_clicked();
    void changePassword(void);


    void on_pushButtoLogo_clicked();
    void on_pushButtonResume_clicked();
    void on_pushButtonActivity_clicked();
    void on_pushButtonWallet_clicked();
    void on_pushButtonSetting_clicked();    

    void on_pushButtonSecondStepForm_clicked();
    void on_pushButtonCreateAccoutForm_clicked();

    void editPersonalInfo(int rowCol);

    void editPhone(int rowCol);
    void deletePhone(int rowCol);    
    void clearLocalInfo(void);
    void btnOutClickSlot(int btn);

    void on_pushButtonCloseSession_clicked();    

    void on_pushButtonAddPhone_clicked();


    void currentRowChanged(QModelIndex ,QModelIndex );

    void on_pushButtonChangePassword_clicked();


    void on_pushButtonBlockAccount_clicked();

    void on_pushButtonDeleteAccount_clicked();

    void on_pushButtonCloseSession_2_clicked();

    void on_pushButtonScanFingerprint_clicked();

    void on_pushButtonAddCreditCard_clicked();

    void on_pushButtonDeleteCard_clicked();

    void on_pushButtonFingerprint_clicked();
    void on_pushButtonLeftHand_clicked();
    void on_pushButtonRightHand_clicked();
    void on_pushButtonFinger3_clicked();
    void on_pushButtonFinger2_clicked();
    void on_pushButtonFinger4_clicked();
    void on_pushButtonFinger1_clicked();
    void on_pushButtonFinger5_clicked();

    void on_pushButtonEditAddress_clicked();

    void on_pushButtonWalletSelectCard_clicked();

    void on_pushButtonGoBackToForm_clicked();

    void on_pushButtonDetail_clicked();

    void on_pushButtonSimple_clicked();

    void on_pushButtonBackToLanding_clicked();

    void on_pushButtonMorePurchasesResults_clicked();

    void on_pushButtonForgottenPassword_clicked();

    void on_pushButtonLandingIcon_clicked();

    void on_pushButtonResumeGoToCards_clicked();

    void on_pushButtonResumeGoToPurchases_clicked();

    void on_pushButtonResumeGoToSettings_clicked();

private:
    Ui::MainWindow *ui;
    bool registerSelected, secondStepForm, createAccountForm, userCreation, loggedIn, passwordChanged, forgottenPassword, firstTimeShown;
    int purchasesInfoMode, numFingerprintScanned;
    Communication com;
    Utils utils;
    FingerprintLoader scanner;
    ProcessFingerprint procFingerprint;    
    QButtonGroup *bgFingerprint;
    QButtonGroup *bgMenu;
    QStringListModel *personalData;
    QStandardItemModel *modelCardResume;
    QStandardItemModel *modelAdquisitionsResume;
    QStandardItemModel *modelTotalAdquisitions;
    QStandardItemModel *modelTotalCards;    
    Hand selectedHand;
    Finger selectedFinger;
    QString key, idDevice, keyDevice, settingsFile;

    QMovie *movieForm;
    QMovie *movieMain;

    MyUser user;
    QHash<QString,QString> cardTypes;
    QHash<int,int> pagination;

    bool eventFilter(QObject* obj, QEvent* e);

    void closeSession(void);
    void startLoadingForm(void);
    void stopLoadingForm(int nextIndex);
    void startLoadingPage(void);
    void stopLoadingPage(int nextIndex);
    void showResumePage(void);
    void showPayments(int , bool morePages);
    void resetFingerprintWidget(void);
};


#endif // MAINWINDOW_H
