#include "simvdir.h"

#include <protocol.h>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
using namespace std;
using namespace LongQt;

SimvDir::SimvDir(shared_ptr<Protocol> proto, string name, QWidget* parent)
    : Simvar(proto, name, parent) {
  parent->setToolTip(this->getToolTip());
  line = new QLineEdit();
  //  auto size = line->minimumSize();
  //  size.setWidth(2 * size.width());
  //  line->setMinimumSize(size);
  QPushButton* setDir = new QPushButton("Choose");
  QHBoxLayout* layout = new QHBoxLayout(parent);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(line);
  layout->addWidget(setDir);
  connect(line, &QLineEdit::textEdited, this, &SimvDir::update_model);
  connect(setDir, &QPushButton::clicked, [=]() {
    QString value = QFileDialog::getExistingDirectory(
        parent, QString(name.c_str()), proto->parsStr(this->name).c_str());
    if (value != "") {
      this->update_model(value);
      this->update_ui();
    }
  });
  connect(line, &QLineEdit::textChanged, [this]() {
    auto text = line->text();
    QFontMetrics fm(QFont("", 0));
    line->setFixedSize(fm.width(text), fm.height());
  });
}

void SimvDir::update_ui() {
  QString model_line = QString(proto->parsStr(this->name).c_str());
  if (line->text() != model_line) {
    line->setText(model_line);
  }
  emit updated();
}

void SimvDir::update_model(QString value) {
  proto->parsStr(name, value.toStdString());
}

SimvDir::~SimvDir() {}
