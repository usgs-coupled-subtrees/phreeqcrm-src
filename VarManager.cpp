#include "VarManager.h"
#include <assert.h>
#include <algorithm>
VarManager::VarManager(PhreeqcRM* rm_ptr_in) 
{
	this->VariantMap[VARS::ComponentCount] = 
		BMIVariant(&VarManager::ComponentCount_Var, "ComponentCount");
	this->VariantMap[VARS::Components] =
		BMIVariant(&VarManager::Components_Var, "Components");
	this->VariantMap[VARS::Concentrations] =
		BMIVariant(&VarManager::Concentrations_Var, "Concentrations");
	this->VariantMap[VARS::Density] =
		BMIVariant(&VarManager::Density_Var, "Density");
	this->VariantMap[VARS::ErrorString] =
		BMIVariant(&VarManager::ErrorString_Var, "ErrorString");
	this->VariantMap[VARS::FilePrefix] =
		BMIVariant(&VarManager::FilePrefix_Var, "FilePrefix");
	this->VariantMap[VARS::Gfw] =
		BMIVariant(&VarManager::Gfw_Var, "Gfw");
	this->VariantMap[VARS::GridCellCount] =
		BMIVariant(&VarManager::GridCellCount_Var, "GridCellCount");
	//this->VariantMap[VARS::InputVarNames] =
	//	BMIVariant(&VarManager::InputVarNames_Var, "InputVarNames");
	this->VariantMap[VARS::NthSelectedOutput] =
		BMIVariant(&VarManager::NthSelectedOutput_Var, "NthSelectedOutput");
	//this->VariantMap[VARS::OutputVarNames] =
	//	BMIVariant(&VarManager::OutputVarNames_Var, "OutputVarNames");
	this->VariantMap[VARS::Saturation] =
		BMIVariant(&VarManager::Saturation_Var, "Saturation");
	this->VariantMap[VARS::SelectedOutput] =
		BMIVariant(&VarManager::SelectedOutput_Var, "SelectedOutput");
	this->VariantMap[VARS::SelectedOutputColumnCount] =
		BMIVariant(&VarManager::SelectedOutputColumnCount_Var, "SelectedOutputColumnCount");
	this->VariantMap[VARS::SelectedOutputCount] =
		BMIVariant(&VarManager::SelectedOutputCount_Var, "SelectedOutputCount");
	this->VariantMap[VARS::SelectedOutputHeadings] =
		BMIVariant(&VarManager::SelectedOutputHeadings_Var, "SelectedOutputHeadings");
	this->VariantMap[VARS::SelectedOutputRowCount] =
		BMIVariant(&VarManager::SelectedOutputRowCount_Var, "SelectedOutputRowCount");
	this->VariantMap[VARS::SolutionVolume] =
		BMIVariant(&VarManager::SolutionVolume_Var, "SolutionVolume");
	this->VariantMap[VARS::Time] =
		BMIVariant(&VarManager::Time_Var, "Time");
#ifdef SKIP
	this->VariantMap[VARS::TimeStep] =
		BMIVariant(&VarManager::TimeStep_Var, "TimeStep");
	this->VariantMap[VARS::CurrentSelectedOutputUserNumber] =
		BMIVariant(&VarManager::CurrentSelectedOutputUserNumber_Var, "CurrentSelectedOutputUserNumber");
	this->VariantMap[VARS::Porosity] =
		BMIVariant(&VarManager::Porosity_Var, "Porosity");
	this->VariantMap[VARS::Pressure] =
		BMIVariant(&VarManager::Pressure_Var, "Pressure");
	this->VariantMap[VARS::SelectedOutputOn] =
		BMIVariant(&VarManager::SelectedOutputOn_Var, "SelectedOutputOn");
	this->VariantMap[VARS::Temperature] =
		BMIVariant(&VarManager::Temperature_Var, "Temperature");
#endif
	///!!!VarFunction x = &VarManager::ComponentCount_var;
	///!!! (this->*x)(rm_ptr); // Remember this !!!///
	//auto it = VariantMap.begin();
	//VarFunction x = it->second.GetFn();
	//(this->*x)();
	rm_ptr = rm_ptr_in;
	this->task = VarManager::VAR_TASKS::no_op;
	this->CurrentVar = VarManager::VARS::NotFound;
	//auto it = VarVariantMap.begin();
	//VarFunction x = it->second.GetFn(rm_ptr);
	//x(rm_ptr);
	// Make EnumMap
	for (auto it = VariantMap.begin(); it != VariantMap.end(); it++)
	{
		std::string name_lc = it->second.GetName();
		std::transform(name_lc.begin(), name_lc.end(), name_lc.begin(), tolower);
		EnumMap[name_lc] = it->first;
	}
}
void VarManager::RM2BMIUpdate(std::string name)
{
	if (this->PointerSet.size() == 0) return;
	VarManager::VARS v_enum = this->GetEnum(name);
	if (this->GetCurrentVar() != v_enum) return;
	auto it = this->VariantMap.find(v_enum);
	if (it != VariantMap.end())
	{
		this->task = VarManager::VAR_TASKS::RMUpdate;
		VarFunction f =  it->second.GetFn(); 
		(this->*f)();
	}
	return;
}
VarManager::VARS VarManager::GetEnum(const std::string name)
{
	std::string name_lc = name;
	std::transform(name_lc.begin(), name_lc.end(), name_lc.begin(), tolower);
	auto m_it = EnumMap.find(name_lc);
	if (m_it != EnumMap.end())
	{
		return m_it->second;
	}
	return VarManager::VARS::NotFound;
}
//// Start_var
void VarManager::ComponentCount_Var()
{
	this->SetCurrentVar(VarManager::VARS::ComponentCount);
	BMIVariant& bv = this->VariantMap[VarManager::VARS::ComponentCount];
	if (!bv.GetInitialized())
	{
		BMIVariant& bv = this->VariantMap[VarManager::VARS::ComponentCount];
		int Itemsize = (int)sizeof(int);
		int Nbytes = (int)sizeof(int);
		//std::string units, set, get, ptr, Nbytes, Itemsize
		bv.SetBasic("count", false, true, true, Nbytes, Itemsize);
		bv.SetTypes("int", "integer", "int");
		bv.SetIVar(rm_ptr->GetComponentCount());
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		int v = rm_ptr->GetComponentCount();
		bv.SetIVar(v);
		bv.SetVoidPtr((void*)(bv.GetIVarPtr()));
		this->PointerSet.insert(VarManager::VARS::ComponentCount);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	{
		int v = rm_ptr->GetComponentCount();
		bv.SetIVar(v);
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		assert(false);
		break;
	case VarManager::VAR_TASKS::RMUpdate:
	{
		assert(false);
		break;
	}	
	case VarManager::VAR_TASKS::UpdateState:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::no_op:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::Components_Var()
{
	this->SetCurrentVar(VarManager::VARS::Components);
	BMIVariant& bv = this->VariantMap[VarManager::VARS::Components];
	if (!bv.GetInitialized() || (this->task == VarManager::VAR_TASKS::Init))
	{
		std::vector<std::string> comps = rm_ptr->GetComponents();
		size_t size = 0;
		for (size_t i = 0; i < comps.size(); i++)
		{
			if (comps[i].size() > size) size = comps[i].size();
		}
		int Itemsize = (int)size;
		int Nbytes = (int)(size * comps.size());
		//name, std::string units, set, get, ptr, Nbytes, Itemsize
		bv.SetBasic("names", false, true, false, Nbytes, Itemsize);
		bv.SetTypes("std::vector<std::string>", "character(len=:),allocatable,dimension(:)", "");
		const std::vector<std::string>& v = rm_ptr->GetComponents();
		bv.SetStringVector(v);
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		std::vector<const char*> CharVector;
		std::vector<std::string>&  Components = bv.GetStringVectorRef();
		for (size_t i = 0; i < Components.size(); i++)
		{
			CharVector.push_back(Components[i].c_str());
		}
		bv.SetCharVector(CharVector);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	{
		const std::vector<std::string>& v = rm_ptr->GetComponents();
		this->VarExchange.SetStringVector(v);
		//bv.SetIVar(v);
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		assert(false);
		break;
	case VarManager::VAR_TASKS::RMUpdate:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::UpdateState:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::no_op:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::Concentrations_Var()
{
	this->SetCurrentVar(VarManager::VARS::Concentrations);
	BMIVariant& bv = this->VariantMap[VarManager::VARS::Concentrations];
	if (!bv.GetInitialized())
	{

		BMIVariant& bv = this->VariantMap[VarManager::VARS::Concentrations];
		int Itemsize = (int)sizeof(double);
		int Nbytes = (int)sizeof(double) *
			rm_ptr->GetGridCellCount() * rm_ptr->GetComponentCount();
		//name, std::string units, set, get, ptr, Nbytes, Itemsize
		int option = rm_ptr->GetUnitsSolution();
		std::string units;
		switch (option)
		{
		case 1:
			units = "mg/L";
			break;
		case 2:
			units = "mol/L";
			break;
		case 3:
			units = "kg/kgs";
			break;
		}
		bv.SetBasic(units, true, true, true, Nbytes, Itemsize);
		bv.SetTypes("double", "real(kind=8)", "");
		rm_ptr->GetConcentrations(bv.GetDoubleVectorRef());
		rm_ptr->GetConcentrations(this->VarExchange.GetDoubleVectorRef());
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		rm_ptr->GetConcentrations(this->VarExchange.GetDoubleVectorRef());
		bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		bv.SetVoidPtr((void*)(bv.GetDoubleVectorPtr()));
		this->PointerSet.insert(VarManager::VARS::Concentrations);
		this->UpdateSet.insert(VarManager::VARS::Concentrations);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	case VarManager::VAR_TASKS::UpdateState:
	case VarManager::VAR_TASKS::RMUpdate:
	{
		rm_ptr->GetConcentrations(this->VarExchange.GetDoubleVectorRef());
		bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		rm_ptr->SetConcentrations(this->VarExchange.GetDoubleVectorRef());
		bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		break;
	case VarManager::VAR_TASKS::no_op:
	case VarManager::VAR_TASKS::Info:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::Density_Var()
{
	this->SetCurrentVar(VarManager::VARS::Density);
	BMIVariant& bv = this->VariantMap[VarManager::VARS::Density];
	if (!bv.GetInitialized())
	{
		BMIVariant& bv = this->VariantMap[VarManager::VARS::Density];
		int Itemsize = sizeof(double);
		int Nbytes = Itemsize * rm_ptr->GetGridCellCount();
		//name, std::string units, set, get, ptr, Nbytes, Itemsize  
		bv.SetBasic("kg L-1", true, true, true, Nbytes, Itemsize);
		bv.SetTypes("double", "real(kind=8)", "");
		rm_ptr->GetDensity(this->VarExchange.GetDoubleVectorRef());
		rm_ptr->GetDensity(bv.GetDoubleVectorRef());
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		rm_ptr->GetDensity(this->VarExchange.GetDoubleVectorRef());
		bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		bv.SetVoidPtr((void*)(bv.GetDoubleVectorPtr()));
		this->PointerSet.insert(VarManager::VARS::Density);
		this->UpdateSet.insert(VarManager::VARS::Density);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	case VarManager::VAR_TASKS::UpdateState:
	case VarManager::VAR_TASKS::RMUpdate:
	{
		rm_ptr->GetDensity(this->VarExchange.GetDoubleVectorRef());
		bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		rm_ptr->SetDensity(this->VarExchange.GetDoubleVectorRef());
		// don't update density vector, only get solution densities
		//bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		break;
	case VarManager::VAR_TASKS::no_op:
	case VarManager::VAR_TASKS::Info:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::ErrorString_Var()
{
	this->SetCurrentVar(VarManager::VARS::ErrorString);
	BMIVariant& bv = this->VariantMap[VarManager::VARS::ErrorString];
	if (!bv.GetInitialized())
	{
		BMIVariant& bv = this->VariantMap[VarManager::VARS::ErrorString];
		int Itemsize = (int)rm_ptr->GetErrorString().size();
		int Nbytes = Itemsize;
		//name, std::string units, set, get, ptr, Nbytes, Itemsize  
		bv.SetBasic("error", false, true, false, Nbytes, Itemsize);
		bv.SetTypes("std::string", "character", "");
		this->VarExchange.GetStringRef() = rm_ptr->GetErrorString(); 
		bv.GetStringRef() = rm_ptr->GetErrorString();
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	case VarManager::VAR_TASKS::UpdateState:
	case VarManager::VAR_TASKS::RMUpdate:
	{
		this->VarExchange.GetStringRef() = rm_ptr->GetErrorString();
		bv.GetStringRef() = rm_ptr->GetErrorString();
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		assert(false);
		break;
	case VarManager::VAR_TASKS::no_op:
	case VarManager::VAR_TASKS::Info:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::FilePrefix_Var()
{
	this->SetCurrentVar(VarManager::VARS::FilePrefix);
	BMIVariant& bv = this->VariantMap[VarManager::VARS::FilePrefix];
	if (!bv.GetInitialized())
	{
		BMIVariant& bv = this->VariantMap[VarManager::VARS::FilePrefix];
		int Itemsize = (int)rm_ptr->GetFilePrefix().size();
		int Nbytes = Itemsize;
		//name, std::string units, set, get, ptr, Nbytes, Itemsize  
		bv.SetBasic("error", true, true, false, Nbytes, Itemsize);
		bv.SetTypes("std::string", "character", "");
		this->VarExchange.GetStringRef() = rm_ptr->GetFilePrefix();
		bv.GetStringRef() = rm_ptr->GetFilePrefix();
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	case VarManager::VAR_TASKS::UpdateState:
	case VarManager::VAR_TASKS::RMUpdate:
	{
		this->VarExchange.GetStringRef() = rm_ptr->GetFilePrefix();
		bv.GetStringRef() = rm_ptr->GetFilePrefix();
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		rm_ptr->SetFilePrefix(this->VarExchange.GetStringRef());
		bv.GetStringRef() = this->VarExchange.GetStringRef();
		break;
	case VarManager::VAR_TASKS::no_op:
	case VarManager::VAR_TASKS::Info:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::Gfw_Var()
{
	VarManager::VARS VARS_myself = VarManager::VARS::Gfw;
	this->SetCurrentVar(VarManager::VARS::Gfw);
	BMIVariant& bv = this->VariantMap[VARS_myself];
	if (!bv.GetInitialized())
	{
		//
		BMIVariant& bv = this->VariantMap[VARS_myself];
		int Itemsize = sizeof(double);
		int Nbytes = Itemsize * rm_ptr->GetComponentCount();
		//name, std::string units, set, get, ptr, Nbytes, Itemsize  
		bv.SetBasic("g mol-1", false, true, true, Nbytes, Itemsize);
		bv.SetTypes("double", "real(kind=8)", "");
		this->VarExchange.GetDoubleVectorRef() = rm_ptr->GetGfw();
		bv.GetDoubleVectorRef() = rm_ptr->GetGfw();
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		this->VarExchange.GetDoubleVectorRef() = rm_ptr->GetGfw();
		bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		bv.SetVoidPtr((void*)(bv.GetDoubleVectorPtr()));
		this->PointerSet.insert(VARS_myself);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	case VarManager::VAR_TASKS::UpdateState:
	case VarManager::VAR_TASKS::RMUpdate:
	{
		this->VarExchange.GetDoubleVectorRef() = rm_ptr->GetGfw();
		bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		assert(false);
		break;
	case VarManager::VAR_TASKS::no_op:
	case VarManager::VAR_TASKS::Info:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::GridCellCount_Var()
{
	VarManager::VARS VARS_myself = VarManager::VARS::GridCellCount;
	this->SetCurrentVar(VARS_myself);
	BMIVariant& bv = this->VariantMap[VARS_myself];
	if (!bv.GetInitialized())
	{
		BMIVariant& bv = this->VariantMap[VARS_myself];
		int Itemsize = (int)sizeof(int);
		int Nbytes = (int)sizeof(int);
		//std::string units, set, get, ptr, Nbytes, Itemsize
		bv.SetBasic("count", false, true, true, Nbytes, Itemsize);
		bv.SetTypes("int", "integer", "int");
		bv.SetIVar(rm_ptr->GetGridCellCount());
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		int v = rm_ptr->GetGridCellCount();
		bv.SetIVar(v);
		bv.SetVoidPtr((void*)(bv.GetIVarPtr()));
		this->PointerSet.insert(VARS_myself);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	{
		int v = rm_ptr->GetGridCellCount();
		bv.SetIVar(v);
		this->PointerSet.insert(VARS_myself);
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		assert(false);
		break;
	case VarManager::VAR_TASKS::RMUpdate:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::UpdateState:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::no_op:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
//
//void VarManager::InputVarNames_Var() // Implement in BRMPhreeqcRM TODO???
//
void VarManager::NthSelectedOutput_Var()
{
	VarManager::VARS VARS_myself = VarManager::VARS::NthSelectedOutput;
	this->SetCurrentVar(VARS_myself);
	BMIVariant& bv = this->VariantMap[VARS_myself];
	if (!bv.GetInitialized())
	{
		BMIVariant& bv = this->VariantMap[VARS_myself];
		int Itemsize = (int)sizeof(int);
		int Nbytes = (int)sizeof(int);
		//std::string units, set, get, ptr, Nbytes, Itemsize
		bv.SetBasic("id", true, false, false, Nbytes, Itemsize);
		bv.SetTypes("int", "integer", "int");
		bv.SetIVar(-1);
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	case VarManager::VAR_TASKS::GetVar:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
	{
		int v = *this->VarExchange.GetIVarPtr();
		rm_ptr->SetNthSelectedOutput(v);
		break;
	}
	case VarManager::VAR_TASKS::RMUpdate:
	case VarManager::VAR_TASKS::UpdateState:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::no_op:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
//
//void VarManager::OutputVarNames_Var() // Implement in BRMPhreeqcRM TODO???
//
void VarManager::Saturation_Var()
{
	VarManager::VARS VARS_myself = VarManager::VARS::Saturation;
	this->SetCurrentVar(VARS_myself);
	BMIVariant& bv = this->VariantMap[VARS_myself];
	if (!bv.GetInitialized())
	{
		BMIVariant& bv = this->VariantMap[VARS_myself];
		int Itemsize = sizeof(double);
		int Nbytes = Itemsize * rm_ptr->GetGridCellCount();
		//name, std::string units, set, get, ptr, Nbytes, Itemsize  
		bv.SetBasic("unitless", true, true, true, Nbytes, Itemsize);
		bv.SetTypes("double", "real(kind=8)", "");
		rm_ptr->GetSaturation(this->VarExchange.GetDoubleVectorRef());
		rm_ptr->GetSaturation(bv.GetDoubleVectorRef());
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		rm_ptr->GetSaturation(this->VarExchange.GetDoubleVectorRef());
		bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		bv.SetVoidPtr((void*)(bv.GetDoubleVectorPtr()));
		this->PointerSet.insert(VARS_myself);
		this->UpdateSet.insert(VARS_myself);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	case VarManager::VAR_TASKS::UpdateState:
	case VarManager::VAR_TASKS::RMUpdate:
	{
		rm_ptr->GetSaturation(this->VarExchange.GetDoubleVectorRef());
		bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		rm_ptr->SetSaturation(this->VarExchange.GetDoubleVectorRef());
		bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		break;
	case VarManager::VAR_TASKS::no_op:
	case VarManager::VAR_TASKS::Info:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::SelectedOutput_Var()
{
	VarManager::VARS VARS_myself = VarManager::VARS::SelectedOutput;
	this->SetCurrentVar(VARS_myself);
	BMIVariant& bv = this->VariantMap[VARS_myself];
	if (!bv.GetInitialized())
	{
		BMIVariant& bv = this->VariantMap[VARS_myself];
		int Itemsize = (int)sizeof(double);
		int Nbytes = Itemsize * rm_ptr->GetSelectedOutputRowCount() *
			rm_ptr->GetSelectedOutputColumnCount();
		//name, std::string units, set, get, ptr, Nbytes, Itemsize  
		bv.SetBasic("user specified", false, true, false, Nbytes, Itemsize);
		bv.SetTypes("double", "real(kind=8)", "");
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	{
		rm_ptr->GetSelectedOutput(this->VarExchange.GetDoubleVectorRef());
		rm_ptr->GetSelectedOutput(bv.GetDoubleVectorRef());
		break;
	}
	case VarManager::VAR_TASKS::UpdateState:
	case VarManager::VAR_TASKS::RMUpdate:
		assert(false);
		break;
	case VarManager::VAR_TASKS::SetVar:
		assert(false);
		break;
	case VarManager::VAR_TASKS::no_op:
	case VarManager::VAR_TASKS::Info:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::SelectedOutputCount_Var()
{
	VarManager::VARS VARS_myself = VarManager::VARS::SelectedOutputCount;
	this->SetCurrentVar(VARS_myself);
	BMIVariant& bv = this->VariantMap[VARS_myself];
	if (!bv.GetInitialized())
	{

		BMIVariant& bv = this->VariantMap[VARS_myself];
		int Itemsize = (int)sizeof(int);
		int Nbytes = (int)sizeof(int);
		//std::string units, set, get, ptr, Nbytes, Itemsize
		bv.SetBasic("count", false, true, false, Nbytes, Itemsize);
		bv.SetTypes("int", "integer", "int");
		bv.SetIVar(rm_ptr->GetSelectedOutputCount());
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	{
		int v = rm_ptr->GetSelectedOutputCount();
		bv.SetIVar(v);
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		assert(false);
		break;
	case VarManager::VAR_TASKS::RMUpdate:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::UpdateState:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::no_op:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::SelectedOutputHeadings_Var()
{
	VarManager::VARS VARS_myself = VarManager::VARS::SelectedOutputCount;
	this->SetCurrentVar(VARS_myself);
	BMIVariant& bv = this->VariantMap[VARS_myself];
	if (!bv.GetInitialized())
	{
		rm_ptr->GetSelectedOutputHeadings(bv.GetStringVectorRef());
		this->VarExchange.GetStringVectorRef() = bv.GetStringVectorRef();
		std::vector<std::string> headings = bv.GetStringVectorRef();
		size_t size = 0;
		for (size_t i = 0; i < headings.size(); i++)
		{
			if (headings[i].size() > size) size = headings[i].size();
		}
		int Itemsize = (int)size;
		int Nbytes = (int)(size * headings.size());
		//name, std::string units, set, get, ptr, Nbytes, Itemsize
		bv.SetBasic("names", false, true, false, Nbytes, Itemsize);
		bv.SetTypes("std::vector<std::string>", "character(len=:),allocatable,dimension(:)", "");
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		std::vector<const char*> CharVector;
		std::vector<std::string>& Components = bv.GetStringVectorRef();
		for (size_t i = 0; i < Components.size(); i++)
		{
			CharVector.push_back(Components[i].c_str());
		}
		bv.SetCharVector(CharVector);
		this->PointerSet.insert(VARS_myself);
		this->UpdateSet.insert(VARS_myself);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	{
		const std::vector<std::string>& v = rm_ptr->GetComponents();
		this->VarExchange.SetStringVector(v);
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		assert(false);
		break;
	case VarManager::VAR_TASKS::RMUpdate:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::UpdateState:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::no_op:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::SelectedOutputRowCount_Var()
{
	VarManager::VARS VARS_myself = VarManager::VARS::SelectedOutputRowCount;
	this->SetCurrentVar(VARS_myself);
	BMIVariant& bv = this->VariantMap[VARS_myself];
	if (!bv.GetInitialized())
	{
		BMIVariant& bv = this->VariantMap[VARS_myself];
		int Itemsize = (int)sizeof(int);
		int Nbytes = (int)sizeof(int);
		//std::string units, set, get, ptr, Nbytes, Itemsize
		bv.SetBasic("count", false, true, false, Nbytes, Itemsize);
		bv.SetTypes("int", "integer", "int");
		bv.SetIVar(rm_ptr->GetSelectedOutputRowCount());
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	{
		int v = rm_ptr->GetSelectedOutputRowCount();
		bv.SetIVar(v);
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		assert(false);
		break;
	case VarManager::VAR_TASKS::RMUpdate:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::UpdateState:
	{
		assert(false);
		break;
	}
	case VarManager::VAR_TASKS::no_op:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::SolutionVolume_Var()
{
	VarManager::VARS VARS_myself = VarManager::VARS::SolutionVolume;
	this->SetCurrentVar(VARS_myself);
	BMIVariant& bv = this->VariantMap[VARS_myself];
	if (!bv.GetInitialized())
	{
		BMIVariant& bv = this->VariantMap[VARS_myself];
		int Itemsize = sizeof(double);
		int Nbytes = Itemsize * rm_ptr->GetGridCellCount();
		//name, std::string units, set, get, ptr, Nbytes, Itemsize  
		bv.SetBasic("L", false, true, true, Nbytes, Itemsize);
		bv.SetTypes("double", "real(kind=8)", "");
		this->VarExchange.GetDoubleVectorRef() = rm_ptr->GetSolutionVolume();
		bv.GetDoubleVectorRef() = rm_ptr->GetSolutionVolume();
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		this->VarExchange.GetDoubleVectorRef() = rm_ptr->GetSolutionVolume();
		bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		bv.SetVoidPtr((void*)(bv.GetDoubleVectorPtr()));
		this->PointerSet.insert(VARS_myself);
		this->UpdateSet.insert(VARS_myself);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	case VarManager::VAR_TASKS::UpdateState:
	case VarManager::VAR_TASKS::RMUpdate:
	{
		this->VarExchange.GetDoubleVectorRef() = rm_ptr->GetSolutionVolume();
		bv.SetDoubleVector(this->VarExchange.GetDoubleVectorRef());
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		assert(false);
		break;
	case VarManager::VAR_TASKS::no_op:
	case VarManager::VAR_TASKS::Info:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
void VarManager::Time_Var()
{
	VarManager::VARS VARS_myself = VarManager::VARS::Time;
	this->SetCurrentVar(VARS_myself);
	BMIVariant& bv = this->VariantMap[VARS_myself];
	if (!bv.GetInitialized())
	{
		BMIVariant& bv = this->VariantMap[VARS_myself];
		int Itemsize = sizeof(double);
		int Nbytes = Itemsize;
		//name, std::string units, set, get, ptr, Nbytes, Itemsize  
		bv.SetBasic("s", true, true, true, Nbytes, Itemsize);
		bv.SetTypes("double", "real(kind=8)", "");
		this->VarExchange.SetDVar(rm_ptr->GetTime());
		bv.SetDVar(rm_ptr->GetTime());
		bv.SetInitialized(true);
	}
	switch (this->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		this->VarExchange.SetDVar(rm_ptr->GetTime());
		bv.SetDVar(rm_ptr->GetTime());
		bv.SetVoidPtr((void*)(bv.GetDVarPtr()));
		this->PointerSet.insert(VARS_myself);
		this->UpdateSet.insert(VARS_myself);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
	case VarManager::VAR_TASKS::UpdateState:
	case VarManager::VAR_TASKS::RMUpdate:
	{
		this->VarExchange.SetDVar(rm_ptr->GetTime());
		bv.SetDVar(rm_ptr->GetTime());
		break;
	}
	case VarManager::VAR_TASKS::SetVar:
		rm_ptr->SetTime(*this->VarExchange.GetDVarPtr());
		bv.SetDVar(*this->VarExchange.GetDVarPtr());
		break;
	case VarManager::VAR_TASKS::no_op:
	case VarManager::VAR_TASKS::Info:
		break;
	}
	this->VarExchange.CopyScalars(bv);
	this->SetCurrentVar(VarManager::VARS::NotFound);
}
/// end_
////////////////////////////////

#ifdef SKIP

void VarManager::TimeStep_var(PhreeqcRM* rm_ptr)
{
	static double TimeStep;
	//
	if (rm_ptr->task == VarManager::VAR_TASKS::Update)
	{
		TimeStep = rm_ptr->GetTimeStep();
		return;
	}
	int Itemsize = sizeof(double);
	int Nbytes = Itemsize;
	//name, std::string units, set, get, ptr, Nbytes, Itemsize  
	BMI_Var bv = BMI_Var("TimeStep", "s", true, true, true, Nbytes, Itemsize);
	bv.SetTypes("double", "real(kind=8)", "float");
	rm_ptr->bmi_variant.bmi_var = bv;
	switch (rm_ptr->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		TimeStep = rm_ptr->GetTimeStep();
		rm_ptr->bmi_variant.SetVoidPtr((void*)&TimeStep);
		rm_ptr->GetUpdateMap().insert("TimeStep");
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
		rm_ptr->bmi_variant.d_var = rm_ptr->GetTimeStep();
		break;
	case VarManager::VAR_TASKS::SetVar:
		TimeStep = rm_ptr->bmi_variant.d_var;
		rm_ptr->SetTimeStep(rm_ptr->bmi_variant.d_var);
		break;
	case VarManager::VAR_TASKS::Info:
		break;
	case VarManager::VAR_TASKS::no_op:
		break;
	}
}
void VarManager::CurrentSelectedOutputUserNumber_var(PhreeqcRM* rm_ptr)
{
	int Itemsize = (int)sizeof(int);
	int Nbytes = (int)sizeof(int);
	//name, std::string units, set, get, ptr, Nbytes, Itemsize
	BMI_Var bv = BMI_Var("CurrentSelectedOutputUserNumber", "id", false, true, false, Nbytes, Itemsize);
	bv.SetTypes("int", "integer", "int");
	rm_ptr->bmi_variant.bmi_var = bv;
	switch (rm_ptr->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
		rm_ptr->bmi_variant.NotImplemented = true;
		break;
	case VarManager::VAR_TASKS::GetVar:
		rm_ptr->bmi_variant.i_var = rm_ptr->GetCurrentSelectedOutputUserNumber();
		break;
	case VarManager::VAR_TASKS::SetVar:
		rm_ptr->bmi_variant.NotImplemented = true;
		break;
	case VarManager::VAR_TASKS::Info:
		break;
	case VarManager::VAR_TASKS::no_op:
		break;
	}
}
void VarManager::Porosity_var(PhreeqcRM* rm_ptr)
{
	static bool initialized = false;
	static std::vector<double> Porosity;
	// 
	if (rm_ptr->task == VarManager::VAR_TASKS::Update)
	{
		rm_ptr->bmi_variant.DoubleVector = rm_ptr->GetPorosity();
		assert(Porosity.size() == rm_ptr->bmi_variant.DoubleVector.size());
		memcpy(Porosity.data(),
			rm_ptr->bmi_variant.DoubleVector.data(),
			Porosity.size() * sizeof(double));
		return;
	}
	//
	int Itemsize = sizeof(double);
	int Nbytes = Itemsize * rm_ptr->GetGridCellCount();
	//name, std::string units, set, get, ptr, Nbytes, Itemsize  
	BMI_Var bv = BMI_Var("Porosity", "unitless", true, true, true, Nbytes, Itemsize);
	bv.SetTypes("double", "real(kind=8)", "");
	rm_ptr->bmi_variant.bmi_var = bv;
	switch (rm_ptr->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		if (!initialized)
		{
			Porosity = rm_ptr->GetPorosity();
			initialized = true;
			rm_ptr->GetUpdateMap().insert("Porosity");
		}
		rm_ptr->bmi_variant.SetVoidPtr((void*)Porosity.data());
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
		rm_ptr->bmi_variant.DoubleVector = rm_ptr->GetPorosity();
		break;
	case VarManager::VAR_TASKS::SetVar:
		if (initialized)
		{
			assert(Porosity.size() == rm_ptr->bmi_variant.DoubleVector.size());
			memcpy(Porosity.data(),
				rm_ptr->bmi_variant.DoubleVector.data(),
				Nbytes);
		}
		rm_ptr->SetPorosity(rm_ptr->bmi_variant.DoubleVector);
		break;
	case VarManager::VAR_TASKS::Info:
		break;
	case VarManager::VAR_TASKS::no_op:
		break;
	}
}
void VarManager::Pressure_var(PhreeqcRM* rm_ptr)
{
	static bool initialized = false;
	static std::vector<double> Pressure;
	// 
	if (rm_ptr->task == VarManager::VAR_TASKS::Update)
	{
		rm_ptr->bmi_variant.DoubleVector = rm_ptr->GetPressure();
		assert(Pressure.size() == rm_ptr->bmi_variant.DoubleVector.size());
		memcpy(Pressure.data(),
			rm_ptr->bmi_variant.DoubleVector.data(),
			Pressure.size() * sizeof(double));
		return;
	}
	int Itemsize = sizeof(double);
	int Nbytes = Itemsize * rm_ptr->GetGridCellCount();
	//name, std::string units, set, get, ptr, Nbytes, Itemsize  
	BMI_Var bv = BMI_Var("Pressure", "atm", true, true, true, Nbytes, Itemsize);
	bv.SetTypes("double", "real(kind=8)", "");
	rm_ptr->bmi_variant.bmi_var = bv;
	switch (rm_ptr->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		if (!initialized)
		{
			Pressure = rm_ptr->GetPressure();
			initialized = true;
			rm_ptr->GetUpdateMap().insert("Pressure");
		}
		rm_ptr->bmi_variant.SetVoidPtr((void*)Pressure.data());
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
		rm_ptr->bmi_variant.DoubleVector = rm_ptr->GetPressure();
		break;
	case VarManager::VAR_TASKS::SetVar:
		if (initialized)
		{
			assert(Pressure.size() == rm_ptr->bmi_variant.DoubleVector.size());
			memcpy(Pressure.data(),
				rm_ptr->bmi_variant.DoubleVector.data(),
				Pressure.size() * sizeof(double));
		}
		rm_ptr->SetPressure(rm_ptr->bmi_variant.DoubleVector);
		break;
	case VarManager::VAR_TASKS::Info:
		break;
	case VarManager::VAR_TASKS::no_op:
		break;
	}
}
void VarManager::SelectedOutputOn_var(PhreeqcRM* rm_ptr)
{
	static bool SelectedOutputOn;
	//
	//
	if (rm_ptr->task == VarManager::VAR_TASKS::Update)
	{
		SelectedOutputOn = rm_ptr->GetSelectedOutputOn();
		return;
	}
	int Itemsize = (int)sizeof(int);
	int Nbytes = (int)sizeof(int);
	//name, std::string units, set, get, ptr, Nbytes, Itemsize
	BMI_Var bv = BMI_Var("SelectedOutputOn", "bool", true, true, true, Nbytes, Itemsize);
	bv.SetTypes("bool", "logical", "");
	rm_ptr->bmi_variant.bmi_var = bv;
	switch (rm_ptr->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		SelectedOutputOn = rm_ptr->GetSelectedOutputOn();
		rm_ptr->bmi_variant.SetVoidPtr((void*)&SelectedOutputOn);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
		rm_ptr->bmi_variant.b_var = rm_ptr->GetSelectedOutputOn();
		break;
	case VarManager::VAR_TASKS::SetVar:
		SelectedOutputOn = rm_ptr->bmi_variant.b_var;
		rm_ptr->SetSelectedOutputOn(rm_ptr->bmi_variant.b_var);
		break;
	case VarManager::VAR_TASKS::Info:
		break;
	case VarManager::VAR_TASKS::no_op:
		break;
	}
}
void VarManager::Temperature_var(PhreeqcRM* rm_ptr)
{
	static bool initialized = false;
	static std::vector<double> Temperature;
	// 
	if (rm_ptr->task == VarManager::VAR_TASKS::Update)
	{
		rm_ptr->bmi_variant.DoubleVector = rm_ptr->GetTemperature();
		assert(Temperature.size() == rm_ptr->bmi_variant.DoubleVector.size());
		memcpy(Temperature.data(),
			rm_ptr->bmi_variant.DoubleVector.data(),
			Temperature.size() * sizeof(double));
		return;
	}
	//
	int Itemsize = sizeof(double);
	int Nbytes = Itemsize * rm_ptr->GetGridCellCount();
	//name, std::string units, set, get, ptr, Nbytes, Itemsize  
	BMI_Var bv = BMI_Var("Temperature", "C", true, true, true, Nbytes, Itemsize);
	bv.SetTypes("double", "real(kind=8)", "");
	rm_ptr->bmi_variant.bmi_var = bv;
	switch (rm_ptr->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		if (!initialized)
		{
			Temperature = rm_ptr->GetTemperature();
			initialized = true;
			rm_ptr->GetUpdateMap().insert("Temperature");
		}
		rm_ptr->bmi_variant.SetVoidPtr((void*)Temperature.data());
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
		rm_ptr->bmi_variant.DoubleVector = rm_ptr->GetTemperature();
		break;
	case VarManager::VAR_TASKS::SetVar:
		if (initialized)
		{
			assert(Temperature.size() == rm_ptr->bmi_variant.DoubleVector.size());
			memcpy(Temperature.data(),
				rm_ptr->bmi_variant.DoubleVector.data(),
				Temperature.size() * sizeof(double));
		}
		rm_ptr->SetTemperature(rm_ptr->bmi_variant.DoubleVector);
		break;
	case VarManager::VAR_TASKS::Info:
		break;
	case VarManager::VAR_TASKS::no_op:
		break;
	}
}
void VarManager::InputVarNames_var(PhreeqcRM* rm_ptr)
{
	static bool initialized = false;
	static std::vector<std::string> InputVarNames;
	static std::vector<const char*> CharVector;
	//
	PhreeqcRM::BMI_TASKS task_save = rm_ptr->task;
	std::vector<std::string> names = rm_ptr->GetInputVarNames();
	rm_ptr->task = task_save;
	size_t size = 0;
	for (size_t i = 0; i < names.size(); i++)
	{
		if (names[i].size() > size) size = names[i].size();
	}
	int Itemsize = (int)size;
	int Nbytes = (int)(size * names.size());
	//name, std::string units, set, get, ptr, Nbytes, Itemsize
	BMI_Var bv = BMI_Var("InputVarNames", "names", false, true, false, Nbytes, Itemsize);
	bv.SetTypes("std::vector<std::string>", "character(len=:),allocatable,dimension(:)", "");
	rm_ptr->bmi_variant.bmi_var = bv;
	switch (rm_ptr->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		if (!initialized)
		{
			InputVarNames = rm_ptr->GetInputVarNames();
			initialized = true;
			for (size_t i = 0; i < InputVarNames.size(); i++)
			{
				CharVector.push_back(InputVarNames[i].c_str());
			}
		}
		rm_ptr->bmi_variant.SetCharVector(CharVector);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
		rm_ptr->bmi_variant.StringVector = rm_ptr->GetInputVarNames();
		rm_ptr->bmi_variant.bmi_var = bv;
		break;
	case VarManager::VAR_TASKS::SetVar:
		rm_ptr->bmi_variant.NotImplemented = true;
		break;
	case VarManager::VAR_TASKS::Info:
		break;
	case VarManager::VAR_TASKS::no_op:
		break;
	}
}
void VarManager::OutputVarNames_var(PhreeqcRM* rm_ptr)
{
	static bool initialized = false;
	static std::vector<std::string> OutputVarNames;
	static std::vector<const char*> CharVector;
	//
	PhreeqcRM::BMI_TASKS task_save = rm_ptr->task;
	std::vector<std::string> names = rm_ptr->GetOutputVarNames();
	rm_ptr->task = task_save;
	size_t size = 0;
	for (size_t i = 0; i < names.size(); i++)
	{
		if (names[i].size() > size) size = names[i].size();
	}
	int Itemsize = (int)size;
	int Nbytes = (int)(size * names.size());
	//name, std::string units, set, get, ptr, Nbytes, Itemsize
	BMI_Var bv = BMI_Var("OutputVarNames", "names", false, true, false, Nbytes, Itemsize);
	bv.SetTypes("std::vector<std::string>", "character(len=:),allocatable,dimension(:)", "");
	rm_ptr->bmi_variant.bmi_var = bv;
	switch (rm_ptr->task)
	{
	case VarManager::VAR_TASKS::GetPtr:
	{
		if (!initialized)
		{
			OutputVarNames = rm_ptr->GetOutputVarNames();
			initialized = true;
			for (size_t i = 0; i < OutputVarNames.size(); i++)
			{
				CharVector.push_back(OutputVarNames[i].c_str());
			}
		}
		rm_ptr->bmi_variant.SetCharVector(CharVector);
		break;
	}
	case VarManager::VAR_TASKS::GetVar:
		rm_ptr->bmi_variant.StringVector = rm_ptr->GetOutputVarNames();
		rm_ptr->bmi_variant.bmi_var = bv;
		break;
	case VarManager::VAR_TASKS::SetVar:
		rm_ptr->bmi_variant.NotImplemented = true;
		break;
	case VarManager::VAR_TASKS::Info:
		break;
	case VarManager::VAR_TASKS::no_op:
		break;
	}
}
#endif


//////////////////