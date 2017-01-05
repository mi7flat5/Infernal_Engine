#include "stdafx.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QFile>
#include "ActorCreationWindow.h"
#include "InfernalEditor.h"
#include <QContextMenuEvent>

InfernalEditor::InfernalEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	

	ui.openGLWidget->setOwner(this);
	
	createMenus();
	
	m_pSceneTreeModel = new QStandardItemModel();
	m_pSceneViewRoot = new QStandardItem("Scene");
	m_pSceneViewRoot->setSelectable(false);
	m_pSceneViewRoot->setEnabled(false);

	m_pSceneTreeModel->setItem(0,m_pSceneViewRoot);
		
	ui.treeView->setModel(m_pSceneTreeModel);
	QStringList labels;
	labels.append("Object Name");
	labels.append("Object Type");
	



	m_pSceneTreeModel->setHorizontalHeaderLabels(labels);
	

	m_pCreationwindow = new ActorCreationWindow();
	m_pCreationwindow->SetOwner(this);
	
}


void InfernalEditor::DeleteActor()
{
	
	QModelIndex index = ui.treeView->selectionModel()->currentIndex();
	QAbstractItemModel *model = ui.treeView->model();
	QVariant ID = model->index(index.row(),2, index.parent()).data();
	
	
	
	if (model->removeRow(index.row(), index.parent()))
		ui.openGLWidget->RemoveFromScene(ID.toUInt());
		
		

		
}
void InfernalEditor::loadfile(const QString &fileName)
{
	tinyxml2::XMLDocument inDoc;
	inDoc.LoadFile(fileName.toStdString().c_str());
	tinyxml2::XMLElement* pRoot = inDoc.FirstChildElement();

	QStandardItem* Name = new QStandardItem(pRoot->Value());
	QStandardItem* Type = new QStandardItem(pRoot->Attribute("type"));
	
	QList<QStandardItem *> NameAndType;
	NameAndType << Name;
	NameAndType << Type;
	
	AddObjectToScene(fileName.toStdString().c_str(), NameAndType);

}
void InfernalEditor::AddObjectToScene(const char* resourcePath, QList<QStandardItem*> inItems) 
{
	unsigned int id = ui.openGLWidget->AddObjectToScene(resourcePath);
	
	std::string intStr = std::to_string(id);
	QStandardItem* IdBlock = new QStandardItem(intStr.c_str());
	IdBlock->setData(QVariant(id));
	inItems.at(0)->setText(inItems.at(0)->text()+"_"+intStr.c_str());
	inItems << IdBlock;
	
	m_pSceneViewRoot->appendRow(inItems);
	
}
void InfernalEditor::createActions()
{
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, &QAction::triggered, this, &InfernalEditor::open);
	
	createObject = new QAction(tr("&Create Object..."), this);
	connect(createObject, &QAction::triggered, this, &InfernalEditor::OpenCreationWindow);
	
	addObject = new QAction(tr("&Add Object"), this);
	connect(addObject, &QAction::triggered, this, &InfernalEditor::open);

	deletObject = new QAction(tr("Delete Object"), this);
	connect(deletObject, &QAction::triggered, this, &InfernalEditor::DeleteActor);
	
	


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

	ObjectMenu = menuBar()->addMenu(tr("&Scene"));
	ObjectMenu->addAction(addObject);
	ObjectMenu->addAction(createObject);
	

	/*fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(printAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);*/ //TODO IMPLEMENT THESE
}


//#ifndef QT_NO_CONTEXTMENU
void InfernalEditor::contextMenuEvent(QContextMenuEvent *event)
{
	contextMenu = new QMenu(this);
	contextMenu->addAction(deletObject);
	/*menu.addAction(cutAct);
	menu.addAction(copyAct);
	menu.addAction(pasteAct);*/
	contextMenu->exec(event->globalPos());
	
	
}
//#endif // QT_NO_CONTEXTMENU


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
void InfernalEditor::newFile()
{
	
}

void InfernalEditor::open()
{
	
	
	
	QString fName = QFileDialog::getOpenFileName(this, tr("Open File"), QString("..//XML//"),
		tr("XML (*.xml);;"));
	QFileInfo fileInfo(fName.toStdString().c_str());
	QString fileName(fileInfo.fileName());
		if (!fileName.isEmpty())
			loadfile("..//XML//"+fileName);
	
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



