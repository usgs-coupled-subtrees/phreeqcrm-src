#if !defined(VARMANAGER_H_INCLUDED)
#define VARMANAGER_H_INCLUDED
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <assert.h>
#include "PhreeqcRM.h"
#include "RMVARS.h"
//class PhreeqcRM;
#include "BMI_Var.h"


class IRM_DLL_EXPORT VarManager
{
public:
	enum class VAR_TASKS {
		RMUpdate,
		Update,
		GetPtr,  
		GetVar,
		SetVar,
		//Init,
		Info,
		no_op
	};
	//enum class RMVARS {
	//	NotFound,
	//	ComponentCount,
	//	Components,
	//	Concentrations,
	//	Density,
	//	ErrorString,
	//	FilePrefix,
	//	Gfw,
	//	GridCellCount,
	//	InputVarNames,
	//	NthSelectedOutput,
	//	OutputVarNames,
	//	Saturation,
	//	SelectedOutput,
	//	SelectedOutputColumnCount,
	//	SelectedOutputCount,
	//	SelectedOutputHeadings,
	//	SelectedOutputRowCount,
	//	SolutionVolume,
	//	Time,
	//	TimeStep,
	//	CurrentSelectedOutputUserNumber,
	//	Porosity,
	//	Pressure,
	//	SelectedOutputOn,
	//	Temperature
	//};
	// Constructor
	VarManager(PhreeqcRM* rm_ptr);
	// Data
	PhreeqcRM* rm_ptr;
public:
	BMIVariant VarExchange;
	std::set<RMVARS> PointerSet;
	std::set<RMVARS> UpdateSet;
	RMVARS CurrentVar;
	std::map < std::string, RMVARS> EnumMap;
	VAR_TASKS task;
	std::map<RMVARS, BMIVariant> VariantMap;
	// Methods
	RMVARS GetEnum(std::string name);
	void RM2BMIUpdate(RMVARS v_enum);


	RMVARS GetCurrentVar() { return this->CurrentVar; }
	std::map<RMVARS, BMIVariant> & GetVariantMap() { return this->VariantMap; }
	void SetCurrentVar(RMVARS v) { this->CurrentVar = v; }
	// Function pointer definition
	typedef void (VarManager::* VarFunction)(void);
	void ExecFn(RMVARS v_enum) {
		VarFunction f = this->GetFn(v_enum);
		((*this).*f)();
	}
	//!typedef void (VarManager::* VarFunction)(PhreeqcRM* rm_ptr);
	//typedef VarManager* (*NewDogFunction)(void);
	//typedef void (VarManager::* VarFunction)(PhreeqcRM* rm_ptr); // function pointer type
	//typedef std::map<std::string, VarFunction> VarFunction_map;
	//VarFunction_map FnMap;
	//void test() { VarFunction x = VarManager::Concentrations_var; 
	//VarVariant vv;
	//vv.SetFn(VarFux);
	VarFunction GetFn(RMVARS v_enum);
	// Var functions
	void ComponentCount_Var();
	void Components_Var();
	void Concentrations_Var();
	void Density_Var();
	void ErrorString_Var();
	void FilePrefix_Var();
	void Gfw_Var();
	void GridCellCount_Var();
	//void InputVarNames_Var();
	void NthSelectedOutput_Var();
	//void OutputVarNames_Var();
	void Saturation_Var();
	void SelectedOutput_Var();
	void SelectedOutputColumnCount_Var();
	void SelectedOutputCount_Var();
	void SelectedOutputHeadings_Var();
	void SelectedOutputRowCount_Var();
	void SolutionVolume_Var();
	void Time_Var();
	void TimeStep_Var();
	void CurrentSelectedOutputUserNumber_Var();
	void Porosity_Var();
	void Pressure_Var();
	void SelectedOutputOn_Var();
	void Temperature_Var();
};
#endif

