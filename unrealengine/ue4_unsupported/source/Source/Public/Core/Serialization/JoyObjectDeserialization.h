// Copyright 2015-2018 Joy Machine, LLC. All rights reserved.

#pragma once

#include "SteelHuntersPCH.h"
#include "UObject/ObjectMacros.h"

#include "Serialization/JsonTypes.h"
#include "Dom/JsonValue.h"

/*
 *	UObject Deserialization class definition.
*/
class FJoyObjectDeserialization
{
private:
	FJoyObjectDeserialization( );

private:
	static bool Deserialize( uint8* ObjectData, UStruct* ObjectClass, const TSharedPtr< FJsonObject >& JSONObject, UObject* Parent, int32 PortFlags, FOutputDevice* ErrorText );

	static bool DeserializeProperty( const TSharedPtr< FJsonValue >& JSONObjectValue, UProperty* Prop, uint8* PropertyValue, UObject* Parent, int32 PortFlags, int32 ArrayIndex, FOutputDevice* ErrorText );

	static bool DeserializePropertyByte( const TSharedPtr< FJsonValue >& JSONObjectValue, UByteProperty* Prop, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText );
	static bool DeserializePropertyBool( const TSharedPtr< FJsonValue >& JSONObjectValue, UBoolProperty* Prop, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText );
	static bool DeserializePropertyAssetReference( const TSharedPtr< FJsonValue >& JSONObjectValue, UObjectPropertyBase* Prop, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText );
	static bool DeserializePropertySubObject( const TSharedPtr< FJsonValue >& JSONObjectValue, UObjectPropertyBase* Prop, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText );
	static bool DeserializePropertyStruct( const TSharedPtr< FJsonValue >& JSONObjectValue, UStructProperty* Prop, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText );
	static bool DeserializePropertyArray( const TSharedPtr< FJsonValue >& JSONObjectValue, UArrayProperty* Prop, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText );
	static bool DeserializePropertyString( const TSharedPtr< FJsonValue >& JSONObjectValue, UProperty* Prop, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText );

public:
	static bool DeserializeDataFromJsonString( uint8*& ObjectData, UStruct* ObjectClass, UObject* Parent, const FString& JSONString, int32 PortFlags );
	static bool DeserializeDataFromJson( uint8*& ObjectData, UStruct* ObjectClass, UObject* Parent, const TSharedPtr< FJsonObject >& JSONObjectValue, int32 PortFlags );
};
