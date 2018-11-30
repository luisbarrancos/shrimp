
/*
    Copyright 2012, Romain Behar <romainbehar@users.sourceforge.net>

    This file is part of Shrimp 2.

    Shrimp 2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Shrimp 2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Shrimp 2.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RIB_BLOCK_H
#define RIB_BLOCK_H

#include "src/shading/rib_root_block.h"

#include "src/services.h"

#include <QDialog>

namespace Ui
{
class ribBlockDialog;
}

class rib_block : public QDialog
{
    Q_OBJECT

  public:
    explicit rib_block(
        QWidget* parent,
        services* shrimpServicesInstance,
        rib_root_block* block);
    ~rib_block() override;

  public slots:
    void cancelButton();
    void okButton();

  private:
    Ui::ribBlockDialog* ui;
    services* shrimpServices;
    rib_root_block* editedBlock;
};

#endif // RIB_BLOCK_H
