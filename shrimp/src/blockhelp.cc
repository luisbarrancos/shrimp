//============================================================================
//
// Shrimp Shader Generator
// Copyright (C) 2000-2004 Andy Gill
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//============================================================================

#include "blockhelp.h"

bool BlockHelp::Load()
{
	sdpGtkObjectContainer::Load(guifile);

	std::string title = block->getName() + " help";

	Window("window").SetTitle(title.c_str());
	Frame("general").SetLabel(block->getName().c_str());

	Label("generaltext").SetLineWrap(true);
	Label("generaltext").SetText(block->getDesc());

	std::string inhelp, outhelp;
	block->getInputHelpString(inhelp);
	block->getOutputHelpString(outhelp);

	Label("inputtext").SetLineWrap(true);
	Label("inputtext").SetText(inhelp);
	Label("outputtext").SetLineWrap(true);
	Label("outputtext").SetText(outhelp);

	Label("usagetext").SetLineWrap(true);
	Label("usagetext").SetText(block->getUsage());

	RootWidget().Show();

	return true;
}


