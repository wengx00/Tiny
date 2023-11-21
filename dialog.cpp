#include "dialog.h"
#include "QFileDialog"
#include "analyze.h"
#include "QMessageBox"
#include "ui_dialog.h"
#include "QDir"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
}

Dialog::~Dialog() { delete ui; }

void Dialog::on_chooseFile_clicked() {
  // 获取文件名
  QString fileName{
      QFileDialog::getOpenFileName(this, "打开源文件", ".", "源文件(*.tny)")};
  // 构造文件对象
  QFile file{fileName};

  if (fileName.isEmpty())
    return;

  // 读取全部内容
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    ui->source->setText(file.readAll());
    QMessageBox::information(this, "提示", "读取成功");
    file.close();
  }

  // 文件打开失败
  else
    QMessageBox::information(this, "提示", "读取失败");
}

void Dialog::on_saveFile_clicked() {
  QString savePath = QFileDialog::getSaveFileName(this);
  if (savePath.isEmpty())
    return;
  QFile file(savePath);
  if (!file.open(QIODevice::ReadWrite)) {
    QMessageBox::information(this, "提示", "文件保存失败");
    return;
  }
  // 写文件
  QString content = "";
  file.write(content.toUtf8());
  file.close();
  QMessageBox::information(this, "提示", "文件保存成功");
}

void Dialog::on_analyze_clicked() {
  QString sourcePath = QDir::tempPath() + "/TinySourceCode";
  QString resPath = QDir::tempPath() + "/TinyResult";
  QFile source(sourcePath);
  if (!source.open(QIODevice::WriteOnly)) {
    QMessageBox::information(this, "提示", "缺失文件访问权限");
    return;
  }
  source.write(ui->source->toPlainText().toUtf8());
  source.close();

  analyzeCode(sourcePath.toStdString().c_str(), resPath.toStdString().c_str());

  QFile result(resPath);
  if (!result.open(QIODevice::ReadWrite)) {
    QMessageBox::information(this, "提示", "结果解析失败");
    return;
  }
  ui->result->setText(result.readAll());
  result.close();
  QMessageBox::information(this, "提示", "解析成功");
  // 删除临时文件
  source.remove();
  result.remove();
}
