#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_InfernalEditor.h"
#include"EventSystem\Event.h"
class ActorCreationWindow;

class InfernalEditor : public QMainWindow
{
	Q_OBJECT
		QStandardItemModel *m_pSceneTreeModel;
		QStandardItem* m_pSceneViewRoot;
public:
    InfernalEditor(QWidget *parent = Q_NULLPTR);

	void AddObjectToScene(const char* resourcePath, QStandardItem* inItem);
	void registerDelegate();
protected:
#ifndef QT_NO_CONTEXTMENU
	void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
#endif // QT_NO_CONTEXTMENU
public slots:


private slots:

	

void Log_event(IEventDataPtr pEventData);

void newFile();
	void open();
	void loadfile(const QString & fileName);
	void save();


	void about();
	void aboutQt();
protected:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::InfernalEditorClass ui;
	
	ActorCreationWindow* m_pCreationwindow;

	void createActions();
	void OpenCreationWindow();
	void createMenus();

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *ObjectMenu;
	QMenu *helpMenu;

	QActionGroup *alignmentGroup;
	QAction *createObject;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *printAct;
	QAction *exitAct;
	QAction *undoAct;
	QAction *redoAct;
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;
	QAction *boldAct;
	QAction *italicAct;
	QAction *leftAlignAct;
	QAction *rightAlignAct;
	QAction *justifyAct;
	QAction *centerAct;
	QAction *setLineSpacingAct;
	QAction *setParagraphSpacingAct;
	QAction *aboutAct;
	QAction *aboutQtAct;
	
};





	