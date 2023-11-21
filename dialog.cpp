#include "dialog.h"
#include "QDebug"
#include "QDir"
#include "QFileDialog"
#include "QMessageBox"
#include "QTextStream"
#include "analyze.h"
#include "ui_dialog.h"

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
  if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    QMessageBox::information(this, "提示", "文件保存失败");
    return;
  }
  // 写文件
  QString content = ui->source->toPlainText().toUtf8();
  QTextStream out(&file);
  out << content << '\n';
  file.close();
  QMessageBox::information(this, "提示", "文件保存成功");
}

void Dialog::on_analyze_clicked() {
  QString sourcePath = QDir::tempPath() + "/TinySourceCode";
  QString resPath = QDir::tempPath() + "/TinyResult";
  QFile source(sourcePath);
  if (!source.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    QMessageBox::information(this, "提示", "缺失文件访问权限");
    return;
  }
  qDebug() << "分析源程序：" << ui->source->toPlainText() << '\n' << "临时文件: " << sourcePath << '\n' ;

  QTextStream out(&source);
  out << ui->source->toPlainText().toUtf8();
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
  QFile::remove(sourcePath);
  QFile::remove(resPath);
}
