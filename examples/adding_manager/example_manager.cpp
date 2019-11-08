/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "example_manager.h"
#include "ui_example_manager.h"

ExampleManager::ExampleManager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ExampleManager),
    mw((cg3::viewer::MainWindow&)*parent)
{
    ui->setupUi(this);
}

ExampleManager::~ExampleManager()
{
    delete ui;
}

void ExampleManager::on_helloWorldPushButton_clicked()
{
	QMessageBox* box = new QMessageBox(this);
	box->setWindowTitle("Hello World!");

	box->setText("Hello World!");
	box->exec();
}
