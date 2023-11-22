//#ifndef DIALOG_H
//#define DIALOG_H
#pragma once

#include <QDialog>
#include "analyze.h"
#include <QTreeWidget>

QT_BEGIN_NAMESPACE

namespace Ui { class Dialog; }

QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_chooseFile_clicked();

    void on_saveFile_clicked();

    void on_analyze_clicked();

private:
    Ui::Dialog *ui;
    void traverseTree(TreeNode*, QTreeWidgetItem *);
};
//#endif // DIALOG_H
