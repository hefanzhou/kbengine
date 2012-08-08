/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2012 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "datatype.hpp"
#include "datatypes.hpp"
#include "fixeddict.hpp"
#include "array.hpp"
#include "pyscript/vector2.hpp"
#include "pyscript/vector3.hpp"
#include "pyscript/vector4.hpp"
	
namespace KBEngine{

//-------------------------------------------------------------------------------------
DataType::DataType()
{
}

//-------------------------------------------------------------------------------------
DataType::~DataType()
{
}

//-------------------------------------------------------------------------------------
bool DataType::initialize(XmlPlus* xmlplus, TiXmlNode* node)
{
	return true;
}

//-------------------------------------------------------------------------------------
UInt64Type::UInt64Type()
{
}

//-------------------------------------------------------------------------------------
UInt64Type::~UInt64Type()
{
}

//-------------------------------------------------------------------------------------
bool UInt64Type::isSameType(PyObject* pyValue)
{
	if (!PyLong_Check(pyValue))
		return false;

	PyLong_AsUnsignedLongLong(pyValue);
	if (!PyErr_Occurred()) 
		return true;
	
	PyErr_Clear();
	OUT_TYPE_ERROR("UINT64");
	return false;
}

//-------------------------------------------------------------------------------------
PyObject* UInt64Type::createObject(MemoryStream* defaultVal)
{
	uint64 val = 0;
	if(defaultVal)
		(*defaultVal) >> val;	
	return PyLong_FromUnsignedLongLong(val);
}

//-------------------------------------------------------------------------------------
MemoryStream* UInt64Type::parseDefaultStr(std::string defaultVal)
{
	MemoryStream* bs = NULL;
	if(!defaultVal.empty())
	{
		std::stringstream stream;
		stream << defaultVal;
		uint64 val = 0;
		stream >> val;
		bs = new MemoryStream();
		(*bs) << val;
	}

	return bs;
}

//-------------------------------------------------------------------------------------
void UInt64Type::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	uint64 udata = static_cast<uint64>(PyLong_AsUnsignedLongLong(pyValue));
	(*mstream) << udata;
}

//-------------------------------------------------------------------------------------
PyObject* UInt64Type::createFromStream(MemoryStream* mstream)
{
	return createObject(mstream);
}

//-------------------------------------------------------------------------------------
UInt32Type::UInt32Type()
{
}

//-------------------------------------------------------------------------------------
UInt32Type::~UInt32Type()
{
}

//-------------------------------------------------------------------------------------
bool UInt32Type::isSameType(PyObject* pyValue)
{
	if (!PyLong_Check(pyValue))
		return false;

	PyLong_AsUnsignedLong(pyValue);
	if (!PyErr_Occurred()) 
		return true;
	
	PyErr_Clear();
	OUT_TYPE_ERROR("UINT32");
	return false;
}

//-------------------------------------------------------------------------------------
PyObject* UInt32Type::createObject(MemoryStream* defaultVal)
{
	uint32 val = 0;
	if(defaultVal)
		(*defaultVal) >> val;	
	return PyLong_FromUnsignedLong(val);
}

//-------------------------------------------------------------------------------------
MemoryStream* UInt32Type::parseDefaultStr(std::string defaultVal)
{
	MemoryStream* bs = NULL;
	if(!defaultVal.empty())
	{
		std::stringstream stream;
		stream << defaultVal;
		uint32 val = 0;
		stream >> val;
		bs = new MemoryStream();
		(*bs) << val;
	}

	return bs;
}

//-------------------------------------------------------------------------------------
void UInt32Type::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	uint32 v = PyLong_AsUnsignedLong(pyValue);
	(*mstream) << v;
}

//-------------------------------------------------------------------------------------
PyObject* UInt32Type::createFromStream(MemoryStream* mstream)
{
	return createObject(mstream);
}

//-------------------------------------------------------------------------------------
Int64Type::Int64Type()
{
}

//-------------------------------------------------------------------------------------
Int64Type::~Int64Type()
{
}

//-------------------------------------------------------------------------------------
bool Int64Type::isSameType(PyObject* pyValue)
{
	if(!PyLong_Check(pyValue))
		return false;

	PyLong_AsLongLong(pyValue);
	if (!PyErr_Occurred()) 
		return true;

	PyErr_Clear();
	OUT_TYPE_ERROR("INT64");
	return false;
}

//-------------------------------------------------------------------------------------
PyObject* Int64Type::createObject(MemoryStream* defaultVal)
{
	int64 val = 0;
	if(defaultVal)
		(*defaultVal) >> val;	
	return PyLong_FromLongLong(val);
}

//-------------------------------------------------------------------------------------
MemoryStream* Int64Type::parseDefaultStr(std::string defaultVal)
{
	MemoryStream* bs = NULL;
	if(!defaultVal.empty())
	{
		std::stringstream stream;
		stream << defaultVal;
		int64 val = 0;
		stream >> val;
		bs = new MemoryStream();
		(*bs) << val;
	}

	return bs;
}

//-------------------------------------------------------------------------------------
void Int64Type::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	int64 v = PyLong_AsLongLong(pyValue);
	(*mstream) << v;
}

//-------------------------------------------------------------------------------------
PyObject* Int64Type::createFromStream(MemoryStream* mstream)
{
	return createObject(mstream);
}

//-------------------------------------------------------------------------------------
FloatType::FloatType()
{
}

//-------------------------------------------------------------------------------------
FloatType::~FloatType()
{
}

//-------------------------------------------------------------------------------------
bool FloatType::isSameType(PyObject* pyValue)
{
	bool ret = PyFloat_Check(pyValue);
	if(!ret)
		OUT_TYPE_ERROR("FLOAT");
	return ret;
}

//-------------------------------------------------------------------------------------
PyObject* FloatType::createObject(MemoryStream* defaultVal)
{
	double val = 0.0;
	if(defaultVal)
		(*defaultVal) >> val;	
	return PyFloat_FromDouble(val);
}

//-------------------------------------------------------------------------------------
MemoryStream* FloatType::parseDefaultStr(std::string defaultVal)
{
	MemoryStream* bs = NULL;
	if(!defaultVal.empty())
	{
		std::stringstream stream;
		stream << defaultVal;
		double val = 0;
		stream >> val;
		bs = new MemoryStream();
		(*bs) << val;
	}

	return bs;
}

//-------------------------------------------------------------------------------------
void FloatType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	(*mstream) << PyFloat_AsDouble(pyValue);
}

//-------------------------------------------------------------------------------------
PyObject* FloatType::createFromStream(MemoryStream* mstream)
{
	return createObject(mstream);
}

//-------------------------------------------------------------------------------------
VectorType::VectorType(int elemCount):elemCount_(elemCount)
{
}

//-------------------------------------------------------------------------------------
VectorType::~VectorType()
{
}

//-------------------------------------------------------------------------------------
bool VectorType::isSameType(PyObject* pyValue)
{
	if(!PySequence_Check(pyValue) || PySequence_Size(pyValue) != elemCount_)
	{
		PyErr_Format(PyExc_TypeError, "must be set to a VECTOR%d type.", elemCount_);
		PyErr_PrintEx(0);
		return false;
	}
	
	return true;
}

//-------------------------------------------------------------------------------------
PyObject* VectorType::createObject(MemoryStream* defaultVal)
{
	float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
	switch(elemCount_)
	{
		case 2:
			if(defaultVal)
				(*defaultVal) >> x >> y;	
			return new script::ScriptVector2(x, y);
		case 3:
			if(defaultVal)
				(*defaultVal) >> x >> y >> z;	
			return new script::ScriptVector3(x, y, z);
		case 4:
			if(defaultVal)
				(*defaultVal) >> x >> y >> z >> w;	
			return new script::ScriptVector4(x, y, z, w);
	}
	
	return NULL;
}

//-------------------------------------------------------------------------------------
MemoryStream* VectorType::parseDefaultStr(std::string defaultVal)
{
	MemoryStream* bs = NULL;
	if(!defaultVal.empty())
	{
		std::stringstream stream;
		stream << defaultVal;
		float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
		bs = new MemoryStream();
		switch(elemCount_)
		{
			case 2:
				stream >> x >> y;
				(*bs) << x << y;
				break;
			case 3:
				stream >> x >> y >> z;
				(*bs) << x << y << z;
				break;
			case 4:
				stream >> x >> y >> z >> w;
				(*bs) << x << y << z << w;
				break;
		}
	}

	return bs;
}

//-------------------------------------------------------------------------------------
void VectorType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	for(int index=0; index<elemCount_; index++)
	{
		PyObject* pyVal = PySequence_GetItem(pyValue, index);
		float v = (float)PyFloat_AsDouble(pyVal);
		(*mstream) << v;
		Py_DECREF(pyVal);
	}
}

//-------------------------------------------------------------------------------------
PyObject* VectorType::createFromStream(MemoryStream* mstream)
{
	return createObject(mstream);
}

//-------------------------------------------------------------------------------------
StringType::StringType()
{
}

//-------------------------------------------------------------------------------------
StringType::~StringType()
{
}

//-------------------------------------------------------------------------------------
bool StringType::isSameType(PyObject* pyValue)
{
	bool ret = PyUnicode_Check(pyValue);
	if(!ret)
		OUT_TYPE_ERROR("STRING");
	return ret;
}

//-------------------------------------------------------------------------------------
PyObject* StringType::createObject(MemoryStream* defaultVal)
{
	std::string val = "";
	if(defaultVal)
		(*defaultVal) >> val;	
	return PyUnicode_FromString(val.c_str());
}

//-------------------------------------------------------------------------------------
MemoryStream* StringType::parseDefaultStr(std::string defaultVal)
{
	MemoryStream* bs = NULL;
	if(!defaultVal.empty())
	{
		bs = new MemoryStream(defaultVal.size());
		(*bs) << defaultVal;
	}

	return bs;
}

//-------------------------------------------------------------------------------------
void StringType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	//(*mstream) << PyUnicode_AsUnicode(pyValue);
}

//-------------------------------------------------------------------------------------
PyObject* StringType::createFromStream(MemoryStream* mstream)
{
	return createObject(mstream);
}

//-------------------------------------------------------------------------------------
PythonType::PythonType()
{
}

//-------------------------------------------------------------------------------------
PythonType::~PythonType()
{
}

//-------------------------------------------------------------------------------------
bool PythonType::isSameType(PyObject* pyValue)
{
	bool ret = script::Pickler::pickle(pyValue).empty();
	if(ret)
		OUT_TYPE_ERROR("PYTHON");
	return !ret;
}

//-------------------------------------------------------------------------------------
PyObject* PythonType::createObject(MemoryStream* defaultVal)
{
	std::string val = "";
	if(defaultVal)
	{
		(*defaultVal) >> val;
	
		PyObject* module = PyImport_AddModule("__main__");
		if(module == NULL)
		{
			PyErr_SetString(PyExc_SystemError, "PythonType::createObject:PyImport_AddModule __main__ is error!");
			S_Return;
		}

		PyObject* mdict = PyModule_GetDict(module);
		return PyRun_String(const_cast<char*>(val.c_str()), Py_eval_input, mdict, mdict);
	}
		
	S_Return;
}

//-------------------------------------------------------------------------------------
MemoryStream* PythonType::parseDefaultStr(std::string defaultVal)
{
	MemoryStream* bs = NULL;
	if(!defaultVal.empty())
	{
		bs = new MemoryStream(defaultVal.size());
		(*bs) << defaultVal;
	}

	return bs;
}

//-------------------------------------------------------------------------------------
void PythonType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	std::string sdata = script::Pickler::pickle(pyValue);
	uint32 length = sdata.length();
	(*mstream) << length;
	mstream->append(sdata.c_str(), length);
}

//-------------------------------------------------------------------------------------
PyObject* PythonType::createFromStream(MemoryStream* mstream)
{
	std::string val = "";
	uint8* udata = NULL;
	uint32 udataLen = 0;

	(*mstream) >> udataLen;
	udata = new uint8[udataLen + 1];
	mstream->read(udata, udataLen);
	val.assign((char*)udata, udataLen);
	SAFE_RELEASE(udata);
	return script::Pickler::unpickle(val);
}

//-------------------------------------------------------------------------------------
MailboxType::MailboxType()
{
}

//-------------------------------------------------------------------------------------
MailboxType::~MailboxType()
{
}

//-------------------------------------------------------------------------------------
bool MailboxType::isSameType(PyObject* pyValue)
{
	bool ret = script::Pickler::pickle(pyValue).empty();
	if(ret)
		OUT_TYPE_ERROR("MAILBOX");
	return !ret;
}

//-------------------------------------------------------------------------------------
PyObject* MailboxType::createObject(MemoryStream* defaultVal)
{
	S_Return;
}

//-------------------------------------------------------------------------------------
MemoryStream* MailboxType::parseDefaultStr(std::string defaultVal)
{
	return NULL;
}

//-------------------------------------------------------------------------------------
void MailboxType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	std::string s = script::Pickler::pickle(pyValue);
	if(!s.empty())
		(*mstream) << s;
}

//-------------------------------------------------------------------------------------
PyObject* MailboxType::createFromStream(MemoryStream* mstream)
{
	std::string val = "";
	if(mstream)
		(*mstream) >> val;
	else
		S_Return;	
	return script::Pickler::unpickle(val);
}

//-------------------------------------------------------------------------------------
ArrayType::ArrayType()
{
}

//-------------------------------------------------------------------------------------
ArrayType::~ArrayType()
{
	dataType_->decRef();
}

//-------------------------------------------------------------------------------------
bool ArrayType::initialize(XmlPlus* xmlplus, TiXmlNode* node)
{
	TiXmlNode* arrayNode = xmlplus->enterNode(node, "of");
	std::string strType = xmlplus->getValStr(arrayNode);
	std::transform(strType.begin(), strType.end(), strType.begin(), toupper);										// 转换为大写

	if(strType == "ARRAY")
	{
		ArrayType* dataType = new ArrayType();
		if(dataType->initialize(xmlplus, arrayNode)){
			dataType_ = dataType;
			dataType_->incRef();
		}
	}
	else
	{
		DataType* dataType = DataTypes::getDataType(strType);
		if(dataType != NULL){
			dataType_ = dataType;
			dataType_->incRef();
		}
		else
		{
			ERROR_MSG("FixedDictType::ArrayType: can't found type[%s] by key[%s].\n", strType.c_str(), "ARRAY");
			return false;
		}			
	}
	return true;
}

//-------------------------------------------------------------------------------------
bool ArrayType::isSameType(PyObject* pyValue)
{
	int size = PySequence_Size(pyValue);
	for(int i=0; i<size; i++)
	{
		PyObject* pyVal = PySequence_GetItem(pyValue, i);
		bool ok = dataType_->isSameType(pyVal);
		Py_DECREF(pyVal);
		if(!ok)
			return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------
PyObject* ArrayType::createObject(MemoryStream* defaultVal)
{
	std::string val = "";
	if(defaultVal)
		(*defaultVal) >> val;	
	return new Array(this, val);
}

//-------------------------------------------------------------------------------------
MemoryStream* ArrayType::parseDefaultStr(std::string defaultVal)
{
	return NULL;
}

//-------------------------------------------------------------------------------------
void ArrayType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
}

//-------------------------------------------------------------------------------------
PyObject* ArrayType::createFromStream(MemoryStream* mstream)
{
	return createObject(mstream);
}

//-------------------------------------------------------------------------------------
FixedDictType::FixedDictType()
{
}

//-------------------------------------------------------------------------------------
FixedDictType::~FixedDictType()
{
	FIXEDDICT_KEYTYPE_MAP::iterator iter = keyTypes_.begin();
	for(; iter != keyTypes_.end(); iter++)
	{
		iter->second->decRef();
	}
	keyTypes_.clear();
}

//-------------------------------------------------------------------------------------
std::string FixedDictType::getKeyNames(void)
{
	std::string keyNames = "";
	FIXEDDICT_KEYTYPE_MAP::iterator iter = keyTypes_.begin();
	for(; iter != keyTypes_.end(); iter++)
	{
		keyNames += iter->first + ",";
	}
	return keyNames;
}

//-------------------------------------------------------------------------------------
bool FixedDictType::initialize(XmlPlus* xmlplus, TiXmlNode* node)
{
	TiXmlNode* propertiesNode = xmlplus->enterNode(node, "Properties");
	std::string strType = "", typeName = "";
	
	XML_FOR_BEGIN(propertiesNode)
	{
		typeName = xmlplus->getKey(propertiesNode);
		TiXmlNode* typeNode = xmlplus->enterNode(propertiesNode->FirstChild(), "Type");
		
		if(typeNode)
		{
			strType = xmlplus->getValStr(typeNode);
			std::transform(strType.begin(), strType.end(), strType.begin(), toupper);										// 转换为大写

			if(strType == "ARRAY")
			{
				ArrayType* dataType = new ArrayType();
				if(dataType->initialize(xmlplus, typeNode)){
					keyTypes_[typeName] = dataType;
					dataType->incRef();
				}
				else
					return false;
			}
			else
			{
				DataType* dataType = DataTypes::getDataType(strType);
				if(dataType != NULL){
					keyTypes_[typeName] = dataType;
					dataType->incRef();
				}
				else
				{
					ERROR_MSG("FixedDictType::initialize: can't found type[%s] by key[%s].\n", strType.c_str(), typeName.c_str());
					return false;
				}
			}
		}		
	}
	XML_FOR_END(propertiesNode);
	return true;
}

//-------------------------------------------------------------------------------------
bool FixedDictType::isSameType(PyObject* pyValue)
{
	if(!PyDict_Check(pyValue))
	{
		OUT_TYPE_ERROR("DICT");
		return false;
	}
	
	Py_ssize_t dictSize = PyDict_Size(pyValue);
	if(dictSize != (Py_ssize_t)keyTypes_.size())
	{
		PyErr_Format(PyExc_TypeError, "FIXED_DICT key no match. size:%d-%d, keyNames=[%s].", 
			dictSize, keyTypes_.size(), getKeyNames().c_str());
		PyErr_PrintEx(0);
		return false;
	}

	FIXEDDICT_KEYTYPE_MAP::iterator iter = keyTypes_.begin();
	for(; iter != keyTypes_.end(); iter++)
	{
		PyObject* pyObject = PyDict_GetItemString(pyValue, const_cast<char*>(iter->first.c_str()));
		if(pyObject == NULL || !iter->second->isSameType(pyObject))
		{
			PyErr_Format(PyExc_TypeError, "set FIXED_DICT is error! at key: %s, keyNames=[%s].", 
				iter->first.c_str(), getKeyNames().c_str());
			PyErr_PrintEx(0);
			return false;
		}
	}
	
	return true;
}

//-------------------------------------------------------------------------------------
PyObject* FixedDictType::createObject(MemoryStream* defaultVal)
{
	std::string val = "";
	if(defaultVal)
		(*defaultVal) >> val;	
	return new FixedDict(this, val);
}

//-------------------------------------------------------------------------------------
MemoryStream* FixedDictType::parseDefaultStr(std::string defaultVal)
{
	return NULL;
}

//-------------------------------------------------------------------------------------
void FixedDictType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
}

//-------------------------------------------------------------------------------------
PyObject* FixedDictType::createFromStream(MemoryStream* mstream)
{
	return createObject(mstream);
}

//-------------------------------------------------------------------------------------
}
