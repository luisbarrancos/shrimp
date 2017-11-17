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

#include "codepreview.h"
#include "mainwindow.h"
#include "resizedialog.h"
#include "shaderprop.h"
#include "helpers.h"

#include <fstream>

#include <sys/types.h>
#include <sys/wait.h>

void MainWindow::OnNewCircuit(std::string eventName)
{
	//remove onnew from name.
	sdpString event2(eventName);
	std::string name = event2.right(event2.length() - 5);

	std::string c_out = name + "_output.shml";
	Block* op = load_block_file(c_out, basePath);
	if(op == 0)
		return;

	int opxpos = circuitBoard->getXSize() - op->getXSize();
	//keep output on the same screen
	if (opxpos > 32)
		opxpos = 32;
	op->setPos(opxpos, 0);
	op->makeImortal();

	circuitBoard->setName("no_name");
	circuitBoard->setAbout("Built with Shrimp.");
	circuitBoard->setShaderType(name);
	circuitBoard->setFilename(std::string(""));
	circuitBoard->clear();
	circuitBoard->addBlock(op);

	Window("mainwindow").SetTitle(sdpString("Shrimp: untitled"));

	forceRedraw();
}

void MainWindow::OnCircuitOpen()
{
	// Popup file requester and load circuit
	sdpGtkFileSelector selector("Open a Shrimp Circuit", "");
	selector.DoModal();

	if(!selector.OK())
		return;

	Circuit* c = loadCircuit(selector.FilePath());

	if(c == 0)
		return;

	delete circuitBoard;
	circuitBoard = c;
	circuitBoard->setFilename(std::string(selector.FilePath()));
	circuitBoard->setZoom(static_cast<int>(Adjustment("zoom").Value()));

	std::string title = "Shrimp: " + sdpFile(circuitBoard->getFilename().c_str());
	Window("mainwindow").SetTitle(title.c_str());
}

void MainWindow::OnCircuitSave()
{
	std::string filename = circuitBoard->getFilename() ;
	if(filename == "")
		OnCircuitSaveAs();
	else
		saveCircuit(filename);
}

void MainWindow::OnCircuitSaveAs()
{
	//popup file requester
	sdpGtkFileSelector selector("Save Shrimp Circuit", "");
	selector.DoModal();

	if(!selector.OK())
		return;

	saveCircuit(selector.FilePath());
	circuitBoard->setFilename(std::string(selector.FilePath()));

	std::string title = "Shrimp: " + sdpFile(sdpString(circuitBoard->getFilename()));
	Window("mainwindow").SetTitle(title.c_str());
}

void MainWindow::OnCircuitClose()
{
	// Reload default blocks
	OnNewCircuit("newsurface");

	/*
		nb if this circuit had a parent we should go back to that
		instead.
	*/
}

void MainWindow::OnCircuitResize()
{
	ResizeDialog rs(circuitBoard->getXSize(), circuitBoard->getYSize());

	std::string guifile = sdpAppendPath(gtkmlPath.c_str(), "resizedialog.gtkml");
	rs.setGuiFile(guifile);
	rs.DoModal();

	if(!rs.OK())
		return;

	int x = rs.getX();
	int y = rs.getY();

	if(!circuitBoard->resize(x, y))
		std::cout << "Resize would lose blocks, move or delete them first" << std::endl;
	else
		forceRedraw();
}

Circuit* MainWindow::loadCircuit(std::string filename)
{
	Circuit* c = 0;

	sdpxml::Document doc(filename);
	doc.Load(filename);

	if(doc.Name() != std::string("shrimp"))
	{
		std::cout << "Error, " << filename << " is not a Shrimp file\n";
		return 0;
	}

	sdpxml::Element* circuit = sdpxml::FindElement(doc, sdpxml::SameName("circuit"));
	if(circuit == 0)
	{
		std::cout << "Error, " << filename << " does not contain a circuit description\n";
		return 0;
	}

	c = new Circuit(canvas);
	g_return_val_if_fail(c, 0);

	sdpxml::AttributeCollection::const_iterator a;
	for(a = doc.Attributes().begin(); a != doc.Attributes().end(); a++)
	{
		if(a->Name() == std::string("name"))
			c->setName(std::string(a->Value()));
		else if(a->Name() == std::string("type"))
			c->setShaderType(std::string(a->Value()));
	}

	sdpxml::Element* about = sdpxml::FindElement(doc, sdpxml::SameName("about"));
	if(about)
		c->setAbout(about->Text());

	c->load(*circuit, basePath);
	return c;
}

void MainWindow::saveCircuit(const std::string& filename)
{
	sdpxml::Document doc("shrimp");
	doc.Attributes().push_back(sdpxml::Attribute("name", circuitBoard->getName()));
	doc.Attributes().push_back(sdpxml::Attribute("type", circuitBoard->getShaderType()));

	doc.Children().push_back(sdpxml::Element("about", circuitBoard->getAbout()));

	doc.Children().push_back(sdpxml::Element("circuit"));
	circuitBoard->saveCircuit(doc.Children().back());

	// Save XML document
	std::ofstream out_file;
	out_file.open(filename.c_str(), std::ios::out | std::ios::trunc);
	out_file << doc << std::endl;
	out_file.close();
}

extern char** environ;

void string_replace(std::string& Text, const std::string& Replacement)
{
	std::string::size_type index = Text.find("%s");
	while(index != std::string::npos)
	{
		// Make the replacement!
		Text.replace(index, 2, Replacement);
		index = Text.find("%s", index + Replacement.size() + 1);
	}
}

void exec_command(const std::string& Command)
{
	std::cout << Command << std::endl;
	system(Command.c_str());
}

void MainWindow::OnPreview()
{
	std::string tempdir = sdpGetTempDirectory();
	std::string preview_sl = sdpAppendPath(sdpString(tempdir), "preview.sl");
	circuitBoard->writeCode(preview_sl);

	// Compile light shaders
	std::string light_shader = sdpAppendPath(basePath.c_str(), "shaders/ambientlight.sl");
	std::string light_compiler = renderOptions.getCompiler();
	string_replace(light_compiler, light_shader);
	exec_command(light_compiler);
	light_shader = sdpAppendPath(basePath.c_str(), "shaders/distantlight.sl");
	light_compiler = renderOptions.getCompiler();
	string_replace(light_compiler, light_shader);
	exec_command(light_compiler);

	std::string compileCommand = renderOptions.getCompiler();
	string_replace(compileCommand, preview_sl);
	exec_command(compileCommand);

	std::string preview_rib = sdpAppendPath(sdpString(tempdir), "preview.rib");
	renderOptions.writeRIB(preview_rib, circuitBoard->getName(), circuitBoard->getShaderType());

	std::string renderCommand = renderOptions.getRenderer();
	string_replace(renderCommand, preview_rib);
	std::string cleanup = "rm -f " + circuitBoard->getName() + ".slc";

	int pid = fork();
	if(pid == -1)
	{
		std::cout << "Error creating new process\n";
		system(cleanup.c_str());
	}
	else if(pid == 0)
	{
		int status;
		int pid2 = fork();
		if(pid2 == -1)
		{
			std::cout << "Error creating new process\n";
			system(cleanup.c_str());
		}
		else if(pid2 == 0)
		{
			std::cout << renderCommand << std::endl;
			char* argv[4];
			argv[0] = "sh";
			argv[1] = "-c";
			argv[2] = const_cast<char*>(renderCommand.c_str());
			argv[3] = 0;
			execve("/bin/sh", argv, environ);
			exit(127);
		}

		// wait until finished rendering then cleanup.
		waitpid(pid2, &status, 0);
		char* argv[4];
		argv[0] = "sh";
		argv[1] = "-c";
		argv[2] = const_cast<char*>(cleanup.c_str());
		argv[3] = 0;
		//std::cout << cleanup << std::endl;
		execve("/bin/sh", argv, environ);
		exit(127);
	}
}

void MainWindow::OnSaveCode()
{
	//popup file requester and load circuit
	sdpGtkFileSelector selector("Save Shader Code", "");
	selector.DoModal();

	if(!selector.OK())
		return;

	circuitBoard->writeCode(selector.FilePath());
}

void MainWindow::OnShaderProperties()
{
	ShaderProperties sp(circuitBoard);
	std::string guifile = sdpAppendPath(sdpString(gtkmlPath), "shaderproperties.gtkml");
	sp.setGuiFile(guifile);
	sp.DoModal();
}

void MainWindow::OnRenderOptions()
{
	std::string guifile = sdpAppendPath(sdpString(gtkmlPath), "renderoptions.gtkml");
	renderOptions.setGuiFile(guifile);
	renderOptions.DoModal();
}

void MainWindow::OnCodePreview()
{
	std::string tempdir = sdpGetTempDirectory();
	std::string preview_sl = sdpAppendPath(sdpString(tempdir), "preview.sl");
	circuitBoard->writeCode(preview_sl);

	CodePreview cpreview(circuitBoard->getName(), preview_sl);
	std::string guifile = sdpAppendPath(sdpString(gtkmlPath), "codepreview.gtkml");
	cpreview.setGuiFile(guifile);
	cpreview.DoModal();
}


