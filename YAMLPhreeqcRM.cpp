#ifdef USE_YAML
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "YAMLPhreeqcRM.h"

std::map<size_t, YAMLPhreeqcRM*> YAMLPhreeqcRM::Instances;
std::mutex YAMLPhreeqcRM::InstancesLock;
size_t YAMLPhreeqcRM::InstancesIndex = 0;

YAMLPhreeqcRM::YAMLPhreeqcRM()
{
	InstancesLock.lock();
	this->Index = YAMLPhreeqcRM::InstancesIndex++;
	std::map<size_t, YAMLPhreeqcRM*>::value_type instance(this->Index, this);
	YAMLPhreeqcRM::Instances.insert(instance);
	InstancesLock.unlock();
}
YAMLPhreeqcRM::~YAMLPhreeqcRM()
{
	InstancesLock.lock();
	std::map<size_t, YAMLPhreeqcRM*>::iterator it = YAMLPhreeqcRM::Instances.find(this->Index);
	if (it != YAMLPhreeqcRM::Instances.end())
	{
		YAMLPhreeqcRM::Instances.erase(it);
	}
	InstancesLock.unlock();
}
void YAMLPhreeqcRM::Clear()
{
	YAML::Node empty;
	YAML_doc = empty;
}
int YAMLPhreeqcRM::GetId(void)const
{
	return (int)this->Index;
}
void YAMLPhreeqcRM::WriteYAMLDoc(std::string file_name)
{
	std::ofstream ofs = std::ofstream(file_name.c_str(), std::ofstream::out);
	ofs << this->GetYAMLDoc();
	ofs.close();
}
void YAMLPhreeqcRM::YAMLCloseFiles (void)
{
	YAML_doc["CloseFiles"] = "";
	return;
};
void YAMLPhreeqcRM::YAMLCreateMapping(std::vector< int >& grid2chem)
{
	YAML_doc["CreateMapping"] = grid2chem;
	YAML_doc["CreateMapping"].SetStyle(YAML::EmitterStyle::Flow);
	return;
};
void YAMLPhreeqcRM::YAMLDumpModule(bool dump_on, bool append)
{
	YAML::Node node;
	node["dump_on"] = dump_on;
	node["append"] = append;
	YAML_doc["DumpModule"] = node;
	return;
}
void YAMLPhreeqcRM::YAMLFindComponents()
{
	YAML_doc["FindComponents"] = "";
	return;
}
void YAMLPhreeqcRM::YAMLInitialPhreeqc2Module(std::vector< int > initial_conditions1) 
{
	YAML_doc["InitialPhreeqc2Module"] = initial_conditions1;
	YAML_doc["InitialPhreeqc2Module"].SetStyle(YAML::EmitterStyle::Flow);
	return;
};

void YAMLPhreeqcRM::YAMLInitialPhreeqc2Module(std::vector< int > initial_conditions1, std::vector< int > initial_conditions2, std::vector< double > fraction1) 
{
	YAML::Node node;
	node["ic1"] = initial_conditions1;
	node["ic2"] = initial_conditions2;
	node["f1"] = fraction1;
	YAML_doc["InitialPhreeqc2Module"] = node;
	YAML_doc["InitialPhreeqc2Module"].SetStyle(YAML::EmitterStyle::Flow);
	return;
};

void YAMLPhreeqcRM::YAMLInitialPhreeqcCell2Module(int n, std::vector< int > cell_numbers) 
{
	YAML::Node node;
	node["n"] = n;
	node["cell_numbers"] = cell_numbers;
	YAML_doc["InitialPhreeqcCell2Module"] = node;
	YAML_doc["InitialPhreeqcCell2Module"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}

void YAMLPhreeqcRM::YAMLLoadDatabase(std::string database) 
{
	YAML_doc["LoadDatabase"] = database;
	return;
}
void YAMLPhreeqcRM::YAMLLogMessage(std::string str)
{
	YAML_doc["LogMessage"] = str;
	return;
}
void YAMLPhreeqcRM::YAMLOpenFiles(void)
{
	YAML_doc["OpenFiles"] = "";
	return;
};
void YAMLPhreeqcRM::YAMLOutputMessage(std::string str) 
{
	YAML_doc["OutputMessage"] = str;
	return;
}
void YAMLPhreeqcRM::YAMLRunCells(void) 
{
	YAML_doc["RunCells"] = "";
	return;
}
void YAMLPhreeqcRM::YAMLRunFile(bool workers, bool initial_phreeqc, bool utility, std::string chemistry_name) 
{
	YAML::Node node;
	node["workers"] = workers;
	node["initial_phreeqc"] = initial_phreeqc;
	node["utility"] = utility;
	node["chemistry_name"] = chemistry_name;
	YAML_doc["RunFile"] = node;
	YAML_doc["RunFile"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLRunString(bool workers, bool initial_phreeqc, bool utility, std::string input_string) 
{
	YAML::Node node;
	node["workers"] = workers;
	node["initial_phreeqc"] = initial_phreeqc;
	node["utility"] = utility;
	node["input_string"] = input_string;
	YAML_doc["RunString"] = node;
	YAML_doc["RunString"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLScreenMessage(std::string str) 
{
	YAML_doc["ScreenMessage"] = str;
	return;
}
void YAMLPhreeqcRM::YAMLSetComponentH2O(bool tf)
{
	YAML_doc["SetComponentH2O"] = tf;
	return;
};
void YAMLPhreeqcRM::YAMLSetConcentrations(std::vector< double >& c) 
{
	YAML_doc["SetConcentrations"] = c;
	YAML_doc["SetConcentrations"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLSetCurrentSelectedOutputUserNumber(int n_user) 
{
	YAML_doc["SetCurrentSelectedOutputUserNumber"] = n_user;
	return;
}
void YAMLPhreeqcRM::YAMLSetDensity(std::vector< double > density) 
{
	YAML_doc["SetDensity"] = density;
	YAML_doc["SetDensity"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLSetDumpFileName(std::string dump_name) 
{
	YAML_doc["SetDumpFileName"] = dump_name;
	return;
}
void YAMLPhreeqcRM::YAMLSetErrorHandlerMode(int mode) 
{
	YAML_doc["SetErrorHandlerMode"] = mode;
	return;
};
void YAMLPhreeqcRM::YAMLSetErrorOn(bool tf) 
{
	YAML_doc["SetErrorOn"] = tf;
	return;
}
void YAMLPhreeqcRM::YAMLSetFilePrefix(std::string prefix) 
{
	YAML_doc["SetFilePrefix"] = prefix;
	return;
};
void YAMLPhreeqcRM::YAMLSetGasCompMoles(std::vector< double > gas_moles) 
{
	YAML_doc["SetGasCompMoles"] = gas_moles;
	YAML_doc["SetGasCompMoles"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLSetGasPhaseVolume(std::vector< double > gas_volume) 
{
	YAML_doc["SetGasPhaseVolume"] = gas_volume;
	YAML_doc["SetGasPhaseVolume"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLSetGridCellCount(int count)
{
	YAML_doc["SetGridCellCount"] = count;
	return;
}
void YAMLPhreeqcRM::YAMLSetNthSelectedOutput(int n)
{
	YAML_doc["SetNthSelectedOutput"] = n;
	return;
}
void YAMLPhreeqcRM::YAMLSetPartitionUZSolids(bool tf)  
{
	YAML_doc["SetPartitionUZSolids"] = tf;
	return;
};
void YAMLPhreeqcRM::YAMLSetPorosity(std::vector< double > por) 
{
	YAML_doc["SetPorosity"] = por;
	YAML_doc["SetPorosity"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLSetPressure(std::vector< double > p) 
{
	YAML_doc["SetPressure"] = p;
	YAML_doc["SetPressure"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLSetPrintChemistryMask(std::vector< int > cell_mask) 
{
	YAML_doc["SetPrintChemistryMask"] = cell_mask;
	YAML_doc["SetPrintChemistryMask"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLSetPrintChemistryOn(bool workers, bool initial_phreeqc, bool utility) 
{
	YAML::Node node;
	node["workers"] = workers;
	node["initial_phreeqc"] = initial_phreeqc;
	node["utility"] = utility;
	YAML_doc["SetPrintChemistryOn"] = node;
	YAML_doc["SetPrintChemistryOn"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLSetRebalanceByCell(bool tf) 
{
	YAML_doc["SetRebalanceByCell"] = tf;
	return;
};
void YAMLPhreeqcRM::YAMLSetRebalanceFraction(double f) 
{
	YAML_doc["SetRebalanceFraction"] = f;
	return;
}
void YAMLPhreeqcRM::YAMLSetRepresentativeVolume(std::vector< double > rv) 
{
	YAML_doc["SetRepresentativeVolume"] = rv;
	YAML_doc["SetRepresentativeVolume"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLSetSaturation(std::vector< double > sat) 
{
	YAML_doc["SetSaturation"] = sat;
	YAML_doc["SetSaturation"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLSetScreenOn(bool tf) 
{
	YAML_doc["SetScreenOn"] = tf;
	return;
}
void YAMLPhreeqcRM::YAMLSetSelectedOutputOn(bool tf) 
{
	YAML_doc["SetSelectedOutputOn"] = tf;
	return;
}
void YAMLPhreeqcRM::YAMLSetSpeciesSaveOn(bool save_on) 
{
	YAML_doc["SetSpeciesSaveOn"] = save_on;
	return;
}
void YAMLPhreeqcRM::YAMLSetTemperature(std::vector< double > t)
{
	YAML_doc["SetTemperature"] = t;
	YAML_doc["SetTemperature"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLSetTime(double time)
{
	YAML_doc["SetTime"] = time;
	return;
}
void YAMLPhreeqcRM::YAMLSetTimeConversion(double conv_factor)
{
	YAML_doc["SetTimeConversion"] = conv_factor;
	return;
}
void YAMLPhreeqcRM::YAMLSetTimeStep(double time_step)
{
	YAML_doc["SetTimeStep"] = time_step;
	return;
}
void YAMLPhreeqcRM::YAMLSetUnitsExchange(int option)
{
	YAML_doc["SetUnitsExchange"] = option;
	return;
};
void YAMLPhreeqcRM::YAMLSetUnitsGasPhase(int option)
{
	YAML_doc["SetUnitsGasPhase"] = option;
	return;
};
void YAMLPhreeqcRM::YAMLSetUnitsKinetics(int option)
{
	YAML_doc["SetUnitsKinetics"] = option;
	return;
};
void YAMLPhreeqcRM::YAMLSetUnitsPPassemblage(int option)
{
	YAML_doc["SetUnitsPPassemblage"] = option;
	return;
};
void YAMLPhreeqcRM::YAMLSetUnitsSolution(int option)
{
	YAML_doc["SetUnitsSolution"] = option;
	return;
};
void YAMLPhreeqcRM::YAMLSetUnitsSSassemblage(int option)
{
	YAML_doc["SetUnitsSSassemblage"] = option;
	return;
};
void YAMLPhreeqcRM::YAMLSetUnitsSurface(int option)
{
	YAML_doc["SetUnitsSurface"] = option;
	return;
}
void YAMLPhreeqcRM::YAMLSpeciesConcentrations2Module(std::vector< double > species_conc) 
{
	YAML_doc["SpeciesConcentrations2Module"] = species_conc;
	YAML_doc["SpeciesConcentrations2Module"].SetStyle(YAML::EmitterStyle::Flow);
	return;
}
void YAMLPhreeqcRM::YAMLStateSave(int istate)
{
	YAML_doc["StateSave"] = istate;
	return;
}
void YAMLPhreeqcRM::YAMLStateApply(int istate)
{
	YAML_doc["StateApply"] = istate;
	return;
}
void YAMLPhreeqcRM::YAMLStateDelete(int istate)
{
	YAML_doc["StateDelete"] = istate;
	return;
}
void YAMLPhreeqcRM::YAMLThreadCount(int nthreads)
{
	YAML_doc["ThreadCount"] = nthreads;
	return;
}
void YAMLPhreeqcRM::YAMLUseSolutionDensityVolume(bool tf)  
{
	YAML_doc["UseSolutionDensityVolume"] = tf;
	return;
};
void YAMLPhreeqcRM::YAMLWarningMessage(std::string warnstr) 
{
	YAML_doc["WarningMessage"] = warnstr;
	return;
}
//
// helper functions
//
int
YAMLPhreeqcRMLib::CreateYAMLPhreeqcRM(void)
{
	int n = IRM_OUTOFMEMORY;
	YAMLPhreeqcRM* YAMLPhreeqcRMPtr;
	try
	{
		YAMLPhreeqcRMPtr = new YAMLPhreeqcRM;
		n = (int)YAMLPhreeqcRMPtr->Index;
	}
	catch (const std::bad_alloc&)
	{
		return IRM_OUTOFMEMORY;
	}
	return n;
}

IRM_RESULT
YAMLPhreeqcRMLib::DestroyYAMLPhreeqcRM(int id)
{
	IRM_RESULT retval = IRM_BADINSTANCE;
	if (id >= 0)
	{
		if (YAMLPhreeqcRM* ptr = YAMLPhreeqcRMLib::GetInstance(id))
		{
			delete ptr;
			retval = IRM_OK;
		}
	}
	return retval;
}

YAMLPhreeqcRM*
YAMLPhreeqcRMLib::GetInstance(int id)
{
	YAMLPhreeqcRM* instance = 0;
	YAMLPhreeqcRM::InstancesLock.lock();
	std::map<size_t, YAMLPhreeqcRM*>::iterator it = YAMLPhreeqcRM::Instances.find(size_t(id));
	if (it != YAMLPhreeqcRM::Instances.end())
	{
		instance = (*it).second;
	}
	YAMLPhreeqcRM::InstancesLock.unlock();
	return instance;
}
#endif