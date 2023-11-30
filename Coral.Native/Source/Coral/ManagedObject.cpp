﻿#include "ManagedObject.hpp"
#include "Assembly.hpp"
#include "NativeCallables.generated.hpp"
#include "String.hpp"
#include "StringHelper.hpp"
#include "Type.hpp"

namespace Coral {

	void ManagedObject::InvokeMethodInternal(std::string_view InMethodName, const void** InParameters, const ManagedType* InParameterTypes, size_t InLength) const
	{
		auto methodName = String::New(InMethodName);
		s_NativeCallables.InvokeMethodFptr(m_Handle, methodName, InParameters, InParameterTypes, static_cast<int32_t>(InLength));
		String::Free(methodName);
	}

	void ManagedObject::InvokeMethodRetInternal(std::string_view InMethodName, const void** InParameters, const ManagedType* InParameterTypes, size_t InLength, void* InResultStorage) const
	{
		auto methodName = String::New(InMethodName);
		s_NativeCallables.InvokeMethodRetFptr(m_Handle, methodName, InParameters, InParameterTypes, static_cast<int32_t>(InLength), InResultStorage);
		String::Free(methodName);
	}

	void ManagedObject::SetFieldValueRaw(std::string_view InFieldName, void* InValue) const
	{
		auto fieldName = String::New(InFieldName);
		s_NativeCallables.SetFieldValueFptr(m_Handle, fieldName, InValue);
		String::Free(fieldName);
	}

	void ManagedObject::GetFieldValueRaw(std::string_view InFieldName, void* OutValue) const
	{
		auto fieldName = String::New(InFieldName);
		s_NativeCallables.GetFieldValueFptr(m_Handle, fieldName, OutValue);
		String::Free(fieldName);
	}

	void ManagedObject::SetPropertyValueRaw(std::string_view InPropertyName, void* InValue) const
	{
		auto propertyName = String::New(InPropertyName);
		s_NativeCallables.SetPropertyValueFptr(m_Handle, propertyName, InValue);
		String::Free(propertyName);
	}
	
	void ManagedObject::GetPropertyValueRaw(std::string_view InPropertyName, void* OutValue) const
	{
		auto propertyName = String::New(InPropertyName);
		s_NativeCallables.GetPropertyValueFptr(m_Handle, propertyName, OutValue);
		String::Free(propertyName);
	}

	const Type& ManagedObject::GetType() const
	{
		return *m_Type;
	}

	void ManagedObject::Destroy()
	{
		if (!m_Handle)
			return;

		s_NativeCallables.DestroyObjectFptr(m_Handle);
		m_Handle = nullptr;
		m_Type = nullptr;
	}

}

