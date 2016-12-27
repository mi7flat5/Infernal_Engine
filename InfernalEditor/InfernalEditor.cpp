#include "stdafx.h"
#include <QtWidgets>

#include "ActorCreationWindow.h"
#include "InfernalEditor.h"


InfernalEditor::InfernalEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	ui.openGLWidget->setOwner(this);
	ui.textBrowser->append(QString("owner set"));
	createMenus();
	

	m_pSceneTreeModel = new QStandardItemModel();
	m_pSceneTreeModel->insertColumn(1);
	m_pSceneViewRoot = new QStandardItem("Scene");
	
	m_pSceneTreeModel->setItem(0,m_pSceneViewRoot);
	
	QStringList labels;
	labels.append("Object Name");
	labels.append("Object Type");
	
	m_pSceneTreeModel->setHorizontalHeaderLabels(labels);
	ui.treeView->setModel(m_pSceneTreeModel);
	
	m_pCreationwindow = new ActorCreationWindow();
	m_pCreationwindow->hide();
	m_pCreationwindow->SetOwner(this);
	
}
void InfernalEditor::AddObjectToScene(const char* resourcePath, QStandardItem* inItem) 
{
	m_pSceneViewRoot->setChild(m_pSceneViewRoot->rowCount(),inItem);
	ui.textBrowser->append(resourcePath);
	ui.openGLWidget->AddObjectToScene(resourcePath);

}
void InfernalEditor::createActions()
{
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, &QAction::triggered, this, &InfernalEditor::open);
	
	createObject = new QAction(tr("&Create Object..."), this);
	connect(createObject, &QAction::triggered, this, &InfernalEditor::OpenCreationWindow);

}
void InfernalEditor::OpenCreationWindow() 
{	
	m_pCreationwindow->show();

}
void InfernalEditor::createMenus()
{
	createActions();
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAct);

	ObjectMenu = menuBar()->addMenu(tr("&Object"));
	ObjectMenu->addAction(createObject);

	/*fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(printAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);*/ //TODO IMPLEMENT THESE
}
void InfernalEditor::registerDelegate()
{
	
	IEventManager* evman = IEventManager::Get();

	evman->VAddListener(fastdelegate::MakeDelegate(this, &InfernalEditor::Log_event), EvtData_Log_Data::sk_EventType);
	ui.textBrowser->append(QString("delegate registered"));
}
void InfernalEditor::Log_event(IEventDataPtr pEventData)
{
	std::shared_ptr<EvtData_Log_Data> pCastEventData = std::static_pointer_cast<EvtData_Log_Data>(pEventData);
	
	ui.textBrowser->append(QString(pCastEventData->getLog()));
	
}

#ifndef QT_NO_CONTEXTMENU
void InfernalEditor::contextMenuEvent(QContextMenuEvent *event)
{
	//QMenu menu(this);
	//menu.addAction(cutAct);
	//menu.addAction(copyAct);
	//menu.addAction(pasteAct);
	////menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void InfernalEditor::newFile()
{
	
}

void InfernalEditor::open()
{
	
		QString fileName = QFileDialog::getOpenFileName(this);
		if (!fileName.isEmpty())
			loadfile(fileName);
	
}
void InfernalEditor::loadfile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot read file %1:\n%2.")
			.arg(QDir::toNativeSeparators(fileName), file.errorString()));
		return;
	}



}
void InfernalEditor::save()
{
	
}





void InfernalEditor::about()
{
	
	QMessageBox::about(this, tr("About Menu"),
		tr("The <b>Menu</b> example shows how to create "
			"menu-bar menus and context menus."));
}

void InfernalEditor::aboutQt()
{
	
}

void InfernalEditor::mousePressEvent(QMouseEvent *event) 
{

}

void InfernalEditor::mouseReleaseEvent(QMouseEvent *event)
{

}

void InfernalEditor::mouseMoveEvent(QMouseEvent *event)
{

}

