// Copyright 2015-2018 Joy Machine, LLC. All rights reserved.

#pragma once

#include "SteelHuntersPCH.h"
#include "UObject/ObjectMacros.h"

#include "Serialization/JsonTypes.h"
#include "Dom/JsonValue.h"

/*
*	UObject Serialization class definition.
*/
class FJoyObjectSerialization
{
private:
	FJoyObjectSerialization( );

private:
	static void Serialize( TSharedPtr< FJsonValue >& JSONObjectValue, UStruct* ObjectClass, const uint8* ObjectData, UObject* Parent, int32 PortFlags, bool SerializeClassName );
	
	static void SerializeProperty( TSharedPtr< FJsonValue >& JSONObjectValue, UProperty* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, int32 ArrayIndex, UObject* SerializeRootScope = NULL );

	static void SerializePropertyBool( TSharedPtr< FJsonValue >& JSONObjectValue, UBoolProperty* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope = NULL );
	static void SerializePropertyByte( TSharedPtr< FJsonValue >& JSONObjectValue, UByteProperty* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope = NULL );	
	static void SerializePropertyAssetReference( TSharedPtr< FJsonValue >& JSONObjectValue, UObjectPropertyBase* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope = NULL );
	static void SerializePropertySubObject( TSharedPtr< FJsonValue >& JSONObjectValue, UObjectPropertyBase* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope = NULL );
	static void SerializePropertyStruct( TSharedPtr< FJsonValue >& JSONObjectValue, UStructProperty* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope = NULL );
	static void SerializePropertyArray( TSharedPtr< FJsonValue >& JSONObjectValue, UArrayProperty* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope = NULL );
	static void SerializePropertyString( TSharedPtr< FJsonValue >& JSONObjectValue, UProperty* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope = NULL );

public:
	static bool SerializeDataToJsonString( const uint8* ObjectData, UStruct* ObjectClass, UObject* Parent, FString& JSONString, bool SerializeClassName, int32 PortFlags);	
	static bool SerializeDataToJson( const uint8* ObjectData, UStruct* ObjectClass, UObject* Parent, TSharedPtr< FJsonValue >& JSONObjectValue, bool SerializeClassName, int32 PortFlags );
};
