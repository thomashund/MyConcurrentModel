#include <QMainWindow>
#include <QGridLayout>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>

#include "proto.h"
#include "heart_cell_sim.h"
#include "varmenu.h"

Simulation::Simulation(QWidget* parent){
//setup class variables
    this->parent = parent;
    proto = new Protocol();
    sim_ready = false;
//local variables
    unsigned int max_height = 8;
    unsigned int max_width = 14;
//create layouts
    QGridLayout* main_layout = new QGridLayout(this);
    QButtonGroup* advanced_buttons = new QButtonGroup(this);
    QGridLayout* advanced = new QGridLayout();
    QHBoxLayout* file_buttons = new QHBoxLayout();
//create buttons/combo boxes
    QPushButton* run = new QPushButton("Run Simulations", this);
    QPushButton* edit_sim = new QPushButton("Edit Simulaiton Variables", this);
    QPushButton* load_sim = new QPushButton("Read Simulation Variabels", this);
    QComboBox* cell_type = new QComboBox(this);
    QComboBox* cell_species = new QComboBox(this);
//set button/combo box inital values
    run->setEnabled(sim_ready);
    cell_type->addItem("Default Cell");
    cell_type->addItem("Choose Cell");
    cell_type->addItem("Ventricular");
    cell_type->addItem("Sinoatrial Node");
    cell_type->addItem("Atrial");
    cell_type->addItem("Kurata");
    cell_species->addItem("Default Species");
    cell_species->addItem("Choose Species");
    cell_species->addItem("Mouse");
    cell_species->addItem("Rabbit");
    cell_species->addItem("Human");
//add buttons to layouts
//advanced buttons
    advanced_buttons->addButton(edit_sim);
    advanced->addWidget(edit_sim, 0,0);
//load variables buttons
    file_buttons->addWidget(load_sim);
//main_layout
    main_layout->addWidget(cell_type, 0,0);
    main_layout->addWidget(cell_species, 0,1);
    main_layout->addLayout(file_buttons,1,-1);
    main_layout->addLayout(advanced, max_height -1, 1);
    main_layout->addWidget(run, max_height, max_width);
//connect buttons
    connect(run, SIGNAL(clicked()),this,SLOT(run_sims()));
    connect(edit_sim, SIGNAL(clicked()), this, SLOT(edit_simvars()));
    connect(load_sim, SIGNAL(clicked()),this, SLOT(load_simvars()));
    
};

Simulation::~Simulation(){};

//void Simulation::set_sim_ready() {};

void Simulation::run_sims() {
};

void Simulation::edit_simvars() {
    simvarMenu* menu = new simvarMenu(proto, this);
    menu->show();
};

bool Simulation::load_simvars() {
    return (bool)proto->readpars(proto->pars, proto->simvarfile);
};
