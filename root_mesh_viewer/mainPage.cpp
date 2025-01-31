#include "mainPage.h"
#include "glArea.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QDebug>

ofstream debugg("output.txt");

mainPage::mainPage(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::mainPageClass)
{	
	area = new glArea(this);
	qInfo() << "new area initialized";
    ui->setupUi(this);
	qInfo() << "new area initialized";
	ui->glLayout->addWidget(area, 1);
	QObject::connect(ui->showSkel, SIGNAL(stateChanged(int)), this, SLOT(showSkelCheckBox(int)));
	QObject::connect(ui->showMesh, SIGNAL(stateChanged(int)), this, SLOT(showMeshCheckBox(int)));
	QObject::connect(ui->alphaSlider, SIGNAL(valueChanged(int)), this, SLOT(alphaChanged(int)));
	QObject::connect(ui->meshColorRedSlider, SIGNAL(valueChanged(int)), this, SLOT(meshColorRedChanged(int)));
	QObject::connect(ui->meshColorGreenSlider, SIGNAL(valueChanged(int)), this, SLOT(meshColorGreenChanged(int)));
	QObject::connect(ui->meshColorBlueSlider, SIGNAL(valueChanged(int)), this, SLOT(meshColorBlueChanged(int)));
	QObject::connect(ui->backColorRedSlider, SIGNAL(valueChanged(int)), this, SLOT(backColorRedChanged(int)));
	QObject::connect(ui->backColorGreenSlider, SIGNAL(valueChanged(int)), this, SLOT(backColorGreenChanged(int)));
	QObject::connect(ui->backColorBlueSlider, SIGNAL(valueChanged(int)), this, SLOT(backColorBlueChanged(int)));
	QObject::connect(ui->skelWidthSlider, SIGNAL(valueChanged(int)), this, SLOT(skelWidthChanged(int)));
	
	QObject::connect(ui->jetMinBox, SIGNAL(valueChanged(double)), this, SLOT(jetMinSpinChanged(double)));
	QObject::connect(ui->jetMaxBox, SIGNAL(valueChanged(double)), this, SLOT(jetMaxSpinChanged(double)));
	QObject::connect(ui->meshFileBrowseBtn, SIGNAL(clicked()), this, SLOT(browseMeshClicked()));
	QObject::connect(ui->meshFileBrowseBtn_obj, SIGNAL(clicked()), this, SLOT(browseMeshClicked_obj()));
	QObject::connect(ui->skelFileBrowseBtn, SIGNAL(clicked()), this, SLOT(browseSkelClicked()));
	QObject::connect(ui->annotationFileBrowseBtn, SIGNAL(clicked()), this, SLOT(browseAnnotationClicked()));

	QObject::connect(ui->showLvl0Root, SIGNAL(stateChanged(int)), this, SLOT(showLvl0RootCheckBox(int)));
	QObject::connect(ui->showLvl1Root, SIGNAL(stateChanged(int)), this, SLOT(showLvl1RootCheckBox(int)));
	QObject::connect(ui->showLvl2Root, SIGNAL(stateChanged(int)), this, SLOT(showLvl2RootCheckBox(int)));
	QObject::connect(ui->showLvl3Root, SIGNAL(stateChanged(int)), this, SLOT(showLvl3RootCheckBox(int)));
	QObject::connect(ui->showLvlLaterRoot, SIGNAL(stateChanged(int)), this, SLOT(showLvlLaterRootCheckBox(int)));
	QObject::connect(ui->whorlBelow, SIGNAL(stateChanged(int)), this, SLOT(whorlBelowCheckBox(int)));
	QObject::connect(ui->whorlAbove, SIGNAL(stateChanged(int)), this, SLOT(whorlAboveCheckBox(int)));
	QObject::connect(ui->nodalRootBelow, SIGNAL(stateChanged(int)), this, SLOT(nodalRootBelowCheckBox(int)));
	QObject::connect(ui->nodalRootAbove, SIGNAL(stateChanged(int)), this, SLOT(nodalRootAboveCheckBox(int)));
	QObject::connect(ui->showPlane, SIGNAL(stateChanged(int)), this, SLOT(showPlaneCheckBox(int)));
	QObject::connect(ui->skeletonColor, SIGNAL(currentIndexChanged(int)), this, SLOT(skeletonColorComboBox(int)));

	QObject::connect(ui->editOn, SIGNAL(stateChanged(int)), this, SLOT(editStateChange(int)));
	//QObject::connect(ui->inputValue, SIGNAL(clicked()), this, SLOT(addCurValue()));
	QObject::connect(ui->inputValuePar, SIGNAL(clicked()), this, SLOT(visualizeParent()));
	QObject::connect(ui->inputValueChi, SIGNAL(clicked()), this, SLOT(visualizeChild()));
	QObject::connect(ui->swapLast, SIGNAL(clicked()), this, SLOT(swapLastT()));
	
	QObject::connect(ui->deleteWhorlConf, SIGNAL(clicked()), this, SLOT(delWhorl()));
	QObject::connect(ui->editWhorlOn, SIGNAL(stateChanged(int)), this, SLOT(editWhorlChange(int)));

	QObject::connect(ui->addWhorl, SIGNAL(clicked()), this, SLOT(addWhorl()));
	QObject::connect(ui->verifyTop, SIGNAL(clicked()), this, SLOT(verifyTop()));
	QObject::connect(ui->verifyBot, SIGNAL(clicked()), this, SLOT(verifyBot()));
}

mainPage::~mainPage()
{
	delete ui;
	
	if (area) {
		delete area;
	}

}

void mainPage::showSkelCheckBox(int _s) {
	ui->statusBar->showMessage("changing the skeleton status");
	area->if_line = (_s == Qt::Checked);
}

void mainPage::showMeshCheckBox(int _s) {
	ui->statusBar->showMessage("changing the mesh status");
	area->if_face = (_s == Qt::Checked);
}

void mainPage::alphaChanged(int _s) {
	ui->statusBar->showMessage("changing the transparency");
	area->alpha = (ui->alphaSlider->maximum() - (float)_s) / (ui->alphaSlider->maximum() - ui->alphaSlider->minimum());
}

void mainPage::meshColorRedChanged(int _s) {
	ui->statusBar->showMessage("changing the mesh color");
	area->mesh_colorR = (/*ui->meshColorRedSlider->maximum() - */(float)_s) / (ui->meshColorRedSlider->maximum() - ui->meshColorRedSlider->minimum());
}

void mainPage::meshColorGreenChanged(int _s) {
	ui->statusBar->showMessage("changing the mesh color");
	area->mesh_colorG = ((float)_s) / (ui->meshColorGreenSlider->maximum() - ui->meshColorGreenSlider->minimum());
}

void mainPage::meshColorBlueChanged(int _s) {
	ui->statusBar->showMessage("changing the mesh color");
	area->mesh_colorB = ((float)_s) / (ui->meshColorBlueSlider->maximum() - ui->meshColorBlueSlider->minimum());
}

void mainPage::backColorRedChanged(int _s) {
	ui->statusBar->showMessage("changing the background color");
	area->back_colorR = ((float)_s) / (ui->backColorRedSlider->maximum() - ui->backColorRedSlider->minimum());
}

void mainPage::backColorGreenChanged(int _s) {
	ui->statusBar->showMessage("changing the background color");
	area->back_colorG = ((float)_s) / (ui->backColorGreenSlider->maximum() - ui->backColorGreenSlider->minimum());
}

void mainPage::backColorBlueChanged(int _s) {
	ui->statusBar->showMessage("changing the background color");
	area->back_colorB = ((float)_s) / (ui->backColorBlueSlider->maximum() - ui->backColorBlueSlider->minimum());
}

// changed from 0.01 + 2 * ... to 0.05 + 2.5 * ... , made lines thicker
// and minimum value larger
void mainPage::skelWidthChanged(int _s) {
	ui->statusBar->showMessage("changing the line width");
	area->line_width = 0.05 + 2.5 * ( (float)_s - ui->skelWidthSlider->minimum()) / (ui->skelWidthSlider->maximum() - ui->skelWidthSlider->minimum());
}



void mainPage::jetMinSpinChanged(double _s)
{
	debugg << "jetMinSpinChanged" << endl;
	area->jet_min = _s;
}

void mainPage::jetMaxSpinChanged(double _s)
{
	//ofstream fout("jetMaxSpin.txt");
	if (area->line_color == Jet) {
		area->jet_max = _s;
	}
	else {
		debugg << "jetMaxSpinChanged Hierarchy " << _s << endl;
		// fout << "changing max box for hierarchy..." << endl;
		// fout << _s << endl;
		area->hierarchyCap = _s;
	}
}

void mainPage::browseMeshClicked()
{
	QString shape_file = QFileDialog::getOpenFileName(this, "Select .off file", "", "*.off",
		NULL/*, QFileDialog::DontUseNativeDialog*/);
	ui->meshFileLabel->setText(shape_file);
	QByteArray shape_byteArray = shape_file.toLatin1();
	ifstream myFile;
	myFile.open(shape_byteArray.data());
	if (myFile.is_open()) {
		area->mesh = ReadOffFile(shape_byteArray.data());
		area->faceDisplayList += 2;
		area->draw_faces();
		area->if_face = true;
		area->adjustView();
	}
	else {
		ui->statusBar->showMessage("no mesh file is loaded");
	}
}

void mainPage::browseMeshClicked_obj()
{
	QString shape_file = QFileDialog::getOpenFileName(this, "Select .obj file", "", "*.obj",
		NULL/*, QFileDialog::DontUseNativeDialog*/);
	ui->meshFileLabel_obj->setText(shape_file);
	QByteArray shape_byteArray = shape_file.toLatin1();
	ifstream myFile;
	myFile.open(shape_byteArray.data());
	if (myFile.is_open()) {
		area->mesh = ReaderOBj(shape_byteArray.data());
		area->faceDisplayList += 2;
		area->draw_faces();
		area->if_face = true;
		area->adjustView();
	}
	else {
		ui->statusBar->showMessage("no mesh file is loaded");
	}
}

void mainPage::browseSkelClicked()
{
	debugg << "broseSkelClicked()" << endl;
	//ofstream fout("browseSkelClicked.txt");
	QString skel_file = QFileDialog::getOpenFileName(this, "Select .ply file", "", "*.ply",
		NULL/*, QFileDialog::DontUseNativeDialog*/);
	ui->skelFileLabel->setText(skel_file);
	QByteArray skel_byteArray = skel_file.toLatin1();
	if (getSkeleton(area->vertexList, area->edgeList, skel_byteArray.data(), area->level, area->radius, area->adjVertex, area->junctions, area->IDs, area->childVertex, area->juncAdj) == 1) {
		area->if_drawWhorlAbove = false;
		area->if_drawWhorlBelow = false;
		area->if_drawNodeAbove = false;
		area->if_drawNodeBelow = false;
		area->if_drawPlane = false;
		area->adjustView();
		ui->whorlAbove->setChecked(false);
		ui->whorlBelow->setChecked(false);
		ui->nodalRootAbove->setChecked(false);
		ui->nodalRootBelow->setChecked(false);
		ui->showPlane->setChecked(false);
		area->annotation_activated = 1;
		// fout << "Successfully initiated ply data... " << endl;
	}
	area->showLevels.clear();
	for (int i = 0; i <= *max_element(area->level.begin(), area->level.end()); i++) {
		area->showLevels.push_back(1);
	}
	// fout << "Level size: " << area->level.size() << endl;

	debugg << "Setting values for jetMax and Min" << endl;
	// fout << "Successfully set levels..." << endl;
	debugg << area->hierarchyCap << endl;

	area->if_line = true;
	ui->jetMaxBox->setValue((double)*max_element(area->radius.begin(), area->radius.end()));
	debugg << area->hierarchyCap << endl;
	
	ui->jetMinBox->setValue((double)*min_element(area->radius.begin(), area->radius.end()));
	debugg << "Success with jetMaxBox value setting..." << endl;
	debugg << area->hierarchyCap << endl;
}

void mainPage::browseAnnotationClicked()
{
	QString annotation_file = QFileDialog::getOpenFileName(this, "Select .txt file", "", "*.txt",
		NULL/*, QFileDialog::DontUseNativeDialog*/);
	ui->annotationFileLabel->setText(annotation_file);
	QByteArray annotation_byteArray = annotation_file.toLatin1();
	if (readAnnotation(area->whorls, area->nodalRoots, annotation_byteArray.data(), area->cent, area->n, area->juncWhorlAbove, area->juncWhorlBelow, area->whorls_inord) == 1 && area->annotation_activated == 1) {
		area->if_drawWhorlAbove = false;
		area->if_drawWhorlBelow = false;
		area->if_drawNodeAbove = false;
		area->if_drawNodeBelow = false;
		area->if_drawPlane = false;
		ui->whorlAbove->setChecked(false);
		ui->whorlBelow->setChecked(false);
		ui->nodalRootAbove->setChecked(false);
		ui->nodalRootBelow->setChecked(false);
		ui->showPlane->setChecked(false);
		area->annotation_activated = 2;
		area->sort_whorls();
		cout << "Successfully initiated annotation data... " << endl;
	}
	else {
		area->annotation_activated = 0;
		ui->statusBar->showMessage("no annotation file is loaded");
	}
}

void mainPage::showLvl0RootCheckBox(int _s)
{
	if (_s == Qt::Checked) {
		area->showLevels[0] = true;
	}
	else {
		area->showLevels[0] = false;
	}
}

void mainPage::showLvl1RootCheckBox(int _s)
{
	if (_s == Qt::Checked) {
		area->showLevels[1] = true;
	}
	else {
		area->showLevels[1] = false;
	}
}

void mainPage::showLvl2RootCheckBox(int _s)
{
	if (_s == Qt::Checked) {
		area->showLevels[2] = true;
	}
	else {
		area->showLevels[2] = false;
	}
}

void mainPage::showLvl3RootCheckBox(int _s)
{
	if (_s == Qt::Checked) {
		area->showLevels[3] = true;
	}
	else {
		area->showLevels[3] = false;
	}
}

void mainPage::showLvlLaterRootCheckBox(int _s)
{
	if (_s == Qt::Checked) {
		for (int i = 4; i < area->showLevels.size(); i++) {
			area->showLevels[i] = true;
		}
	}
	else {
		for (int i = 4; i < area->showLevels.size(); i++) {
			area->showLevels[i] = false;
		}
	}
}

void mainPage::whorlBelowCheckBox(int _s)
{
	if (_s == Qt::Checked) {
		area->if_drawWhorlBelow = true;
	}
	else {
		area->if_drawWhorlBelow = false;
	}
}

void mainPage::whorlAboveCheckBox(int _s)
{
	if (_s == Qt::Checked) {
		area->if_drawWhorlAbove = true;
	}
	else {
		area->if_drawWhorlAbove = false;
	}
}

void mainPage::nodalRootBelowCheckBox(int _s)
{
	if (_s == Qt::Checked) {
		area->if_drawNodeBelow = true;
	}
	else {
		area->if_drawNodeBelow = false;
	}
}

void mainPage::nodalRootAboveCheckBox(int _s)
{
	if (_s == Qt::Checked) {
		area->if_drawNodeAbove = true;
	}
	else {
		area->if_drawNodeAbove = false;
	}
}

void mainPage::showPlaneCheckBox(int _s) {
	ui->statusBar->showMessage("showing the plane");
	area->if_drawPlane = (_s == Qt::Checked);
}

void mainPage::skeletonColorComboBox(int _s)
{
	debugg << "skeletonColorComboBox" << endl;
	// ofstream fout("skeletonColorComboBox.txt");
	if (_s == 0) {
		area->line_color = Normal;
		ui->statusBar->showMessage("changing the skeleton color to normal");
	}
	else if (_s == 1){
		// fout << "Setting by hierarchy" << endl;
		debugg << area->hierarchyCap << endl;
		area->line_color = Hierarchy;
		ui->jetMaxBox->setMaximum(5);
		ui->jetMaxBox->setValue(area->hierarchyCap);
		ui->jetMaxBox->setMinimum(0);
		ui->jetMaxBox->setSingleStep(1);
		ui->statusBar->showMessage("changing the skeleton color according to hierarchy");
		// fout << area->hierarchyCap << endl;
	}
	else {
		area->line_color = Jet;
		// fout << "Set by Jet" << endl;
		ui->statusBar->showMessage("changing the skeleton color according to radius");
		ui->jetMaxBox->setMaximum((double)*max_element(area->radius.begin(), area->radius.end()));
		ui->jetMaxBox->setValue((double)*max_element(area->radius.begin(), area->radius.end()));
		ui->jetMaxBox->setSingleStep(.01);
	}
}

void mainPage::editStateChange(int _s) {
	if (_s == Qt::Checked) {
		area->editOn = 1;
		//area->ind.clear();
	}
	else area->editOn = 0;
}

//void mainPage::addCurValue() {
//	if (area->editOn) {
//		bool flag;
//		QString qs = ui->inputText->toPlainText();
//		int cind = qs.toInt(&flag);
//
//		if (flag) {
//			ui->statusBar->showMessage("selected index " + qs);
//			area->ind.push_back(cind);
//		}
//	}
//}

void mainPage::visualizeParent() {
	if (area->editOn) {
		bool flag;
		QString qs = ui->inputTextPar->toPlainText();
		int cind = qs.toInt(&flag);
	
		if (flag) {
			ui->statusBar->showMessage("selected parent " + qs);
			area->parVisualize = cind;
			//area->ind.push_back(cind);
		}
	}
}

void mainPage::visualizeChild() {
	if (area->editOn) {
		bool flag;
		QString qs = ui->inputTextChi->toPlainText();
		int cind = qs.toInt(&flag);

		if (flag) {
			ui->statusBar->showMessage("selected child " + qs);
			area->chiVisualize = cind;
			//area->ind.push_back(cind);
		}
	}
}

void mainPage::swapLastT() {
	if (area->parVisualize != -1 && area->chiVisualize != -1) {
		int schi = area->chiVisualize;
		int par = area->parVisualize;
		int fchi = -1; /*FIND ADJ TO PAR WITH SAME COLOR*/
		for (const auto &v : area->childVertex[par]) {
			if (area->level[v] == area->level[par])
			{
				fchi = v;
				break;
			}
		}

		area->fchiVisualize = fchi;
		if (fchi == -1) ui->statusBar->showMessage("error in finding the continuation vertice");
		else {
			//ui->statusBar->showMessage("reprop " + QString(fchi) + " " + QString(schi));
			ui->statusBar->showMessage("repropagating");

			swap(area->level[fchi], area->level[schi]);
			propagate(area->adjVertex, area->level, area->hierarchyCap, schi, -1, par, area->level[schi] - area->level[fchi]);
			propagate(area->adjVertex, area->level, area->hierarchyCap, fchi, -1, par, area->level[fchi] - area->level[schi]);
			area->fchiVisualize = -1;
			area->parVisualize = -1;
			area->chiVisualize = -1;
		}
	}
	else ui->statusBar->showMessage("not enough indices");
}

void mainPage::editWhorlChange(int _s) {
	if (_s == Qt::Checked) {
		area->editWhorlOn = 1;
		//area->ind.clear();
	}
	else area->editWhorlOn = 0;
}

void mainPage::delWhorl() {
	if (area->editWhorlOn) {
		QString qs = ui->whorlDelete->toPlainText();
		char cind = qs.at(0).toLatin1();

		if (area->deleteWhorl(cind)) {
			ui->statusBar->showMessage("deleted whorl " + qs);
		}
		else {
			ui->statusBar->showMessage("whorl" + qs + " out of range, please try again");
		}
	}
}

void mainPage::addWhorl() {
	bool flag1, flag2;
	QString qs = ui->inputTextTop->toPlainText();
	int cind = qs.toInt(&flag1);
	qs = ui->inputTextBot->toPlainText();
	int cind2 = qs.toInt(&flag2);

	if (flag1 && flag2) {
		if (area->juncWhorlAbove.count(cind) && area->juncWhorlAbove.count(cind2)) {
			if (area->addNewBox(cind, cind2, 1)) {
				ui->statusBar->showMessage("successfully added whorl to above");
				area->topWh = -1, area->botWh = -1;
			}
			else ui->statusBar->showMessage("whorl addition failed, please try again");
		}
		else if (area->juncWhorlBelow.count(cind) && area->juncWhorlBelow.count(cind2)) {
			if (area->addNewBox(cind, cind2, 0)) {
				ui->statusBar->showMessage("successfully added whorl to below");
				area->topWh = -1, area->botWh = -1;
			}
			else ui->statusBar->showMessage("whorl addition failed, please try again");
		} else ui->statusBar->showMessage("invalid junctions, please try again");
	}
}

void mainPage::verifyTop() {
	if (area->editWhorlOn) {
		bool flag;
		QString qs = ui->inputTextTop->toPlainText();
		int cind = qs.toInt(&flag);

		if (flag) {
			ui->statusBar->showMessage("selected junction " + qs);
			area->topWh = cind;
			//area->ind.push_back(cind);
		}
	}
}

void mainPage::verifyBot() {
	if (area->editWhorlOn) {
		bool flag;
		QString qs = ui->inputTextBot->toPlainText();
		int cind = qs.toInt(&flag);

		if (flag) {
			ui->statusBar->showMessage("selected junction " + qs);
			area->botWh = cind;
			//area->ind.push_back(cind);
		}
	}
}