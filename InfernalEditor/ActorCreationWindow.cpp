#include "stdafx.h"
#include "ActorCreationWindow.h"
#include "InfernalEditor.h"

using namespace tinyxml2;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { EDITOR_LOG("error saving file") }
#endif

void ActorCreationWindow::CreatObject()
{
	QList<QStandardItem *> NameAndType;
	NameAndType << new QStandardItem(ui.NameText->text());
	NameAndType << new QStandardItem(ui.typeBox->currentText());
	
	




	QString Name =ui.NameText->text().remove(QString(""));
	QString resourcePath = "..//XML/" + Name+ ".xml";
	InfernalEditor* properOwnerPointer = dynamic_cast<InfernalEditor*>(Owner);
	

	XMLDocument OutDoc;
	XMLElement * pRoot = OutDoc.NewElement(ui.NameText->text().toStdString().c_str());
	pRoot->SetAttribute("type", ui.typeBox->currentText().toStdString().c_str() );
	pRoot->SetAttribute("resource", resourcePath.toStdString().c_str());
	OutDoc.InsertFirstChild(pRoot);

	
	
														 
	XMLElement *pTransformComponent = OutDoc.NewElement("TransformComponent");
	XMLElement *pPosition = OutDoc.NewElement("Position");
	pPosition->SetAttribute("x", ToStr(ui.px->value()).c_str());
	pPosition->SetAttribute("y", ToStr(ui.py->value()).c_str());
	pPosition->SetAttribute("z", ToStr(ui.pz->value()).c_str());
	XMLElement *pRotation = OutDoc.NewElement("Rotation");
	pRotation->SetAttribute("pitch", ToStr(ui.rx->value()).c_str());
	pRotation->SetAttribute("yaw", ToStr(ui.ry->value()).c_str());
	pRotation->SetAttribute("roll", ToStr(ui.rz->value()).c_str());
	XMLElement *pScale = OutDoc.NewElement("Scale");
	pScale->SetAttribute("x", ToStr(ui.sx->value()).c_str());
	pScale->SetAttribute("y", ToStr(ui.sy->value()).c_str());
	pScale->SetAttribute("z", ToStr(ui.sz->value()).c_str());
	pTransformComponent->InsertEndChild(pPosition);
	pTransformComponent->InsertEndChild(pRotation);
	pTransformComponent->InsertEndChild(pScale);
	pRoot->InsertEndChild(pTransformComponent);

	XMLElement* pRenderComponent = OutDoc.NewElement(GetRenderCompnentType());
	XMLElement* pPaths = OutDoc.NewElement("Paths");
	pPaths->SetAttribute("shaderV", ui.VshaderText->text().toStdString().c_str());
	pPaths->SetAttribute("shaderF", ui.FshaderText->text().toStdString().c_str());
	pPaths->SetAttribute("mesh", ui.assetFileText->text().toStdString().c_str());
	pRenderComponent->InsertEndChild(pPaths);
	pRoot->InsertEndChild(pRenderComponent);

	XMLError eResult = OutDoc.SaveFile(resourcePath.toStdString().c_str());
	XMLCheckResult(eResult);
	
	
	properOwnerPointer->AddObjectToScene(resourcePath.toStdString().c_str(), NameAndType);
	hide();
}

ActorCreationWindow::ActorCreationWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.typeBox->addItem(tr("Mesh"));
	ui.typeBox->addItem(tr("CubeMap"));
	ui.typeBox->addItem(tr("Terrain"));
	
	connect(ui.Creation_Button, &QPushButton::clicked, this, &ActorCreationWindow::CreatObject);
	
	connect(ui._assetFile_button, &QPushButton::clicked, this, &ActorCreationWindow::SetMeshAsset);
	connect(ui._VertexShaderButton, &QPushButton::clicked, this, &ActorCreationWindow::SetVertexShader);
	connect(ui._FragmentShaderButton, &QPushButton::clicked, this, &ActorCreationWindow::SetFragShader);
}

ActorCreationWindow::~ActorCreationWindow()
{
}




void ActorCreationWindow::SetFragShader()
{
	QString fName = QFileDialog::getOpenFileName(this, tr("Fragment Shader"), QString("..//shaders//"),
		tr("Shader (*.glsl);;"));
	QFileInfo fileInfo(fName.toStdString().c_str());
	QString fileName(fileInfo.fileName());

	if (!fileName.isEmpty())
		ui.FshaderText->setText("..//shaders//" + fileName);
}

void ActorCreationWindow::SetVertexShader()
{
	QString fName = QFileDialog::getOpenFileName(this, tr("Vertex Shader"), QString("..//shaders//"),
		tr("Shader (*.glsl);;"));
	QFileInfo fileInfo(fName.toStdString().c_str());
	QString fileName(fileInfo.fileName());
	
	if (!fileName.isEmpty())
		ui.VshaderText->setText("..//shaders//" + fileName);
}

void ActorCreationWindow::SetMeshAsset()
{

	QString fName = QFileDialog::getOpenFileName(this, tr("Mesh Asset"), QString("..//assets//"),
		tr("FBX (*.fbx);;"));
	QFileInfo fileInfo(fName.toStdString().c_str());
	QString fileName(fileInfo.fileName());
	if (!fileName.isEmpty())
		ui.assetFileText->setText("..//assets//"+fileName);
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

const char* ActorCreationWindow::GetRenderCompnentType()
{
	switch (ui.typeBox->currentIndex()) 
	{
	case (0) :
		return "MeshRenderComponent";
	case (1) :
		return "CubeMapRenderComponent";
	case (2) :
		return "TerrainRenderComponent";
	default: return "UNKNOWN OBJECT TYPE";
	}
}
