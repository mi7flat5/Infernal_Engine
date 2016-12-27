#include "stdafx.h"
#include "ActorCreationWindow.h"
#include "InfernalEditor.h"
void ActorCreationWindow::CreatObject()
{
	InfernalEditor* properOwnerPointer = dynamic_cast<InfernalEditor*>(Owner);
	QStandardItem* item= new QStandardItem(ui.NameText->text());
	QString resourcePath = ui.ResourceFileText->text().replace(QString("/"), QString("//"));
	properOwnerPointer->AddObjectToScene(resourcePath.toStdString().c_str(),item);
	hide();
}

ActorCreationWindow::ActorCreationWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	
	connect(ui.Creation_Button, &QPushButton::clicked, this, &ActorCreationWindow::CreatObject);
	connect(ui.LoadResourceButton, &QPushButton::clicked, this, &ActorCreationWindow::open);
}

ActorCreationWindow::~ActorCreationWindow()
{
}
void ActorCreationWindow::open()
{

	QString fileName = QFileDialog::getOpenFileName(this);
	if (!fileName.isEmpty())
		ui.ResourceFileText->setText(fileName);

}
void ActorCreationWindow::loadfile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot read file %1:\n%2.")
			.arg(QDir::toNativeSeparators(fileName), file.errorString()));
		return;
	}

}