/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_all;
    QAction *actionNew_project;
    QAction *actionExit;
    QAction *actionManual;
    QAction *actionOtsu;
    QAction *actionEntropy;
    QAction *actionCopyright;
    QAction *actionDiscription;
    QAction *actionGx;
    QAction *actionGy;
    QAction *actionGx_2;
    QAction *actionGy_2;
    QAction *actionGx_3;
    QAction *actionGy_3;
    QAction *actionMedian;
    QAction *action3x3;
    QAction *action5x5;
    QAction *action3x3_input;
    QAction *actionCircle;
    QAction *action3x3_input_2;
    QAction *actionCircle_input;
    QAction *action3x3_input_3;
    QAction *actionCircle_2;
    QAction *action3x3_input_4;
    QAction *actionCircle_input_2;
    QAction *actionChessboard;
    QAction *actionCity_block;
    QAction *actionChessboard_2;
    QAction *actionCity_block_2;
    QAction *actionRestoration;
    QAction *action3x3_2;
    QAction *actionSquare;
    QAction *action3x3_3;
    QAction *actionSquare_2;
    QAction *action3x3_4;
    QAction *actionSquare_3;
    QAction *action3x3_5;
    QAction *actionSquare_4;
    QAction *actionStandard;
    QAction *actionExternal;
    QAction *actionInternal;
    QAction *actionStandard_2;
    QAction *actionExternal_2;
    QAction *actionInternal_2;
    QAction *actionConditional_dilation;
    QAction *actionOBR;
    QAction *actionCBR;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QGraphicsView *graphicsView;
    QGraphicsView *Hist;
    QSlider *slider;
    QGroupBox *groupBox_2;
    QGraphicsView *graphicsView2;
    QGraphicsView *Hist1;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QMenu *menuFile_F;
    QMenu *menuOperation;
    QMenu *menuThreshold;
    QMenu *menuEdge_detection;
    QMenu *menuRoberts;
    QMenu *menuPrewitt;
    QMenu *menuSobel;
    QMenu *menuNoise_reduction;
    QMenu *menuGaussian;
    QMenu *menuDilation;
    QMenu *menuErosion;
    QMenu *menuOpening;
    QMenu *menuClosing;
    QMenu *menuDistance_transform;
    QMenu *menuSkeleton;
    QMenu *menuGrayscale_dilation;
    QMenu *menuGrayscale_erosion;
    QMenu *menuGrayscale_opening;
    QMenu *menuGrayscale_closing;
    QMenu *menuMorphological_edge;
    QMenu *menuGradient;
    QMenu *menuGrayscale_reconstruction;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(857, 602);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_all = new QAction(MainWindow);
        actionSave_all->setObjectName(QStringLiteral("actionSave_all"));
        actionNew_project = new QAction(MainWindow);
        actionNew_project->setObjectName(QStringLiteral("actionNew_project"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionManual = new QAction(MainWindow);
        actionManual->setObjectName(QStringLiteral("actionManual"));
        actionManual->setCheckable(true);
        actionOtsu = new QAction(MainWindow);
        actionOtsu->setObjectName(QStringLiteral("actionOtsu"));
        actionOtsu->setCheckable(true);
        actionEntropy = new QAction(MainWindow);
        actionEntropy->setObjectName(QStringLiteral("actionEntropy"));
        actionEntropy->setCheckable(true);
        actionCopyright = new QAction(MainWindow);
        actionCopyright->setObjectName(QStringLiteral("actionCopyright"));
        actionDiscription = new QAction(MainWindow);
        actionDiscription->setObjectName(QStringLiteral("actionDiscription"));
        actionGx = new QAction(MainWindow);
        actionGx->setObjectName(QStringLiteral("actionGx"));
        actionGy = new QAction(MainWindow);
        actionGy->setObjectName(QStringLiteral("actionGy"));
        actionGx_2 = new QAction(MainWindow);
        actionGx_2->setObjectName(QStringLiteral("actionGx_2"));
        actionGy_2 = new QAction(MainWindow);
        actionGy_2->setObjectName(QStringLiteral("actionGy_2"));
        actionGx_3 = new QAction(MainWindow);
        actionGx_3->setObjectName(QStringLiteral("actionGx_3"));
        actionGy_3 = new QAction(MainWindow);
        actionGy_3->setObjectName(QStringLiteral("actionGy_3"));
        actionMedian = new QAction(MainWindow);
        actionMedian->setObjectName(QStringLiteral("actionMedian"));
        action3x3 = new QAction(MainWindow);
        action3x3->setObjectName(QStringLiteral("action3x3"));
        action5x5 = new QAction(MainWindow);
        action5x5->setObjectName(QStringLiteral("action5x5"));
        action3x3_input = new QAction(MainWindow);
        action3x3_input->setObjectName(QStringLiteral("action3x3_input"));
        actionCircle = new QAction(MainWindow);
        actionCircle->setObjectName(QStringLiteral("actionCircle"));
        action3x3_input_2 = new QAction(MainWindow);
        action3x3_input_2->setObjectName(QStringLiteral("action3x3_input_2"));
        actionCircle_input = new QAction(MainWindow);
        actionCircle_input->setObjectName(QStringLiteral("actionCircle_input"));
        action3x3_input_3 = new QAction(MainWindow);
        action3x3_input_3->setObjectName(QStringLiteral("action3x3_input_3"));
        actionCircle_2 = new QAction(MainWindow);
        actionCircle_2->setObjectName(QStringLiteral("actionCircle_2"));
        action3x3_input_4 = new QAction(MainWindow);
        action3x3_input_4->setObjectName(QStringLiteral("action3x3_input_4"));
        actionCircle_input_2 = new QAction(MainWindow);
        actionCircle_input_2->setObjectName(QStringLiteral("actionCircle_input_2"));
        actionChessboard = new QAction(MainWindow);
        actionChessboard->setObjectName(QStringLiteral("actionChessboard"));
        actionCity_block = new QAction(MainWindow);
        actionCity_block->setObjectName(QStringLiteral("actionCity_block"));
        actionChessboard_2 = new QAction(MainWindow);
        actionChessboard_2->setObjectName(QStringLiteral("actionChessboard_2"));
        actionCity_block_2 = new QAction(MainWindow);
        actionCity_block_2->setObjectName(QStringLiteral("actionCity_block_2"));
        actionRestoration = new QAction(MainWindow);
        actionRestoration->setObjectName(QStringLiteral("actionRestoration"));
        action3x3_2 = new QAction(MainWindow);
        action3x3_2->setObjectName(QStringLiteral("action3x3_2"));
        actionSquare = new QAction(MainWindow);
        actionSquare->setObjectName(QStringLiteral("actionSquare"));
        action3x3_3 = new QAction(MainWindow);
        action3x3_3->setObjectName(QStringLiteral("action3x3_3"));
        actionSquare_2 = new QAction(MainWindow);
        actionSquare_2->setObjectName(QStringLiteral("actionSquare_2"));
        action3x3_4 = new QAction(MainWindow);
        action3x3_4->setObjectName(QStringLiteral("action3x3_4"));
        actionSquare_3 = new QAction(MainWindow);
        actionSquare_3->setObjectName(QStringLiteral("actionSquare_3"));
        action3x3_5 = new QAction(MainWindow);
        action3x3_5->setObjectName(QStringLiteral("action3x3_5"));
        actionSquare_4 = new QAction(MainWindow);
        actionSquare_4->setObjectName(QStringLiteral("actionSquare_4"));
        actionStandard = new QAction(MainWindow);
        actionStandard->setObjectName(QStringLiteral("actionStandard"));
        actionExternal = new QAction(MainWindow);
        actionExternal->setObjectName(QStringLiteral("actionExternal"));
        actionInternal = new QAction(MainWindow);
        actionInternal->setObjectName(QStringLiteral("actionInternal"));
        actionStandard_2 = new QAction(MainWindow);
        actionStandard_2->setObjectName(QStringLiteral("actionStandard_2"));
        actionExternal_2 = new QAction(MainWindow);
        actionExternal_2->setObjectName(QStringLiteral("actionExternal_2"));
        actionInternal_2 = new QAction(MainWindow);
        actionInternal_2->setObjectName(QStringLiteral("actionInternal_2"));
        actionConditional_dilation = new QAction(MainWindow);
        actionConditional_dilation->setObjectName(QStringLiteral("actionConditional_dilation"));
        actionOBR = new QAction(MainWindow);
        actionOBR->setObjectName(QStringLiteral("actionOBR"));
        actionCBR = new QAction(MainWindow);
        actionCBR->setObjectName(QStringLiteral("actionCBR"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(90, 10, 341, 531));
        graphicsView = new QGraphicsView(groupBox);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(20, 20, 300, 300));
        Hist = new QGraphicsView(groupBox);
        Hist->setObjectName(QStringLiteral("Hist"));
        Hist->setGeometry(QRect(20, 340, 300, 161));
        slider = new QSlider(groupBox);
        slider->setObjectName(QStringLiteral("slider"));
        slider->setEnabled(true);
        slider->setGeometry(QRect(20, 505, 300, 22));
        slider->setMaximum(299);
        slider->setOrientation(Qt::Horizontal);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(470, 10, 341, 531));
        graphicsView2 = new QGraphicsView(groupBox_2);
        graphicsView2->setObjectName(QStringLiteral("graphicsView2"));
        graphicsView2->setGeometry(QRect(20, 20, 300, 300));
        Hist1 = new QGraphicsView(groupBox_2);
        Hist1->setObjectName(QStringLiteral("Hist1"));
        Hist1->setGeometry(QRect(20, 340, 300, 161));
        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(80, 504, 75, 23));
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(180, 504, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 857, 23));
        menuFile_F = new QMenu(menuBar);
        menuFile_F->setObjectName(QStringLiteral("menuFile_F"));
        menuOperation = new QMenu(menuBar);
        menuOperation->setObjectName(QStringLiteral("menuOperation"));
        menuThreshold = new QMenu(menuOperation);
        menuThreshold->setObjectName(QStringLiteral("menuThreshold"));
        menuEdge_detection = new QMenu(menuOperation);
        menuEdge_detection->setObjectName(QStringLiteral("menuEdge_detection"));
        menuRoberts = new QMenu(menuEdge_detection);
        menuRoberts->setObjectName(QStringLiteral("menuRoberts"));
        menuPrewitt = new QMenu(menuEdge_detection);
        menuPrewitt->setObjectName(QStringLiteral("menuPrewitt"));
        menuSobel = new QMenu(menuEdge_detection);
        menuSobel->setObjectName(QStringLiteral("menuSobel"));
        menuNoise_reduction = new QMenu(menuOperation);
        menuNoise_reduction->setObjectName(QStringLiteral("menuNoise_reduction"));
        menuGaussian = new QMenu(menuNoise_reduction);
        menuGaussian->setObjectName(QStringLiteral("menuGaussian"));
        menuDilation = new QMenu(menuOperation);
        menuDilation->setObjectName(QStringLiteral("menuDilation"));
        menuErosion = new QMenu(menuOperation);
        menuErosion->setObjectName(QStringLiteral("menuErosion"));
        menuOpening = new QMenu(menuOperation);
        menuOpening->setObjectName(QStringLiteral("menuOpening"));
        menuClosing = new QMenu(menuOperation);
        menuClosing->setObjectName(QStringLiteral("menuClosing"));
        menuDistance_transform = new QMenu(menuOperation);
        menuDistance_transform->setObjectName(QStringLiteral("menuDistance_transform"));
        menuSkeleton = new QMenu(menuOperation);
        menuSkeleton->setObjectName(QStringLiteral("menuSkeleton"));
        menuGrayscale_dilation = new QMenu(menuOperation);
        menuGrayscale_dilation->setObjectName(QStringLiteral("menuGrayscale_dilation"));
        menuGrayscale_erosion = new QMenu(menuOperation);
        menuGrayscale_erosion->setObjectName(QStringLiteral("menuGrayscale_erosion"));
        menuGrayscale_opening = new QMenu(menuOperation);
        menuGrayscale_opening->setObjectName(QStringLiteral("menuGrayscale_opening"));
        menuGrayscale_closing = new QMenu(menuOperation);
        menuGrayscale_closing->setObjectName(QStringLiteral("menuGrayscale_closing"));
        menuMorphological_edge = new QMenu(menuOperation);
        menuMorphological_edge->setObjectName(QStringLiteral("menuMorphological_edge"));
        menuGradient = new QMenu(menuOperation);
        menuGradient->setObjectName(QStringLiteral("menuGradient"));
        menuGrayscale_reconstruction = new QMenu(menuOperation);
        menuGrayscale_reconstruction->setObjectName(QStringLiteral("menuGrayscale_reconstruction"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile_F->menuAction());
        menuBar->addAction(menuOperation->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile_F->addAction(actionOpen);
        menuFile_F->addAction(actionSave);
        menuFile_F->addAction(actionSave_all);
        menuFile_F->addAction(actionExit);
        menuFile_F->addSeparator();
        menuFile_F->addAction(actionNew_project);
        menuOperation->addAction(menuThreshold->menuAction());
        menuOperation->addSeparator();
        menuOperation->addAction(menuEdge_detection->menuAction());
        menuOperation->addAction(menuNoise_reduction->menuAction());
        menuOperation->addSeparator();
        menuOperation->addAction(menuDilation->menuAction());
        menuOperation->addAction(menuErosion->menuAction());
        menuOperation->addAction(menuOpening->menuAction());
        menuOperation->addAction(menuClosing->menuAction());
        menuOperation->addSeparator();
        menuOperation->addAction(menuDistance_transform->menuAction());
        menuOperation->addAction(menuSkeleton->menuAction());
        menuOperation->addSeparator();
        menuOperation->addAction(menuGrayscale_dilation->menuAction());
        menuOperation->addAction(menuGrayscale_erosion->menuAction());
        menuOperation->addAction(menuGrayscale_opening->menuAction());
        menuOperation->addAction(menuGrayscale_closing->menuAction());
        menuOperation->addSeparator();
        menuOperation->addAction(menuMorphological_edge->menuAction());
        menuOperation->addAction(menuGradient->menuAction());
        menuOperation->addAction(actionConditional_dilation);
        menuOperation->addAction(menuGrayscale_reconstruction->menuAction());
        menuThreshold->addAction(actionManual);
        menuThreshold->addAction(actionOtsu);
        menuThreshold->addAction(actionEntropy);
        menuEdge_detection->addAction(menuRoberts->menuAction());
        menuEdge_detection->addAction(menuPrewitt->menuAction());
        menuEdge_detection->addAction(menuSobel->menuAction());
        menuRoberts->addAction(actionGx);
        menuRoberts->addAction(actionGy);
        menuPrewitt->addAction(actionGx_2);
        menuPrewitt->addAction(actionGy_2);
        menuSobel->addAction(actionGx_3);
        menuSobel->addAction(actionGy_3);
        menuNoise_reduction->addAction(menuGaussian->menuAction());
        menuNoise_reduction->addAction(actionMedian);
        menuGaussian->addAction(action3x3);
        menuGaussian->addAction(action5x5);
        menuDilation->addAction(action3x3_input);
        menuDilation->addAction(actionCircle);
        menuErosion->addAction(action3x3_input_2);
        menuErosion->addAction(actionCircle_input);
        menuOpening->addAction(action3x3_input_3);
        menuOpening->addAction(actionCircle_2);
        menuClosing->addAction(action3x3_input_4);
        menuClosing->addAction(actionCircle_input_2);
        menuDistance_transform->addAction(actionChessboard);
        menuDistance_transform->addAction(actionCity_block);
        menuSkeleton->addAction(actionChessboard_2);
        menuSkeleton->addAction(actionCity_block_2);
        menuSkeleton->addSeparator();
        menuSkeleton->addAction(actionRestoration);
        menuGrayscale_dilation->addAction(action3x3_2);
        menuGrayscale_dilation->addAction(actionSquare);
        menuGrayscale_erosion->addAction(action3x3_3);
        menuGrayscale_erosion->addAction(actionSquare_2);
        menuGrayscale_opening->addAction(action3x3_4);
        menuGrayscale_opening->addAction(actionSquare_3);
        menuGrayscale_closing->addAction(action3x3_5);
        menuGrayscale_closing->addAction(actionSquare_4);
        menuMorphological_edge->addAction(actionStandard);
        menuMorphological_edge->addAction(actionExternal);
        menuMorphological_edge->addAction(actionInternal);
        menuGradient->addAction(actionStandard_2);
        menuGradient->addAction(actionExternal_2);
        menuGradient->addAction(actionInternal_2);
        menuGrayscale_reconstruction->addAction(actionOBR);
        menuGrayscale_reconstruction->addAction(actionCBR);
        menuHelp->addAction(actionCopyright);
        menuHelp->addAction(actionDiscription);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionSave_all->setText(QApplication::translate("MainWindow", "Save all", 0));
        actionNew_project->setText(QApplication::translate("MainWindow", "New project", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionManual->setText(QApplication::translate("MainWindow", "manual", 0));
        actionOtsu->setText(QApplication::translate("MainWindow", "otsu", 0));
        actionEntropy->setText(QApplication::translate("MainWindow", "entropy", 0));
        actionCopyright->setText(QApplication::translate("MainWindow", "copyright", 0));
        actionDiscription->setText(QApplication::translate("MainWindow", "discription", 0));
        actionGx->setText(QApplication::translate("MainWindow", "Gx", 0));
        actionGy->setText(QApplication::translate("MainWindow", "Gy", 0));
        actionGx_2->setText(QApplication::translate("MainWindow", "Gx", 0));
        actionGy_2->setText(QApplication::translate("MainWindow", "Gy", 0));
        actionGx_3->setText(QApplication::translate("MainWindow", "Gx", 0));
        actionGy_3->setText(QApplication::translate("MainWindow", "Gy", 0));
        actionMedian->setText(QApplication::translate("MainWindow", "Median", 0));
        action3x3->setText(QApplication::translate("MainWindow", "3x3(delta=1)", 0));
        action5x5->setText(QApplication::translate("MainWindow", "5x5(delta=1)", 0));
        action3x3_input->setText(QApplication::translate("MainWindow", "3x3", 0));
        actionCircle->setText(QApplication::translate("MainWindow", "square", 0));
        action3x3_input_2->setText(QApplication::translate("MainWindow", "3x3", 0));
        actionCircle_input->setText(QApplication::translate("MainWindow", "circle", 0));
        action3x3_input_3->setText(QApplication::translate("MainWindow", "3x3", 0));
        actionCircle_2->setText(QApplication::translate("MainWindow", "square", 0));
        action3x3_input_4->setText(QApplication::translate("MainWindow", "3x3", 0));
        actionCircle_input_2->setText(QApplication::translate("MainWindow", "square", 0));
        actionChessboard->setText(QApplication::translate("MainWindow", "chessboard", 0));
        actionCity_block->setText(QApplication::translate("MainWindow", "city block", 0));
        actionChessboard_2->setText(QApplication::translate("MainWindow", "chessboard", 0));
        actionCity_block_2->setText(QApplication::translate("MainWindow", "city block", 0));
        actionRestoration->setText(QApplication::translate("MainWindow", "restoration", 0));
        action3x3_2->setText(QApplication::translate("MainWindow", "3x3", 0));
        actionSquare->setText(QApplication::translate("MainWindow", "square", 0));
        action3x3_3->setText(QApplication::translate("MainWindow", "3x3", 0));
        actionSquare_2->setText(QApplication::translate("MainWindow", "square", 0));
        action3x3_4->setText(QApplication::translate("MainWindow", "3x3", 0));
        actionSquare_3->setText(QApplication::translate("MainWindow", "square", 0));
        action3x3_5->setText(QApplication::translate("MainWindow", "3x3", 0));
        actionSquare_4->setText(QApplication::translate("MainWindow", "square", 0));
        actionStandard->setText(QApplication::translate("MainWindow", "standard", 0));
        actionExternal->setText(QApplication::translate("MainWindow", "external", 0));
        actionInternal->setText(QApplication::translate("MainWindow", "internal", 0));
        actionStandard_2->setText(QApplication::translate("MainWindow", "standard", 0));
        actionExternal_2->setText(QApplication::translate("MainWindow", "external", 0));
        actionInternal_2->setText(QApplication::translate("MainWindow", "internal", 0));
        actionConditional_dilation->setText(QApplication::translate("MainWindow", "conditional dilation", 0));
        actionOBR->setText(QApplication::translate("MainWindow", "OBR", 0));
        actionCBR->setText(QApplication::translate("MainWindow", "CBR", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Original Image", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Processed Image", 0));
        pushButton->setText(QApplication::translate("MainWindow", "switch", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "step", 0));
        menuFile_F->setTitle(QApplication::translate("MainWindow", "File(&F)", 0));
        menuOperation->setTitle(QApplication::translate("MainWindow", "Operation", 0));
        menuThreshold->setTitle(QApplication::translate("MainWindow", "thresholding", 0));
        menuEdge_detection->setTitle(QApplication::translate("MainWindow", "edge detection", 0));
        menuRoberts->setTitle(QApplication::translate("MainWindow", "Roberts", 0));
        menuPrewitt->setTitle(QApplication::translate("MainWindow", "Prewitt", 0));
        menuSobel->setTitle(QApplication::translate("MainWindow", "Sobel", 0));
        menuNoise_reduction->setTitle(QApplication::translate("MainWindow", "noise reduction", 0));
        menuGaussian->setTitle(QApplication::translate("MainWindow", "Gaussian", 0));
        menuDilation->setTitle(QApplication::translate("MainWindow", "binary dilation", 0));
        menuErosion->setTitle(QApplication::translate("MainWindow", "binary erosion", 0));
        menuOpening->setTitle(QApplication::translate("MainWindow", "binary opening", 0));
        menuClosing->setTitle(QApplication::translate("MainWindow", "binary closing", 0));
        menuDistance_transform->setTitle(QApplication::translate("MainWindow", "distance transform", 0));
        menuSkeleton->setTitle(QApplication::translate("MainWindow", "skeleton", 0));
        menuGrayscale_dilation->setTitle(QApplication::translate("MainWindow", "grayscale dilation", 0));
        menuGrayscale_erosion->setTitle(QApplication::translate("MainWindow", "grayscale erosion", 0));
        menuGrayscale_opening->setTitle(QApplication::translate("MainWindow", "grayscale opening", 0));
        menuGrayscale_closing->setTitle(QApplication::translate("MainWindow", "grayscale closing", 0));
        menuMorphological_edge->setTitle(QApplication::translate("MainWindow", "morphological edge", 0));
        menuGradient->setTitle(QApplication::translate("MainWindow", "gradient", 0));
        menuGrayscale_reconstruction->setTitle(QApplication::translate("MainWindow", "grayscale reconstruction", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
