/********************************************************************************
** Form generated from reading UI file 'ActorCreationWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTORCREATIONWINDOW_H
#define UI_ACTORCREATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ActorCreationWindow
{
public:
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_6;
    QPushButton *Creation_Button;
    QGroupBox *renderComponent;
    QGridLayout *gridLayout_2;
    QLineEdit *assetFileText;
    QLineEdit *VshaderText;
    QLineEdit *FshaderText;
    QLabel *_vertexShader_label;
    QPushButton *_VertexShaderButton;
    QLabel *_assetPath_label;
    QLabel *_fragmentshader_label;
    QPushButton *_FragmentShaderButton;
    QPushButton *_assetFile_button;
    QGroupBox *transformComponent;
    QGridLayout *gridLayout_5;
    QDoubleSpinBox *sx;
    QDoubleSpinBox *px;
    QLabel *label_12;
    QDoubleSpinBox *pz;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_15;
    QDoubleSpinBox *ry;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_16;
    QLabel *label_13;
    QDoubleSpinBox *rx;
    QDoubleSpinBox *rz;
    QLabel *label_11;
    QDoubleSpinBox *py;
    QLabel *label_14;
    QLabel *label_2;
    QLabel *label_4;
    QDoubleSpinBox *sy;
    QDoubleSpinBox *sz;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QComboBox *typeBox;
    QLineEdit *NameText;
    QLabel *_name_label;
    QLabel *_type_Label;
    QGroupBox *ComponentsGroupBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QCheckBox *RenderComponent_checkbox;
    QCheckBox *transformComponentCheckbox;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox;

    void setupUi(QWidget *ActorCreationWindow)
    {
        if (ActorCreationWindow->objectName().isEmpty())
            ActorCreationWindow->setObjectName(QStringLiteral("ActorCreationWindow"));
        ActorCreationWindow->resize(515, 526);
        gridLayout_7 = new QGridLayout(ActorCreationWindow);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        Creation_Button = new QPushButton(ActorCreationWindow);
        Creation_Button->setObjectName(QStringLiteral("Creation_Button"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(156, 53, 240, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(213, 161, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(184, 107, 247, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(78, 26, 120, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(104, 35, 160, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(205, 154, 247, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        Creation_Button->setPalette(palette);

        gridLayout_6->addWidget(Creation_Button, 2, 0, 1, 3);

        renderComponent = new QGroupBox(ActorCreationWindow);
        renderComponent->setObjectName(QStringLiteral("renderComponent"));
        gridLayout_2 = new QGridLayout(renderComponent);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        assetFileText = new QLineEdit(renderComponent);
        assetFileText->setObjectName(QStringLiteral("assetFileText"));
        assetFileText->setEnabled(true);
        assetFileText->setReadOnly(true);

        gridLayout_2->addWidget(assetFileText, 1, 0, 1, 1);

        VshaderText = new QLineEdit(renderComponent);
        VshaderText->setObjectName(QStringLiteral("VshaderText"));
        VshaderText->setReadOnly(true);

        gridLayout_2->addWidget(VshaderText, 1, 1, 1, 1);

        FshaderText = new QLineEdit(renderComponent);
        FshaderText->setObjectName(QStringLiteral("FshaderText"));
        FshaderText->setReadOnly(true);

        gridLayout_2->addWidget(FshaderText, 6, 0, 1, 1);

        _vertexShader_label = new QLabel(renderComponent);
        _vertexShader_label->setObjectName(QStringLiteral("_vertexShader_label"));

        gridLayout_2->addWidget(_vertexShader_label, 0, 1, 1, 1);

        _VertexShaderButton = new QPushButton(renderComponent);
        _VertexShaderButton->setObjectName(QStringLiteral("_VertexShaderButton"));

        gridLayout_2->addWidget(_VertexShaderButton, 2, 1, 1, 1);

        _assetPath_label = new QLabel(renderComponent);
        _assetPath_label->setObjectName(QStringLiteral("_assetPath_label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(_assetPath_label->sizePolicy().hasHeightForWidth());
        _assetPath_label->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(_assetPath_label, 0, 0, 1, 1);

        _fragmentshader_label = new QLabel(renderComponent);
        _fragmentshader_label->setObjectName(QStringLiteral("_fragmentshader_label"));
        sizePolicy.setHeightForWidth(_fragmentshader_label->sizePolicy().hasHeightForWidth());
        _fragmentshader_label->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(_fragmentshader_label, 3, 0, 1, 1);

        _FragmentShaderButton = new QPushButton(renderComponent);
        _FragmentShaderButton->setObjectName(QStringLiteral("_FragmentShaderButton"));

        gridLayout_2->addWidget(_FragmentShaderButton, 8, 0, 1, 1);

        _assetFile_button = new QPushButton(renderComponent);
        _assetFile_button->setObjectName(QStringLiteral("_assetFile_button"));

        gridLayout_2->addWidget(_assetFile_button, 2, 0, 1, 1);


        gridLayout_6->addWidget(renderComponent, 1, 1, 1, 1);

        transformComponent = new QGroupBox(ActorCreationWindow);
        transformComponent->setObjectName(QStringLiteral("transformComponent"));
        gridLayout_5 = new QGridLayout(transformComponent);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        sx = new QDoubleSpinBox(transformComponent);
        sx->setObjectName(QStringLiteral("sx"));
        sx->setMinimum(0.01);
        sx->setSingleStep(0.1);
        sx->setValue(1);

        gridLayout_5->addWidget(sx, 10, 0, 1, 1);

        px = new QDoubleSpinBox(transformComponent);
        px->setObjectName(QStringLiteral("px"));
        px->setMinimum(-2048);
        px->setMaximum(2048);

        gridLayout_5->addWidget(px, 2, 0, 1, 1);

        label_12 = new QLabel(transformComponent);
        label_12->setObjectName(QStringLiteral("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_12, 1, 2, 1, 1);

        pz = new QDoubleSpinBox(transformComponent);
        pz->setObjectName(QStringLiteral("pz"));
        pz->setMinimum(-2048);
        pz->setMaximum(2048);

        gridLayout_5->addWidget(pz, 2, 2, 1, 1);

        label_9 = new QLabel(transformComponent);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_9, 0, 0, 1, 1);

        label_10 = new QLabel(transformComponent);
        label_10->setObjectName(QStringLiteral("label_10"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(label_10, 1, 0, 1, 1);

        label_15 = new QLabel(transformComponent);
        label_15->setObjectName(QStringLiteral("label_15"));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_15, 4, 1, 1, 1);

        ry = new QDoubleSpinBox(transformComponent);
        ry->setObjectName(QStringLiteral("ry"));
        ry->setMinimum(-180);
        ry->setMaximum(180);

        gridLayout_5->addWidget(ry, 5, 1, 1, 1);

        label = new QLabel(transformComponent);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label, 8, 0, 1, 1);

        label_3 = new QLabel(transformComponent);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_3, 9, 1, 1, 1);

        label_16 = new QLabel(transformComponent);
        label_16->setObjectName(QStringLiteral("label_16"));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_16, 4, 2, 1, 1);

        label_13 = new QLabel(transformComponent);
        label_13->setObjectName(QStringLiteral("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_13, 3, 0, 1, 1);

        rx = new QDoubleSpinBox(transformComponent);
        rx->setObjectName(QStringLiteral("rx"));
        rx->setMinimum(-180);
        rx->setMaximum(180);

        gridLayout_5->addWidget(rx, 5, 0, 1, 1);

        rz = new QDoubleSpinBox(transformComponent);
        rz->setObjectName(QStringLiteral("rz"));
        rz->setMinimum(-180);
        rz->setMaximum(180);

        gridLayout_5->addWidget(rz, 5, 2, 1, 1);

        label_11 = new QLabel(transformComponent);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_11, 1, 1, 1, 1);

        py = new QDoubleSpinBox(transformComponent);
        py->setObjectName(QStringLiteral("py"));
        py->setMinimum(-2048);
        py->setMaximum(2048);

        gridLayout_5->addWidget(py, 2, 1, 1, 1);

        label_14 = new QLabel(transformComponent);
        label_14->setObjectName(QStringLiteral("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_14, 4, 0, 1, 1);

        label_2 = new QLabel(transformComponent);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_2, 9, 0, 1, 1);

        label_4 = new QLabel(transformComponent);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_4, 9, 2, 1, 1);

        sy = new QDoubleSpinBox(transformComponent);
        sy->setObjectName(QStringLiteral("sy"));
        sy->setMinimum(0.01);
        sy->setSingleStep(0.01);
        sy->setValue(1);

        gridLayout_5->addWidget(sy, 10, 1, 1, 1);

        sz = new QDoubleSpinBox(transformComponent);
        sz->setObjectName(QStringLiteral("sz"));
        sz->setMinimum(0.01);
        sz->setSingleStep(0.1);
        sz->setValue(1);

        gridLayout_5->addWidget(sz, 10, 2, 1, 1);


        gridLayout_6->addWidget(transformComponent, 1, 2, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        typeBox = new QComboBox(ActorCreationWindow);
        typeBox->setObjectName(QStringLiteral("typeBox"));

        gridLayout_3->addWidget(typeBox, 2, 1, 1, 1);

        NameText = new QLineEdit(ActorCreationWindow);
        NameText->setObjectName(QStringLiteral("NameText"));

        gridLayout_3->addWidget(NameText, 2, 0, 1, 1);

        _name_label = new QLabel(ActorCreationWindow);
        _name_label->setObjectName(QStringLiteral("_name_label"));
        sizePolicy.setHeightForWidth(_name_label->sizePolicy().hasHeightForWidth());
        _name_label->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(_name_label, 1, 0, 1, 1);

        _type_Label = new QLabel(ActorCreationWindow);
        _type_Label->setObjectName(QStringLiteral("_type_Label"));

        gridLayout_3->addWidget(_type_Label, 1, 1, 1, 1);

        ComponentsGroupBox = new QGroupBox(ActorCreationWindow);
        ComponentsGroupBox->setObjectName(QStringLiteral("ComponentsGroupBox"));
        layoutWidget = new QWidget(ComponentsGroupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 126, 65));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        RenderComponent_checkbox = new QCheckBox(layoutWidget);
        RenderComponent_checkbox->setObjectName(QStringLiteral("RenderComponent_checkbox"));

        gridLayout->addWidget(RenderComponent_checkbox, 0, 0, 1, 1);

        transformComponentCheckbox = new QCheckBox(layoutWidget);
        transformComponentCheckbox->setObjectName(QStringLiteral("transformComponentCheckbox"));

        gridLayout->addWidget(transformComponentCheckbox, 1, 0, 1, 1);

        checkBox_3 = new QCheckBox(layoutWidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        gridLayout->addWidget(checkBox_3, 2, 0, 1, 1);


        gridLayout_3->addWidget(ComponentsGroupBox, 4, 0, 1, 2);

        checkBox = new QCheckBox(ActorCreationWindow);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout_3->addWidget(checkBox, 3, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 0, 0, 1, 3);


        gridLayout_7->addLayout(gridLayout_6, 0, 0, 1, 1);


        retranslateUi(ActorCreationWindow);

        QMetaObject::connectSlotsByName(ActorCreationWindow);
    } // setupUi

    void retranslateUi(QWidget *ActorCreationWindow)
    {
        ActorCreationWindow->setWindowTitle(QApplication::translate("ActorCreationWindow", "ActorCreationWindow", 0));
        Creation_Button->setText(QApplication::translate("ActorCreationWindow", "Create Object", 0));
        renderComponent->setTitle(QApplication::translate("ActorCreationWindow", "Render Component", 0));
        _vertexShader_label->setText(QApplication::translate("ActorCreationWindow", "Vertex Shader", 0));
        _VertexShaderButton->setText(QApplication::translate("ActorCreationWindow", "Choose Vertex Shader", 0));
        _assetPath_label->setText(QApplication::translate("ActorCreationWindow", "Asset File", 0));
        _fragmentshader_label->setText(QApplication::translate("ActorCreationWindow", "Fragment Shader", 0));
        _FragmentShaderButton->setText(QApplication::translate("ActorCreationWindow", "Choose Fragment Shader", 0));
        _assetFile_button->setText(QApplication::translate("ActorCreationWindow", "Choose Asset File", 0));
        transformComponent->setTitle(QApplication::translate("ActorCreationWindow", "Transform Component", 0));
        label_12->setText(QApplication::translate("ActorCreationWindow", "Z", 0));
        label_9->setText(QApplication::translate("ActorCreationWindow", "Position", 0));
        label_10->setText(QApplication::translate("ActorCreationWindow", "X", 0));
        label_15->setText(QApplication::translate("ActorCreationWindow", "Y", 0));
        label->setText(QApplication::translate("ActorCreationWindow", "Scale", 0));
        label_3->setText(QApplication::translate("ActorCreationWindow", "Y", 0));
        label_16->setText(QApplication::translate("ActorCreationWindow", "Z", 0));
        label_13->setText(QApplication::translate("ActorCreationWindow", "Rotation", 0));
        label_11->setText(QApplication::translate("ActorCreationWindow", "Y", 0));
        label_14->setText(QApplication::translate("ActorCreationWindow", "X", 0));
        label_2->setText(QApplication::translate("ActorCreationWindow", "X", 0));
        label_4->setText(QApplication::translate("ActorCreationWindow", "Z", 0));
        _name_label->setText(QApplication::translate("ActorCreationWindow", "Object Name", 0));
        _type_Label->setText(QApplication::translate("ActorCreationWindow", "Object Type", 0));
        ComponentsGroupBox->setTitle(QApplication::translate("ActorCreationWindow", "Components", 0));
        RenderComponent_checkbox->setText(QApplication::translate("ActorCreationWindow", "Render Component", 0));
        transformComponentCheckbox->setText(QApplication::translate("ActorCreationWindow", "Trasform Component", 0));
        checkBox_3->setText(QApplication::translate("ActorCreationWindow", "Other Components", 0));
        checkBox->setText(QApplication::translate("ActorCreationWindow", "Static", 0));
    } // retranslateUi

};

namespace Ui {
    class ActorCreationWindow: public Ui_ActorCreationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTORCREATIONWINDOW_H
