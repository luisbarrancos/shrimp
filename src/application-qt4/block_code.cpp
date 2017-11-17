
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


#include "block_code.h"
#include "ui_block_code.h"

#include "src/miscellaneous/logging.h"

block_code::block_code(QWidget* parent, services* shrimpServicesInstance, shader_block* block) :
    QDialog (parent),
    ui (new Ui::blockCodeDialog),
    shrimpServices (shrimpServicesInstance),
    editedBlock (block)
{
    ui->setupUi(this);

    log() << aspect << "Block Code dialog" << std::endl;

    // set values
    ui->ioTextEdit->setPlainText (QString::fromStdString (buildInfo()));
    ui->codeTextEdit->setPlainText (QString::fromStdString (block->get_code()));

    // connect events
    connect (ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton()));
    connect (ui->okButton, SIGNAL(clicked()), this, SLOT(okButton()));
}


block_code::~block_code()
{
}


void block_code::cancelButton()
{
    close();
}


void block_code::okButton()
{
    log() << aspect << "Save block code" << std::endl;

    // save code
    editedBlock->set_code (ui->codeTextEdit->toPlainText().toStdString());

    close();
}


std::string block_code::buildInfo()
{
    // get block content
    std::string inputs ("");
    for (shader_block::properties_t::const_iterator input = editedBlock->m_inputs.begin(); input != editedBlock->m_inputs.end(); ++input)
    {
        if (!inputs.empty())
        {
            inputs += ", ";
        }

        inputs += input->m_name;
    }

    std::string outputs ("");
    for (shader_block::properties_t::const_iterator output = editedBlock->m_outputs.begin(); output != editedBlock->m_outputs.end(); ++output)
    {
        if (!outputs.empty())
        {
            outputs += ", ";
        }

        outputs += output->m_name;
    }

    std::string info = "inputs: " + inputs + "\n"
            + "outputs: " + outputs;

    return info;
}

