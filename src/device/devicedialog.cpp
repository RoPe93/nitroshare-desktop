/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 **/

#include <QPushButton>

#include "devicedialog.h"
#include "ui_devicedialog.h"

DeviceDialog::DeviceDialog(DeviceModel *model)
    : ui(new Ui::DeviceDialog)
{
    ui->setupUi(this);

    ui->deviceView->setModel(model);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    connect(ui->deviceView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &DeviceDialog::toggleOkButton);
}

DeviceDialog::~DeviceDialog()
{
    delete ui;
}

QModelIndex DeviceDialog::selectedDeviceIndex() const
{
    QModelIndexList selection(ui->deviceView->selectionModel()->selectedIndexes());
    return selection.count() ? selection.at(0) : QModelIndex();
}

QModelIndex DeviceDialog::getDevice(DeviceModel *model)
{
    DeviceDialog deviceDialog(model);

    if(deviceDialog.exec() == QDialog::Accepted) {
        return deviceDialog.selectedDeviceIndex();
    } else {
        return QModelIndex();
    }
}

void DeviceDialog::toggleOkButton(const QItemSelection &, const QItemSelection &)
{
    bool itemSelected(ui->deviceView->selectionModel()->hasSelection());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(itemSelected);
}
