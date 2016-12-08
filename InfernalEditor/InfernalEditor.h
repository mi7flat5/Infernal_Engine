#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_InfernalEditor.h"
#include"EventSystem\Event.h"
class InfernalEditor : public QMainWindow
{
    Q_OBJECT

public:
    InfernalEditor(QWidget *parent = Q_NULLPTR);
	void registerDelegate();
protected:
#ifndef QT_NO_CONTEXTMENU
	void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
#endif // QT_NO_CONTEXTMENU
public slots:


private slots:

	void stdLogOut();

void Log_event(IEventDataPtr pEventData);

void newFile();
	void open();
	void save();
	void print();
	void undo();
	void redo();
	void cut();
	void copy();
	void paste();
	void bold();
	void italic();
	void leftAlign();
	void rightAlign();
	void justify();
	void center();
	void setLineSpacing();
	void setParagraphSpacing();
	void about();
	void aboutQt();

private:
    Ui::InfernalEditorClass ui;
	
	

	void createActions();
	void createMenus();

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *formatMenu;
	QMenu *helpMenu;
	QActionGroup *alignmentGroup;
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





	