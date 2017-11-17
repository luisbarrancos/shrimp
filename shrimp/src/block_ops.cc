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
#include "ioproperties.h"
#include "helpers.h"
#include "mainwindow.h"

void MainWindow::OnBlockMove()
{
	if(!currentElement || state != Ready)
		return;

	if(currentElement->isIOPad())
	{
		IOPad* currentPad = (IOPad*)currentElement;
		currentElement = currentPad->getParent();
	}

	old_x = currentElement->getXPos();
	old_y = currentElement->getYPos();
	drawCurrentElement(old_x, old_y);

	circuitBoard->removeBlock((Block*)currentElement);
	state = Moving;
}

void MainWindow::OnBlockAdd(std::string name)
{
	cancelAction();

	//name = onblockloadfilename
	//so remove first 10 characters
	sdpString name2(name);
	name2 = name2.right(name2.length() - 10) + ".shml";
	currentElement = load_block_file(name2, basePath);

	if(currentElement == 0)
		return;

	old_x = -100;//out of sight to start
	old_y = -100;

	state = Adding;
}

void MainWindow::OnBlockDelete()
{
	if(!currentElement || state != Ready)
		return;

	if(currentElement->isIOPad())
	{
		IOPad* currentPad = (IOPad*)currentElement;
		currentElement = currentPad->getParent();
	}

	Block* currentBlock = (Block*)currentElement;
	if(currentBlock->isImortal())
	{
		Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("connect"), sdpString("Cannot delete this block"));
	}
	else
	{
		circuitBoard->deleteBlock((Block*)currentElement);
		forceRedraw();
	}
}

void MainWindow::OnBlockCopy()
{
	if(!currentElement || state != Ready)
		return;

	if(currentElement->isIOPad())
	{
		IOPad* currentPad = (IOPad*)currentElement;
		currentElement = currentPad->getParent();
	}

	Block* currentBlock = (Block*)currentElement;
	std::string currentFile = currentBlock->getFilename();
	currentElement = load_block_file(currentFile, basePath);

	if(currentElement == 0)
		return;

	old_x = -100;//out of sight to start
	old_y = -100;

	state = Adding;
}

void MainWindow::OnBlockHelp()
{
	if(!currentElement || state != Ready)
		return;

	if(currentElement->isIOPad())
	{
		IOPad* currentPad = (IOPad*)currentElement;
		currentElement = currentPad->getParent();
	}

	Block* currentBlock = (Block*)currentElement;
	BlockHelp help(currentBlock);
	std::string guifile = sdpAppendPath(sdpString(gtkmlPath), "blockhelp.gtkml");
	help.setGuiFile(guifile);
	help.DoModal();
}

void MainWindow::OnPadDisconnect()
{
	if(!currentElement || state != Ready)
		return;

	if(!currentElement->isIOPad())
		return;
	else
	{
		IOPad* currentPad = (IOPad*)currentElement;
		if(!currentPad->isInput())
			return;
	}

	InputPad* currentIn = (InputPad*)currentElement;
	currentIn->disconnect();
	forceRedraw();
}

void MainWindow::OnPadProperties()
{
	if(!currentElement || state != Ready)
		return;

	if(!currentElement->isIOPad())
		return;

	IOPad* currentPad = (IOPad*)currentElement;
	IOProperties prop(currentPad);
	std::string guifile = sdpAppendPath(sdpString(gtkmlPath), "ioproperties.gtkml");
	prop.setGuiFile(guifile);
	prop.DoModal();
	forceRedraw();
}

InputPad* MainWindow::addMultiPad(InputPad* inPad)
{
	Block* mum = inPad->getParent();

	if(! inPad->isMultiPad())
	{
		std::cout << "Error: pad doesn't support multiness" << std::endl;
		return 0;
	}

	//check for space o grid
	if(mum->numInputs() > mum->numOutputs())
	{
		int x = mum->getXPos();
		int y = mum->getYPos() + mum->getYSize();
		int w = mum->getXSize();
		int h = 1;

		if(!circuitBoard->freeSpaceAt(x, y, w, h))
		{
			Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("multi"), sdpString("Error: not enough space for new pad"));
			return 0;
		}
	}

	InputPad* result = mum->newMultiInput(inPad);
	circuitBoard->replaceBlock(mum);

	return result;
}

void MainWindow::removeMultiPad(InputPad* inPad)
{
	Block* mum = inPad->getParent();

	if(	!(inPad->isMultiPad() && inPad->isCopy()))
	{
		Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("multi"), sdpString("Error: cannot delete this input"));
		return;
	}

	mum->removeMultiInput(inPad);
	circuitBoard->replaceBlock(mum);
}

void MainWindow::drawCurrentElement(int x, int y)
{
	gdk_gc_set_function(gc, GDK_INVERT);
	int x0, y0, w, h;

	x0 = circuitBoard->toScreen(x);
	y0 = circuitBoard->toScreen(y);
	w = circuitBoard->toScreen(currentElement->getXSize());
	h = circuitBoard->toScreen(currentElement->getYSize());
	gdk_draw_rectangle(pixmap, gc, FALSE, x0, y0, w, h);


	gdk_gc_set_function(gc, GDK_COPY);

	GdkRectangle area;

	area.x = x0;
	area.y = y0;
	area.width = w + 1;
	area.height = h + 1;
	gtk_widget_draw(canvas, &area);
}

void MainWindow::connectPads(IOPad* aPad, IOPad* bPad)
{
	InputPad* inPad;
	OutputPad* outPad;

	if(aPad->isInput())
	{
		if(bPad->isInput())
		{
			Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("connect"), sdpString("Error: Cannot connect Input to Input"));
			return;
		}
		else
		{
			inPad = (InputPad*) aPad;
			outPad = (OutputPad*) bPad;
		}
	}
	else
	{
		if(!bPad->isInput())
		{
			Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("connect"), sdpString("Error: Cannot connect Output to Output"));
			return;
		}
		else
		{
			inPad = (InputPad*) bPad;
			outPad = (OutputPad*) aPad;
		}
	}

	if(outPad->getType() != "float" && inPad->getType() != outPad->getType())
	{
		// Try to change in pad's type
		if(!inPad->changeType(outPad->getType()))
		{
			// If that fails try to change out pad's type
			if(!outPad->changeType(inPad->getType()))
			{
				Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("connect"), sdpString("Error: Type mismatch"));
				return;
			}
		}
	}

	if(!inPad->isConnectable())
	{
		if(inPad->isMultiPad())
		{
			if(!(inPad = addMultiPad(inPad)))
			{
				Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("connect"), sdpString("Error: not enough space for new pad"));
				return;
			}
		}
		else
		{
			//Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("connect"), "Error: Input already connected, disconnect first");
			//return;
			inPad->disconnect();
		}
	}


	inPad->connect(outPad);
	Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("connect"), sdpString("Connected"));
	forceRedraw();

}


